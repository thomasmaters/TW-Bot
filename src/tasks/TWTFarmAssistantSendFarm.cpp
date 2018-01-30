/*
 * TWTFarmAssistantSendFarm.cpp
 *
 *  Created on: 26 aug. 2017
 *      Author: Thomas
 */

#include "TWTFarmAssistantSendFarm.hpp"

#include "../BotManager.hpp"
#include "../GameManager.hpp"
#include "../Mouse.hpp"
#include "../TW_Enums.hpp"

#include "TWTGotoNavigation.hpp"

TWT_FarmAssistantSendFarm::TWT_FarmAssistantSendFarm(const TW_ENUMS::FarmAssistantTemplates& aFarmTemplate, uint8_t aAmountOfFarmsToSend)
  : farmTemplate(aFarmTemplate), amountOfFarmsToSend(aAmountOfFarmsToSend)
{
}

void TWT_FarmAssistantSendFarm::preBotTask() const
{
    BotManager::getInstance().addTask(std::shared_ptr<TW_Task>(new TWT_GotoNavigation(TW_ENUMS::NavigationNames::FARM_ASSISTANT)));
}

void TWT_FarmAssistantSendFarm::executeBotTask() const
{
    try
    {
        std::vector<cv::Rect> templatePos =
          GameManager::getInstance().getTemplatePositionsOnScreen("farm", TW_ENUMS::enumToFATemplate(farmTemplate), 10);

        for (cv::Rect& a : templatePos)
        {
            Mouse::moveMouse(a);
            Mouse::mouseClick();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << __PRETTY_FUNCTION__ << e.what() << std::endl;
    }
}

void TWT_FarmAssistantSendFarm::postBotTask() const
{
    BotManager::getInstance().addTask(std::shared_ptr<TW_Task>(new TWT_GotoNavigation(TW_ENUMS::NavigationNames::OVERVIEW)));
}

TWT_FarmAssistantSendFarm::~TWT_FarmAssistantSendFarm()
{
}
