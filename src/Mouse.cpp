/*
 * Mouse.cpp
 *
 *  Created on: 1 okt. 2016
 *      Author: Thomas
 */

#include "Mouse.hpp"

#include <chrono>
#include <iostream>
#include <thread>

void Mouse::holdMouse()
{
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
}

void Mouse::releaseMouse()
{
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void Mouse::mouseClick()
{
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    std::this_thread::sleep_for(std::chrono::microseconds(85));
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void Mouse::mouseDoubleClick()
{
    mouseClick();
    std::this_thread::sleep_for(std::chrono::microseconds(50));
    mouseClick();
}

void Mouse::moveMouse(const RECT& moveTo)
{
    POINT a;
    GetCursorPos(&a);

    // Get a random position in the rectangle.
    uint16_t moveToX = moveTo.left + std::rand() % (moveTo.right - moveTo.left);
    uint16_t moveToY = moveTo.top + std::rand() % (moveTo.bottom - moveTo.top);

    std::cout << "pos" << a.x << " " << a.y << std::endl;
    std::cout << "moveto" << moveToX << " " << moveToY << std::endl;
    // Move the mouse blocking.
    HumanLikeMouseMovement movement = HumanLikeMouseMovement();
    movement.MoveMouseHumanLike({ a.x, a.y }, { moveToX, moveToY });
}

void Mouse::moveMouse(const POINT& moveTo)
{
    moveMouse((RECT){ moveTo.x, moveTo.y, moveTo.x + 1, moveTo.y + 1 });
}

void Mouse::moveMouse(const cv::Rect& moveTo)
{
    moveMouse((RECT){ moveTo.x, moveTo.y, moveTo.x + moveTo.width + 1, moveTo.y + moveTo.height + 1 });
}

void Mouse::moveMouse(uint16_t x, uint16_t y)
{
    moveMouse((RECT){ x, y, x + 1, y + 1 });
}

void Mouse::moveMouse(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    moveMouse((RECT){ x, y, x + width, y + height });
}

void Mouse::setCursorPosition(POINT point)
{
    int xPos = (double)point.x / GetSystemMetrics(SM_CXSCREEN) * 65535;
    int yPos = (double)point.y / GetSystemMetrics(SM_CYSCREEN) * 65535;
    mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, xPos, yPos, 0, 0);
}

POINT Mouse::getCursorPosition()
{
    POINT a;
    GetCursorPos(&a);
    return a;
}

Mouse::~Mouse()
{
}
