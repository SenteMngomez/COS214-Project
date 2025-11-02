#include "GroundStaff.h"

GroundStaff::GroundStaff(std::string name):Staff(name){}

void GroundStaff::handleRequest(Person* person){

	if(person->getMessageType()=="Care"){

		std::string plants="";

		int numPlants=person->getTags()->size();

		for(int i=0;i<numPlants;i++){

			plants+="Plant-"+to_string((*person->getTags())[i]);

			if(i<numPlants-1){

				plants+=", ";
			}

		}

		std::cout<<"(Ground staff)"<<this->getName()<<" will care for plants: "<<plants<<"\nRequest made by "<<person->getName()<<std::endl;

		careForPlant(person->getTags());
		
	}else{

		Staff::handleRequest(person);
	}
}

void GroundStaff::careForPlant(std::vector<int>* tags) {

	if(waterPlantCmd){

		waterPlantCmd->execute(tags);
	}else{

		std::cout<<getName()<<" is unable to water plant(s)\n";
	}
	
	if(giveSunCmd){

		giveSunCmd->execute(tags);
	}else{

		std::cout<<getName()<<" is unable to give sunlight to plant(s)\n";
	}
	

}

void GroundStaff::addPlant(Greenhouse* greenHouse, string type) {

	//greenHouse->addPlant()
}

void GroundStaff::setWaterPlantCommand(WaterPlant* waterPlantCommand){

	waterPlantCmd=waterPlantCommand;
}

void GroundStaff::setGiveSunlightCommand(GiveSunlight* giveSunlightCommand){

	giveSunCmd=giveSunlightCommand;
}
