#include "RayTracer.h"

void RayTracer::clear() const {//what does this func do? //iterate framebuffer to set to background
}

void RayTracer::render(const Scene& _scene) const {

  for(int i = 0; i<length; i++){//length is # of col
    for(int j = 0; j<height; j++){//height is # of rows
      //using ray struct that takes in some origin and direction
      //using collision function for the sphere
      //use material struct???
    }
  }
  // for each column i do
  //   for each row j do
  //     generate a ray origin and direction
  //     
  //     find the first intersection point of the ray
  //
  //     shade the ray intersection
  //
  // Copy framebuffer to screne
}