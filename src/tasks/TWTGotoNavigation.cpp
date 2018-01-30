#include "TWTGotoNavigation.hpp"

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
        std::cerr << __PRETTY_FUNCTION__ << e.what() << std::endl;
        return false;
    }
    return true;
}

TWT_GotoNavigation::~TWT_GotoNavigation()
{
}
