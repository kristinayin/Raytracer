#ifndef _SCENE_H_
#define _SCENE_H_

#include "object.h"

class Scene {
  public:
    void addObject(Object *_obj);
  private:
    std::vector<Object*> objects;
};

#endif
