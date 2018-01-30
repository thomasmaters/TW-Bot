/*
 * TWEUnitResearchFinished.hpp
 *
 *  Created on: 29 aug. 2017
 *      Author: Thomas
 */

#ifndef TWEUNITRESEARCHFINISHED_HPP_
#define TWEUNITRESEARCHFINISHED_HPP_

#include "TWEvent.hpp"

class TWE_UnitResearchFinished : public TW_Event
{
public:
    TWE_UnitResearchFinished(const TW_ENUMS::TroopNames& aUnit, const uint32_t aVillageID) : TW_Event(), unit(aUnit), villageID(aVillageID)
    {
    }

    virtual ~TWE_UnitResearchFinished()
    {
    }

    TW_ENUMS::TroopNames unit;
    uint32_t villageID;

private:
};


#endif /* TWEUNITRESEARCHFINISHED_HPP_ */
