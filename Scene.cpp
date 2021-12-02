#include "Scene.h"
#include "Object.h"
#include <string>
#include "Sphere.h"
#include "Plane.h"
#include <fstream>

void Scene::addObject(Object *_obj){
    objects.push_back(_obj);
}


void Scene::addLight(Light lt){
    lights.push_back(lt);
}

 /*
 // converts strings to float values
 float stringToFloat(const std::string& str) {
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
// to do: take in lights
void Scene::readFromFile(const std::string& file) {
    std::string line;
    std::ifstream File;
    File.open(file);
    if (File.is_open()){
        while(getline(File,line)){
            if(line=="Sphere"){
                glm::vec3 sCenter;
                float sRadius;
                // read in material
                glm::vec4 sKd, sKs, sKa;
                float sP;
                //Material sMaterial;
                while(getline(File, line)) {
                    if (line == "~Sphere") { break; }
                    std::vector<std::string> parsed;
                    parsed = parse(line);
                    if(parsed[0] == "center") {
                        sCenter = glm::vec3(stringToFloat(parsed[1]), stringToFloat(parsed[2]), stringToFloat(parsed[3]));
                    }
                    if(parsed[0] == "radius") {
                        sRadius = stringToFloat(parsed[1]);
                    }
                    if (parsed[0] == "material") {
                        /*
                        sMaterial.readMtl(parsed[1]);
                        sKa = sMaterial.ka;
                        sKd = sMaterial.kd;
                        sKs = sMaterial.ks;
                        sP = sMaterial.p;
                        sMaterial = Material(sKd, sKs, sKa, sP);
                        
                    }
                    
                }
            objects.push_back(new Sphere(sCenter, sRadius, sMaterial));
            } else if (line=="Plane") {
                glm::vec3 pPosition, pNormal;
                glm::vec4 pKd, pKs, pKa;
                float pP;
                //Material pMaterial;
                // read in material
                while(getline(File, line)) {
                    if (line=="~Plane"){ break; }
                    std::vector<std::string> parsed;
                    parsed = parse(line);
                    if(parsed[0]=="p") {
                        pPosition = glm::vec3(stringToFloat(parsed[1]), stringToFloat(parsed[2]), stringToFloat(parsed[3]));
                    }
                    if(parsed[0]=="n") {
                        pNormal = glm::vec3(stringToFloat(parsed[1]), stringToFloat(parsed[2]), stringToFloat(parsed[3]));
                    }
                    if (parsed[0] == "material") {
                        /*
                        pMaterial.readMtl(parsed[1]);
                        pKa = pMaterial.ka;
                        pKd = pMaterial.kd;
                        pKs = pMaterial.ks;
                        pP = pMaterial.p;
                        pMaterial = Material(pKd, pKs, pKa, pP);
                        
                    }
                }
            objects.push_back(new Plane(pNormal, pPosition, pMaterial));
            } else if (line=="Camera") {
                glm::vec3 cEye, cAt, cUp;
                while (getline(File, line)) {
                    if (line == "~Camera") { break; }
                    std::vector<std::string> parsed;
                    parsed = parse(line);
                    if (parsed[0]=="eye") {
                        cEye = glm::vec3(stringToFloat(parsed[1]), stringToFloat(parsed[2]), stringToFloat(parsed[3]));
                    }
                    if (parsed[0]=="at") {
                        cAt = glm::vec3(stringToFloat(parsed[1]), stringToFloat(parsed[2]), stringToFloat(parsed[3]));
                    }
                    if (parsed[0]=="up") {
                        cUp = glm::vec3(stringToFloat(parsed[1]), stringToFloat(parsed[2]), stringToFloat(parsed[3])); 
                    }
                }
                c = Camera(cEye, cAt, cUp, 1, 10);
            }
        }
    }

    File.close();
    
}
 
*/
