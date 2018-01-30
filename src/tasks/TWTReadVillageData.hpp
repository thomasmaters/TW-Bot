/*
 * TaskGetVillageData.hpp
 *
 *  Created on: 28 jan. 2017
 *      Author: Thomas
 */

#ifndef TWTREADVILLAGEDATA_HPP_
#define TWTREADVILLAGEDATA_HPP_

#include "TWTask.hpp"

class TWT_ReadVillageData : public TW_Task
{
public:
    TWT_ReadVillageData();

    bool executeBotTask() const;

    virtual ~TWT_ReadVillageData();
};
#endif /* TWTREADVILLAGEDATA_HPP_ */
