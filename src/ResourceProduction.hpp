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

#include "Resources.hpp"

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
