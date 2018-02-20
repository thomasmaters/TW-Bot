/*
 * GameManager.cpp
 *
 *  Created on: 15 jan. 2017
 *      Author: Thomas Maters
 */

#include "GameManager.hpp"
#include "BotManager.hpp"
#include "Screen.hpp"
#include "tasks/TWTGotoBuilding.hpp"
#include "tasks/TWTGotoNextVillage.hpp"
#include "tasks/TWTResearchUnit.hpp"
#include "tasks/TWTUpgradeBuilding.hpp"

#include <fstream>
#include <iostream>

GameManager& GameManager::getInstance()
{
    static GameManager instance;
    return instance;
}

cv::Rect GameManager::getBuildingPositionOnScreen(const enum TW_ENUMS::BuildingNames& aBuildingName)
{
    std::cout << __PRETTY_FUNCTION__ << " " << TW_ENUMS::enumToBuildingName(aBuildingName) << std::endl;
    std::string buildingString     = TW_ENUMS::enumToBuildingName(aBuildingName);
    tinyxml2::XMLElement* building = templateData.FirstChildElement("buildings")->FirstChildElement(buildingString.c_str());

    uint8_t level = currentVillage->getBuildingLevel(aBuildingName);

    for (tinyxml2::XMLElement* child = building->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
    {
        if (level >= std::atoi(child->Attribute("minLevel")) && level <= std::atoi(child->Attribute("maxLevel")))
        {
            std::cout << "Finding building template: " << child->GetText() << std::endl;
            return getTemplatePositionOnScreen(child->GetText(), 0.75);
        }
    }

    // We could not find our template. This shouldn't happen.
    throw std::runtime_error("Could not get building position on screen.");
}

std::vector<cv::Rect> GameManager::getTemplatePositionsOnScreen(const std::string& aParent, const std::string& aChild, uint8_t amountOfResults)
{
    tinyxml2::XMLElement* xmlElement = templateData.FirstChildElement(aParent.c_str())->FirstChildElement(aChild.c_str());
    return imageParser.matchTemplates("screenshot.bmp", xmlElement->GetText(), amountOfResults, 5, 0.75);
}


cv::Rect GameManager::getTemplatePositionOnScreen(const std::string& aParent, const std::string& aChild)
{
    tinyxml2::XMLElement* xmlElement = templateData.FirstChildElement(aParent.c_str())->FirstChildElement(aChild.c_str());
    return getTemplatePositionOnScreen(xmlElement->GetText());
}

cv::Rect GameManager::getTemplatePositionOnScreen(const std::string& aTemplate, double matchingFactor)
{
    return imageParser.matchTemplate("screenshot.bmp", aTemplate, 5, matchingFactor);
}

/************************************
 * Event Handlers
 *************************************/
void GameManager::OnUpgradeStartedEvent(const TWE_BuildingUpgradeStarted& event)
{
}

void GameManager::OnUpgradeFinishedEvent(const TWE_BuildingUpgradeFinished& event)
{
}

/*************************************
 *
 *************************************/

GameManager::GameManager()
{
    // Attach event handlers.
    BotManager::getInstance().TWE_BuildingUpgradeStartedHandler.connect(boost::bind(&GameManager::OnUpgradeStartedEvent, this, _1));
    BotManager::getInstance().TWE_BuildingUpgradeFinishedHandler.connect(boost::bind(&GameManager::OnUpgradeFinishedEvent, this, _1));

    try
    {
        // Load some default tribalwars data.
        buildingData.LoadFile("interface.xml");
        troopData.LoadFile("troops.xml");

        // Load some other data.
        templateData.LoadFile("templates.xml");
    }
    catch (std::exception& e)
    {
        std::cerr << __PRETTY_FUNCTION__ << ": " << e.what() << std::endl;
    }
}

// https://forum.tribalwars.us/index.php?threads/guide-building-formulas.389/
double GameManager::getBuildingTime(const TW_ENUMS::BuildingNames& building, uint8_t upgradeToLevel, uint8_t mainBuildingLevel) const
{
    if (upgradeToLevel <= 3)
    {
        return 10 + (upgradeToLevel - 1) * 50;
    }

    const tinyxml2::XMLElement* buildingXMLNode = buildingData.FirstChild()->FirstChildElement(TW_ENUMS::enumToBuildingName(building).c_str());

    std::string build_time = buildingXMLNode->FirstChildElement("build_time")->GetText();
    double buildTime       = std::atof(build_time.c_str());

    // [build_time]*1.05^(-[level of the village headquarters])*2,1*1,18^(level - 1 - 35/(level-1))
    return buildTime * std::pow(1.05, -mainBuildingLevel) * 2.1 * std::pow(1.18, ((double)upgradeToLevel - 1 - 35.0 / (upgradeToLevel - 1)));
}

double GameManager::getTroopBuildTime(const TW_ENUMS::TroopNames& troop, uint8_t recruitmentBuildingLevel) const
{
    const tinyxml2::XMLElement* buildingXMLNode = troopData.FirstChild()->FirstChildElement(TW_ENUMS::enumToTroopName(troop).c_str());

    std::string build_time = buildingXMLNode->FirstChildElement("build_time")->GetText();
    double buildTime       = std::atof(build_time.c_str());
    if (troop == TW_ENUMS::TroopNames::KNIGHT)
    {
        return buildTime;
    }

    return (double)2 / 3 * buildTime * std::pow(1.06, -recruitmentBuildingLevel);
}

uint32_t GameManager::getPopulationCost(const TW_ENUMS::BuildingNames& building, uint8_t upgradeToLevel) const
{
    const tinyxml2::XMLElement* buildingXMLElement = buildingData.FirstChild()->FirstChildElement(TW_ENUMS::enumToBuildingName(building).c_str());

    int pop       = std::atoi(buildingXMLElement->FirstChildElement("pop")->GetText());
    int popFactor = std::atoi(buildingXMLElement->FirstChildElement("pop_factor")->GetText());

    return (double)pop * std::pow(popFactor, upgradeToLevel - 1);
}

Resources GameManager::getBuildingCost(const TW_ENUMS::BuildingNames& building, const uint8_t level)
{
    try
    {
        const tinyxml2::XMLElement* buildingXMLElement = buildingData.FirstChild()->FirstChildElement(TW_ENUMS::enumToBuildingName(building).c_str());

        double baseWood    = std::atof(buildingXMLElement->FirstChildElement("wood")->GetText());
        double baseStone   = std::atof(buildingXMLElement->FirstChildElement("stone")->GetText());
        double baseIron    = std::atof(buildingXMLElement->FirstChildElement("iron")->GetText());
        double woodFactor  = std::atof(buildingXMLElement->FirstChildElement("wood_factor")->GetText());
        double stoneFactor = std::atof(buildingXMLElement->FirstChildElement("stone_factor")->GetText());
        double ironFactor  = std::atof(buildingXMLElement->FirstChildElement("iron_factor")->GetText());

        return Resources(baseWood * std::pow(woodFactor, level - 1), baseStone * std::pow(stoneFactor, level - 1),
                         baseIron * std::pow(ironFactor, level - 1));
    }
    catch (std::exception& e)
    {
        std::cerr << __PRETTY_FUNCTION__ << ": " << e.what() << std::endl;
    }

    return Resources(0, 0, 0);
}

double GameManager::getResourceProduction(uint8_t buildingLevel) const
{
    return 30 * std::pow(1.163118, buildingLevel - 1) * gameSpeed;
}

uint32_t GameManager::getMaxStorage(uint8_t storageLevel) const
{
    return std::round(1000 * std::pow(1.2294934, storageLevel - 1));
}

uint16_t GameManager::getMaxPopulation(uint8_t farmLevel) const
{
    return std::round(240 * std::pow(1.172103, farmLevel - 1));
}

/*************************************
 *
 *************************************/

void GameManager::createNewVillage()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    // Start by processing the village into memory.
    villages.push_back(std::shared_ptr<Village>(new Village()));

    // Set the current village.
    currentVillage = villages.front();
}

void GameManager::developVillage()
{
    villageBuilder.developVillage(currentVillage);
}

GameManager::~GameManager()
{
}
