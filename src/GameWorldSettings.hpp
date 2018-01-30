/*
 * GameWorldSettings.hpp
 *
 *  Created on: 22 jan. 2017
 *      Author: Thomas
 */

#ifndef GAMEWORLDSETTINGS_HPP_
#define GAMEWORLDSETTINGS_HPP_

#include "TW_Enums.hpp"
#include "TimeSpan.hpp"

#include <cstdint>
#include <map>

class GameWorldSettings
{
public:
    GameWorldSettings();
    virtual ~GameWorldSettings();

protected:
    double gameSpeed;
    double unitSpeed;

    std::map<TW_ENUMS::TroopNames, Resources, std::hash<int>> troopCost;

private:
};

#endif /* GAMEWORLDSETTINGS_HPP_ */
