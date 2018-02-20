/*
 * TWTFarmAssistantSetTemplate.hpp
 *
 *  Created on: 26 aug. 2017
 *      Author: Thomas Maters
 */

#ifndef TWTFARMASSISTANTSETTEMPLATE_HPP_
#define TWTFARMASSISTANTSETTEMPLATE_HPP_

#include "TWTask.hpp"

class TWT_FarmAssistantSetTemplate : public TW_Task
{
public:
    TWT_FarmAssistantSetTemplate();

    bool executeBotTask() const
    {
        return true;
    }

    virtual ~TWT_FarmAssistantSetTemplate();
};


#endif /* TWTFARMASSISTANTSETTEMPLATE_HPP_ */
