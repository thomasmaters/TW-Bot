#include "TWTResearchUnit.hpp"

#include "../BotManager.hpp"
#include "../GameManager.hpp"
#include "../Mouse.hpp"
#include "../Screen.hpp"
#include "../tasks/TWTGotoBuilding.hpp"
#include "../tasks/TWTGotoNavigation.hpp"

TWT_ResearchUnit::TWT_ResearchUnit(const TW_ENUMS::TroopNames aUnit, const std::shared_ptr<Village>& village) : unit(aUnit), village(village)
{
}

void TWT_ResearchUnit::preBotTask() const
{
    BotManager::getInstance().executeSubTask(std::shared_ptr<TW_Task>(new TWT_GotoBuilding(TW_ENUMS::BuildingNames::SMITH)));
}

void TWT_ResearchUnit::executeBotTask() const
{
    try
    {
        cv::Rect templatePos         = GameManager::getInstance().getTemplatePositionOnScreen("research", TW_ENUMS::enumToTroopName(unit));
        std::time_t researchDuration = village->getUnitResearchTime(unit);

        templatePos.x += RESEARCH_BUTTON_OFFSET_X;
        templatePos.y += RESEARCH_BUTTON_OFFSET_Y;

        Mouse::moveMouse(cv::Rect(templatePos.x, templatePos.y, RESEARCH_BUTTON_SIZE_X, RESEARCH_BUTTON_SIZE_Y));
        Mouse::mouseClick();

        BotManager::getInstance().scheduleEvent(researchDuration,
                                                std::shared_ptr<TW_Event>(new TWE_UnitResearchFinished(unit, village->getVillageId())));
    }
    catch (const std::exception& e)
    {
        std::cerr << __PRETTY_FUNCTION__ << e.what() << std::endl;
    }
}

void TWT_ResearchUnit::postBotTask() const
{
    BotManager::getInstance().executeSubTask(std::shared_ptr<TW_Task>(new TWT_GotoNavigation(TW_ENUMS::NavigationNames::OVERVIEW)));

    BotManager::getInstance().addEvent(std::shared_ptr<TW_Event>(new TWE_UnitResearchStarted(unit, village->getVillageId())));
}

TWT_ResearchUnit::~TWT_ResearchUnit()
{
}