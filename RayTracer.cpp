#include "RayTracer.h"
#include "Camera.h"
#include "Collision.h"
#include "Plane.h"


#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

void RayTracer::clear() const {//what does this func do? //iterate framebuffer to set to background
  //prob do some for loop in this function by using the m_frame
  for(int i = 0; i< m_width * m_height; i++){
    m_frame[i]=glm::vec4(1.f,1.f,1.f,1.f);
  }
}

glm::vec3 getDirection(float tau, float sigma, const Camera& c){
  glm::vec3 dir;
  dir= c.focal*c.w + tau*c.u + sigma*c.v;

  return glm::normalize(dir);

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
  float t = 1.f*tan(glm::radians(45.f/2));
  float b = -t;
  float r = ((float)length/height)*t;
  float l = -r;

  glm::vec3 origin(0.f,0.f,0.f);
  for(int i = 0; i<length; i++){//length is # of col
    for(int j = 0; j<height; j++){//height is # of rows
      //using ray struct that takes in some origin and direction
      glm::vec3 direction;//initializes direction
      direction = getDirection(tauVal(i, r, l, length), sigmaVal(j, t, b, height), dummy);//calculates direction
      //create camera class to represent origin??
      Ray r(origin,direction);
      //std::cout<<_scene.objects.size()<<" scene size"<<std::endl;
      for(int k = 0; k<_scene.objects.size(); k++){//iterates through objects in scene to look for collisions with the ray
        
        Collision h_ = _scene.objects[k]->collide(r);//tests to see if a ray has collided with scene object
        //Collision.Type miss = Collision.Type::kMiss;
        //figure out if it hits something and then get the color of the x value
        //get the x value and the color and then send it into the g_frame


        if(h_.m_type==Collision::Type::kHit){
          //std::cout<<" ray has hit the plane"<<std::endl;
          m_frame[length*j+i]= glm::vec4(.5f, .5f, .5f, 1.f);// this should draw pixels to the framebuffer and give them a generic color
          //compute shadow color at that point
        }
      }
      //glm::vec4 color((direction+glm::vec3(1,1,1))/2,1);
      //m_frame[length*j+i]= color;
    }
  }
  //commenting out now but might be useful later
  //std::cout<<m_width<<"  = mwidth "<< m_height<< " mheight "<<std::endl;
  glDrawPixels(m_width, m_height, GL_RGBA, GL_FLOAT, m_frame.get());
}




