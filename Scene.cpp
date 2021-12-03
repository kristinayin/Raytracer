#include "Scene.h"
#include "Object.h"
#include <string>
#include "Sphere.h"
#include "Plane.h"
#include <fstream>
/*
void Scene::addObject(Object *_obj){
    objects.push_back(_obj);
}
*/

void Scene::addLight(Light lt){
    lights.push_back(lt);
}

 
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

                glm::vec4 a_color(.6f,.2f,.4f,1);
                glm::vec4 d_color(.1f,.4f,.8f,1);
                glm::vec4 s_color(1.f,.8f,0.f,1);

                Material sMaterial = Material(a_color, d_color, s_color, 10.f);
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
                    /*
                    if (parsed[0] == "material") {
                        sMaterial.readMtl(parsed[1]);
                    }
                    */
                    
                }
            objects.push_back(new Sphere(sCenter, sRadius, sMaterial));
            
            } else if (line=="Plane") {
                glm::vec3 pPosition, pNormal;
                glm::vec4 pKd, pKs, pKa;
                float pP;

                glm::vec4 a_color3(.2f,.7f,.5f,1);
                glm::vec4 d_color3(.3f,.4f,.2f,1);
                glm::vec4 s_color3(.6f,.8f,.2f,1);

                Material pMaterial = Material(a_color3, d_color3, s_color3, 10.f);
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
                    /*
                    if (parsed[0] == "material") {
                        pMaterial.readMtl(parsed[1]);
                        
                    }
                    */
                }
            objects.push_back(new Plane(pNormal, pPosition, pMaterial));
            /*
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
                */
            }
            
        }
        std::cout<<"Obj is made"<<std::endl;
    }

    File.close();
    
}
 

