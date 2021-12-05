#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>
#include "Object.h"
#include "Camera.h"

class Scene {
  public:
    Scene(){}

    void addLight(Light lt){
      lights.push_back(lt);
    }
    
    void readFromFile(const std::string& file);
    
    const std::vector<Object*>& getObj() const{
      return objects;
    }

    const std::vector<Light>& getLights() const{
      return lights;
    }
    
    const Camera& getCam() const{
      return c;
    }
    
    Camera& getCam(){
      return c;
    }
    
    glm::mat4 mv(glm::mat4 view, glm::mat4 transformation){
      return view*transformation;
    }
    

  private:
    std::vector<Object*> objects;
    std::vector<Light> lights;
    Camera c;
    
};

#endif
