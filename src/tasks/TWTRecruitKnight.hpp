/*
 * TWTRecruitKnight.hpp
 *
 *  Created on: 14 feb. 2018
 *      Author: Thomas Maters
 */

#ifndef TWTRECRUITKNIGHT_HPP_
#define TWTRECRUITKNIGHT_HPP_

#include "TWTask.hpp"

class TWT_RecruitKnight : TW_Task
{
public:
    TWT_RecruitKnight();

    bool preBotTask() const;

    bool executeBotTask() const;

    bool postBotTask() const;

    virtual ~TWT_RecruitKnight();
};


#endif /* TWTRECRUITKNIGHT_HPP_ */
