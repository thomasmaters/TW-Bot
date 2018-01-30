/*
 * Keyboard.hpp
 *
 *  Created on: 24 jan. 2017
 *      Author: Thomas
 */

#ifndef KEYBOARD_HPP_
#define KEYBOARD_HPP_

#include <windows.h>

#include <cstdint>
#include <string>

class Keyboard {
public:
	static void pressCharKey(const char& key);
	static void pressKey(const uint8_t& key);
	static void pressKeyCombi(const uint8_t keys[], const uint8_t& size);
	static void holdKey(const uint8_t& key);
	static void releaseKey(const uint8_t& key);
	static void typeString(const std::string& text);
	static bool isKeyPressed ( const uint8_t key );

	static std::string getClipBoardText();

	virtual ~Keyboard();
private:
	Keyboard(){
	}
};

#endif /* KEYBOARD_HPP_ */
