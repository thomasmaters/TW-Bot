/*
 * TWETaskFailed.hpp
 *
 *  Created on: 30 jan. 2018
 *      Author: Thomas Maters
 */

#ifndef TWETASKFAILED_HPP_
#define TWETASKFAILED_HPP_

#include "../BotManager.hpp"
#include "../tasks/TWTask.hpp"
#include "TWEvent.hpp"

class TWE_TaskFailed : public TW_Event
{
public:
    explicit TWE_TaskFailed(std::shared_ptr<const TW_Task> task, const std::exception& reason) : TW_Event(), task(task), reason(reason)
    {
        std::cout << "Task shared pointer is owned by: " << task.use_count() << " objects." << std::endl;
    }

    virtual ~TWE_TaskFailed()
    {
    }

    std::shared_ptr<const TW_Task> task;
    std::exception reason;
};


#endif /* TWETASKFAILED_HPP_ */
