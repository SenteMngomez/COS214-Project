#ifndef HEAVYCARESTRATEGY_H
#define HEAVYCARESTRATEGY_H

#include "CareStrategy.h"

class HeavyCareStrategy :public CareStrategy {


public:
	void water();

	void sunlight();

	void soil();
};

#endif
