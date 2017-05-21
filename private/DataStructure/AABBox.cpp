#include "AABBox.h"

using namespace std;

AABBox::AABBox() {
  left = nullptr;
  right = nullptr;
}

AABBox::AABBox(Triangle *triangles, int numTriangles) {
  for(int i = 0; i < numTriangles; i++) {
    addTri(&triangles[i]);
  }
}

int AABBox::getNumTris() {
  return tris.size();
}

vec3 AABBox::getVmin() {
  return vmin;
}

vec3 AABBox::getVmax() {
  return vmax;
}

bool AABBox::intersect(const Ray &ray, Intersection &hit) {
  bool successLeft = false;
  bool successRight = false;
  if(boxIntersect(ray, hit) == false) {
    return false;
  }
  if(left != nullptr) {
    successLeft = left->intersect(ray, hit);
  }
  if(right != nullptr) {
    successRight = right->intersect(ray, hit);
  }
  if(left == nullptr && right == nullptr) {
    bool success = false;
    for(int i = 0; i < tris.size(); i++) {
      if(tris[i]->intersect(ray, hit)) success=true;
    }
    return success;
  }
  return successLeft || successRight;
}

bool AABBox::boxIntersect(const Ray &ray, Intersection &hit) {

  float hitDis;

  vec3 org = ray.org;
  vec3 dir = ray.dir;
  vec3 t1, t2;

  t1.x = (vmin.x - org.x) / dir.x;
  t2.x = (vmax.x - org.x) / dir.x;
  t1.y = (vmin.y - org.y) / dir.y;
  t2.y = (vmax.y - org.y) / dir.y;
  t1.z = (vmin.z - org.z) / dir.z;
  t2.z = (vmax.z - org.z) / dir.z;

  float tmin = max(max(min(t1.x, t2.x), min(t1.y, t2.y)), min(t1.z, t2.z));
  float tmax = min(min(max(t1.x, t2.x), max(t1.y, t2.y)), max(t1.z, t2.z));

  if(tmin <= tmax && tmax > 0) {
    if(tmin < 0) {
      hitDis = tmax;
      return true;
    } else {
      hitDis = tmin;
      if(hitDis < hit.hitDis) return true;
    }
  }
  return false;
}

void AABBox::addTri(Triangle* tri) {

  if(tris.size() == 0) {
    vmin = tri->getVertice(0)->pos;
    vmax = tri->getVertice(0)->pos;
  }

  tris.push_back(tri);

  vec3 vertices[3];
  vertices[0] = tri->getVertice(0)->pos;
  vertices[1] = tri->getVertice(1)->pos;
  vertices[2] = tri->getVertice(2)->pos;

  for(int i=0; i<3; i++) {
    float x,y,z;
    x = vertices[i].x;
    y = vertices[i].y;
    z = vertices[i].z;

    if(x < vmin.x) vmin.x = x;
    else if (x > vmax.x) vmax.x = x;

    if(y < vmin.y) vmin.y = y;
    else if (y > vmax.y) vmax.y = y;

    if(z < vmin.z) vmin.z = z;
    else if (z > vmax.z) vmax.z = z;
  }
}

bool AABBox::split(int axis) {
  if(tris.size() < 10) {
    return false;
  }

  std::vector<Triangle *> leftTris;
  std::vector<Triangle *> rightTris;

  if(axis == 0) {
    float line = (vmax.x + vmin.x) / 2.0f;
    for(int i = 0; i < tris.size(); i++) {
      if(tris[i]->computeCenter().x < line) {
        leftTris.push_back(tris[i]);
      } else {
        rightTris.push_back(tris[i]);
      }
    }
  } else if(axis == 1) {
    float line = (vmax.y + vmin.y) / 2.0f;
    for(int i = 0; i < tris.size(); i++) {
      if(tris[i]->computeCenter().y < line) {
        leftTris.push_back(tris[i]);
      } else {
        rightTris.push_back(tris[i]);
      }
    }
  } else if(axis == 2) {
    float line = (vmax.z + vmin.z) / 2.0f;
    for(int i = 0; i < tris.size(); i++) {
      if(tris[i]->computeCenter().z < line) {
        leftTris.push_back(tris[i]);
      } else {
        rightTris.push_back(tris[i]);
      }
    }
  }

  //resplit if inbalanced
  if(leftTris.size() == 0) {
    leftTris.push_back(rightTris.back());
    rightTris.pop_back();
  } else if (rightTris.size() == 0) {
    rightTris.push_back(leftTris.back());
    leftTris.pop_back();
  }

  left = new AABBox();
  right = new AABBox();

  for(int i=0; i<leftTris.size(); i++) {
    left->addTri(leftTris[i]);
  }

  for(int i=0; i<rightTris.size(); i++) {
    right->addTri(rightTris[i]);
  }

  left->split((axis + 1) % 3);
  right->split((axis + 1) % 3);

  vector<Triangle*>().swap(tris);

  return true;
}

AABBox::~AABBox() {
  if(left != nullptr) delete left;
  if(right != nullptr) delete right;
  left = nullptr;
  right = nullptr;
}
