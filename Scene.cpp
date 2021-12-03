#include "Scene.h"
#include "Object.h"
#include <string>
#include "Sphere.h"
#include "Plane.h"
#include <fstream>

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
            std::vector<std::string> parsed = parse(line);
            std::cout<<"At the beginning"<<std::endl;
            if(parsed[0]=="Sphere"){
                std::cout<<"Creating a sphere"<<std::endl;
                glm::vec3 sCenter;
                float sRadius;
                // read in material
                glm::vec4 sKd, sKs, sKa;
                float sP;

                glm::vec4 a_color(.6f,.2f,.4f,1);
                glm::vec4 d_color(.1f,.4f,.8f,1);
                glm::vec4 s_color(1.f,.8f,0.f,1);

                Material sMaterial = Material(a_color, d_color, s_color, 10.f);

                std::cout<<"Reading sphere line"<<std::endl;
                for(int i = 1; i<parsed.size(); i++){          
                    if(parsed[i] == "center") {
                        std::cout<<"Reading center"<<std::endl;
                        sCenter = glm::vec3(stringToFloat(parsed[i+1]), stringToFloat(parsed[i+2]), stringToFloat(parsed[i+3]));
                    }
                    if(parsed[i] == "radius") {
                        std::cout<<"Reading radius"<<std::endl;
                        sRadius = stringToFloat(parsed[i+1]);
                    }
                        /*
                        if (parsed[i] == "material") {
                            sMaterial.readMtl(parsed[i+1]);
                        }
                        */

                    }

                std::cout<<"Added a new sphere"<<std::endl;
                objects.push_back(new Sphere(sCenter, sRadius, sMaterial));
            
            } else if (parsed[0]=="Plane") {
                std::cout<<"Creating a plane"<<std::endl;
                glm::vec3 pPosition, pNormal;
                glm::vec4 pKd, pKs, pKa;
                float pP;

                glm::vec4 a_color3(.2f,.7f,.5f,1);
                glm::vec4 d_color3(.3f,.4f,.2f,1);
                glm::vec4 s_color3(.6f,.8f,.2f,1);

                Material pMaterial = Material(a_color3, d_color3, s_color3, 10.f);
                for(int i = 0; i<parsed.size(); i++){           
                    if(parsed[i]=="p") {
                        std::cout<<"Reading place: "<<parsed[i+1]<<std::endl;
                        pPosition = glm::vec3(stringToFloat(parsed[i+1]), stringToFloat(parsed[i+2]), stringToFloat(parsed[i+3]));
                    }
                    if(parsed[i]=="n") {
                        std::cout<<"Reading normal: "<<parsed[i+1]<<std::endl;
                        pNormal = glm::vec3(stringToFloat(parsed[i+1]), stringToFloat(parsed[i+2]), stringToFloat(parsed[i+3]));
                    }
                    /*
                    if (parsed[i] == "material") {
                        pMaterial.readMtl(parsed[i+1]);
                           
                    }*/
                        
                }
                
                std::cout<<"Added a new plane"<<std::endl;
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
                c = Camera();
            }
            
        }
        std::cout<<"Finished reading file"<<std::endl;
    }

    File.close();
    
}
 

