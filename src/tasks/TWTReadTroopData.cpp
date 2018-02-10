#include "TWTReadTroopData.hpp"

#include "../BotManager.hpp"
#include "../Keyboard.hpp"
#include "../Mouse.hpp"
#include "../tasks/TWTGotoBuilding.hpp"
#include "../tasks/TWTGotoNavigation.hpp"

#include "../../lib/json.hpp"

#include <string>

TWT_ReadTroopData::TWT_ReadTroopData()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

bool TWT_ReadTroopData::preBotTask() const
{
    return BotManager::getInstance().executeSubTask(std::shared_ptr<TW_Task>(new TWT_GotoBuilding(TW_ENUMS::BuildingNames::SMITH)));
}

// Before executing this task go to the smith.
bool TWT_ReadTroopData::executeBotTask() const
{
    Keyboard::pressKey(VK_F12);
    Mouse::moveMouse((POINT){ 1800, 150 });
    Mouse::mouseClick();
    Keyboard::holdKey(VK_LCONTROL);
    Keyboard::pressCharKey('f');
    Keyboard::releaseKey(VK_LCONTROL);
    Keyboard::typeString(".techs");
    Keyboard::pressKey(VK_EXECUTE);
    Mouse::mouseClick();
    Keyboard::pressKey(VK_F2);
    Keyboard::holdKey(VK_LCONTROL);
    Keyboard::pressCharKey('a');
    Keyboard::pressCharKey('c');
    Keyboard::releaseKey(VK_LCONTROL);
    Keyboard::pressKey(VK_F12);

    // Try parsing clipboard data.
    nlohmann::json troopData;
    try
    {
        // Get the text from the clipboard.
        std::string clipboardText = Keyboard::getClipBoardText();

        // Find the gamedata array.
        std::size_t jsonDataStart = clipboardText.find(".techs = ");
        std::size_t jsonDataEnd   = clipboardText.find("]};", jsonDataStart);
        clipboardText             = clipboardText.substr(jsonDataStart + 9, jsonDataEnd - jsonDataStart - 7);

        std::cout << clipboardText << std::endl;

        // Try to parse it.
        troopData = nlohmann::json::parse(clipboardText);
        if (troopData.is_null())
        {
            throw std::runtime_error("Troopdata is empty");
        }
    }
    catch (std::exception& e)
    {
        BotManager::getInstance().addEvent(std::shared_ptr<TW_Event>(new TWE_TaskFailed(shared_from_this(), e)));
        return false;
    }

    BotManager::getInstance().addEvent(std::shared_ptr<TW_Event>(new TWE_TroopDataParsed(troopData)));
    return true;
}

bool TWT_ReadTroopData::postBotTask() const
{
    return BotManager::getInstance().executeSubTask(std::shared_ptr<TW_Task>(new TWT_GotoNavigation(TW_ENUMS::NavigationNames::OVERVIEW)));
}

TWT_ReadTroopData::~TWT_ReadTroopData()
{
}
