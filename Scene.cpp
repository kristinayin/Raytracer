#include "Scene.h"
#include "Object.h"
#include "Sphere.h"
#include "Plane.h"
#include "Lighting.h"
#include "Material.h"
#include "Camera.h"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
 
 // converts strings to float values
float sTF(const std::string& str) {
    float f = std::stof(str);
    return f;
}
 

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
            
            /* separates each word of line by spaces using stringstream and put them into parsed vector
            std::stringstream s(line);
            std::string word;
            while (s >> word) {
                parsed.push_back(word);
            }
            */
            std::vector<std::string> parsed = parse(line);
            
            if(parsed[0]=="Sphere"){
                glm::vec3 sCenter;
                float sRadius;
                
                glm::vec4 sKd, sKs, sKa;
                float sP;
                
                for(int i = 1; i<parsed.size(); i++){          
                    if(parsed[i] == "center") {
                        sCenter = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                    if(parsed[i] == "radius") {
                        sRadius = sTF(parsed[i+1]);
                    }
                    /*
                    if(parsed[i] == "material"){
                        std::string mtlLine;
                        std::ifstream mtlFile;
                        mtlFile.open(parsed[i+1]);

                        if(mtlFile.is_open()){
                            while(getline(mtlFile, mtlLine)){
                                std::vector<std::string> mtlParsed = parse(mtlLine);

                                if(mtlParsed[0] == "Ka"){
                                    for(int i = 1; i<mtlParsed.size(); i++){
                                        sKa = glm::vec4(sTF(mtlParsed[i+1]), sTF(mtlParsed[i+2]), sTF(mtlParsed[i+3]), 1);
                                    }
                                }
                                
                                if(mtlParsed[0] == "Kd"){
                                    for(int i = 1; i<mtlParsed.size(); i++){
                                        sKd = glm::vec4(sTF(mtlParsed[i+1]), sTF(mtlParsed[i+2]), sTF(mtlParsed[i+3]), 1);
                                    }
                                    

                                }

                                if(mtlParsed[0] == "Ks"){
                                    for(int i = 1; i<mtlParsed.size(); i++){
                                        sKs = glm::vec4(sTF(mtlParsed[i+1]), sTF(mtlParsed[i+2]), sTF(mtlParsed[i+3]), 1);
                                    }
                                    
                                }

                                if(mtlParsed[0] == "Ns"){
                                    sP = sTF(mtlParsed[i+1]);
                                }

                            }
                        }else{
                            cout<<"File is not opening"<<endl;
                        }

                        mtlFile.close();
                    }
                    */
                    
                    if (parsed[i] == "ka") {
                        sKa = glm::vec4(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]), 1.0);
                    }

                    if (parsed[i] == "kd") {
                        sKd = glm::vec4(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]), 1.0);
                    }

                    if (parsed[i] == "ks") {
                        sKs = glm::vec4(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]), 1.0);
                    }

                    if (parsed[i] == "Ns") {
                        sP = sTF(parsed[i+1]);
                    }
                    
                     
                    
                }
                objects.push_back(new Sphere(sCenter, sRadius, Material(sKd, sKs, sKa, sP)));
            
            } else if (parsed[0]=="Plane") {
                glm::vec3 pPosition, pNormal;
                glm::vec4 pKd, pKs, pKa;
                float pP;
                
                for(int i = 0; i<parsed.size(); i++){           
                    if(parsed[i]=="p") {
                        pPosition = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                    if(parsed[i]=="n") {
                        pNormal = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                    /*
                    if(parsed[i] == "material"){
                        std::string mtlLine;
                        std::ifstream mtlFile;
                        mtlFile.open(parsed[i+1]);

                        if(mtlFile.is_open()){
                            while(getline(mtlFile, mtlLine)){
                                std::vector<std::string> mtlParsed = parse(mtlLine);

                                if(mtlParsed[0] == "Ka"){
                                    for(int i = 1; i<mtlParsed.size(); i++){
                                        pKa = glm::vec4(sTF(mtlParsed[i+1]), sTF(mtlParsed[i+2]), sTF(mtlParsed[i+3]), 1);
                                    }
                                    
                                }
                                
                                if(mtlParsed[0] == "Kd"){
                                    for(int i = 1; i<mtlParsed.size(); i++){
                                        pKd = glm::vec4(sTF(mtlParsed[i+1]), sTF(mtlParsed[i+2]), sTF(mtlParsed[i+3]), 1);
                                    }
                                    

                                }

                                if(mtlParsed[0] == "Ks"){
                                    for(int i = 1; i<mtlParsed.size(); i++){
                                        pKs = glm::vec4(sTF(mtlParsed[i+1]), sTF(mtlParsed[i+2]), sTF(mtlParsed[i+3]), 1);
                                    }
                                    
                                }

                                if(mtlParsed[0] == "Ns"){
                                    pP = sTF(mtlParsed[i+1]);
                                }

                            }
                        }else{
                            cout<<"File is not opening"<<endl;
                        }

                        mtlFile.close();
                    }
                    */
                    
                    if (parsed[i] == "ka") {
                        pKa = glm::vec4(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]), 1.0);
                    }

                    if (parsed[i] == "kd") {
                        pKd = glm::vec4(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]), 1.0);
                    }

                    if (parsed[i] == "ks") {
                        pKs = glm::vec4(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]), 1.0);
                    }

                    if (parsed[i] == "Ns") {
                        pP = sTF(parsed[i+1]);
                    }
                    
                        
                }
                objects.push_back(new Plane(pNormal, pPosition, Material(pKd, pKs, pKa, pP)));
            
            } else if (parsed[0]=="Camera") {
                glm::vec3 cEye, cAt, cUp;
                float cFov, cRatio, cF;

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
                    if (parsed[i] == "angle") {
                        cFov = sTF(parsed[i+1]);
                        cout<<cFov<<endl;
                    }
                    if (parsed[i] == "aspect") {
                        cRatio = (sTF(parsed[i+1])/sTF(parsed[i+2]));
                        cout<<cRatio<<endl;
                    }
                    if (parsed[i] == "focal") {
                        cF = sTF(parsed[i+1]);
                        cout<<cF<<endl;
                    }
                }
                cout<<"Added camera"<<endl;
                c = Camera(cEye, cAt, cUp, cF, 10);
                
            }
            
            else if (parsed[0]=="Light") { // only dealing with point lights (might add dif lights like ambient, direction)
                
                glm::vec4 lIa, lId, lIs;
                glm::vec3 lP, lAtten;
                
                for (int i = 1; i<parsed.size(); i++) {
                    if (parsed[i]=="ia") {//find ambient intensity
                        cout<<parsed[i+1]<<endl;
                        lIa = glm::vec4(sTF(parsed[i+1]),sTF(parsed[i+2]),sTF(parsed[i+3]),sTF(parsed[i+4]));
                    }
                   
                    if (parsed[i]=="p") {//find point
                        cout<<parsed[i+1]<<endl;
                        lP = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                   
                    if (parsed[i]=="id") {//find diffuse intensity
                        cout<<parsed[i+1]<<endl;
                        lId = glm::vec4(sTF(parsed[i+1]),sTF(parsed[i+2]),sTF(parsed[i+3]),sTF(parsed[i+4]));
                    }
                    if (parsed[i]=="is") {//find specular intensity
                        cout<<parsed[i+1]<<endl;
                        lIs = glm::vec4(sTF(parsed[i+1]),sTF(parsed[i+2]),sTF(parsed[i+3]),sTF(parsed[i+4]));
                    }
                    
                    if (parsed[i]=="attenconst") {//find linear attenuation const
                        cout<<parsed[i+1]<<endl;
                        lAtten = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                    
                    // calling light constructors based on type of light -- in example.scene, light type has to go at the end
                    /*
                    if (parsed[i] == "ambient") { sLight = Light(lIa); }
                    if (parsed[i] == "directional") { sLight = Light(lD, lIa, lId, lIs); }
                    if (parsed[i] == "point") { sLight = Light(lP, lIa, lId, lIs, lAtten); }
                    if (parsed[i] == "spotlight") { sLight = Light(lP, lD, lT, lIa, lId, lIs, lAtten, lA); }
                    */
                         
                }
                lights.push_back(Light(lP, lIa, lId, lIs, lAtten));
            }
        }
    }
    File.close();
    
}
 

