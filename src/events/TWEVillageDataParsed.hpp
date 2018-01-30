/*
 * TWEVillageDataParsed.hpp
 *
 *  Created on: 29 aug. 2017
 *      Author: Thomas
 */

#ifndef TWEVILLAGEDATAPARSED_HPP_
#define TWEVILLAGEDATAPARSED_HPP_

#include "TWEvent.hpp"

#include "../../lib/json.hpp"

class TWE_VillageDataParsed : public TW_Event
{
public:
    explicit TWE_VillageDataParsed(const nlohmann::json& aVillageData) : TW_Event(), villageData(aVillageData)
    {
    }

    virtual ~TWE_VillageDataParsed()
    {
    }

    nlohmann::json villageData;

private:
};


#endif /* TWEVILLAGEDATAPARSED_HPP_ */
