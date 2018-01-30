#include "TWTReadVillageData.hpp"

#include "../BotManager.hpp"
#include "../Keyboard.hpp"
#include "../Mouse.hpp"

#include "../../lib/json.hpp"

#include <string>

TWT_ReadVillageData::TWT_ReadVillageData()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

bool TWT_ReadVillageData::executeBotTask() const
{
    Keyboard::pressKey(VK_F12);
    Mouse::moveMouse((POINT){ 1800, 150 });
    Mouse::mouseClick();
    Keyboard::holdKey(VK_LCONTROL);
    Keyboard::pressCharKey('f');
    Keyboard::releaseKey(VK_LCONTROL);
    Keyboard::typeString("updategamedata");
    Keyboard::pressKey(VK_EXECUTE);
    Mouse::mouseClick();
    Keyboard::pressKey(VK_RETURN);
    Keyboard::holdKey(VK_LCONTROL);
    Keyboard::pressCharKey('c');
    Keyboard::releaseKey(VK_LCONTROL);
    Keyboard::pressKey(VK_F12);

    // Try parsing clipboard data.
    nlohmann::json villageData;
    try
    {
        // Get the text from the clipboard.
        std::string clipboardText = Keyboard::getClipBoardText();

        // Find the gamedata array.
        std::size_t jsonDataStart = clipboardText.find("updateGameData(");
        std::size_t jsonDataEnd   = clipboardText.find("});", jsonDataStart);
        clipboardText             = clipboardText.substr(jsonDataStart + 15, jsonDataEnd + 1);
        jsonDataEnd               = clipboardText.find("});");
        clipboardText             = clipboardText.substr(0, jsonDataEnd + 1);

        // Try to parse it.
        villageData = nlohmann::json::parse(clipboardText);
        if (villageData.is_null())
        {
            throw std::runtime_error("Village data is empty!");
        }
        villageData.erase("player");
        std::cout << villageData << std::endl;
    }
    catch (const std::exception& e)
    {
        BotManager::getInstance().addEvent(std::shared_ptr<TW_Event>(new TWE_TaskFailed(shared_from_this(), e)));
        std::cerr << __PRETTY_FUNCTION__ << e.what() << std::endl;
        return false;
    }

    BotManager::getInstance().addEvent(std::shared_ptr<TW_Event>(new TWE_VillageDataParsed(villageData)));
    return true;
}

TWT_ReadVillageData::~TWT_ReadVillageData()
{
}
