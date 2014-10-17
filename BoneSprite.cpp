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
    base.sy=20;

    base.joints.push_back(Joint(Bone("testb",2,10),1));


}

Joint::Joint(Bone b, float a){
    bone=b; angle=a;
    bx=by=tx=ty=0;

}

BoneSprite::~BoneSprite(){
    //dtor
}

void Bone::render(GLuint vao,glm::mat4 model){

    glUseProgram(getShader("sprite"));
    GLuint tempLoc;

    glm::mat4 temp = glm::translate(model,glm::vec3(0.0,sy,1));
    temp = glm::scale(temp,glm::vec3(sx,sy,0));
    tempLoc=glGetUniformLocation(getShader("sprite"), "modelMatrix");
    glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);

    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D,getTexture(tex));
    glDrawArrays(GL_QUADS,0,4);
    glBindVertexArray(0);

    for_each(list<Joint>,it,joints){

        temp = glm::translate(model,glm::vec3(-it->tx,-it->ty,0));
        temp = glm::rotate(temp,it->angle,glm::vec3(0,0,1));
        temp = glm::translate(temp,glm::vec3(it->bx,it->by,0));

        it->bone.render(vao,temp);

    }

}

void BoneSprite::render(glm::mat4 view){

    glUseProgram(getShader("sprite"));
    GLuint tempLoc=glGetUniformLocation(getShader("sprite"), "viewMatrix");
    glUniformMatrix4fv(tempLoc,1, GL_FALSE,&view[0][0]);

    base.render(vao.vao,glm::mat4());


}
