/*
 * BotManager.cpp
 *
 *  Created on: 27 nov. 2016
 *      Author: Thomas
 */

#include "BotManager.hpp"

#include <iostream>

BotManager& BotManager::getInstance()
{
    static BotManager instance;
    return instance;
}

void BotManager::startBotManager()
{
    eventQueue.setCallbackFunction([](std::shared_ptr<TW_Event> b) { BotManager::getInstance().handleEvent(b); });
    taskQueue.setCallbackFunction([](std::shared_ptr<TW_Task> b) { BotManager::getInstance().handleTask(b); });
}

void BotManager::addEvent(const std::shared_ptr<TW_Event>& aEvent)
{
    std::cerr << "Event added: " << typeid(*aEvent).name() << std::endl;
    eventQueue.addToQueue(aEvent);
}

void BotManager::scheduleEvent(const uint32_t aDelay, const std::shared_ptr<TW_Event>& aEvent)
{
    std::cerr << "Event scheduled: " << typeid(*aEvent).name() << " Dispatched in " << aDelay << " ms." << std::endl;
    eventQueue.scheduleEvent(aDelay, aEvent);
}

void BotManager::handleEvent(const std::shared_ptr<TW_Event>& aEvent) const
{
    std::cerr << "Handling event: " << typeid(*aEvent).name() << std::endl;

    if (typeid(*aEvent) == typeid(TWE_VillageDataParsed))
    {
        TWE_VillageDataParsed& a = dynamic_cast<TWE_VillageDataParsed&>(*aEvent);
        TWE_VillageDataParsedHandler(a);
    }
    if (typeid(*aEvent) == typeid(TWE_TroopDataParsed))
    {
        TWE_TroopDataParsed& a = dynamic_cast<TWE_TroopDataParsed&>(*aEvent);
        TWE_TroopDataParsedHandler(a);
    }
    if (typeid(*aEvent) == typeid(TWE_BuildingUpgradeStarted))
    {
        TWE_BuildingUpgradeStarted& a = dynamic_cast<TWE_BuildingUpgradeStarted&>(*aEvent);
        TWE_BuildingUpgradeStartedHandler(a);
    }
    if (typeid(*aEvent) == typeid(TWE_BuildingUpgradeFinished))
    {
        TWE_BuildingUpgradeFinished& a = dynamic_cast<TWE_BuildingUpgradeFinished&>(*aEvent);
        TWE_BuildingUpgradeFinishedHandler(a);
    }
    if (typeid(*aEvent) == typeid(TWE_UnitResearchStarted))
    {
        TWE_UnitResearchStarted& a = dynamic_cast<TWE_UnitResearchStarted&>(*aEvent);
        TWE_UnitResearchStartedHandler(a);
    }
    if (typeid(*aEvent) == typeid(TWE_UnitResearchFinished))
    {
        TWE_UnitResearchFinished& a = dynamic_cast<TWE_UnitResearchFinished&>(*aEvent);
        TWE_UnitResearchFinishedHandler(a);
    }
    if (typeid(*aEvent) == typeid(TWE_UnitRecruitmentStarted))
    {
        TWE_UnitRecruitmentStarted& a = dynamic_cast<TWE_UnitRecruitmentStarted&>(*aEvent);
        TWE_UnitRecruitmentStartedHandler(a);
    }
    if (typeid(*aEvent) == typeid(TWE_UnitRecruitmentFinished))
    {
        TWE_UnitRecruitmentFinished& a = dynamic_cast<TWE_UnitRecruitmentFinished&>(*aEvent);
        TWE_UnitRecruitmentFinishedHandler(a);
    }
}

void BotManager::addTask(const std::shared_ptr<TW_Task>& aTask)
{
    std::cerr << "Task added: " << typeid(*aTask).name() << std::endl;
    taskQueue.addToQueue(aTask);
}

void BotManager::scheduleTask(const uint32_t aDelay, const std::shared_ptr<TW_Task>& aTask)
{
    std::cerr << "Task scheduled: " << typeid(*aTask).name() << "Dispatched in " << aDelay << " ms." << std::endl;
    taskQueue.scheduleEvent(aDelay, aTask);
}

void BotManager::handleTask(const std::shared_ptr<TW_Task>& aTask) const
{
    std::cerr << "Handling task: " << typeid(*aTask).name() << std::endl;
    aTask->preBotTask();
    aTask->executeBotTask();
    aTask->postBotTask();
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
}

void BotManager::executeSubTask(const std::shared_ptr<TW_Task>& aEvent) const
{
    handleTask(aEvent);
}

BotManager::~BotManager()
{
}
