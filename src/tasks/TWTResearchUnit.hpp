#ifndef TWTRESEARCHUNIT_HPP_
#define TWTRESEARCHUNIT_HPP_

#include "TWTask.hpp"

#include "../TW_Enums.hpp"
#include "../Village.hpp"

#define RESEARCH_BUTTON_OFFSET_X 80
#define RESEARCH_BUTTON_OFFSET_Y 45
#define RESEARCH_BUTTON_SIZE_X 170
#define RESEARCH_BUTTON_SIZE_Y 20

class TWT_ResearchUnit : public TW_Task
{
public:
    TWT_ResearchUnit(const TW_ENUMS::TroopNames aUnit, const std::shared_ptr<Village>& village);

    void preBotTask() const;

    void executeBotTask() const;

    void postBotTask() const;

    virtual ~TWT_ResearchUnit();

private:
    TW_ENUMS::TroopNames unit;
    std::shared_ptr<Village> village;
};

#endif
