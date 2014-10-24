#ifndef BONESPRITE_H
#define BONESPRITE_H
#include "Sprite.h"
#include <GL/glew.h>
#include "stdvao.h"
#include "Predictor.h"
#include <list>
#include <string>
#include <vector>

using namespace std;

class Joint;

class Bone {
public:
    Bone(){sx=sy=0;}
    Bone(string s,float x, float y){tex=s;sx=x;sy=y;}
	~Bone();

    void render(GLuint vao,glm::mat4 model,int state);

    string tex;
    //size x,y
    float sx,sy;
    list<Joint*> joints;
};

class Joint{
public:
    Joint(Bone b, float a);
	~Joint();
    void update(int state);

    Bone bone;
    float angle;

    //base affix point
    float bx,by;
    //this affix point
    float tx,ty;

	vector<Predictor*> pre;
    float speed;
    int type;

};

class BoneSprite:public Sprite {
public:
    BoneSprite();
    virtual ~BoneSprite();
    virtual void render(glm::mat4 view,float x, float y);
    virtual void setState(int s);

    vao::UpperCornerSquare vao;
    Bone base;
    float offset;
};

#endif // BONESPRITE_H
