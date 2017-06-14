#pragma once

#include "Bitmap.h"
#include "Scene.h"
#include "PathTrace.h"
#include "Random.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <time.h>
#include <sys/time.h>

#define TILE_SIZE 8
#define THREAD_NUM 6

typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::mat4 mat4;

class Camera {
private:
  //BASIC FIELDS//
  float vfov;
  float aspect;
  mat4 cam;
  Bitmap * window;
  PathTrace * tracer;
  std::mutex tileLock;
  int tileNum;
  ///////////////

  //ANTIALIASING//
  Random* randGen;
  bool enableJitter;
  bool enableShirley;
  int xSamples;
  int ySamples;
  ///////////////

  //DEPTH OF FIELD EFFECT//
  bool enableDOF;
  float aperture;
  float focusDis;
  /////////////////////////

  vec2 shirleyWeight(float x, float y);
  vec2 cosWeight();
  vec3 generateRayOrg();
  vec3 generateRayDir(int x, int y, float u, float v, vec3 pos);
  void renderTile(int tileID);
  Ray* generateRays(int x, int y);
  void renderPixel(int x, int y);

public:
  Camera();
  ~Camera();

  void lookAt(const vec3& pos, const vec3& target, const vec3& up);

  void setResolution(int xRes, int yRes);
  void setFOV(float fov);
  void setAspect(float aspect);
  void setDOF(float aperture, float focusDis);


  void setJitter(bool enable);
  void setShirley(bool enable);
  void setSuperSample(int xSamples, int ySamples);

  void render(Scene& scene);
  void saveBitmap(const char* filename);
};

double getTime();
