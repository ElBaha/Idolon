#ifndef GLMHELP_H_INCLUDED
#define GLMHELP_H_INCLUDED

#include <glm/glm.hpp>
#include <map>
#include <ostream>

#define sign(x) (x>0?1:(x<0?-1:0))

using namespace std;

struct veccomp {
  bool operator() (const glm::vec3& lhs, const glm::vec3& rhs) const
  {
  if(rhs.x==lhs.x&&rhs.y==lhs.y)
  return lhs.z<rhs.z;
  if(rhs.x==lhs.x)
  return lhs.y<rhs.y;
  return lhs.x<rhs.x;
  }
};

struct paircomp {
  bool operator() (const pair<glm::vec3,int>& lhs, const pair<glm::vec3,int>& rhs) const
  {
      return veccomp()(lhs.first,rhs.first);
  }
};

static ostream& operator<<(ostream& out, const glm::vec3 & v){
return out<<v.x<<" "<<v.y<<" "<<v.z;
}

static ostream& operator<<(ostream& out, const glm::vec4 & v){
return out<<v.x<<" "<<v.y<<" "<<v.z<<" "<<v.w;
}
#endif // GLMHELP_H_INCLUDED
