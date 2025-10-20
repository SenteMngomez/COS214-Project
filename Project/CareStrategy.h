#ifndef CARESTRATEGY_H
#define CARESTRATEGY_H

class CareStrategy {


public:
	virtual void water() = 0;

	virtual void sunlight() = 0;

	virtual void soil() = 0;
};

#endif
