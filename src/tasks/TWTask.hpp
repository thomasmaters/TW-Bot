/*
 * BotTasks.hpp
 *
 *  Created on: 12 jan. 2017
 *      Author: Thomas
 */

#ifndef TWTASK_HPP_
#define TWTASK_HPP_

class TW_Task
{
public:
    TW_Task(){};

    TW_Task& operator=(const TW_Task& other)
    {
        if (this != &other)
        {
        }
        return *this;
    }

    virtual void preBotTask() const
    {
    }
    virtual void executeBotTask() const = 0;
    virtual void postBotTask() const
    {
    }

    virtual ~TW_Task(){};
};

#endif /* TWTASK_HPP_ */
