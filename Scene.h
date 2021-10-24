#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>
#include "Object.h"

class Scene {
  public:
    void addObject(Object *_obj);
    //making objects vector public for now
  //private:
    std::vector<Object*> objects;
};

#endif
