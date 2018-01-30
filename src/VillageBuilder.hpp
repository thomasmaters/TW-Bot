/*
 * VillageBuilder.hpp
 *
 *  Created on: 30 aug. 2017
 *      Author: Thomas
 */

#ifndef VILLAGEBUILDER_HPP_
#define VILLAGEBUILDER_HPP_

#include "TW_Enums.hpp"
#include "Village.hpp"

#include "../lib/tinyxml2.h"

class VillageBuilder
{
public:
    VillageBuilder();

    /**
     * Starts cycle to determine what to upgrade.
     * @param currentVillage
     */
    void developVillage(const std::shared_ptr<Village>& currentVillage);

    virtual ~VillageBuilder();

private:
    /**
     * Starts an upgrade in the current village. Starts building farm first if there is no population left. Starts building storage if there is no
     * storage to house the build cost.
     * @param currentVillage
     * @param building
     */
    void startVillageBuild(const std::shared_ptr<Village>& currentVillage, const TW_ENUMS::BuildingNames& building);

    /**
     * Calculates the best resource building to upgrade.
     * @param currentVillage
     * @return
     */
    TW_ENUMS::BuildingNames upgradeNextResource(const std::shared_ptr<Village>& currentVillage, uint16_t maxEfficienty);

    /**
     * Returns true if one of the resources buildings is lower then the maxEfficienty.
     * @param currentVillage
     * @param maxEfficienty
     * @return
     */
    bool canUpgradeResourceBuilding(const std::shared_ptr<Village>& currentVillage, uint16_t maxEfficienty);

    /**
     * Calculates efficiency factor of upgrading a resource production building.
     * @param currentVillage
     * @param building
     * @param level
     * @return
     */
    double getUpgradeEfficiency(const std::shared_ptr<Village>& currentVillage, const TW_ENUMS::BuildingNames& building, uint8_t level);

    Resources getResourcesEfficiency(const std::shared_ptr<Village>& currentVillage);

    tinyxml2::XMLDocument villageUpgradePath;
};


#endif /* VILLAGEBUILDER_HPP_ */
