/*
 * TWEBuildingUpgradeFinished.hpp
 *
 *  Created on: 29 aug. 2017
 *      Author: Thomas
 */

#ifndef TWEBUILDINGUPGRADEFINISHED_HPP_
#define TWEBUILDINGUPGRADEFINISHED_HPP_

#include "TWEvent.hpp"

class TWE_BuildingUpgradeFinished : public TW_Event
{
public:
    TWE_BuildingUpgradeFinished(const TW_ENUMS::BuildingNames& aBuilding, const uint32_t aVillageID, const uint8_t aNewBuildingLevel)
      : TW_Event(), building(aBuilding), villageID(aVillageID), newBuildingLevel(aNewBuildingLevel)
    {
    }

    virtual ~TWE_BuildingUpgradeFinished()
    {
    }


    TW_ENUMS::BuildingNames building;
    uint32_t villageID;
    uint8_t newBuildingLevel;

private:
};


#endif /* TWEBUILDINGUPGRADEFINISHED_HPP_ */
