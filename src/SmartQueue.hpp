/*
 * SmartQueue.hpp
 *
 *  Created on: 26 jan. 2017
 *      Author: Thomas
 */

#ifndef SMARTQUEUE_HPP_
#define SMARTQUEUE_HPP_

#include "Queue.hpp"

#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

template <class T>
class SmartQueue
{
public:
    SmartQueue()
    {
        eventLoopRunning = false;

        std::thread newEventLoopThread([this] { consumeEvents(); });
        eventLoopThread.swap(newEventLoopThread);
    }

    void addToQueue(const std::shared_ptr<T>& aEvent)
    {
        eventQueue.enqueue(aEvent);
        notifyEventLoop();
    }

    void setCallbackFunction(const std::function<void(std::shared_ptr<T>)>& aCallback)
    {
        callback = aCallback;
    }

    void scheduleEvent(const long aDelay, const std::shared_ptr<T>& aEvent)
    {
        scheduledEventsQueue.emplace_back(std::thread([this, aDelay, aEvent]() {
            std::cout << "Thread paused: " << std::this_thread::get_id() << std::endl;
            // Let thread sleep and add an event when it wakes again.
            std::this_thread::sleep_for(std::chrono::milliseconds(aDelay));
            std::cout << "Thread resumed: " << std::this_thread::get_id() << std::endl;
            addToQueue(aEvent);

            // Let the thread find and detach itself.
            for (std::thread& thread : scheduledEventsQueue)
            {
                if (thread.get_id() == std::this_thread::get_id())
                {
                    thread.detach();
                }
            }
        }));
    }

    virtual ~SmartQueue(){};

private:
    /*
     * Function that signals the event loop there is some work to do.
     */
    void notifyEventLoop()
    {
        eventLoopRunning = true;
        eventLoopCondition.notify_one();
    }

    /*
     * Handles events from event queue.
     */
    void consumeEvents()
    {
        while (1)
        {
            std::cout << "EVENTLOOP RUNNING. AMOUND SCHEDULED EVENTS: " << scheduledEventsQueue.size() << std::endl;
            // Do we have events in our queue?
            if (eventQueue.size() > 0)
            {
                std::cout << "SOMETHING IN THE QUEUE" << std::endl;
                // If we have a callback given trigger it. Remove it from memory otherwise.
                if (callback)
                {
                    std::cout << "CALLING CALLBACK." << std::endl;
                    callback(eventQueue.dequeue());
                }
                else
                {
                    std::cout << "NO CALLBACK SPECIFIED" << std::endl;
                    eventQueue.dequeue();
                }

                // TODO fix deze functie
                //                cleanScheduledEventThreads();
            }
            else
            {
                std::cout << "PAUSING QUEUE." << std::endl;
                // Stop looping and wait until something signals the eventloop to run again.
                eventLoopRunning = false;
                std::unique_lock<std::mutex> lk(eventLoopMutex);
                eventLoopCondition.wait(lk, [this] { return eventLoopRunning; });
            }
        }
        std::cout << "worker stopped" << std::endl;
    }

    /*
     * Cleans finished threads from scheduled events vector.
     */
    void cleanScheduledEventThreads()
    {
        // Do we have scheduled event threads that have depatched there event and
        // are ready to be cleaned.
        if (scheduledEventsQueue.size() == 0)
        {
            return;
        }

        for (std::size_t i = scheduledEventsQueue.size() - 1; i >= 0; --i)
        {
            // Is event finished? Delete the event.
            if (!scheduledEventsQueue[i].joinable())
            {
                scheduledEventsQueue.erase(scheduledEventsQueue.begin() + i);
                break;
            }
        }
    }

    /**************************************************************
     **************************************************************
     **************************************************************/

    // Event queue and a vector of scheduled events, that dispatch there event at a later point in time.
    SafeQueue<std::shared_ptr<T> > eventQueue;
    std::vector<std::thread> scheduledEventsQueue;

    // Callback function.
    std::function<void(std::shared_ptr<T>)> callback;
    // Bool to trigger eventloop can run.
    bool eventLoopRunning;

    // Thread stuff.
    std::thread eventLoopThread;
    std::condition_variable eventLoopCondition;
    std::mutex eventLoopMutex;
};

#endif /* SMARTQUEUE_HPP_ */
