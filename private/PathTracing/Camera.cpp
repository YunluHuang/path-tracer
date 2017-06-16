#include "Camera.h"
#include "Statistic.h"

#include <time.h>
#include <math.h>

Camera::Camera() {
  randGen = new Random();
  xSamples = 1;
  ySamples = 1;
  enableJitter = false;
  enableShirley = false;
  enableDOF = false;
}

/**
  Set up the camera coordinates based on camera pos, target, and up
*/
void Camera::lookAt(const vec3& pos, const vec3& target, const vec3& up) {
  vec3 d = pos;
  vec3 c = normalize(d - target);
  vec3 a = normalize(cross(up, c));
  vec3 b = cross(c, a);

  //initialize the cam
  cam = mat4(vec4(a, 0), vec4(b, 0), vec4(c, 0), vec4(d, 1));
}

/**
  Set the resolution for the window
*/
void Camera::setResolution(int xRes, int yRes) {
  window = new Bitmap(xRes, yRes);
  tileLock.lock();
  tileNum = (xRes / TILE_SIZE) * (yRes / TILE_SIZE);
  tileLock.unlock();
}

/**
  Set the vertical field of view
*/
void Camera::setFOV(float fov) {
  float pi = 3.1415926f;
  vfov = fov * pi / 180.0f;
}

/**
  Set the aspect of the window
*/
void Camera::setAspect(float aspect) {
  this->aspect = aspect;
}

void Camera::setDOF(float aperture, float focusDis) {
  enableDOF = true;
  this->aperture = aperture;
  this->focusDis = focusDis;
}

/**
  Enable/disable jittering for each supersample
*/
void Camera::setJitter(bool enable){
  enableJitter = enable;
}

/**
  Enable/disable shirley for each supersample
*/
void Camera::setShirley(bool enable){
  enableShirley = enable;
}

/**
  Supersample each pixel in a x*y grid
*/
void Camera::setSuperSample(int xSamples, int ySamples) {
  this->xSamples = xSamples;
  this->ySamples = ySamples;
}

/**
  Render the image
*/
void Camera::render(Scene& scene) {
  tracer = new PathTrace(scene);
  tileLock.lock();
  const int totalTiles = tileNum;
  tileLock.unlock();

  double timer = getTime();
  // std::cout<<"rendering:"<<std::endl;

  std::thread * threads[THREAD_NUM];
  for(int i = 0; i < THREAD_NUM; i++) {
    std::cout << i << std::endl;
    threads[i] = new std::thread([=](){
      while(1) {
        tileLock.lock();
        int tileID = --tileNum;
        if((totalTiles - tileID) % 32 == 0) {
          printProgress((float)(totalTiles - tileID) / (float)totalTiles);
        }
        tileLock.unlock();
        if(tileID < 0) {
          return;
        }
        renderTile(tileID);
      }
    });
  }

  for(int i = 0; i < THREAD_NUM; i++) {
    threads[i]->join();
  }

  // int x, y;
  // float progress = 0.0f;
  // int count = 0;
  // for(x = 0; x < window->getXRes(); x++) {
  //   for(y = 0; y < window->getYRes(); y++) {
  //     renderPixel(x, y);
  //     progress = (float)(y + x * window->getYRes()) / (window->getXRes() * window->getYRes());
  //   }
  //   if(count > window->getXRes() / 70) {
  //     count = 0;
  //     printProgress(progress);
  //   }
  //   count++;
  // }

  printProgress(1.0f);
  std::cout << std::endl;
  timer = getTime() - timer;
  printf("Render took %f seconds. \n", timer);
}

/**
  Save the window to bitmap
*/
void Camera::saveBitmap(const char* filename) {
  window->saveBMP(filename);
}

////////////////////////////////////////////////////////////////////////////////
vec2 Camera::shirleyWeight(float x, float y) {
  if(x < 0.5) {
    x = -0.5f + sqrt(2 * x);
  } else {
    x = 1.5f - sqrt(2 - 2 * x);
  }
  if(y < 0.5) {
    y = -0.5f + sqrt(2 * y);
  } else {
    y = 1.5f - sqrt(2 - 2 * y);
  }
  return vec2(x, y);
}

vec2 Camera::cosWeight() {
  float s = randGen->next();
  float t = randGen->next();
  float u = 2 * PI * s;
  float v = sqrt(1 - t) * aperture / 2;
  return vec2(v * cos(u), v * sin(u));
}

vec3 Camera::generateRayOrg() {
  vec3 a = vec3(cam[0]);
  vec3 b = vec3(cam[1]);
  vec3 c = vec3(cam[2]);
  vec3 d = vec3(cam[3]);

  if(enableDOF) {
    vec2 cameraShift = cosWeight();
    d = d + cameraShift.x * a + cameraShift.y * b;
  }

  return d;
}

vec3 Camera::generateRayDir(int x, int y, float u, float v, vec3 pos) {
  float hfov = 2.0f * atan(aspect * tan(vfov / 2.0f));

  float fx = (x + u) / window->getXRes() - 0.5f;
  float fy = (y + v) / window->getYRes() - 0.5f;

  vec3 a = vec3(cam[0]);
  vec3 b = vec3(cam[1]);
  vec3 c = vec3(cam[2]);
  vec3 d = vec3(cam[3]);

  if(enableDOF) {
    a = a * focusDis;
    b = b * focusDis;
    c = c * focusDis;
  }

  float scaleX = 2*tan(hfov / 2.0f);
  float scaleY = 2*tan(vfov / 2.0f);

  vec3 dir = normalize(fx * scaleX * a + fy * scaleY * b - c - (pos - d));

  return dir;
}

void Camera::renderTile(int tileID) {
  int w = window->getXRes() / TILE_SIZE;
  int h = window->getYRes() / TILE_SIZE;
  int tw = tileID % w;
  int th = tileID / w;
  for(int x = tw * TILE_SIZE; x < (tw + 1) * TILE_SIZE; x++) {
    for(int y = th * TILE_SIZE; y < (th + 1) * TILE_SIZE; y++) {
      renderPixel(x, y);
    }
  }
}

Ray * Camera::generateRays(int x, int y) {
  Ray *rays = new Ray[xSamples * ySamples];

  for(int i = 0; i < xSamples; i++) {
    for(int j = 0; j < ySamples; j++) {
      //generate random (u, v) point inside the pixel
      float u = randGen->next();
      float v = randGen->next();

      // apply uniform grid to the random numbers
      if(enableJitter) {
        u = (i + u) / xSamples;
        v = (j + v) / ySamples;
      }

      // apply Shirley mapping
      if(enableShirley) {
        vec2 newCoords = shirleyWeight(u, v);
        u = newCoords.x;
        v = newCoords.y;
      }

      Ray ray;
      ray.t = randGen->next();
      ray.org = generateRayOrg();
      ray.dir = generateRayDir(x, y, u, v, ray.org);
      rays[i + xSamples * j] = ray;
    }
  }
  return rays;
}

void Camera::renderPixel(int x, int y) {
  //std::cout << "render: " << x << ", " << y << std::endl;
  Ray* rays = generateRays(x, y);
  Color finalColor = Color(0, 0, 0);

  for(int i = 0; i < xSamples * ySamples; i++) {
    Ray ray = rays[i];
    Intersection hit;

    tracer->traceRay(ray, hit, 0);
    finalColor += hit.shade;
  }

  finalColor *= (1.0f / (xSamples * ySamples));
  window->setPixel(x, y, finalColor.toInt());
}

////////////////////////////////////////////////////////////////////////////////
/**
  Destructor
*/
Camera::~Camera() {
  if(window != 0) {
    delete window;
    window = 0;
  }
  if(tracer != 0) {
    delete tracer;
    tracer = 0;
  }
  if(randGen != 0) {
    delete randGen;
    randGen = 0;
  }
}
////////////////////////////////////////////////////////////////////////////////
double getTime(){
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}
