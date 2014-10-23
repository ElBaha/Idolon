#include "BoneSprite.h"
#include "ShaderHelp.h"
#include "Textures.h"


#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#define for_each(x,y,z) for(x::iterator y = z.begin(); y != z.end(); y++)
#define sign(x) (x>0?1:(x<0?-1:0))

#define ANIM_STAND 2
#define ANIM_IDLE 0
#define ANIM_WALK 1



BoneSprite::BoneSprite() {
    base.tex="testb";
    base.sx=5;
    base.sy=10;
    offset=9;


    Joint *urleg,*lrleg,*ulleg,*llleg;
    urleg=new Joint(Bone("testb",1,5),1);
    lrleg=new Joint(Bone("testb",1,5),1);
    ulleg=new Joint(Bone("testb",1,5),1);
    llleg=new Joint(Bone("testb",1,5),1);


    ulleg->tx=urleg->tx=.5;
    ulleg->ty=urleg->ty=4.5;
    ulleg->bx=urleg->bx=2.5;
    ulleg->by=urleg->by=0;

    llleg->tx=lrleg->tx=.5;
    llleg->ty=lrleg->ty=4.5;
    llleg->bx=lrleg->bx=.5;
    llleg->by=lrleg->by=.5;


    base.joints.push_back(ulleg);
    base.joints.push_back(urleg);
    ulleg->bone.joints.push_back(llleg);
    urleg->bone.joints.push_back(lrleg);

    Joint *ufarm,*lfarm,*ubarm,*lbarm;
    ufarm=new Joint(Bone("testb",1,5),1);
    ubarm=new Joint(Bone("testb",1,5),1);
    lfarm=new Joint(Bone("testb",1,5),1);
    lbarm=new Joint(Bone("testb",1,5),1);


    ubarm->tx=ufarm->tx=.5;
    ubarm->ty=ufarm->ty=4.5;
    ubarm->bx=ufarm->bx=2.5;
    ubarm->by=ufarm->by=8;

    lbarm->tx=lfarm->tx=.5;
    lbarm->ty=lfarm->ty=4.5;
    lbarm->bx=lfarm->bx=.5;
    lbarm->by=lfarm->by=.5;


    base.joints.push_back(ufarm);
    base.joints.push_back(ubarm);
    ufarm->bone.joints.push_back(lfarm);
    ubarm->bone.joints.push_back(lbarm);




}

Joint::Joint(Bone b, float a) {
    bone=b;
    angle=a;
    bx=by=tx=ty=0;
    //pre=NULL;
    pre= new MinMaxPredictor(-.5,.5,.05,0);
    type=2;
    //min=-1,max=1;
    speed=.05;
}

Joint::~Joint() {
    if(pre)
        delete pre;
}
static int boneFrame=0;
void Joint::update() {

    /*if(type==0||type==1){
    if(type==0)
        angle+=speed;
    else if(type==1)
        angle-=speed;

    if(angle>max)
        type=1;
    if(angle<min)
        type=0;
    }*/

    if(type==2) {
        float pred=0;
        if(pre)
            pred=pre->pred(boneFrame);

        angle+=sign(pred-angle)*min(speed,abs(pred-angle));
    }
}

BoneSprite::~BoneSprite() {
    //dtor
}

Bone::~Bone() {

    for_each(list<Joint*>,it,joints) {
        delete *it;
    }

}

void Bone::render(GLuint vao,glm::mat4 model) {

    glUseProgram(getShader("sprite"));
    GLuint tempLoc;

    glm::mat4 temp = glm::translate(model,glm::vec3(0.0,0.0,1));
    temp = glm::scale(temp,glm::vec3(sx,-sy,0));
    tempLoc=glGetUniformLocation(getShader("sprite"), "modelMatrix");
    glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);

    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D,getTexture(tex));
    glDrawArrays(GL_QUADS,0,4);
    glBindVertexArray(0);

    for_each(list<Joint*>,it,joints) {
        (*it)->update();
        temp = glm::translate(model,glm::vec3((*it)->bx,(*it)->by,0));
        temp = glm::rotate(temp,(*it)->angle,glm::vec3(0,0,1));
        temp = glm::translate(temp,glm::vec3(-(*it)->tx,-(*it)->ty,0));

        (*it)->bone.render(vao,temp);

    }

}

void BoneSprite::render(glm::mat4 view,float x, float y) {
    boneFrame++;
    glUseProgram(getShader("sprite"));
    GLuint tempLoc=glGetUniformLocation(getShader("sprite"), "viewMatrix");
    glUniformMatrix4fv(tempLoc,1, GL_FALSE,&view[0][0]);

    base.render(vao.vao,glm::translate(glm::mat4(),glm::vec3(x,y+offset,0)));


}
