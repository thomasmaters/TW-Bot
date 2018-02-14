/*
 * VillageBuilder.cpp
 *
 *  Created on: 30 aug. 2017
 *      Author: Thomas
 */

#include "VillageBuilder.hpp"

#include "BotManager.hpp"
#include "GameManager.hpp"
#include "tasks/TWTResearchUnit.hpp"
#include "tasks/TWTUpgradeBuilding.hpp"

VillageBuilder::VillageBuilder()
{
    try
    {
        villageUpgradePath.LoadFile("village_build.xml");
    }
    catch (std::exception& e)
    {
        std::cerr << __PRETTY_FUNCTION__ << ": " << e.what() << std::endl;
    }
}

void VillageBuilder::developVillage(const std::shared_ptr<Village>& currentVillage)
{
    try
    {
        for (tinyxml2::XMLElement* child = villageUpgradePath.FirstChildElement(); child != NULL; child = child->NextSiblingElement())
        {
            if (std::string(child->Name()) == "build" && !currentVillage->isCurrentlyBuilding())
            {
                uint8_t level                    = std::stoi(child->GetText());
                TW_ENUMS::BuildingNames building = TW_ENUMS::stringToEnum<TW_ENUMS::BuildingNames>(child->Attribute("building"));

                // Do we have to upgrade this building?
                if (currentVillage->getBuildingLevel(building) < level)
                {
                    // Start building.
                    startVillageBuild(currentVillage, building);
                    break;
                }
            }
            else if (std::string(child->Name()) == "research" && !currentVillage->isCurrentlyResearching())
            {
                TW_ENUMS::TroopNames troop = TW_ENUMS::stringToEnum<TW_ENUMS::TroopNames>(child->Attribute("unit"));
                if (currentVillage->canUnitBeResearched(troop))
                {
                    BotManager::getInstance().addTask(std::shared_ptr<TW_Task>(new TWT_ResearchUnit(troop, currentVillage)));
                    break;
                }
            }
            else if (std::string(child->Name()) == "resources" && !currentVillage->isCurrentlyBuilding())
            {
                uint16_t maxEfficienty = std::stoi(child->GetText());

                if (canUpgradeResourceBuilding(currentVillage, maxEfficienty))
                {
                    TW_ENUMS::BuildingNames bestResourceToUpgrade = upgradeNextResource(currentVillage, maxEfficienty);
                    startVillageBuild(currentVillage, bestResourceToUpgrade);
                    break;
                }
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Could't develop village: " << e.what() << std::endl;
    }
}

void VillageBuilder::startVillageBuild(const std::shared_ptr<Village>& currentVillage, const TW_ENUMS::BuildingNames& building)
{
    // Calculate cost.
    uint8_t level           = currentVillage->getBuildingLevel(building) + 1;
    Resources buildingCost  = GameManager::getInstance().getBuildingCost(building, level);
    uint32_t populationCost = GameManager::getInstance().getPopulationCost(building, level);

    std::cout << "Upgrading: " << TW_ENUMS::enumToBuildingName(building) << " cost: " << buildingCost.toString()
              << " to level: " << std::to_string(level) << std::endl;

    // If we don't have enough population to start a upgrade, consider upgrading the farm.
    if (!currentVillage->hasEnoughPopulation(populationCost))
    {
        std::cout << "NOT ENOUGH POPULATION" << std::endl;
        startVillageBuild(currentVillage, TW_ENUMS::BuildingNames::FARM);
        return;
    }

    // If we don't have enough storage consider upgrading the storage.
    if (!currentVillage->hasEnoughStorage(buildingCost))
    {
        std::cout << "NOT ENOUGH STORAGE" << std::endl;
        startVillageBuild(currentVillage, TW_ENUMS::BuildingNames::STORAGE);
        return;
    }

    // Can we start the upgrade now?
    if (currentVillage->hasEnoughResources(buildingCost))
    {
        BotManager::getInstance().addTask(std::shared_ptr<TW_Task>(new TWT_UpgradeBuilding(currentVillage, building, currentVillage->getCsrf())));
    }
    else
    {
        // Add a delayed upgrade task.
        BotManager::getInstance().scheduleTask(
          currentVillage->timeToGetResources(buildingCost) * 1000,
          std::shared_ptr<TW_Task>(new TWT_UpgradeBuilding(currentVillage, building, currentVillage->getCsrf())));
    }
}

TW_ENUMS::BuildingNames VillageBuilder::upgradeNextResource(const std::shared_ptr<Village>& currentVillage, uint16_t maxEfficienty)
{
    Resources efficiency = getResourcesEfficiency(currentVillage);

    if (efficiency.wood < efficiency.iron && efficiency.wood < efficiency.stone && efficiency.wood < maxEfficienty)
    {
        return TW_ENUMS::BuildingNames::WOOD;
    }
    else if (efficiency.stone < efficiency.wood && efficiency.stone < efficiency.iron && efficiency.stone < maxEfficienty)
    {
        return TW_ENUMS::BuildingNames::STONE;
    }
    else if (efficiency.iron < 9999 && efficiency.iron < maxEfficienty)
    {
        return TW_ENUMS::BuildingNames::IRON;
    }
    else
    {
        // Should not occur if 'canUpgradeResourceBuilding' has been called before this function.
        throw std::runtime_error("Resources can't be upgraded");
    }
}

bool VillageBuilder::canUpgradeResourceBuilding(const std::shared_ptr<Village>& currentVillage, uint16_t maxEfficienty)
{
    Resources efficiency = getResourcesEfficiency(currentVillage);
    return efficiency < maxEfficienty;
}

double VillageBuilder::getUpgradeEfficiency(const std::shared_ptr<Village>& currentVillage, const TW_ENUMS::BuildingNames& building,
                                            uint8_t upgradeToLevel)
{
    // Building is at desired level, return an immense efficiency.
    if (currentVillage->getBuildingLevel(building) + 1 > upgradeToLevel)
    {
        return 9999;
    }
    Resources cost = GameManager::getInstance().getBuildingCost(building, upgradeToLevel);
    uint32_t productionIncrease =
      GameManager::getInstance().getResourceProduction(upgradeToLevel) - GameManager::getInstance().getResourceProduction(upgradeToLevel - 1);
    return (cost.wood + cost.iron + cost.stone) / productionIncrease;
}

VillageBuilder::~VillageBuilder()
{
}

Resources VillageBuilder::getResourcesEfficiency(const std::shared_ptr<Village>& currentVillage)
{
    double woodEff =
      getUpgradeEfficiency(currentVillage, TW_ENUMS::BuildingNames::WOOD, currentVillage->getBuildingLevel(TW_ENUMS::BuildingNames::WOOD) + 1);
    double stoneEff =
      getUpgradeEfficiency(currentVillage, TW_ENUMS::BuildingNames::STONE, currentVillage->getBuildingLevel(TW_ENUMS::BuildingNames::STONE) + 1);
    double ironEff =
      getUpgradeEfficiency(currentVillage, TW_ENUMS::BuildingNames::IRON, currentVillage->getBuildingLevel(TW_ENUMS::BuildingNames::IRON) + 1);

    return Resources(woodEff, stoneEff, ironEff);
}
