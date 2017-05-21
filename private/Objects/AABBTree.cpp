#include "AABBTree.h"

#include <stdio.h>
#include <time.h>

AABBTree::AABBTree() {
  root = NULL;
}

void AABBTree::construct(MeshObject& mesh) {
  clock_t timer;
  timer = clock();

  root = new AABBox(mesh.getTriangles(), mesh.getNumTriangles());
  root->split(0);

  timer = clock() - timer;
  printf("Construct took %f seconds. \n", ((float)timer)/CLOCKS_PER_SEC);
}

bool AABBTree::intersect(const Ray& ray, Intersection& hit) {
  bool success = root->intersect(ray, hit);
  return success;
}

AABBTree::~AABBTree(){
  if(root != NULL) delete root;
  root = NULL;
}
