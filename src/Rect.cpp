#include "Rect.h"
#include "ShaderHelp.h"
#include <iostream>

#define min(a, b) ((a)<(b)?(a):(b))
#define max(a, b) ((a)>(b)?(a):(b))
#define abs(a) ((a)<0?-(a):(a))

vao::CornerSquare *Rect::vao = NULL;

Rect::Rect(glm::vec2 org, glm::vec2 dim) : origin(org), dimension(dim) {spr=NULL;}

Rect::Rect(const Rect &r) : origin(r.origin), dimension(r.dimension) {spr=NULL;}

Rect::Rect() : origin(), dimension() {spr=NULL;}

glm::vec2 &Rect::org() {return origin;}

glm::vec2 &Rect::dim() {return dimension;}

glm::vec2 Rect::opp() {return origin+dimension;}

void Rect::setOpp(glm::vec2 opp) {dimension = opp-origin;}

bool Rect::operator!() {
	return dimension.x==0 || dimension.y==0;
}

void Rect::normalize() {
	if(dimension.x<0) {
		dimension.x*=-1;
		origin.x-=dimension.x;
	}
	if(dimension.y<0) {
		dimension.y*=-1;
		origin.y-=dimension.y;
	}
}

void Rect::normalize_zero() {
	if(dimension.x<0) dimension.x=0;
	if(dimension.y<0) dimension.y=0;
}

Rect Rect::normalized() {
	Rect ret = *this;
	ret.normalize();
	return ret;
}

void Rect::translate(glm::vec2 delta) {origin+=delta;}

void Rect::scale(glm::vec2 coef, glm::vec2 about) {
	origin=about+coef*(origin-about);
	setOpp(about+coef*(opp()-about));
}

void Rect::scale(glm::vec2 coef) {
	scale(coef, origin);
}

#define UNCONST(a) (*const_cast<Rect *>(&a))

Rect Rect::unite(const Rect &r) {
	glm::vec2 minorg(min(origin.x, r.origin.x), min(origin.y, r.origin.y));
	glm::vec2 maxopp(max(opp().x, UNCONST(r).opp().x), max(opp().y, UNCONST(r).opp().y));
	Rect ret(minorg, maxopp-minorg);
	ret.normalize_zero();
	return ret;
}

void writeRect(std::ostream &os, Rect &r) {
	os<<r.org().x<<" "<<r.org().y<<" "<<r.dim().x<<" "<<r.dim().y<<std::endl;
}

Rect Rect::intersect(const Rect &r) {
	glm::vec2 maxorg(max(origin.x, r.origin.x), max(origin.y, r.origin.y));
	glm::vec2 minopp(min(opp().x, UNCONST(r).opp().x), min(opp().y, UNCONST(r).opp().y));
	Rect ret(maxorg, minopp-maxorg);
	ret.normalize_zero();
	//std::cout<<"ISCT:\n";
	//writeRect(std::cout, *this);
	//writeRect(std::cout, UNCONST(r));
	//writeRect(std::cout, ret);
	return ret;
}

HitRec Rect::testHit(const Rect &r) {
	Rect isct = intersect(r);
	HitRec rec = {HIT_NONE, glm::vec2(0, 0)};
	if(!isct) return rec;
	rec.d = isct.dimension;
	if(abs(isct.dimension.x)>abs(isct.dimension.y)) {
		if(isct.origin.y<=origin.y) {
			rec.hit |= HIT_BOTTOM;
		}
		if(isct.opp().y>=opp().y) {
			rec.hit |= HIT_TOP;
		}
	} else {
		if(isct.origin.x<=origin.x) {
			rec.hit |= HIT_LEFT;
		}
		if(isct.opp().x>=opp().x) {
			rec.hit |= HIT_RIGHT;
		}
	}
	return rec;
}

void writeMatrix(std::ostream &os, glm::mat4 &mat) {
	int i, j;
	for(i=0; i<4; i++) {
		for(j=0; j<4; j++) {
			os.width(8);
			os<<mat[j][i]<<" ";
		}
		os<<std::endl;
	}
}

void Rect::render(glm::mat4 view) {
	/*if(!spr) {
		spr = new StatSprite("ERROR", dimension.x, dimension.y);
	}
	spr->sx = dimension.x;
	spr->sy = dimension.y;
	spr->render(view, origin.x, origin.y);*/
	
	if(!vao) {
		vao = new vao::CornerSquare();
	}
	glUseProgram(getShader("basic"));
	GLuint uviewmat=glGetUniformLocation(getShader("basic"), "viewMatrix");
	GLuint umodelmat=glGetUniformLocation(getShader("basic"), "modelMatrix");
	
	glm::mat4 modelmat = glm::translate(glm::mat4(),glm::vec3(origin.x,origin.y,1));
	modelmat = glm::scale(modelmat, glm::vec3(dimension.x,-dimension.y,0));
	
	glUniformMatrix4fv(umodelmat, 1, GL_FALSE, &modelmat[0][0]);
	glUniformMatrix4fv(uviewmat, 1, GL_FALSE, &view[0][0]);
	writeMatrix(std::cout, modelmat);
	std::cout<<std::endl;
	glBindVertexArray(vao->vao);
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glDrawArrays(GL_TRIANGLES, 0, 4);
	glPopAttrib();
	glBindVertexArray(0);
}
	

#undef UNCONST
#undef min
#undef max
#undef abs