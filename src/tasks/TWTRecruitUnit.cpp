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
    else if (unit == TW_ENUMS::TroopNames::KNIGHT)
    {
        return BotManager::getInstance().executeSubTask(std::shared_ptr<TW_Task>(new TWT_GotoBuilding(TW_ENUMS::BuildingNames::STATUE)));
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
        if (unit == TW_ENUMS::TroopNames::KNIGHT)
        {
            recruitKnight();
        }
        else
        {
            cv::Rect templatePos = GameManager::getInstance().getTemplatePositionOnScreen("recruit", TW_ENUMS::enumToTroopName(unit));

            // Move mouse to the input box.
            templatePos.x += RECRUIT_INPUT_OFFSET_X;
            templatePos.y += RECRUIT_INPUT_OFFSET_Y;

            Mouse::moveMouse(cv::Rect(templatePos.x, templatePos.y, RECRUIT_INPUT_SIZE_X, RECRUIT_INPUT_SIZE_Y));
            Mouse::mouseClick();

            Keyboard::typeString(std::to_string(amountOfUnits));
            Keyboard::pressKey(VK_RETURN);
        }

        // Calculate the time needed for recruiting the amount of troops.
        double recruitmentTime;
        if (unit == TW_ENUMS::TroopNames::AXE || unit == TW_ENUMS::TroopNames::SPEAR || unit == TW_ENUMS::TroopNames::SWORD)
        {
            recruitmentTime = GameManager::getInstance().getTroopBuildTime(unit, village->getBuildingLevel(TW_ENUMS::BuildingNames::BARRACKS));
        }
        else
        {
            recruitmentTime = GameManager::getInstance().getTroopBuildTime(unit, village->getBuildingLevel(TW_ENUMS::BuildingNames::STABLE));
        }

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

void TWT_RecruitUnit::recruitKnight() const
{
    Mouse::moveMouse(GameManager::getInstance().getTemplatePositionOnScreen("recruit", TW_ENUMS::enumToTroopName(unit)));
    Mouse::mouseClick();

    // Sleep the thread so the browser can catchup.
    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    // We now have 2 recruitment buttons, get them both
    std::vector<cv::Rect> templatePositions = GameManager::getInstance().getTemplatePositionsOnScreen("recruit", TW_ENUMS::enumToTroopName(unit), 2);

    // Click the template that is more to the right of the screen.
    bool templateToSelect = templatePositions.at(0).x < templatePositions.at(1).x;
    Mouse::moveMouse(cv::Rect(templatePositions.at(templateToSelect).x, templatePositions.at(templateToSelect).y + RECRUIT_KNIGHT_INPUT_OFFSET_Y,
                              RECRUIT_INPUT_SIZE_X, RECRUIT_INPUT_SIZE_Y));
    Mouse::mouseClick();

    // TODO Knight name in config file
    Keyboard::typeString("Jan Hendrik");
    Keyboard::pressKey(VK_RETURN);
}

bool TWT_RecruitUnit::postBotTask() const
{
    return BotManager::getInstance().executeSubTask(std::shared_ptr<TW_Task>(new TWT_GotoNavigation(TW_ENUMS::NavigationNames::OVERVIEW)));
}

TWT_RecruitUnit::~TWT_RecruitUnit()
{
}
