#ifndef GROUNDSTAFF_H
#define GROUNDSTAFF_H

#include "Staff.h"
#include "Greenhouse.h"
#include "WaterPlant.h"
#include "GIveSunlight.h"

/**
 * @file GroundStaff.h
 * @brief Concrete class representing ground staff who care for plants
 * @author Sente
 * @date October 26, 2025
 */

/**
 * @class GroundStaff
 * @brief Represents ground staff in the system. Inherits from Staff and
 *        handles "Care" requests by executing watering and sunlight commands
 *        on specified plant tags. Also provides helper methods to add plants
 *        to a greenhouse and configure care commands.
 */
class GroundStaff :public Staff {


	public:
		/**
		 * @brief Constructs a GroundStaff with the given name.
		 * @param name The name of the ground staff member.
		 */
		GroundStaff(std::string name);

		/**
         * @brief Handles a request sent by a person. GroundStaff will handle
         *        requests of type "Care"; otherwise it should delegate to the
         *        base Staff handler.
         * @param person The person who made the request.
         */
		void handleRequest(Person* person);

		/**
         * @brief Performs care actions (watering and sunlight) for the given plant tags.
         * @param tags Vector of plant tag IDs to care for.
         */
		void careForPlant(std::vector<int>* tags);

		/**
         * @brief Adds a plant of the given type to the specified greenhouse.
         * @param greenHouse Pointer to the Greenhouse to add the plant to.
         * @param type The plant type to add.
         */
		void addPlant(Greenhouse* greenHouse, string type);

		/**
         * @brief Sets the WaterPlant command used to water plants.
         * @param waterPlantCommand Pointer to a WaterPlant command object.
         */
		void setWaterPlantCommand(WaterPlant* waterPlantCommand);

		/**
         * @brief Sets the GiveSunlight command used to give sunlight to plants.
         * @param giveSunlightCommand Pointer to a GiveSunlight command object.
         */
		void setGiveSunlightCommand(GiveSunlight* giveSunlightCommand);

	private:
		WaterPlant* waterPlantCmd;/** Command used to water plants */
		GiveSunlight* giveSunCmd;/** Command used to give sunlight to plants */
};

#endif
