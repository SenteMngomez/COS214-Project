#ifndef MODERATECARESTRATEGY_H
#define MODERATECARESTRATEGY_H

#include "CareStrategy.h"
class ModerateCareStrategy :public CareStrategy {


public:
	void water();

	void sunlight();

	void soil();
};

#endif
