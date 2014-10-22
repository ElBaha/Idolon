#include "BoneSprite.h"
#include "ShaderHelp.h"
#include "Textures.h"


#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#define for_each(x,y,z) for(x::iterator y = z.begin(); y != z.end(); y++)
#define sign(x) (x>0?1:(x<0?-1:0))

BoneSprite::BoneSprite(){
    base.tex="IncrediblyAlphaSpectre2";
    base.sx=5;
    base.sy=10;

    base.joints.push_back(new Joint(Bone("testb",2,10),1));
    base.joints.front()->type=2;
    //base.joints.front().min=-.5;
    base.joints.front()->tx=1;
    base.joints.front()->ty=1;
    base.joints.front()->bx=2.5;
    base.joints.front()->by=10;

    Joint* j=base.joints.front();
    j->bone.joints.push_back(new Joint(Bone("testc",3.5,10),.2));
    //j->bone.joints.front().max=0;
    j->bone.joints.front()->speed=.012121212;
    j->bone.joints.front()->tx=1;
    j->bone.joints.front()->ty=1;
    j->bone.joints.front()->bx=1;
    j->bone.joints.front()->by=9;

    base.joints.push_front(new Joint(Bone("testb",2,10),-.5));
    //base.joints.front().min=-.5;
    base.joints.front()->tx=1;
    base.joints.front()->ty=1;
    base.joints.front()->bx=2.5;
    base.joints.front()->by=10;

    j=base.joints.front();
    j->bone.joints.push_back(new Joint(Bone("testc",3.5,10),.7));
    //j->bone.joints.front().max=0;
    j->bone.joints.front()->speed=.012121212;
    j->bone.joints.front()->tx=1;
    j->bone.joints.front()->ty=1;
    j->bone.joints.front()->bx=1;
    j->bone.joints.front()->by=9;


}

Joint::Joint(Bone b, float a){
    bone=b; angle=a;
    bx=by=tx=ty=0;
	//pre=NULL;
	pre= new MinMaxPredictor(-.5,.5,.1,0);
    type=2;
    //min=-1,max=1;
    speed=.01;
}

Joint::~Joint(){
	if(pre)
		delete pre;
}
static int boneFrame=0;
void Joint::update(){

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

    if(type==2){
		float pred=0;
		if(pre)
			pred=pre->pred(boneFrame);

        angle+=sign(pred-angle)*min(speed,abs(pred-angle));
    }
}

BoneSprite::~BoneSprite(){
    //dtor
}

Bone::~Bone(){

	for_each(list<Joint*>,it,joints){
		delete *it;
	}

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

    for_each(list<Joint*>,it,joints){
        (*it)->update();
        temp = glm::translate(model,glm::vec3((*it)->bx,-(*it)->by,0));
        temp = glm::rotate(temp,(*it)->angle,glm::vec3(0,0,1));
        temp = glm::translate(temp,glm::vec3(-(*it)->tx,(*it)->ty,0));

        (*it)->bone.render(vao,temp);

    }

}

void BoneSprite::render(glm::mat4 view,float x, float y){
	boneFrame++;
    glUseProgram(getShader("sprite"));
    GLuint tempLoc=glGetUniformLocation(getShader("sprite"), "viewMatrix");
    glUniformMatrix4fv(tempLoc,1, GL_FALSE,&view[0][0]);

    base.render(vao.vao,glm::translate(glm::mat4(),glm::vec3(x,y+10,0)));


}
