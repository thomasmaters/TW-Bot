/*
 * Resources.hpp
 *
 *  Created on: 30 jan. 2018
 *      Author: Thomas
 */

#ifndef RESOURCES_HPP_
#define RESOURCES_HPP_

#include <string>

struct Resources
{
    Resources(double wood = 0, double stone = 0, double iron = 0) : wood(wood), stone(stone), iron(iron)
    {
    }

    double wood;
    double stone;
    double iron;

    std::string toString()
    {
        return "Wood: " + std::to_string(wood) + "   Stone: " + std::to_string(stone) + "   Iron: " + std::to_string(iron);
    }

    Resources& operator-=(const Resources& rhs)
    {
        wood -= rhs.wood;
        stone -= rhs.stone;
        iron -= rhs.iron;
        return *this;
    }
};

typedef Resources ResourceBonus;
typedef Resources ResourceProd;

#endif /* RESOURCES_HPP_ */
