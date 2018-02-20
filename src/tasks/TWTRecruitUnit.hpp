#ifndef TWTRECRUITUNIT_HPP_
#define TWTRECRUITUNIT_HPP_

#include "TWTask.hpp"

#include "../TW_Enums.hpp"
#include "../Village.hpp"

#define RECRUIT_INPUT_OFFSET_X 722
#define RECRUIT_INPUT_OFFSET_Y 18
#define RECRUIT_KNIGHT_INPUT_OFFSET_Y -65
#define RECRUIT_INPUT_SIZE_X 30
#define RECRUIT_INPUT_SIZE_Y 5

class TWT_RecruitUnit : public TW_Task
{
public:
    TWT_RecruitUnit(const std::shared_ptr<Village>& aVillage, const TW_ENUMS::TroopNames& aUnit, uint32_t aAmountOfUnits = 1);

    bool preBotTask() const;

    bool executeBotTask() const;

    bool postBotTask() const;

    void recruitKnight() const;

    virtual ~TWT_RecruitUnit();

private:
    std::shared_ptr<Village> village;
    TW_ENUMS::TroopNames unit;
    uint32_t amountOfUnits;
};

#endif
