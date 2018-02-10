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

bool TWT_ResearchUnit::preBotTask() const
{
    return BotManager::getInstance().executeSubTask(std::shared_ptr<TW_Task>(new TWT_GotoBuilding(TW_ENUMS::BuildingNames::SMITH)));
}

bool TWT_ResearchUnit::executeBotTask() const
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
        BotManager::getInstance().addEvent(std::shared_ptr<TW_Event>(new TWE_TaskFailed(shared_from_this(), e)));
        return false;
    }
    return true;
}

bool TWT_ResearchUnit::postBotTask() const
{
    if (BotManager::getInstance().executeSubTask(std::shared_ptr<TW_Task>(new TWT_GotoNavigation(TW_ENUMS::NavigationNames::OVERVIEW))))
    {
        BotManager::getInstance().addEvent(std::shared_ptr<TW_Event>(new TWE_UnitResearchStarted(unit, village->getVillageId())));
        return true;
    }
    return false;
}

TWT_ResearchUnit::~TWT_ResearchUnit()
{
}
