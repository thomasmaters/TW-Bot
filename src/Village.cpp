/*
 * VillageSettings.cpp
 *
 *  Created on: 25 jan. 2017
 *      Author: Thomas
 */

#include "Village.hpp"
#include "BotManager.hpp"
#include "GameManager.hpp"
#include "tasks/TWTReadTroopData.hpp"
#include "tasks/TWTReadVillageData.hpp"
#include "tasks/TWTRecruitUnit.hpp"

#include <boost/signals2.hpp>

#include <iostream>

Village::Village() : currentlyBuilding(false), currentlyResearching(false), villageID(0), csrf(), world()
{
    BotManager::getInstance().TWE_VillageDataParsedHandler.connect(boost::bind(&Village::OnVillageDataParsedEvent, this, _1));
    BotManager::getInstance().TWE_TroopDataParsedHandler.connect(boost::bind(&Village::OnTroopDataParsedEvent, this, _1));
    BotManager::getInstance().TWE_BuildingUpgradeStartedHandler.connect(boost::bind(&Village::OnUpgradeStartedEvent, this, _1));
    BotManager::getInstance().TWE_BuildingUpgradeFinishedHandler.connect(boost::bind(&Village::OnUpgradeFinishedEvent, this, _1));
    BotManager::getInstance().TWE_UnitResearchStartedHandler.connect(boost::bind(&Village::OnUnitResearchStarted, this, _1));
    BotManager::getInstance().TWE_UnitResearchFinishedHandler.connect(boost::bind(&Village::OnUnitResearchFinished, this, _1));
    BotManager::getInstance().TWE_UnitRecruitmentStartedHandler.connect(boost::bind(&Village::OnUnitRecruitmentStarted, this, _1));
    BotManager::getInstance().TWE_UnitRecruitmentFinishedHandler.connect(boost::bind(&Village::OnUnitRecruitmentFinished, this, _1));
    BotManager::getInstance().TWE_TaskFailedHandler.connect(boost::bind(&Village::OnTaskFailed, this, _1));
    // Schedule task to get the villageData.
    BotManager::getInstance().addTask(std::shared_ptr<TW_Task>(new TWT_ReadVillageData()));
}

void Village::OnVillageDataParsedEvent(const TWE_VillageDataParsed& event)
{
    std::cout << __PRETTY_FUNCTION__ << "  " << std::endl;

    parseVillageClipboardData(event.villageData);
    BotManager::getInstance().TWE_VillageDataParsedHandler.disconnect(boost::bind(&Village::OnVillageDataParsedEvent, this, _1));

    if (getBuildingLevel(TW_ENUMS::BuildingNames::SMITH) != 0)
    {
        BotManager::getInstance().addTask(std::shared_ptr<TW_Task>(new TWT_ReadTroopData()));
    }
    else
    {
        GameManager::getInstance().developVillage();
    }
}

void Village::OnTroopDataParsedEvent(const TWE_TroopDataParsed& event)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    parseTroopClipboardData(event.troopData);

    GameManager::getInstance().developVillage();
}

void Village::OnUpgradeStartedEvent(const TWE_BuildingUpgradeStarted& event)
{
    if (event.villageID != villageID)
    {
        return;
    }

    decreaseCurrentResources(event.building, buildings[event.building] + 1);
    increaseCurrenPopulation(event.building);
    updateCurrentResources();

    // If we upgrade the main building, increase its level to account for the time reduction.
    if (event.building == TW_ENUMS::BuildingNames::MAIN)
    {
        increaseBuildingLevel(event.building);
    }

    currentlyBuilding = true;
}

void Village::OnUpgradeFinishedEvent(const TWE_BuildingUpgradeFinished& event)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if (event.villageID != villageID)
    {
        return;
    }

    if (event.building == TW_ENUMS::BuildingNames::FARM)
    {
        maxPopulation = GameManager::getInstance().getMaxPopulation(buildings[TW_ENUMS::BuildingNames::FARM] + 1);
    }

    if (event.building != TW_ENUMS::BuildingNames::MAIN)
    {
        increaseBuildingLevel(event.building);
    }
    currentlyBuilding = false;

    GameManager::getInstance().developVillage();
}

void Village::OnUnitResearchStarted(const TWE_UnitResearchStarted& event)
{
    if (event.villageID != villageID)
    {
        return;
    }
    unitResearch[event.unit].canBeResearched = false;
    currentlyResearching                     = true;
}

void Village::OnUnitResearchFinished(const TWE_UnitResearchFinished& event)
{
    if (event.villageID != villageID)
    {
        return;
    }
    unitResearch.erase(unitResearch.find(event.unit));
    currentlyResearching = false;
}

void Village::OnUnitRecruitmentStarted(const TWE_UnitRecruitmentStarted& event)
{
}

void Village::OnUnitRecruitmentFinished(const TWE_UnitRecruitmentFinished& event)
{
}

void Village::OnTaskFailed(const TWE_TaskFailed& event)
{
    if (typeid(*event.task) == typeid(TWT_ReadVillageData) && villageID == 0)
    {
        std::cout << "Read village data failed. Trying again." << std::endl;
        BotManager::getInstance().scheduleTask(5000, std::shared_ptr<TW_Task>(new TWT_ReadVillageData()));
    }
}

/***********************************************
 ***********************************************
 ***********************************************/

bool Village::canUnitBeResearched(const TW_ENUMS::TroopNames& unit)
{
    if (unitResearch.find(unit) == unitResearch.end())
    {
        return false;
    }
    else
    {
        return unitResearch[unit].canBeResearched;
    }
}

uint8_t Village::getBuildingLevel(const TW_ENUMS::BuildingNames& building)
{
    if (buildings.find(building) != buildings.end())
    {
        return buildings[building];
    }
    return 0;
}

std::time_t Village::getUnitResearchTime(const TW_ENUMS::TroopNames unit)
{
    if (unitResearch.find(unit) == unitResearch.end())
    {
        throw std::runtime_error("Cannot research unit.");
    }
    else
    {
        return unitResearch[unit].duration;
    }
}

Village::~Village()
{
}

void Village::increaseBuildingLevel(const TW_ENUMS::BuildingNames& building)
{
    // Did the building already exisit in the village or are we constructing it?
    if (buildings.find(building) != buildings.end())
    {
        buildings[building]++;
    }
    else
    {
        buildings[building] = 1;
    }
}

void Village::increaseCurrenPopulation(const TW_ENUMS::BuildingNames& building)
{
    population += GameManager::getInstance().getPopulationCost(building, buildings[building]);
}

void Village::decreaseCurrentResources(const TW_ENUMS::BuildingNames& building, uint8_t level)
{
    Resources cost = GameManager::getInstance().getBuildingCost(building, level);
    if (resources.wood - cost.wood < 0 || resources.stone - cost.stone < 0 || resources.iron - cost.iron < 0)
    {
        throw std::underflow_error("Failed to decrease current resources.");
    }
    resources -= cost;
}

void Village::decreaseCurrentResources(const TW_ENUMS::TroopNames& troop, uint32_t amount)
{
}

void Village::parseVillageClipboardData(nlohmann::json villageData)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if (villageData.find("village") != villageData.end())
    {
        // Parse available buildings in village.
        for (nlohmann::json::iterator it = villageData["village"]["buildings"].begin(); it != villageData["village"]["buildings"].end(); ++it)
        {
            int buildingLevel = atoi(it.value().get<std::string>().c_str());
            if (buildingLevel > MIN_BUILDING_LEVEL && buildingLevel <= MAX_BUILDING_LEVEL)
            {
                buildings[TW_ENUMS::stringToEnum<TW_ENUMS::BuildingNames>(it.key())] = buildingLevel;
            }
        }

        // Get village identifier.
        villageID = villageData["village"]["id"];
        csrf      = villageData["csrf"];
        world     = villageData["world"];

        // Get resource information.
        population    = villageData["village"]["pop"];
        maxPopulation = villageData["village"]["pop_max"];
        maxStorage    = villageData["village"]["storage_max"];
        resources     = Resources(villageData["village"]["wood"], villageData["village"]["stone"], villageData["village"]["iron"]);
        production    = ResourceProd(villageData["village"]["wood_prod"], villageData["village"]["stone_prod"], villageData["village"]["iron_prod"]);
        last_res_tick = std::time_t(villageData["village"]["last_res_tick"].get<uint64_t>() / 1000);

        // Does or village has a resource bonus?
        if (villageData["village"].find("bonus") != villageData["village"].end() && !villageData["village"]["bonus"].empty())
        {
            bonus = ResourceBonus(villageData["village"]["bonus"]["wood"], villageData["village"]["bonus"]["stone"],
                                  villageData["village"]["bonus"]["iron"]);
        }
        else
        {
            bonus = ResourceBonus(0, 0, 0);
        }
    }
}

void Village::parseTroopClipboardData(nlohmann::json troopData)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    unitResearch.clear();

    for (nlohmann::json::iterator it = troopData["available"].begin(); it != troopData["available"].end(); ++it)
    {
        if (troopData["available"][it.key()]["image_state"].get<std::string>().find("grey") != std::string::npos ||
            troopData["available"][it.key()]["image_state"].get<std::string>().find("cros") != std::string::npos)
        {
            // TODO Als de smederij is geupgrade even de clipboard data opnieuw parsen.
            // Convert string to construction time.
            struct std::tm tm;
            UnitResearch tempStruct;

            if (troopData["available"][it.key()].find("research_time") != troopData["available"][it.key()].end())
            {
                std::istringstream ss(troopData["available"][it.key()]["research_time"].get<std::string>());
                ss >> std::get_time(&tm, "%H:%M:%S");

                tempStruct.duration        = mktime(&tm);
                tempStruct.cost            = Resources(troopData["available"][it.key()]["wood"], troopData["available"][it.key()]["stone"],
                                            troopData["available"][it.key()]["iron"]);
                tempStruct.canBeResearched = true;
            }
            else
            {
                tempStruct.canBeResearched = false;
            }
            unitResearch[TW_ENUMS::stringToEnum<TW_ENUMS::TroopNames>(it.key())] = tempStruct;
        }
    }
}
