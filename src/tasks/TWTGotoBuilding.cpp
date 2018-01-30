#include "TWTGotoBuilding.hpp"

#include "../GameManager.hpp"
#include "../Mouse.hpp"

#include <opencv2/core/types.hpp>

TWT_GotoBuilding::TWT_GotoBuilding(const enum TW_ENUMS::BuildingNames& gotoLocation) : location(gotoLocation)
{
}

void TWT_GotoBuilding::executeBotTask() const
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
        std::cout << __PRETTY_FUNCTION__ << e.what() << std::endl;
    }
}

TWT_GotoBuilding::~TWT_GotoBuilding()
{
}
