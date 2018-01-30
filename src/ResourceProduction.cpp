/*
 * ResourceProduction.cpp
 *
 *  Created on: 3 aug. 2017
 *      Author: Thomas
 */

#include "ResourceProduction.hpp"

#include <chrono>

ResourceProduction::ResourceProduction()
  : population(0), maxPopulation(0), maxStorage(0), resources(), production(), bonus(), last_res_tick(std::time_t(0))
{
}


bool ResourceProduction::hasEnoughResources(const Resources& cost) const
{
    Resources currentResources = getCurrentResources();
    return cost.wood <= currentResources.wood && cost.stone <= currentResources.stone && cost.iron <= currentResources.iron;
}

bool ResourceProduction::hasEnoughPopulation(const uint32_t populationCost) const
{
    return population + populationCost <= maxPopulation;
}

bool ResourceProduction::hasEnoughStorage(const uint32_t amountToStore) const
{
    return amountToStore <= maxStorage;
}

bool ResourceProduction::hasEnoughStorage(const Resources& amountToStore) const
{
    return amountToStore.wood <= maxStorage && amountToStore.iron <= maxStorage && amountToStore.stone <= maxStorage;
}

uint32_t ResourceProduction::timeToGetResources(const Resources& cost) const
{
    if (hasEnoughResources(cost))
    {
        return 0;
    }

    double woodTime  = (cost.wood - resources.wood) / production.wood;
    double ironTime  = (cost.iron - resources.iron) / production.iron;
    double stoneTime = (cost.stone - resources.stone) / production.stone;

    return std::max({ woodTime, ironTime, stoneTime });
}

ResourceProduction::~ResourceProduction()
{
}

void ResourceProduction::updateCurrentResources()
{
    resources     = getCurrentResources();
    last_res_tick = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

Resources ResourceProduction::getCurrentResources() const
{
    std::chrono::system_clock::duration timeDifference = std::chrono::system_clock::now() - std::chrono::system_clock::from_time_t(last_res_tick);
    uint64_t timeSinceLastUpdate                       = std::chrono::duration_cast<std::chrono::seconds>(timeDifference).count();

    return Resources(resources.wood + production.wood * timeSinceLastUpdate, resources.stone + production.stone * timeSinceLastUpdate,
                     resources.iron + production.iron * timeSinceLastUpdate);
}
