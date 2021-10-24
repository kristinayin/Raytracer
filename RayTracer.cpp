#include "RayTracer.h"

void RayTracer::clear() const {//what does this func do? //iterate framebuffer to set to background
}


glm::vec3 getDirection( float tau, float sigma, float focal){
  glm::vec3 w(0.f, 0.f, -1.f);
  glm::vec3 u(1.f, 0.f, 0.f);
  glm::vec3 v(0.f, 1.f, 0.f);
  glm::vec3 dir;
  dir= focal*w + tau*u + sigma*v;
  return dir;
}


//ASK JORY ABOUT LRBT!!!
float tauVal(float col, float right, float left, float pixelX){//finding the value of tau (x-axis)
  float tau = left + ((right - left)/pixelX)*(col + 0.5);
  return tau;
}

float sigmaVal(float row, float top, float bott, float pixelY){//finding the value of sigma (y-axis)
  float sigma = bott + ((top - bott)/pixelY)*(row + 0.5);
  return sigma;
}

void RayTracer::render(const Scene& _scene) const {

  int length=1360;
  int height= 768;
  glm::vec3 origin(0.f,0.f,0.f);
  for(int i = 0; i<length; i++){//length is # of col
    for(int j = 0; j<height; j++){//height is # of rows
      //using ray struct that takes in some origin and direction
      glm::vec3 direction;
      direction = getDirection(tauVal(i, 1360, 1360, 1360), sigmaVal(i, 768, 768, 768), 1.f);
      //create camera class to represent origin??
      Ray r(origin,direction);
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

