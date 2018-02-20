/*
 * TWT.hpp
 *
 *  Created on: 8 feb. 2017
 *      Author: Thomas
 */

#ifndef TWTGOTONAVIGATION_HPP_
#define TWTGOTONAVIGATION_HPP_

#include "TWSubTask.hpp"
#include "TWTask.hpp"

#include "../TW_Enums.hpp"

class TWT_GotoNavigation : public TW_Task, public TW_SubTask
{
public:
    explicit TWT_GotoNavigation(const enum TW_ENUMS::NavigationNames& gotoLocation);

    bool executeBotTask() const;

    virtual ~TWT_GotoNavigation();

private:
    const enum TW_ENUMS::NavigationNames location;
};

#endif /* TWTGOTOBUILDING_HPP_ */
