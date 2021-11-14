#include "RayTracer.h"
#include "Camera.h"
#include "Collision.h"
#include "Plane.h"
#include "Lighting.h"
#include "Material.h"


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

glm::vec3 getDirection(float col, float right, float left, float pixelX, 
                       float row, float top, float bott, float pixelY, const Camera& c){
  
  float tau = left + ((right - left)/pixelX)*(col + 0.5);
  float sigma = bott + ((top - bott)/pixelY)*(row + 0.5);
  glm::vec3 dir = c.focal*c.w + tau*c.u + sigma*c.v;
  return glm::normalize(dir);

}

Collision isCollision(const Ray& r, const Scene& s){
  for(int k = 0; k<s.objects.size(); k++){//iterates through objects in scene to look for collisions with the ray
        Collision h_ = s.objects[k]->collide(r);//tests to see if a ray has collided with scene object

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
      
      glm::vec3 direction = getDirection(i, r, l, length, j, t, b, height, dummy);//calculates direction from camera to fragment

      Ray r(dummy._eye,direction);//using ray struct that takes in some origin and direction
      //std::cout<<_scene.objects.size()<<" scene size"<<std::endl;
      Collision pointOfColl = isCollision(r, _scene);
      

      if(pointOfColl.m_type == Collision::Type::kHit){
        glm::vec4 color = pointOfColl.m_material->ka*glm::vec4(0.1,0.1,0.1,1);

        for(int k = 0; k<_scene.Lights.size(); k++){
          color+=pointOfColl.m_material->ka*_scene.Lights[k].getIa();
          glm::vec3 lightDir = _scene.Lights[k].getPoint() - pointOfColl.m_x;//ray direction from point of collision to light source
          Ray toLight(pointOfColl.m_x, lightDir);

          Collision shadow = isCollision(toLight, _scene);//sees if shadow occurs at this point based on other objects
          if(shadow.m_type == Collision::Type::kMiss){
            color+= pointOfColl.m_material->lambertian(_scene.Lights[k], pointOfColl.m_normal,pointOfColl.m_x)
            + pointOfColl.m_material->blinnPhong(_scene.Lights[k],dummy._eye,pointOfColl.m_x);

          }
          
        }
        m_frame[length*j+i]= color;
       
      }
      
      
      //std::cout<<" ray has hit the plane"<<std::endl;
    
      // this should draw pixels to the framebuffer and give them a generic color
      //glm::vec4 color((direction+glm::vec3(1,1,1))/2,1);
      //m_frame[length*j+i]= color;
    }
    
  }
  //commenting out now but might be useful later
  //std::cout<<m_width<<"  = mwidth "<< m_height<< " mheight "<<std::endl;
  glDrawPixels(m_width, m_height, GL_RGBA, GL_FLOAT, m_frame.get());
}




