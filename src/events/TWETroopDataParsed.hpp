/*
 * TWETroopDataParsed.hpp
 *
 *  Created on: 29 aug. 2017
 *      Author: Thomas
 */

#ifndef TWETROOPDATAPARSED_HPP_
#define TWETROOPDATAPARSED_HPP_

#include "TWEvent.hpp"

#include "../../lib/json.hpp"

class TWE_TroopDataParsed : public TW_Event
{
public:
    explicit TWE_TroopDataParsed(const nlohmann::json& aTroopData) : TW_Event(), troopData(aTroopData)
    {
    }

    virtual ~TWE_TroopDataParsed()
    {
    }

    nlohmann::json troopData;

private:
};


#endif /* TWETROOPDATAPARSED_HPP_ */
