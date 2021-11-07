#include "Scene.h"
#include "Object.h"

void Scene::addObject(Object *_obj){
    objects.push_back(_obj);
}

/**
#include <string>
#include "Sphere.h"
#include "Plane.h"
 
 // converts strings to float values
 void stringToFloat(const std::string& str) {
    float f = std::stof(str);
    return f;
 }
 
 // parse through, make each word (split by space) into a string
 std::vector<std::string> parse(std::string str){
    std::vector<std::string> split;
    int found;
    while(str.find(" ")!=-1){
      found=str.find(" ");
      split.push_back(str.substr(0,found));
      str=str.substr(found+1);
    }
    split.push_back(str);
    return split;
  }
 
 // take in example.scene file
 void Scene::readFromFile(const std::string& file) {
    std::string line;
    std::ifstream File;
    File.open(file);
    if (File.is_open()){
        while(getline(File,line)){
            if(line=="Sphere"){
                glm::vec3 sCenter;
                float sRadius;
                while(getline(File,line)){
                    if (line == "~Sphere") { break; }
                    std::vector<std::string> parsed;
                    parsed = parse(line);
                    if(parsed[0] == "center") {
                        sCenter = glm::vec3(stingToFloat(parsed[1]),stringToFloat(parsed[2]),stringToFloat(parsed[3]));
                    }
                    if(parsed[0] == "radius") {
                        sRadius = stringToFloat(parsed[1]);
                    }
                }
            objects.push_back(new Sphere(sCenter, sRadius));
            } else if (line=="Plane") {
                glm::vec3 pPosition;
                glm::vec3 pNormal;
                while(getline(File,line)){
                    if (line=="~Plane"){ break; }
                    std::vector<std::string> parsed;
                    parsed = parse(line);
                    if(parsed[0]=="p") {
                        pPosition = glm::vec3(stingToFloat(parsed[1]),stringToFloat(parsed[2]),stringToFloat(parsed[3]));
                    }
                    if(parsed[0]=="n") {
                        pNormal = glm::vec3(stingToFloat(parsed[1]),stringToFloat(parsed[2]),stringToFloat(parsed[3]));
                    }
                }
            objects.push_back(new Plane(pNormal, pPostition);
            }
    }
 }
 
 */
