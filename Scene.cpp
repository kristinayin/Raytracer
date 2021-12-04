#include "Scene.h"
#include "Object.h"
#include "Sphere.h"
#include "Plane.h"
#include "Light.h"
#include "Material.h"
#include "Camera.h"
#include <string>
#include <fstream>
#include <sstream>

void Scene::addLight(Light lt){
    lights.push_back(lt);
}

 
 // converts strings to float values
float sTF(const std::string& str) {
    float f = std::stof(str);
    return f;
}
 
/*
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
*/
 
// take in example.scene file
void Scene::readFromFile(const std::string& file) {
    std::vector<std::string> parsed;
    std::string line;
    std::ifstream File;
    File.open(file);
    if (File.is_open()){
        while(getline(File,line)){
            
            // separates each word of line by spaces using stringstream and put them into parsed vector
            std::stringstream s(line);
            std::string word;
            while (s >> word) {
                parsed.push_back(word);
            }
            
            if(parsed[0]=="Sphere"){
                glm::vec3 sCenter;
                float sRadius;
                // read in material
                glm::vec4 sKd, sKs, sKa;
                float sP;

                glm::vec4 a_color(.6f,.2f,.4f,1);
                glm::vec4 d_color(.1f,.4f,.8f,1);
                glm::vec4 s_color(1.f,.8f,0.f,1);

                Material sMaterial = Material(a_color, d_color, s_color, 10.f);

                for(int i = 1; i<parsed.size(); i++){          
                    if(parsed[i] == "center") {
                        sCenter = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                    if(parsed[i] == "radius") {
                        sRadius = sTF(parsed[i+1]);
                    }
                        /*
                        if (parsed[i] == "material") {
                            sMaterial.readMtl(parsed[i+1]);
                        }
                        */

                    }

                objects.push_back(new Sphere(sCenter, sRadius, sMaterial));
            
            } else if (parsed[0]=="Plane") {
                glm::vec3 pPosition, pNormal;
                glm::vec4 pKd, pKs, pKa;
                float pP;

                glm::vec4 a_color3(.2f,.7f,.5f,1);
                glm::vec4 d_color3(.3f,.4f,.2f,1);
                glm::vec4 s_color3(.6f,.8f,.2f,1);

                Material pMaterial = Material(a_color3, d_color3, s_color3, 10.f);
                for(int i = 0; i<parsed.size(); i++){           
                    if(parsed[i]=="p") {
                        pPosition = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                    if(parsed[i]=="n") {
                        pNormal = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                    /*
                    if (parsed[i] == "material") {
                        pMaterial.readMtl(parsed[i+1]);
                           
                    }*/
                        
                }
                
                objects.push_back(new Plane(pNormal, pPosition, pMaterial));
            
            } else if (parsed[0]=="Camera") {
                glm::vec3 cEye, cAt, cUp;
                
                for (int i = 1; i<parsed.size(); i++) {
                    if (parsed[i] == "eye"){
                        cEye = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                    if (parsed[i] == "at") {
                        cAt = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                    if (parsed[i] == "up") {
                        cUp = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                }
                c = Camera(cEye, cAt, cUp, 1, 10);
                
            } else if (parsed[0]=="Light") { // pLight = point light (might add dif lights like ambient, direction)
                Light sLight;
                
                for (int i = 1; i<parsed.size(); i++) {
                    if (parsed[i]=="ia") {
                        glm::vec4 lIa = glm::vec4(sTF(parsed[i+1]),sTF(parsed[i+2]),sTF(parsed[i+3]),sTF(parsed[i+4]));
                    }
                    if (parsed[i]=="d") {
                        glm::vec3 lD = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                    if (parsed[i]=="p") {
                        glm::vec3 lP = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                    if (parsed[i]=="t") {
                        float lT = sTF(parsed[i+1]);
                    }
                    if (parsed[i]=="id") {
                        glm::vec4 lId = glm::vec4(sTF(parsed[i+1]),sTF(parsed[i+2]),sTF(parsed[i+3]),sTF(parsed[i+4]));
                    }
                    if (parsed[i]=="is") {
                        glm::vec4 lIs = glm::vec4(sTF(parsed[i+1]),sTF(parsed[i+2]),sTF(parsed[i+3]),sTF(parsed[i+4]));
                    }
                    if (parsed[i]=="attenconst") {
                        glm::vec3 lAtten = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                    if (parsed[i]=="a") {
                        float lA = sTF(parsed[i+1]);
                    }
                    
                    // calling light constructors based on type of light -- in example.scene, light type has to go at the end
                    if (parsed[i] == "ambient") { sLight = new Light(lIa); }
                    if (parsed[i] == "directional") { sLight = new Light(lD, lIa, lId, lIs); }
                    if (parsed[i] == "point") { sLight = new Light(lP, lIa, lId, lIs, lAtten); }
                    if (parsed[i] == "spotlight") { sLight = new Light(lP, lD, lT, lIa, lId, lIs, lAtten, lA); }
                        
                }
                lights.push_back(sLight);
            
            }
        }
    }
    File.close();
    
}
 

