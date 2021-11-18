#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>
#include "Object.h"

class Scene {
  public:
    Scene(){}
    void addObject(Object *_obj);
    void addLight(Light * lt);
    //making objects vector public for now

    std::vector<Object*> getObj(){
      return objects;
    }

    std::vector<Light> getLights(){
      return lights;
    }
    
  private:
    std::vector<Object*> objects;
    std::vector<Light> lights;//adding a light vector
    
    /**
    #include <iostream>//stringstream
     
    void readFromFile(const std::string& file);
    std::vector<Light*> lights; // needs light class
    */
    
};

#endif
