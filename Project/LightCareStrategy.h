#ifndef LIGHTCARESTRATEGY_H
#define LIGHTCARESTRATEGY_H

#include "CareStrategy.h"

class LightCareStrategy :public CareStrategy {


public:
	void water();

	void sunlight();

	void soil();
};

#endif
