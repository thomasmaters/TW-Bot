/*
 * TWESwitchedToVillage.hpp
 *
 *  Created on: 29 aug. 2017
 *      Author: Thomas
 */

#ifndef TWESWITCHEDTOVILLAGE_HPP_
#define TWESWITCHEDTOVILLAGE_HPP_

#include "TWEvent.hpp"

#include "../Village.hpp"

class Village;  // Forward declaration because the Village class needs this event. (Circular dependency)
class TWE_SwitchedToVillage : public TW_Event
{
public:
    TWE_SwitchedToVillage() /*const std::shared_ptr<Village>& aVillage) : village(aVillage)*/
    {
    }

    virtual ~TWE_SwitchedToVillage()
    {
    }

    // std::shared_ptr<Village> village;

private:
};


#endif /* TWESWITCHEDTOVILLAGE_HPP_ */
