/*
 * ResourceProduction.hpp
 *
 *  Created on: 3 aug. 2017
 *      Author: Thomas
 */

#ifndef RESOURCEPRODUCTION_HPP_
#define RESOURCEPRODUCTION_HPP_

#include <stdint.h>
#include <algorithm>
#include <ctime>

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

class ResourceProduction
{
public:
    ResourceProduction();

    /**
     * Checks if this village has enough resources.
     * @param cost Amount of resources.
     * @return
     */
    bool hasEnoughResources(const Resources& cost) const;

    /**
     * Checks if this village has enough population.
     * @param popCost Amount of population;
     * @return
     */
    bool hasEnoughPopulation(const uint32_t popCost) const;

    /**
     * Checks if there is enough storage in this village.
     * @param amountToStore
     * @return
     */
    bool hasEnoughStorage(const uint32_t amountToStore) const;

    /**
     * Checks if there is enough storage in this village.
     * @param amountToStore
     * @return
     */
    bool hasEnoughStorage(const Resources& amountToStore) const;

    /**
     * Calculates time the village needs to get the amount of resources. Resource production only.
     * @param resources The amount of needed resources.
     * @return Time in seconds.
     */
    uint32_t timeToGetResources(const Resources& resources) const;

    virtual ~ResourceProduction();

private:
protected:
    void updateCurrentResources();

    Resources getCurrentResources() const;

    uint32_t population;
    uint32_t maxPopulation;
    uint32_t maxStorage;
    Resources resources;
    ResourceProd production;
    ResourceBonus bonus;

    std::time_t last_res_tick;
};


#endif /* RESOURCEPRODUCTION_HPP_ */
