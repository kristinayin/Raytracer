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
  glm::vec3 dir = c.focal*c.w + tau*c.u + sigma*c.v;
  return glm::normalize(dir);

}

//ASK JORY ABOUT LRBT!!!
float tauVal(float col, float right, float left, float pixelX){//finding the value of tau (x-axis)
  return left + ((right - left)/pixelX)*(col + 0.5);;
}

float sigmaVal(float row, float top, float bott, float pixelY){//finding the value of sigma (y-axis)
  return bott + ((top - bott)/pixelY)*(row + 0.5);
}

Collision isCollision(Ray r, Scene s){
  for(int k = 0; k<_s.objects.size(); k++){//iterates through objects in scene to look for collisions with the ray
        Collision h_ = _s.objects[k]->collide(r);//tests to see if a ray has collided with scene object
        //figure out if it hits something and then get the color of the x value
        //get the x value and the color and then send it into the g_frame
        if(h_.m_type==Collision::Type::kHit){
          return h_;
          
        }
  }

  return Collision(); 
}


void RayTracer::render(const Scene& _scene) const {
  Camera dummy;

  int length=1360;
  int height= 768;
  float t = 1.f*tan(glm::radians(45.f/2));
  float b = -t;
  float r = ((float)length/height)*t;
  float l = -r;

  for(int i = 0; i<length; i++){//length is # of col
    for(int j = 0; j<height; j++){//height is # of rows
      //using ray struct that takes in some origin and direction
      glm::vec3 direction;//initializes direction
      direction = getDirection(tauVal(i, r, l, length), sigmaVal(j, t, b, height), dummy);//calculates direction
      //create camera class to represent origin??
      Ray r(dummy._eye,direction);
      //std::cout<<_scene.objects.size()<<" scene size"<<std::endl;
      Collision point = Collision(r, _scene);

      glm::vec3 lightDir = l.point - h_.m_x; //ray direction from point of collision to light source
      Ray toLight(h_.m_x, lightDir);

      Collision shadow = Collision(toLight, _scene);//sees if shadow occurs at this point based on other objects
      if(shadow.m_type == Collision::Type::kHit){
        m_frame[length*j+i]= glm::vec4(.5f, .5f, .5f, 1.f);
      }else{
        m_frame[length*j+i]= glm::vec4(0.f, 0.f, 0.f, 1.f);
      }
      //compute shadow color at that point
          //std::cout<<" ray has hit the plane"<<std::endl;
          
          //Scatch code for shadow computation:
          //Light l (but we'll need to add vector<Light> in the future)

          /*
          
          
          Collision shadow = _scene.objects[k]->collide(toLight);
          */
      // this should draw pixels to the framebuffer and give them a generic color
      //glm::vec4 color((direction+glm::vec3(1,1,1))/2,1);
      //m_frame[length*j+i]= color;
    }
  }
  //commenting out now but might be useful later
  //std::cout<<m_width<<"  = mwidth "<< m_height<< " mheight "<<std::endl;
  glDrawPixels(m_width, m_height, GL_RGBA, GL_FLOAT, m_frame.get());
}




