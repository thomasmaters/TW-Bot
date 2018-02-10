#include "TWTGotoNavigation.hpp"

#include "../BotManager.hpp"
#include "../GameManager.hpp"
#include "../Mouse.hpp"

TWT_GotoNavigation::TWT_GotoNavigation(const enum TW_ENUMS::NavigationNames& gotoLocation) : location(gotoLocation)
{
}

bool TWT_GotoNavigation::executeBotTask() const
{
    try
    {
        std::cout << __PRETTY_FUNCTION__ << ": " << TW_ENUMS::enumToNavName(location) << std::endl;
        cv::Rect a = GameManager::getInstance().getTemplatePositionOnScreen("nav", TW_ENUMS::enumToNavName(location));
        Mouse::moveMouse(a);
        Mouse::mouseClick();
    }
    catch (std::exception& e)
    {
        BotManager::getInstance().addEvent(std::shared_ptr<TW_Event>(new TWE_TaskFailed(shared_from_this(), e)));
        return false;
    }
    return true;
}

TWT_GotoNavigation::~TWT_GotoNavigation()
{
}
