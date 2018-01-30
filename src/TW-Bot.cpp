#include "BotManager.hpp"
#include "GameManager.hpp"

#include "events/TWESwitchedToVillage.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include <windows.h>

// TODO Verkijgen van troepen productie in dorp.
// TODO Sturen van farmen.
// TODO DONE Kijken of een upgrade kan aan de hand van de benodigde bevolking.
// TODO Alle dorpen ophalen dmv : https://nl57.tribalwars.nl/map/village.txt
// https://help.tribalwars.nl/wiki/Wereld_Data


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE P, LPSTR CMD, int nShowCmd)
{
    try
    {
        //        std::string toHashStrings[] = { "stable", "garage", "church", "church_f", "snob",    "smith", "place", "statue",    "market",
        //                                        "wood",   "stone",  "iron",   "farm",     "storage", "hide",  "wall",  "watchtower" };
        //        std::string toHashStrings[] = { "spear", "sword", "axe", "archer", "spy", "light", "heavy", "ram", "catapult", "knight", "nobel" };
        //        std::string toHashStrings[] = { "A", "B", "C" };
        //        for (std::string& a : toHashStrings)
        //        {
        //            std::cout << a << " -> " << std::hash<std::string>{}(a) << std::endl;
        //        }
        BotManager::getInstance().startBotManager();
        std::cout << GameManager::getInstance().getTroopBuildTime(TW_ENUMS::TroopNames::SPEAR, 2) << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        //        BotManager::getInstance().scheduleEvent(180000, std::shared_ptr<TW_Event>(new TWE_SwitchedToVillage()));
        GameManager::getInstance().createNewVillage();

        std::thread test([] {
            while (1)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        });
        test.join();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
