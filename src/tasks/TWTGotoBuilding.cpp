#include "TWTGotoBuilding.hpp"

#include "../BotManager.hpp"
#include "../GameManager.hpp"
#include "../Mouse.hpp"
#include "../events/TWETaskFailed.hpp"

#include <opencv2/core/types.hpp>

TWT_GotoBuilding::TWT_GotoBuilding(const enum TW_ENUMS::BuildingNames& gotoLocation) : location(gotoLocation)
{
}

bool TWT_GotoBuilding::executeBotTask() const
{
    try
    {
        std::cout << __PRETTY_FUNCTION__ << ": " << TW_ENUMS::enumToBuildingName(location) << std::endl;
        cv::Rect a = GameManager::getInstance().getBuildingPositionOnScreen(location);
        Mouse::moveMouse(a);
        Mouse::mouseClick();
    }
    catch (std::exception& e)
    {
        BotManager::getInstance().addEvent(std::shared_ptr<TW_Event>(new TWE_TaskFailed(shared_from_this(), e)));
        std::cout << __PRETTY_FUNCTION__ << e.what() << std::endl;
        return false;
    }
    return true;
}

TWT_GotoBuilding::~TWT_GotoBuilding()
{
}
