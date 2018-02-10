#include "TWTUpgradeBuilding.hpp"

#include "../BotManager.hpp"
#include "../GameManager.hpp"
#include "../Keyboard.hpp"
#include "../Mouse.hpp"
#include "TWTGotoBuilding.hpp"
#include "TWTGotoNavigation.hpp"

TWT_UpgradeBuilding::TWT_UpgradeBuilding(const std::shared_ptr<Village>& village, const TW_ENUMS::BuildingNames& building, const std::string& csrf)
  : village(village), building(building), csrf(csrf)
{
}

bool TWT_UpgradeBuilding::preBotTask() const
{
    return BotManager::getInstance().executeSubTask(std::shared_ptr<TW_Task>(new TWT_GotoBuilding(TW_ENUMS::BuildingNames::MAIN)));
}

bool TWT_UpgradeBuilding::executeBotTask() const
{
    try
    {
        std::cout << __PRETTY_FUNCTION__ << ": " << TW_ENUMS::enumToBuildingName(building) << std::endl;
        // Can we start the upgrade for sure?
        // TODO something is wrong with this check.
        //        if (!village->hasEnoughResources(GameManager::getInstance().getBuildingCost(building, village->getBuildingLevel(building) + 1)) ||
        //            !village->hasEnoughPopulation(GameManager::getInstance().getPopulationCost(building, village->getBuildingLevel(building) + 1)))
        //        {
        //            throw std::runtime_error("Not enough resources or population.");
        //        }

        Keyboard::holdKey(VK_CONTROL);
        Keyboard::pressCharKey('l');
        Keyboard::releaseKey(VK_CONTROL);
        Keyboard::typeString("https://" + village->getWorld() + ".tribalwars.nl/game.php?village=" + std::to_string(village->getVillageId()) +
                             "&screen=main&action=upgrade_building&id=" + TW_ENUMS::enumToBuildingName(building) + "&type=main&h=" + csrf);
        Keyboard::pressKey(VK_RETURN);

        // Get some variables to calculate building time.
        uint8_t mainLevel  = village->getBuildingLevel(TW_ENUMS::BuildingNames::MAIN);
        uint8_t buildLevel = village->getBuildingLevel(building) + 1;
        double buildTime   = GameManager::getInstance().getBuildingTime(building, buildLevel, mainLevel) * 1000;

        BotManager::getInstance().scheduleEvent(
          buildTime, std::shared_ptr<TW_Event>(new TWE_BuildingUpgradeFinished(building, village->getVillageId(), buildLevel)));
        BotManager::getInstance().addEvent(std::shared_ptr<TW_Event>(new TWE_BuildingUpgradeStarted(building, village->getVillageId())));
    }
    catch (const std::exception& e)
    {
        BotManager::getInstance().addEvent(std::shared_ptr<TW_Event>(new TWE_TaskFailed(shared_from_this(), e)));
        return false;
    }
    return true;
}

bool TWT_UpgradeBuilding::postBotTask() const
{
    return BotManager::getInstance().executeSubTask(std::shared_ptr<TW_Task>(new TWT_GotoNavigation(TW_ENUMS::NavigationNames::OVERVIEW)));
}

TWT_UpgradeBuilding::~TWT_UpgradeBuilding()
{
}
