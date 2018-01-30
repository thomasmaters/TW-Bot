/*
 * GameManager.hpp
 *
 *  Created on: 15 jan. 2017
 *      Author: Thomas
 */

#ifndef GAMEMANAGER_HPP_
#define GAMEMANAGER_HPP_

#include "GameWorldSettings.hpp"
#include "ImageRecognition.hpp"
#include "TW_Enums.hpp"
#include "Village.hpp"
#include "VillageBuilder.hpp"
#include "util/Singleton.hpp"
#include "Resources.hpp"

#include <opencv2/core/types.hpp>
#include "../lib/tinyxml2.h"

#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

class GameManager : public GameWorldSettings, public Singleton
{
public:
    static GameManager& getInstance();

    /**
     * Gets the position on the screen a specific building in the overview window.
     * @param aBuildingName
     * @return
     */
    cv::Rect getBuildingPositionOnScreen(const enum TW_ENUMS::BuildingNames& aBuildingName);

    /**
     * Finds a template in the latest taken screenshot.
     * @param aTemplate Filelocation of the template.
     * @return
     */
    cv::Rect getTemplatePositionOnScreen(const std::string& aTemplate);

    /**
     * Gets the position of a template on the screen.
     * @param aParent XML parent name.
     * @param aChild XML child name.
     * @param amountOfResults How many matches to return.
     * @return
     */
    std::vector<cv::Rect> getTemplatePositionsOnScreen(const std::string& aParent, const std::string& aChild, uint8_t amountOfResults);

    /**
     * Gets the position of a template on the screen.
     * @param aParent XML parent name.
     * @param aChild XML child name.
     * @return
     */
    cv::Rect getTemplatePositionOnScreen(const std::string& aParent, const std::string& aChild);

    /**
     * Event handlers
     */
    void OnUpgradeStartedEvent(const TWE_BuildingUpgradeStarted& event);
    void OnUpgradeFinishedEvent(const TWE_BuildingUpgradeFinished& event);

    virtual ~GameManager();

    /**
     * Gets the village the game is currently looking at.
     * @return
     */
    std::shared_ptr<Village> getCurrentVillage() const
    {
        return currentVillage;
    }

    /**
     * Gets the time it takes to upgrade a building.
     * @param building
     * @param upgradeToLevel To which level the building will be upgraded.
     * @param mainBuildingLevel The current level of the main building.
     * @return Time in seconds it takes to upgrade the building.
     */
    double getBuildingTime(const TW_ENUMS::BuildingNames& building, uint8_t upgradeToLevel, uint8_t mainBuildingLevel) const;

    /**
     * Gets the time it takes recruit 1 unit of a specific troop.
     * @param troop
     * @param upgradeBuildingLevel
     * @return Time in seconds.
     */
    double getTroopBuildTime(const TW_ENUMS::TroopNames& troop, uint8_t upgradeBuildingLevel) const;

    /**
     * Gets the population cost of a building.
     * @param building
     * @param level
     * @return
     */
    uint32_t getPopulationCost(const TW_ENUMS::BuildingNames& building, uint8_t upgradeToLevel) const;

    /**
     * Gets the cost of upgrading a building to a level.
     * @param building
     * @param upgradeToLevel
     * @return Amount of resources that upgrade will cost.
     */
    Resources getBuildingCost(const TW_ENUMS::BuildingNames& building, const uint8_t upgradeToLevel);

    /**
     * Gets the amount of resources that will be produced in a hour.
     * @param buildingLevel Level of a production building.
     * @return Amount of resources/hour.
     */
    double getResourceProduction(uint8_t buildingLevel) const;

    uint32_t getMaxStorage(uint8_t storageLevel) const;
    uint16_t getMaxPopulation(uint8_t farmLevel) const;
    void createNewVillage();
    void developVillage();

private:
    GameManager();

    std::vector<std::shared_ptr<Village>> villages;  ///< Vector of the users villages.
    std::shared_ptr<Village> currentVillage;         ///< Pointer to the current village that is being displayed.

    tinyxml2::XMLDocument buildingData;
    tinyxml2::XMLDocument troopData;
    tinyxml2::XMLDocument templateData;

    ImageRecognition imageParser;
    VillageBuilder villageBuilder;

    static GameManager instance;
};

#endif /* GAMEMANAGER_HPP_ */
