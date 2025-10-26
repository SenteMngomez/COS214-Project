#ifndef GROUNDSTAFF_H
#define GROUNDSTAFF_H

#include "Staff.h"
#include "Greenhouse.h"
#include "WaterPlant.h"
#include "GIveSunlight.h"


class GroundStaff :public Staff {


	public:
		GroundStaff(std::string name);

		void handleRequest(Person* person);

		void careForPlant(std::vector<int>* tags);

		void addPlant(Greenhouse* greenHouse, string type);

		void setWaterPlantCommand(WaterPlant* waterPlantCommand);

		void setGiveSunlightCommand(GiveSunlight* giveSunlightCommand);

	private:
		WaterPlant* waterPlantCmd;
		GiveSunlight* giveSunCmd;
};

#endif
