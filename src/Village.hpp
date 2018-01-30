/*
 * VillageSettings.hpp
 *
 *  Created on: 25 jan. 2017
 *      Author: Thomas
 */

#ifndef VILLAGE_HPP_
#define VILLAGE_HPP_

#include "ResourceProduction.hpp"
#include "TW_Enums.hpp"
#include "events/TWEvent.hpp"

#include "../lib/json.hpp"

#include <iostream>
#include <string>
#include <unordered_map>


#define MIN_BUILDING_LEVEL 0
#define MAX_BUILDING_LEVEL 30

// Forward declaration of events because of circular dependency.
class TWE_VillageDataParsed;
class TWE_TroopDataParsed;
class TWE_BuildingUpgradeStarted;
class TWE_BuildingUpgradeFinished;
class TWE_UnitResearchStarted;
class TWE_UnitResearchFinished;
class TWE_UnitRecruitmentStarted;
class TWE_UnitRecruitmentFinished;
class TWE_TaskFailed;

struct UnitResearch
{
    Resources cost;
    std::time_t duration;
    bool canBeResearched;
};

class Village : public ResourceProduction
{
public:
    Village();

    /**
     * Event handlers.
     */
    void OnVillageDataParsedEvent(const TWE_VillageDataParsed& event);
    void OnTroopDataParsedEvent(const TWE_TroopDataParsed& event);
    void OnUpgradeStartedEvent(const TWE_BuildingUpgradeStarted& event);
    void OnUpgradeFinishedEvent(const TWE_BuildingUpgradeFinished& event);
    void OnUnitResearchStarted(const TWE_UnitResearchStarted& event);
    void OnUnitResearchFinished(const TWE_UnitResearchFinished& event);
    void OnUnitRecruitmentStarted(const TWE_UnitRecruitmentStarted& event);
    void OnUnitRecruitmentFinished(const TWE_UnitRecruitmentFinished& event);
    void OnTaskFailed(const TWE_TaskFailed& event);

    /**
     * Checks if the unit can currently be researched.
     * @param unit
     * @return
     */
    bool canUnitBeResearched(const TW_ENUMS::TroopNames& unit);

    /**
     * Gets the current building level in this village.
     * @param building
     * @return
     */
    uint8_t getBuildingLevel(const TW_ENUMS::BuildingNames& building);

    /**
     * Returns the amount of time in seconds it will take to research a unit.
     * Throws a runtime error otherwise.
     * @param unit
     * @return
     */
    std::time_t getUnitResearchTime(const TW_ENUMS::TroopNames unit);

    virtual ~Village();

    uint32_t getVillageId() const
    {
        return villageID;
    }
    const std::string& getCsrf() const
    {
        return csrf;
    }

    bool isCurrentlyBuilding() const
    {
        return currentlyBuilding;
    }

    bool isCurrentlyResearching() const
    {
        return currentlyResearching;
    }

private:
    /**
     * Converts json data and stores it.
     * @param villageData
     */
    void parseVillageClipboardData(nlohmann::json villageData);

    /**
     * Converts json data about the current researched units in the village.
     * @param troopData
     */
    void parseTroopClipboardData(nlohmann::json troopData);

    /**
     * Increases the level of a building.
     * @param building
     */
    void increaseBuildingLevel(const TW_ENUMS::BuildingNames& building);

    /**
     * Increases the current population in the village.
     * @param building
     */
    void increaseCurrenPopulation(const TW_ENUMS::BuildingNames& building);

    /**
     * Decreases the current resources in the village by the cost of a building.
     * @param building
     * @param level
     */
    void decreaseCurrentResources(const TW_ENUMS::BuildingNames& building, uint8_t level);

    void decreaseCurrentResources(const TW_ENUMS::TroopNames& troop, uint32_t amount);

    bool currentlyBuilding;
    bool currentlyResearching;

    uint32_t villageID;
    std::string csrf;  ///< I have no idea where this stands for, but it's a kind of cookie. When something goes wrong this 'cookie' is reset.
    std::unordered_map<TW_ENUMS::BuildingNames, uint8_t, std::hash<int>> buildings;       ///< Map with buildings and there levels
    std::unordered_map<TW_ENUMS::TroopNames, UnitResearch, std::hash<int>> unitResearch;  ///< Map with units that need to be researched.
};

#endif /* VILLAGE_HPP_ */
