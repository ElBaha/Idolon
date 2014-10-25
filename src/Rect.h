#ifndef RECT_H
#define RECT_H

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "stdvao.h"
#include "StatSprite.h"

#define HIT_NONE 0
#define HIT_TOP 1
#define HIT_BOTTOM 2
#define HIT_LEFT 4
#define HIT_RIGHT 8

struct HitRec {
	unsigned short hit;
	glm::vec2 d;
};

class Rect {
public:
	Rect(glm::vec2, glm::vec2);
	Rect(const Rect &);
	Rect();
	
	glm::vec2 &org();
	glm::vec2 &dim();
	glm::vec2 opp();
	void setOpp(glm::vec2);
	
	void normalize();
	void normalize_zero();
	Rect normalized();
	bool operator!();
	
	void translate(glm::vec2);
	void scale(glm::vec2, glm::vec2);
	void scale(glm::vec2);
	
	Rect unite(const Rect &);
	Rect intersect(const Rect &);
	
	HitRec testHit(const Rect &);
	
	void render(glm::mat4);
	
protected:
	glm::vec2 origin;
	glm::vec2 dimension;
	
	static vao::CornerSquare *vao;
	StatSprite *spr;
};

#endif