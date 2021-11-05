#include "Scene.h"
#include "Object.h"

void Scene::addObject(Object *_obj){
    objects.push_back(_obj);
}

