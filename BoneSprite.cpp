#include "BoneSprite.h"
#include "ShaderHelp.h"
#include "Textures.h"
//todo force radians
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#define for_each(x,y,z) for(x::iterator y = z.begin(); y != z.end(); y++)

BoneSprite::BoneSprite(){
    base.tex="testa";
    base.sx=10;
    base.sy=30;

    base.joints.push_back(Joint(Bone("testb",2,10),1));
    base.joints.front().type=1;
    base.joints.front().min=-.05;
    base.joints.front().tx=1;
    base.joints.front().ty=1;
    base.joints.front().bx=5;
    base.joints.front().by=30;

    Joint* j=&base.joints.front();
    j->bone.joints.push_back(Joint(Bone("testb",2,10),0));
    j->bone.joints.front().max=0;
    j->bone.joints.front().tx=1;
    j->bone.joints.front().ty=1;
    j->bone.joints.front().bx=1;
    j->bone.joints.front().by=9;

    base.joints.push_front(Joint(Bone("testb",2,10),-.5));
    base.joints.front().min=-.05;
    base.joints.front().tx=1;
    base.joints.front().ty=1;
    base.joints.front().bx=5;
    base.joints.front().by=30;

    j=&base.joints.front();
    j->bone.joints.push_back(Joint(Bone("testb",2,10),0));
    j->bone.joints.front().max=0;
    j->bone.joints.front().tx=1;
    j->bone.joints.front().ty=1;
    j->bone.joints.front().bx=1;
    j->bone.joints.front().by=9;


}

Joint::Joint(Bone b, float a){
    bone=b; angle=a;
    bx=by=tx=ty=0;
    type=0;
    min=-1,max=1;
    speed=.01;
}

void Joint::update(){

    if(type==0)
        angle+=speed;
    else if(type==1)
        angle-=speed;

    if(angle>max)
        type=1;
    if(angle<min)
        type=0;

}

BoneSprite::~BoneSprite(){
    //dtor
}

void Bone::render(GLuint vao,glm::mat4 model){

    glUseProgram(getShader("sprite"));
    GLuint tempLoc;

    glm::mat4 temp = glm::translate(model,glm::vec3(0.0,0.0,1));
    temp = glm::scale(temp,glm::vec3(sx,sy,0));
    tempLoc=glGetUniformLocation(getShader("sprite"), "modelMatrix");
    glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);

    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D,getTexture(tex));
    glDrawArrays(GL_QUADS,0,4);
    glBindVertexArray(0);

    for_each(list<Joint>,it,joints){
        it->update();
        temp = glm::translate(model,glm::vec3(it->bx,-it->by,0));
        temp = glm::rotate(temp,it->angle,glm::vec3(0,0,1));
        temp = glm::translate(temp,glm::vec3(-it->tx,it->ty,0));

        it->bone.render(vao,temp);

    }

}

void BoneSprite::render(glm::mat4 view,float x, float y){
    glUseProgram(getShader("sprite"));
    GLuint tempLoc=glGetUniformLocation(getShader("sprite"), "viewMatrix");
    glUniformMatrix4fv(tempLoc,1, GL_FALSE,&view[0][0]);

    base.render(vao.vao,glm::translate(glm::mat4(),glm::vec3(x,y,0)));


}
