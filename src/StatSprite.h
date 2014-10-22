#ifndef STATSPRITE_H
#define STATSPRITE_H
#include "Sprite.h"
#include <GL/glew.h>
#include "stdvao.h"
#include <list>
#include <string>

using namespace std;

class StatSprite:public Sprite {
public:
    StatSprite(string t, float w, float h);
    virtual ~StatSprite();
    virtual void render(glm::mat4 view,float x, float y);

    vao::UpperCornerSquare vao;
    string tex;
    int sx,sy;
};

#endif // BONESPRITE_H
