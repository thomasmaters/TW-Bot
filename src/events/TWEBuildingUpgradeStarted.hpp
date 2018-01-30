/*
 * TWEBuildingUpgradeStarted.hpp
 *
 *  Created on: 29 aug. 2017
 *      Author: Thomas
 */

#ifndef TWEBUILDINGUPGRADESTARTED_HPP_
#define TWEBUILDINGUPGRADESTARTED_HPP_

#include "TWEvent.hpp"

class TWE_BuildingUpgradeStarted : public TW_Event
{
public:
    TWE_BuildingUpgradeStarted(const TW_ENUMS::BuildingNames& aBuilding, const uint32_t aVillageID)
      : TW_Event(), building(aBuilding), villageID(aVillageID)
    {
    }

    virtual ~TWE_BuildingUpgradeStarted()
    {
    }

    TW_ENUMS::BuildingNames building;
    uint32_t villageID;

private:
};


#endif /* TWEBUILDINGUPGRADESTARTED_HPP_ */
