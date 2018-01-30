/*
 * TWTFarmAssistantSendFarm.hpp
 *
 *  Created on: 26 aug. 2017
 *      Author: Thomas
 */

#ifndef TWTFARMASSISTANTSENDFARM_HPP_
#define TWTFARMASSISTANTSENDFARM_HPP_

#include "TWTask.hpp"

#include "../TW_Enums.hpp"

class TWT_FarmAssistantSendFarm : public TW_Task
{
public:
    TWT_FarmAssistantSendFarm(const TW_ENUMS::FarmAssistantTemplates& aFarmTemplate, uint8_t aAmountOfFarmsToSend);

    bool preBotTask() const;

    bool executeBotTask() const;

    bool postBotTask() const;

    virtual ~TWT_FarmAssistantSendFarm();

private:
    TW_ENUMS::FarmAssistantTemplates farmTemplate;
    uint8_t amountOfFarmsToSend;
};


#endif /* TWTFARMASSISTANTSENDFARM_HPP_ */
