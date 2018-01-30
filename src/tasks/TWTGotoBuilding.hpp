/*
 * TWT.hpp
 *
 *  Created on: 8 feb. 2017
 *      Author: Thomas
 */

#ifndef TWTGOTOBUILDING_HPP_
#define TWTGOTOBUILDING_HPP_

#include "TWTask.hpp"

#include "../TW_Enums.hpp"

class TWT_GotoBuilding : public TW_Task
{
public:
    explicit TWT_GotoBuilding(const enum TW_ENUMS::BuildingNames& gotoLocation);

    bool executeBotTask() const;

    virtual ~TWT_GotoBuilding();

private:
    const enum TW_ENUMS::BuildingNames location;
};

#endif /* TWTGOTOBUILDING_HPP_ */
