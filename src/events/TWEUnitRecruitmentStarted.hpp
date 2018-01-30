/*
 * TWEUnitRecruitmentStarted.hpp
 *
 *  Created on: 29 aug. 2017
 *      Author: Thomas
 */

#ifndef TWEUNITRECRUITMENTSTARTED_HPP_
#define TWEUNITRECRUITMENTSTARTED_HPP_

#include "TWEvent.hpp"

class TWE_UnitRecruitmentStarted : public TW_Event
{
public:
    TWE_UnitRecruitmentStarted(const TW_ENUMS::TroopNames& aUnit, const uint32_t aAmountOfUnits, const uint32_t aVillageID)
      : TW_Event(), unit(aUnit), amountOfUnits(aAmountOfUnits), villageID(aVillageID)
    {
    }

    virtual ~TWE_UnitRecruitmentStarted()
    {
    }

    TW_ENUMS::TroopNames unit;
    uint32_t amountOfUnits;
    uint32_t villageID;

private:
};


#endif /* TWEUNITRECRUITMENTSTARTED_HPP_ */
