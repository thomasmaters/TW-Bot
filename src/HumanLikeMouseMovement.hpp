/*
 * HumanLikeMouseMovement.hpp
 *
 *  Created on: 22 jan. 2017
 *      Author: Thomas
 */

#ifndef HUMANLIKEMOUSEMOVEMENT_HPP_
#define HUMANLIKEMOUSEMOVEMENT_HPP_

#include <windows.h>
#include <math.h>

#include <cstdint>

class HumanLikeMouseMovement
{
public:
	HumanLikeMouseMovement();
	HumanLikeMouseMovement(const HumanLikeMouseMovement& other);

	void MoveMouseHumanLike(POINT start, POINT end);

	virtual ~HumanLikeMouseMovement();
private:
	double distanceBetweenPoints2D(POINT start, POINT end);
};

#endif /* HUMANLIKEMOUSEMOVEMENT_HPP_ */
