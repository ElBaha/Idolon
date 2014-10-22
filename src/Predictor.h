#ifndef PREDICTOR_H
#define PREDICTOR_H

class Predictor{
public:
	Predictor();
	virtual ~Predictor();

	virtual float pred(int time)=0;
};

class MinMaxPredictor:public Predictor{
public:
	MinMaxPredictor(float mi, float ma, float sp, float st):min(mi),max(ma),speed(sp),start(st){}

	virtual float pred(int time)=0;

	int dir;
	float min,max,speed,start;

};

class MirrorPredictor:public Predictor{
public:
	MirrorPredictor();

	virtual float pred(int time)=0;
};

class StaticPredictor:public Predictor{
public:
	StaticPredictor();

	virtual float pred(int time)=0;
};

#endif
