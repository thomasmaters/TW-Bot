/*
 * HumanLikeMouseMovement.cpp
 *
 *  Created on: 22 jan. 2017
 *      Author: Thomas
 */

#include "HumanLikeMouseMovement.hpp"
#include "Mouse.hpp"

#define M_PIl 3.141592653589793238462643383279502884L
#include <chrono>
#include <random>
#include <thread>

HumanLikeMouseMovement::HumanLikeMouseMovement()
{
    // TODO Auto-generated constructor stub
    std::srand(std::time(0));
}

void HumanLikeMouseMovement::MoveMouseHumanLike(POINT start, POINT end)
{
    // Calculate needed steps.
    int count = 2 + distanceBetweenPoints2D(start, end) / 7;

    // Perform movement and add randomasation.
    for (int i = 0; i < count; ++i)
    {
        long xposf = (double)start.x + (end.x - start.x) * sin(M_PIl / 2 * i / count);
        long xrand = std::rand() % 4 - sin(M_PIl * 2 * i / count) * 10;
        long yposf = (double)start.y + (end.y - start.y) * sin(M_PIl / 2 * i / count);
        long yrand = std::rand() % 4 - sin(M_PIl * 2 * i / count) * 10;

        Mouse::setCursorPosition({ xposf + xrand, yposf + yrand });
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // Set cursor to exact location.
    Mouse::setCursorPosition(end);
}

double HumanLikeMouseMovement::distanceBetweenPoints2D(POINT start, POINT end)
{
    double xDiff = end.x - start.x;
    double yDiff = end.y - start.y;

    return sqrt(xDiff * xDiff + yDiff * yDiff);
}

HumanLikeMouseMovement::~HumanLikeMouseMovement()
{
    // TODO Auto-generated destructor stub
}
