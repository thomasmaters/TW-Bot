/*
 * TWEUnitRecruitmentFinished.hpp
 *
 *  Created on: 29 aug. 2017
 *      Author: Thomas
 */

#ifndef TWEUNITRECRUITMENTFINISHED_HPP_
#define TWEUNITRECRUITMENTFINISHED_HPP_

#include "TWEvent.hpp"

class TWE_UnitRecruitmentFinished : public TW_Event
{
public:
    TWE_UnitRecruitmentFinished(const TW_ENUMS::TroopNames& aUnit, const uint32_t aAmountOfUnits, const uint32_t aVillageID)
      : TW_Event(), unit(aUnit), amountOfUnits(aAmountOfUnits), villageID(aVillageID)
    {
    }

    virtual ~TWE_UnitRecruitmentFinished()
    {
    }

    TW_ENUMS::TroopNames unit;
    uint32_t amountOfUnits;
    uint32_t villageID;

private:
};


#endif /* TWEUNITRECRUITMENTFINISHED_HPP_ */
