#ifndef BONESPRITE_H
#define BONESPRITE_H
#include "Sprite.h"
#include <GL/glew.h>
#include "stdvao.h"
#include <list>
#include <string>

using namespace std;

class Joint;

class Bone {
public:
    Bone(){sx=sy=0;}
    Bone(string s,float x, float y){tex=s;sx=x;sy=y;}

    void render(GLuint vao,glm::mat4 model);

    string tex;
    //size x,y
    float sx,sy;
    list<Joint> joints;
};

class Joint{
public:
    Joint(Bone b, float a);

    Bone bone;
    float angle;

    //base affix point
    float bx,by;
    //this affix point
    float tx,ty;

};

class BoneSprite:public Sprite {
public:
    BoneSprite();
    virtual ~BoneSprite();
    virtual void render(glm::mat4 view);

    vao::UpperCornerSquare vao;
    Bone base;
};

#endif // BONESPRITE_H
