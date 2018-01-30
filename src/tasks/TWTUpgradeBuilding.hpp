/*
 * TWTUpgradeBuilding.hpp
 *
 *  Created on: 5 jul. 2017
 *      Author: Thomas
 */

#ifndef TWTUPGRADEBUILDING_HPP_
#define TWTUPGRADEBUILDING_HPP_

#include "TWTask.hpp"

#include "../TW_Enums.hpp"
#include "../Village.hpp"

class TWT_UpgradeBuilding : public TW_Task
{
public:
    TWT_UpgradeBuilding(const std::shared_ptr<Village>& village, const TW_ENUMS::BuildingNames& building, const std::string& csrf);

    bool preBotTask() const;

    bool executeBotTask() const;

    bool postBotTask() const;

    virtual ~TWT_UpgradeBuilding();

private:
    std::shared_ptr<Village> village;  ///< Id of the village to upgrade a building
    TW_ENUMS::BuildingNames building;
    std::string csrf;
};


#endif /* TWTUPGRADEBUILDING_HPP_ */
