#ifndef STDVAO_H_INCLUDED
#define STDVAO_H_INCLUDED

namespace vao{

class CenterSquare{
public:
CenterSquare(){

    GLfloat vertexCoords[]={-1,-1,0, -1,1,0, 1,1,0, 1,-1,0};
    GLfloat colors[]={0,1, 0,0, 1,0, 1,1};

    glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);

	glGenBuffers(2,vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*12,vertexCoords,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*8,colors,GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);


	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

}

~CenterSquare(){
glBindVertexArray(0);
glDeleteVertexArrays(1,&vao);
glDeleteBuffers(2,vbo);
}


GLuint vao;
GLuint vbo[2];

};

class CornerSquare{
public:
CornerSquare(){

    GLfloat vertexCoords[]={0,0,0, 0,1,0, 1,1,0, 1,0,0};
    GLfloat colors[]={0,0, 0,1, 1,1, 1,0};

    glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);

	glGenBuffers(2,vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*12,vertexCoords,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*8,colors,GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);


	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

}

~CornerSquare(){
glBindVertexArray(0);
glDeleteVertexArrays(1,&vao);
glDeleteBuffers(2,vbo);
}


GLuint vao;
GLuint vbo[2];

};




}

#endif // STDVAO_H_INCLUDED
