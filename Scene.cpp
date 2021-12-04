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
                
                
                // glm::vec4 sKd, sKs, sKa;
                // float sP;
                
                glm::vec4 a_color(.6f,.2f,.4f,1);
                glm::vec4 d_color(.1f,.4f,.8f,1);
                glm::vec4 s_color(1.f,.8f,0.f,1);
                
                Material sMaterial = Material(a_color, d_color, s_color, 10.f);
                
                cout<<"Making a sphere"<<endl;
                for(int i = 1; i<parsed.size(); i++){          
                    if(parsed[i] == "center") {
                        cout<<"Found center"<<endl;
                        sCenter = glm::vec3(sTF(parsed[i+1]), sTF(parsed[i+2]), sTF(parsed[i+3]));
                    }
                    if(parsed[i] == "radius") {
                        cout<<"Found radius"<<endl;
                        sRadius = sTF(parsed[i+1]);
                    }
                    /*    
                    if (parsed[i] == "material") {
                        cout<<"Found material"<<endl;
                        //Material getMaterial;
                        sMaterial = readMtl(parsed[i+1]);
                        //cout<<sMaterial.ka[0]<<endl;
                    }    
                    */
                }
                cout<<"New sphere added"<<endl;
                objects.push_back(new Sphere(sCenter, sRadius, sMaterial));
            
            } else if (parsed[0]=="Plane") {
                glm::vec3 pPosition, pNormal;
                glm::vec4 pKd, pKs, pKa;
                float pP;
                
                glm::vec4 a_color3(.2f,.7f,.5f,1);
                glm::vec4 d_color3(.3f,.4f,.2f,1);
                glm::vec4 s_color3(.6f,.8f,.2f,1);
                
                Material pMaterial = Material(a_color3, d_color3, s_color3, 10.f);
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
                    /*
                    if (parsed[i] == "material") {
                        pMaterial = readMtl(parsed[i+1]);
                        //cout<<pMaterial.ka[0]<<endl;
                    }
                    */
                        
                }
                cout<<"New plane added"<<endl;
                objects.push_back(new Plane(pNormal, pPosition, pMaterial));
            
            } else if (parsed[0]=="Camera") {
                glm::vec3 cEye, cAt, cUp;
                
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
                }
                cout<<"Added camera"<<endl;
                c = Camera(cEye, cAt, cUp, 1, 10);
                
            }else if (parsed[0]=="Light") { // pLight = point light (might add dif lights like ambient, direction)
                
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
                    */
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
                    */
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
                    */
                         
                }
                lights.push_back(new Light(lP, lIa, lId, lIs, lAtten));
            
            }
        }
    }
    File.close();
    
}
 

