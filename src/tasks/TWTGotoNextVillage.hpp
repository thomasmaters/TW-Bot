#ifndef TWTGOTONEXTVILLAGE_HPP_
#define TWTGOTONEXTVILLAGE_HPP_

#include "TWTask.hpp"

class TWT_GotoNextVillage : public TW_Task
{
public:
    TWT_GotoNextVillage();

    bool executeBotTask() const;

    virtual ~TWT_GotoNextVillage();

private:
};


#endif /* TWTGOTONEXTVILLAGE_HPP_ */
