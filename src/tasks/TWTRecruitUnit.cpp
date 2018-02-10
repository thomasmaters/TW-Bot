#include "TWTRecruitUnit.hpp"

#include "../BotManager.hpp"
#include "../GameManager.hpp"
#include "../Keyboard.hpp"
#include "../Mouse.hpp"
#include "../tasks/TWTGotoBuilding.hpp"
#include "../tasks/TWTGotoNavigation.hpp"

TWT_RecruitUnit::TWT_RecruitUnit(const std::shared_ptr<Village>& aVillage, const TW_ENUMS::TroopNames& aUnit, uint32_t aAmountOfUnits)
  : village(aVillage), unit(aUnit), amountOfUnits(aAmountOfUnits)
{
}

bool TWT_RecruitUnit::preBotTask() const
{
    if (unit == TW_ENUMS::TroopNames::AXE || unit == TW_ENUMS::TroopNames::SPEAR || unit == TW_ENUMS::TroopNames::SWORD)
    {
        return BotManager::getInstance().executeSubTask(std::shared_ptr<TW_Task>(new TWT_GotoBuilding(TW_ENUMS::BuildingNames::BARRACKS)));
    }
    else
    {
        return BotManager::getInstance().executeSubTask(std::shared_ptr<TW_Task>(new TWT_GotoBuilding(TW_ENUMS::BuildingNames::STABLE)));
    }
    return false;
}

bool TWT_RecruitUnit::executeBotTask() const
{
    try
    {
        cv::Rect templatePos = GameManager::getInstance().getTemplatePositionOnScreen("recruit", TW_ENUMS::enumToTroopName(unit));

        // Move mouse to the input box.
        templatePos.x += RECRUIT_INPUT_OFFSET_X;
        templatePos.y += RECRUIT_INPUT_OFFSET_Y;

        Mouse::moveMouse(cv::Rect(templatePos.x, templatePos.y, RECRUIT_INPUT_SIZE_X, RECRUIT_INPUT_SIZE_Y));
        Mouse::mouseClick();

        if (unit != TW_ENUMS::TroopNames::KNIGHT)
        {
            Keyboard::typeString(std::to_string(amountOfUnits));
            Keyboard::pressKey(VK_RETURN);
        }

        // Calculate the time needed for recruiting the amount of troops.
        double recruitmentTime;
        if (unit == TW_ENUMS::TroopNames::AXE || unit == TW_ENUMS::TroopNames::SPEAR || unit == TW_ENUMS::TroopNames::SWORD)
        {
            std::cout << "CALCULATING RECRUITMENT TIME" << std::endl;
            recruitmentTime = GameManager::getInstance().getTroopBuildTime(unit, village->getBuildingLevel(TW_ENUMS::BuildingNames::BARRACKS));
        }
        else
        {
            recruitmentTime = GameManager::getInstance().getTroopBuildTime(unit, village->getBuildingLevel(TW_ENUMS::BuildingNames::STABLE));
        }
        std::cout << "RECRUITMENT TIME CALCULATED" << std::endl;

        BotManager::getInstance().scheduleEvent(
          (uint32_t)recruitmentTime * 1000, std::shared_ptr<TW_Event>(new TWE_UnitRecruitmentFinished(unit, amountOfUnits, village->getVillageId())));
        BotManager::getInstance().addEvent(std::shared_ptr<TW_Event>(new TWE_UnitRecruitmentStarted(unit, amountOfUnits, village->getVillageId())));
    }
    catch (const std::exception& e)
    {
        BotManager::getInstance().addEvent(std::shared_ptr<TW_Event>(new TWE_TaskFailed(shared_from_this(), e)));
        return false;
    }
    return true;
}

bool TWT_RecruitUnit::postBotTask() const
{
    return BotManager::getInstance().executeSubTask(std::shared_ptr<TW_Task>(new TWT_GotoNavigation(TW_ENUMS::NavigationNames::OVERVIEW)));
}

TWT_RecruitUnit::~TWT_RecruitUnit()
{
}
