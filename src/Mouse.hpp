/*
 * Mouse.hpp
 *
 *  Created on: 1 okt. 2016
 *      Author: Thomas Maters
 */

#ifndef MOUSE_HPP_
#define MOUSE_HPP_

#include "HumanLikeMouseMovement.hpp"

#include <windows.h>
#include <opencv2/core/types.hpp>

class Mouse
{
public:
    static void mouseClick();
    static void mouseDoubleClick();
    static void holdMouse();
    static void releaseMouse();
    static void moveMouse(const RECT& moveTo);
    static void moveMouse(const POINT& moveTo);
    static void moveMouse(const cv::Rect& moveTo);
    static void moveMouse(uint16_t x, uint16_t y);
    static void moveMouse(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
    static void setCursorPosition(POINT point);
    static POINT getCursorPosition();

    virtual ~Mouse();

private:
    Mouse()
    {
    }

    HumanLikeMouseMovement mouseMovement;
    POINT mousePosition;
};

#endif /* MOUSE_HPP_ */
