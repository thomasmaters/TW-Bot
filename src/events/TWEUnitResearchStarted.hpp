/*
 * TWEUnitResearchStarted.hpp
 *
 *  Created on: 29 aug. 2017
 *      Author: Thomas
 */

#ifndef TWEUNITRESEARCHSTARTED_HPP_
#define TWEUNITRESEARCHSTARTED_HPP_

#include "TWEvent.hpp"

class TWE_UnitResearchStarted : public TW_Event
{
public:
    TWE_UnitResearchStarted(const TW_ENUMS::TroopNames& aUnit, const uint32_t aVillageID) : TW_Event(), unit(aUnit), villageID(aVillageID)
    {
    }

    virtual ~TWE_UnitResearchStarted()
    {
    }

    TW_ENUMS::TroopNames unit;
    uint32_t villageID;

private:
};


#endif /* TWEUNITRESEARCHSTARTED_HPP_ */
