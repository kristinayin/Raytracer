#ifndef _SCENE_H_
#define _SCENE_H_

#include "object.h"

class Scene {
  public:
    void addObject(Object *o);
  private:
    std::vector<Object*> objects;
};

#endif
