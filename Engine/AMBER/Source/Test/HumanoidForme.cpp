#include "HumanoidForme.hpp"

namespace lia
{
    HumanoidForme::HumanoidForme() : BodyForme("Humanoid")
    {
        bodyParts.push_back(new BodyPart("Torso",40,1,100,40.5f,false,{"Torso"},{}));
        bodyParts.push_back(new BodyPart("Neck",25,1,7.5f,1.5f,false,{"Neck"},{bodyParts[0]}));
        bodyParts.push_back(new BodyPart("Head",25,1,80.0f,2.82f,false,{"UpperHead","FullHead","HeadAttackTool"},{bodyParts[1]}));
        bodyParts.push_back(new BodyPart("Skull",25,1,18.0f,0.51f,true,{"UpperHead","Eyes","FullHead"},{bodyParts[2]}));
        bodyParts.push_back(new BodyPart("Brain",10,1,80.0f,0.41f,true,{"UpperHead","Eyes","FullHead"},{bodyParts[3]}));
        bodyParts.push_back(new BodyPart("Eye",10,2,7.0f,0.42f,false,{"Eyes","FullHead"},{bodyParts[2]}));
        bodyParts.push_back(new BodyPart("Ear",12,2,7.0f,0.42f,false,{"UpperHead","FullHead"},{bodyParts[2]}));
        bodyParts.push_back(new BodyPart("Nose",10,1,10.0f,0.6f,false,{"FullHead"},{bodyParts[2]}));
        bodyParts.push_back(new BodyPart("Jaw",20,1,15.0f,0.9f,false,{"Teeth","FullHead"},{bodyParts[2]}));        
        bodyParts.push_back(new BodyPart("Tongue",10,1,0.0f,0.0f,true,{"FullHead"},{bodyParts[8]}));        
        bodyParts.push_back(new BodyPart("Waist",10,1,0.0f,0.0f,true,{"FullHead"},{bodyParts[8]}));        
        bodyParts.push_back(new BodyPart("Spine",25,1,2.5f,1.01f,true,{"Torso"},{bodyParts[0]}));        
        bodyParts.push_back(new BodyPart("Ribcage",30,1,3.6f,1.46f,true,{"Torso"},{bodyParts[0]}));        
        bodyParts.push_back(new BodyPart("Sternum",20,1,1.5f,0.61f,true,{"Torso"},{bodyParts[0]}));        
        bodyParts.push_back(new BodyPart("Heart",15,1,2.0f,0.81f,true,{"Torso"},{bodyParts[0]}));        
        bodyParts.push_back(new BodyPart("Lung",15,2,2.5f,1.01f,true,{"Torso"},{bodyParts[0]}));
        bodyParts.push_back(new BodyPart("Stomach",20,1,2.5f,1.01f,true,{"Torso"},{bodyParts[0]}));
        bodyParts.push_back(new BodyPart("Liver",20,1,2.5f,1.01f,true,{"Torso"},{bodyParts[0]}));
        bodyParts.push_back(new BodyPart("Kidney",15,2,1.7f,0.69f,true,{"Torso"},{bodyParts[0]}));
        bodyParts.push_back(new BodyPart("Shoulder",30,2,12.0f,2.76f,false,{"Shoulders"},{bodyParts[0]}));
        bodyParts.push_back(new BodyPart("Arm",30,2,77.0f,7.95f,false,{"Arms"},{bodyParts[19]}));
        bodyParts.push_back(new BodyPart("Clavicle",25,2,9.0f,1.08f,true,{"Torso"},{bodyParts[19]}));
        bodyParts.push_back(new BodyPart("Humerus",25,2,10.0f,0.79f,true,{"Arms"},{bodyParts[20]}));
        bodyParts.push_back(new BodyPart("Radius",20,2,10.0f,0.79f,true,{"Arms"},{bodyParts[20]}));
        bodyParts.push_back(new BodyPart("Hand",20,2,14.0f,0.83f,true,{"Hands"},{bodyParts[20]}));
        //https://rimworldwiki.com/wiki/Body_Parts

    }
}