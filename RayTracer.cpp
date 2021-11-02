#include "RayTracer.h"
#include "Camera.h"
#include "Collision.h"

void RayTracer::clear() const {//what does this func do? //iterate framebuffer to set to background
  //prob do some for loop in this function by using the m_frame
}

glm::vec3 getDirection(float tau, float sigma, const Camera& c){
  glm::vec3 dir;
  dir= c.focal*c.w + tau*c.u + sigma*c.v;
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

  Camera dummy;
  int length=1360;
  int height= 768;
  float t = 1*tan(45/2);
  float b = -t;
  float r = (length/height)*t;
  float l = -r;
  m_frame = std::make_unique<glm::vec4[]>(length*height);

  glm::vec3 origin(0.f,0.f,0.f);
  for(int i = 0; i<length; i++){//length is # of col
    for(int j = 0; j<height; j++){//height is # of rows
      //using ray struct that takes in some origin and direction
      glm::vec3 direction;
      
      direction = getDirection(tauVal(i, r, l, length), sigmaVal(i, t, b, height), dummy);

      direction = getDirection(tauVal(i, 1360, 1360, 1360), sigmaVal(i, 768, 768, 768), dummy);

      direction = getDirection(tauVal(i, r, l, length), sigmaVal(j, t, b, height), dummy);
      //create camera class to represent origin??
      Ray r(origin,direction);
      for(int i = 0; i<_scene.objects.size(); i++){
        
        Collision h_ = _scene.objects[i]->collide(r);//tests to see if a ray has collided with scene object
        //Collision.Type miss = Collision.Type::kMiss;
        //figure out if it hits something and then get the color of the x value
        //get the x value and the color and then send it into the g_frame
        if(h_.hm == true){
         // float r = i/length;
          //float c = i%length
          m_frame[height*(i-1)+j]
        }
        //theres an issue with the > operator
       
      }
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

