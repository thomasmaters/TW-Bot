/*
 * TaskGetVillageData.hpp
 *
 *  Created on: 28 jan. 2017
 *      Author: Thomas
 */

#ifndef TWTREADTROOPDATA_HPP_
#define TWTREADTROOPDATA_HPP_

#include "TWTask.hpp"

class TWT_ReadTroopData : public TW_Task
{
public:
    TWT_ReadTroopData();

    void preBotTask() const;

    void executeBotTask() const;

    void postBotTask() const;

    virtual ~TWT_ReadTroopData();
};
#endif /* TWTREADTROOPDATA_HPP_ */
