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

glm::vec4 readMtlKa(const std::string& mtlFile){
    std::string line;
    std::ifstream mtl;
    mtl.open(mtlFile);
    glm::vec4 ka;//ambient


    if(mtl.is_open()){
      while(getline(mtl, line)){
        std::vector<std::string> parsed = parse(line);
        
        if(parsed[0] == "Ka") {
            for (int i = 1; parsed.size(); i++) {
                ka = glm::vec4(sTF(parsed[i+1]),sTF(parsed[i+2]),sTF(parsed[i+3]),1);
                mtl.close();
                break;
            }
        }
        
      }
    }

    return ka;
}

glm::vec4 readMtlKd(const std::string& mtlFile){
    std::string line;
    std::ifstream mtl;
    mtl.open(mtlFile);
    glm::vec4 kd;//diffuse


    if(mtl.is_open()){
      while(getline(mtl, line)){
        std::vector<std::string> parsed = parse(line);
        
        if(parsed[0] == "Kd") {
            for (int i = 1; parsed.size(); i++) {
                kd = glm::vec4(sTF(parsed[i+1]),sTF(parsed[i+2]),sTF(parsed[i+3]),1);
                mtl.close();
                break;
            }
        }
        
      }
    }

    return kd;
}

glm::vec4 readMtlKs(const std::string& mtlFile){
    std::string line;
    std::ifstream mtl;
    mtl.open(mtlFile);
    glm::vec4 ks;//specular


    if(mtl.is_open()){
      while(getline(mtl, line)){
        std::vector<std::string> parsed = parse(line);
        
        if(parsed[0] == "Ks") {
            for (int i = 1; parsed.size(); i++) {
                ks = glm::vec4(sTF(parsed[i+1]),sTF(parsed[i+2]),sTF(parsed[i+3]),1);
                mtl.close();
                break;
            }
        }
        
      }
    }

    return ks;
}

float readMtlP(const std::string& mtlFile){
    std::string line;
    std::ifstream mtl;
    mtl.open(mtlFile);
    float p;//shininess


    if(mtl.is_open()){
      while(getline(mtl, line)){
        std::vector<std::string> parsed = parse(line);
        
        if(parsed[0] == "Ka") {
            for (int i = 1; parsed.size(); i++) {
                p = sTF(parsed[1]);
                mtl.close();
                break;
            }
        }
        
      }
    }

    return p;
}

/*
Material readMtl(const std::string& mtlFile){//read thru one mtl file for each obj
    std::string line;
    std::ifstream mtl;
    mtl.open(mtlFile);

    glm::vec4 kd;//diffuse
    glm::vec4 ks;//specular
    glm::vec4 ka;//ambient
    float p;

    if(mtl.is_open()){
      while(getline(mtl, line)){
        std::vector<std::string> parsed = parse(line);
        
        if(parsed[0] == "Ka") {
            for (int i = 1; parsed.size(); i++) {
                ka = glm::vec4(sTF(parsed[i+1]),sTF(parsed[i+2]),sTF(parsed[i+3]),sTF(parsed[i+4]));
                cout<<ka[0]<<endl;
            }
        }
        if(parsed[0]=="Kd") {
            for (int i = 1; parsed.size(); i++) {
                kd = glm::vec4(sTF(parsed[i+1]),sTF(parsed[i+2]),sTF(parsed[i+3]),sTF(parsed[i+4]));
                cout<<kd[0]<<endl;
            }
        }
        if(parsed[0]=="Ks") {
            for (int i = 1; parsed.size(); i++) {
                ks = glm::vec4(sTF(parsed[i+1]),sTF(parsed[i+2]),sTF(parsed[i+3]),sTF(parsed[i+4]));
                cout<<ks[0]<<endl;
            }
        }
        if(parsed[0]=="Ns") {
            p = sTF(parsed[1]);
        }
      }
    }

    mtl.close();
    
    return Material(kd, ks, ka, p);
  }
*/

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
                //glm::vec4 ka, kd, ks;
                //float p;
                
                glm::vec4 sKd, sKs, sKa;
                float sP;
                
                glm::vec4 a_color(0.737255f,0.560784f,0.560784f,1);
                glm::vec4 d_color(.7f,.7f,5.f,1);
                glm::vec4 s_color(0.f,1.f,1.f,1);
                
                //Material sMaterial = Material(a_color, d_color, s_color, 100.f);
                //Material getMaterial = Material(a_color, d_color, s_color, 100.f);
                cout<<"Making a sphere"<<endl;
                for(int i = 1; i<parsed.size(); i++){          
                    if(parsed[i] == "center") {
                        //cout<<"Found center"<<endl;
                        sCenter = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                    if(parsed[i] == "radius") {
                        //cout<<"Found radius"<<endl;
                        sRadius = sTF(parsed[i+1]);
                    }
                      
                    if (parsed[i] == "ka") {
                        //cout<<"Found material"<<endl;
                        sKa = glm::vec4(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]), 1.0);
                    }

                    if (parsed[i] == "kd") {
                        //cout<<"Found material"<<endl;
                        sKd = glm::vec4(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]), 1.0);
                    }

                    if (parsed[i] == "ks") {
                        //cout<<"Found material"<<endl;
                        sKs = glm::vec4(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]), 1.0);
                    }

                    if (parsed[i] == "Ns") {
                        //cout<<"Found material"<<endl;
                        sP = sTF(parsed[i+1]);
                    }
                     
                    
                }
                cout<<"New sphere added"<<endl;
                objects.push_back(new Sphere(sCenter, sRadius, Material(sKd, sKs, sKa, sP)));
            
            } else if (parsed[0]=="Plane") {
                glm::vec3 pPosition, pNormal;
                glm::vec4 pKd, pKs, pKa;
                float pP;
                
                glm::vec4 a_color3(1.f,0.f,0.f,1);
                glm::vec4 d_color3(1.f,0.f,0.f,1);
                glm::vec4 s_color3(1.f,0.f,0.f,1);
                
                //Material pMaterial = Material(a_color3, d_color3, s_color3, 10.f);
                cout<<"Making new plane"<<endl;
                for(int i = 0; i<parsed.size(); i++){           
                    if(parsed[i]=="p") {
                        cout<<"Found point"<<endl;
                        pPosition = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                    if(parsed[i]=="n") {
                        cout<<"Found normal"<<endl;
                        pNormal = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                     
                    if (parsed[i] == "ka") {
                        //cout<<"Found material"<<endl;
                        pKa = glm::vec4(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]), 1.0);
                    }

                    if (parsed[i] == "kd") {
                        //cout<<"Found material"<<endl;
                        pKd = glm::vec4(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]), 1.0);
                    }

                    if (parsed[i] == "ks") {
                        //cout<<"Found material"<<endl;
                        pKs = glm::vec4(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]), 1.0);
                    }

                    if (parsed[i] == "Ns") {
                        //cout<<"Found material"<<endl;
                        pP = sTF(parsed[i+1]);
                    }
                    
                        
                }
                cout<<"New plane added"<<endl;
                objects.push_back(new Plane(pNormal, pPosition, Material(pKd, pKs, pKa, pP)));
            
            } else if (parsed[0]=="Camera") {
                glm::vec3 cEye, cAt, cUp;
                float cFov, cRatio, cF;

                cout<<"Creating camera"<<endl;
                for (int i = 1; i<parsed.size(); i++) {
                    if (parsed[i] == "eye"){
                        cout<<"Found eye"<<endl;
                        cEye = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                    if (parsed[i] == "at") {
                        cout<<"Found at"<<endl;
                        cAt = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                    if (parsed[i] == "up") {
                        cout<<"Found up"<<endl;
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
            
            /*else if (parsed[0]=="Light") { // pLight = point light (might add dif lights like ambient, direction)
                
                glm::vec4 lIa, lId, lIs;
                glm::vec3 lP, lAtten;
                // float lT, lA;
                
                cout<<"Creating a new light source"<<endl;
                for (int i = 1; i<parsed.size(); i++) {
                    if (parsed[i]=="ia") {
                        cout<<"Found ambient"<<endl;
                        cout<<parsed[i+1]<<endl;
                        lIa = glm::vec4(sTF(parsed[i+1]),sTF(parsed[i+2]),sTF(parsed[i+3]),sTF(parsed[i+4]));
                    }
                    /*
                    if (parsed[i]=="d") {
                        cout<<"Found distance"<<endl;
                        cout<<parsed[i+1]<<endl;
                        lD = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                    
                   
                    if (parsed[i]=="p") {
                        cout<<"Found point"<<endl;
                        cout<<parsed[i+1]<<endl;
                        lP = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                    
                    /*
                    if (parsed[i]=="t") {
                        cout<<"Found theta"<<endl;
                        cout<<parsed[i+1]<<endl;
                        lT = sTF(parsed[i+1]);
                    }
                    
                   
                    if (parsed[i]=="id") {
                        cout<<"Found diffuse"<<endl;
                        cout<<parsed[i+1]<<endl;
                        lId = glm::vec4(sTF(parsed[i+1]),sTF(parsed[i+2]),sTF(parsed[i+3]),sTF(parsed[i+4]));
                    }
                    if (parsed[i]=="is") {
                        cout<<"Found specular"<<endl;
                        cout<<parsed[i+1]<<endl;
                        lIs = glm::vec4(sTF(parsed[i+1]),sTF(parsed[i+2]),sTF(parsed[i+3]),sTF(parsed[i+4]));
                    }
                    
                    if (parsed[i]=="attenconst") {
                        cout<<"Found linear attencost"<<endl;
                        cout<<parsed[i+1]<<endl;
                        lAtten = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                    
                    /*
                    if (parsed[i]=="a") {
                        cout<<"Found angular attencost"<<endl;
                        cout<<parsed[i+1]<<endl;
                        lA = sTF(parsed[i+1]);
                    }
                    */
                    
                    // calling light constructors based on type of light -- in example.scene, light type has to go at the end
                    /*
                    if (parsed[i] == "ambient") { sLight = Light(lIa); }
                    if (parsed[i] == "directional") { sLight = Light(lD, lIa, lId, lIs); }
                    if (parsed[i] == "point") { sLight = Light(lP, lIa, lId, lIs, lAtten); }
                    if (parsed[i] == "spotlight") { sLight = Light(lP, lD, lT, lIa, lId, lIs, lAtten, lA); }
                    
                         
                }
                Light l(lP, lIa, lId, lIs, lAtten);
                cout<<l.getId()[0]<<" "<<l.getId()[1]<<" "<<l.getId()[2]<<endl;
                //addLight(l);
                //lights.push_back(Light(glm::vec3 (0, 5, -10), glm::vec4 (0.1, 0.1, 0.1, 1), glm::vec4 (0.5, 0.7, 0.4, 1), glm::vec4 (0.8, 0.8, 0.8, 1), glm::vec3 (1., 1., 1.)));
                lights.push_back(l);
            }*/
        }
    }
    File.close();
    
}
 

