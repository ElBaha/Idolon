#ifndef PREDICTOR_H
#define PREDICTOR_H
#include <iostream>
using namespace std;

class Predictor {
public:
    Predictor() {}
    virtual ~Predictor() {}

    virtual float pred(int time)=0;
};

class MinMaxPredictor:public Predictor {
public:
    MinMaxPredictor(float mi, float ma, float sp, float st):min(mi),max(ma),speed(sp),start(st) {}

    virtual float pred(int time) {
        int tmp=(speed*time+start)*1000;
        tmp=tmp%(int)(((max-min)/speed)*2000);

        float p=((max-min)/speed)*1000;
	//cout<<tmp/1000.0<<" "<<p<<endl;
        if(tmp>p)
            return max-((tmp-p)/1000.0)*speed;
        else
            return min+(tmp/1000.0)*speed;

    }

    int dir;
    float min,max,speed,start;

};

class MirrorPredictor:public Predictor {
public:
    MirrorPredictor(Predictor* p):other(p){}

    virtual float pred(int time){
	return -other->pred(time);
    }

    Predictor* other;
};

class HalfPredictor:public Predictor {
public:
    HalfPredictor(Predictor* p):other(p){}

    virtual float pred(int time){
	float t=-other->pred(time);
	if(t<0)
	return t;
	return 0;
    }

    Predictor* other;
};

class StaticPredictor:public Predictor {
public:
    StaticPredictor(float aa):a(aa) {}

    virtual float pred(int time) {
        return a;
    }
    float a;
};

#endif
