#include "StatSprite.h"
#include "ShaderHelp.h"
#include "Textures.h"
//todo force radians
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#define for_each(x,y,z) for(x::iterator y = z.begin(); y != z.end(); y++)

StatSprite::StatSprite(string t, float x, float y){
    tex=t;
    sx=x;
    sy=y;
}

StatSprite::~StatSprite(){
    //dtor
}

void StatSprite::render(glm::mat4 view,float x, float y){
    glUseProgram(getShader("sprite"));
    GLuint tempLoc=glGetUniformLocation(getShader("sprite"), "viewMatrix");
    glUniformMatrix4fv(tempLoc,1, GL_FALSE,&view[0][0]);

    glm::mat4 temp = glm::translate(glm::mat4(),glm::vec3(x,y,1));
    temp = glm::scale(temp,glm::vec3(sx,-sy,0));
    tempLoc=glGetUniformLocation(getShader("sprite"), "modelMatrix");
    glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);

    glBindVertexArray(vao.vao);
    glBindTexture(GL_TEXTURE_2D,getTexture(tex));
    glDrawArrays(GL_QUADS,0,4);
    glBindVertexArray(0);

}
