/*
 * BotManager.hpp
 *
 *  Created on: 27 nov. 2016
 *      Author: Thomas
 */

#ifndef BOTMANAGER_HPP_
#define BOTMANAGER_HPP_

#include "Listener.hpp"
#include "SmartQueue.hpp"
#include "events/TWEBuildingUpgradeFinished.hpp"
#include "events/TWEBuildingUpgradeStarted.hpp"
#include "events/TWESwitchedToVillage.hpp"
#include "events/TWETroopDataParsed.hpp"
#include "events/TWEUnitRecruitmentFinished.hpp"
#include "events/TWEUnitRecruitmentStarted.hpp"
#include "events/TWEUnitResearchFinished.hpp"
#include "events/TWEUnitResearchStarted.hpp"
#include "events/TWEVillageDataParsed.hpp"
#include "events/TWEvent.hpp"
#include "tasks/TWTask.hpp"
#include "util/Singleton.hpp"

class BotManager : public Dispatcher, public Singleton
{
public:
    static BotManager& getInstance();

    void startBotManager();

    // Functions for adding and handling events.
    void addEvent(const std::shared_ptr<TW_Event>& aEvent);
    void scheduleEvent(const uint32_t aDelay, const std::shared_ptr<TW_Event>& aEvent);

    // Functions for adding and handling tasks.
    void addTask(const std::shared_ptr<TW_Task>& aTask);
    void scheduleTask(const uint32_t aDelay, const std::shared_ptr<TW_Task>& aTask);

    void executeSubTask(const std::shared_ptr<TW_Task>& aEvent) const;

    virtual ~BotManager();

protected:
    void handleEvent(const std::shared_ptr<TW_Event>& aEvent) const;
    void handleTask(const std::shared_ptr<TW_Task>& aTask) const;

private:
    BotManager()
    {
    }

    SmartQueue<TW_Event> eventQueue;
    SmartQueue<TW_Task> taskQueue;

    static BotManager instance;
};


#endif /* BOTMANAGER_HPP_ */
