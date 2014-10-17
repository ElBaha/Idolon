#ifndef SPRITE_H
#define SPRITE_H
#include <glm/glm.hpp>

class Sprite
{
    public:
        Sprite();
        virtual ~Sprite();
        virtual void render(glm::mat4 view)=0;
    protected:
    private:
};

#endif // SPRITE_H
