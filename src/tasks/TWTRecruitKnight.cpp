/*
 * TWTRecruitKnight.cpp
 *
 *  Created on: 14 feb. 2018
 *      Author: Thomas Maters
 */
#include "../BotManager.hpp"
#include "../GameManager.hpp"
#include "../Mouse.hpp"

#include "TWTGotoBuilding.hpp"
#include "TWTGotoNavigation.hpp"
#include "TWTRecruitKnight.hpp"


TWT_RecruitKnight::TWT_RecruitKnight()
{
}

bool TWT_RecruitKnight::preBotTask() const
{
    return BotManager::getInstance().executeSubTask(std::shared_ptr<TW_Task>(new TWT_GotoBuilding(TW_ENUMS::BuildingNames::STATUE)));
}

bool TWT_RecruitKnight::executeBotTask() const
{
    try
    {
        cv::Rect templatePos =
          GameManager::getInstance().getTemplatePositionOnScreen("recruit", TW_ENUMS::enumToTroopName(TW_ENUMS::TroopNames::KNIGHT));

        Mouse::moveMouse(templatePos);
        Mouse::mouseClick();
        return true;
    }
    catch (std::exception& e)
    {
        std::cerr << __PRETTY_FUNCTION__ << ": " << e.what() << std::endl;
    }
    return false;
}

bool TWT_RecruitKnight::postBotTask() const
{
    return BotManager::getInstance().executeSubTask(std::shared_ptr<TW_Task>(new TWT_GotoNavigation(TW_ENUMS::NavigationNames::OVERVIEW)));
}

TWT_RecruitKnight::~TWT_RecruitKnight()
{
}
