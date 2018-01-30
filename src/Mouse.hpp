/*
 * Mouse.hpp
 *
 *  Created on: 1 okt. 2016
 *      Author: Thomas
 */

#ifndef MOUSE_HPP_
#define MOUSE_HPP_

#include "HumanLikeMouseMovement.hpp"

#include <opencv2/core/types.hpp>
#include <windows.h>

class Mouse {
public:
	static void mouseClick();
	static void mouseDoubleClick();
	static void holdMouse();
	static void releaseMouse();
	static void moveMouse(const RECT& moveTo);
	static void moveMouse(const POINT& moveTo);
	static void moveMouse(const cv::Rect& moveTo);
	static void setCursorPosition(POINT point);
	static POINT getCursorPosition();

	virtual ~Mouse();
private:
	Mouse(){}

	HumanLikeMouseMovement mouseMovement;
	POINT mousePosition;
};

#endif /* MOUSE_HPP_ */
