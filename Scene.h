#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>
#include "Object.h"

class Scene {
  public:
    Scene(){}
    void addObject(Object *_obj);
    //making objects vector public for now
  //private:
    std::vector<Object*> objects;
    
    /**
    #include <iostream>//stringstream
     
    void readFromFile(const std::string& file);
    std::vector<Light*> lights; // needs light class
    */
    
};

#endif
