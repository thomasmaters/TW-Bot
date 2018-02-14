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
#include "events/TWETaskFailed.hpp"
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

    /**
     * Adds an event to the back of the queue.
     * @param aEvent
     */
    void addEvent(const std::shared_ptr<TW_Event>& aEvent);

    /**
     * Schedules a event to be added to the queue.
     * @param aDelay in miliseconds.
     * @param aEvent
     */
    void scheduleEvent(const uint32_t aDelay, const std::shared_ptr<TW_Event>& aEvent);

    /**
     * Adds a task to the back of the queue.
     * @param aTask
     */
    void addTask(const std::shared_ptr<TW_Task>& aTask);

    /**
     * Schedules a task to be added to the queue.
     * @param aDelay Delay in miliseconds.
     * @param aTask
     */
    void scheduleTask(const uint32_t aDelay, const std::shared_ptr<TW_Task>& aTask);

    /**
     * Imiditly executes a task.
     * @param aEvent
     * @return True if executed correctly.
     */
    bool executeSubTask(const std::shared_ptr<TW_Task>& aEvent) const;

    virtual ~BotManager();

protected:
    /**
     * Starts the handling of an event.
     * @param aEvent
     */
    void handleEvent(const std::shared_ptr<TW_Event>& aEvent) const;

    /**
     * Starts the execution of a task.
     * @param aTask
     * @return True if executed correctly.
     */
    bool handleTask(const std::shared_ptr<TW_Task>& aTask) const;

private:
    BotManager()
    {
    }

    SmartQueue<TW_Event> eventQueue;
    SmartQueue<TW_Task> taskQueue;

    static BotManager instance;
};


#endif /* BOTMANAGER_HPP_ */
