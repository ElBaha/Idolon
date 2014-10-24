#ifndef SPRITE_H
#define SPRITE_H
#include <glm/glm.hpp>

#define ANIM_IDLE 0
#define ANIM_WALK 1
#define ANIM_STAND 2

class Sprite
{
    public:
        Sprite();
        virtual ~Sprite();
        virtual void render(glm::mat4 view,float x, float y)=0;
	virtual void setState(int s){state=s;}
    protected:
	int state;
};

#endif // SPRITE_H
