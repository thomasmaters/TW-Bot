/*
 * TWETaskFailed.hpp
 *
 *  Created on: 30 jan. 2018
 *      Author: Thomas Maters
 */

#ifndef TWETASKFAILED_HPP_
#define TWETASKFAILED_HPP_

#include "TWEvent.hpp"

class TWE_TaskFailed : public TW_Event
{
public:
    explicit TWE_TaskFailed() : TW_Event()
    {
    }

    virtual ~TWE_TaskFailed()
    {
    }

private:
};


#endif /* TWETASKFAILED_HPP_ */
