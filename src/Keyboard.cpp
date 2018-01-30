/*
 * Keyboard.cpp
 *
 *  Created on: 24 jan. 2017
 *      Author: Thomas
 */

#include "Keyboard.hpp"

#include <chrono>
#include <iostream>
#include <thread>

HKL layout = GetKeyboardLayout(0);

void Keyboard::pressCharKey(const char& key)
{
    short aKey = VkKeyScanEx(key, layout);
    if ((aKey >> 8 & 0xFF) == 1)
    {
        holdKey(VK_SHIFT);
    }
    //	std::cout << key << " " << std::to_string(aKey) << " " << std::to_string(aKey >> 8 & 0xFF) <<std::endl;
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wVk = aKey;
    ip.ki.dwFlags = 0;

    // Press key.
    SendInput(1, &ip, sizeof(INPUT));

    std::this_thread::sleep_for(std::chrono::milliseconds(120));

    // Release key.
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));

    if ((aKey >> 8 & 0xFF) == 1)
    {
        releaseKey(VK_SHIFT);
    }
}

void Keyboard::pressKey(const uint8_t& key)
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wVk = key;
    ip.ki.dwFlags = 0;

    // Press key.
    SendInput(1, &ip, sizeof(INPUT));

    std::this_thread::sleep_for(std::chrono::milliseconds(180));

    // Release key.
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
}

void Keyboard::holdKey(const uint8_t& key)
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wVk = key;
    ip.ki.dwFlags = 0;

    SendInput(1, &ip, sizeof(INPUT));
}


void Keyboard::releaseKey(const uint8_t& key)
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wVk = key;
    ip.ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(1, &ip, sizeof(INPUT));
}


void Keyboard::pressKeyCombi(const uint8_t keys[], const uint8_t& size)
{
    INPUT keyCombi[size * 2];
    // Press keys.
    for (std::size_t i = 0; i < size; ++i)
    {
        keyCombi[i].type = INPUT_KEYBOARD;
        keyCombi[i].ki.wVk = keys[i];
        keyCombi[i].ki.dwFlags = 0;
    }
    // Add release keys.
    for (std::size_t i = size * 2 - 1; i >= size; --i)
    {
        keyCombi[i].type = INPUT_KEYBOARD;
        keyCombi[i].ki.dwFlags = KEYEVENTF_KEYUP;
        keyCombi[i].ki.wVk = keys[-size + i];
    }

    SendInput(size * 2, keyCombi, sizeof(INPUT));
}

void Keyboard::typeString(const std::string& text)
{
    for (uint16_t i = 0; i < text.length(); ++i)
    {
        pressCharKey(text.at(i));
    }
}

std::string Keyboard::getClipBoardText()
{
    // Can we open the clipboard?
    if (!OpenClipboard(nullptr))
    {
        return "";
    }

    // Get handle of clipboard object for ANSI text.
    HANDLE hData = GetClipboardData(CF_TEXT);
    if (hData == nullptr)
    {
        return "";
    }

    // Lock the handle to get the actual text pointer.
    char* pszText = static_cast<char*>(GlobalLock(hData));
    if (pszText == nullptr)
    {
        return "";
    }

    // Save text in a string class instance.
    std::string clipboardText(pszText);

    // Release the lock and close clipboard.
    GlobalUnlock(hData);
    CloseClipboard();

    return clipboardText;
}

bool Keyboard::isKeyPressed(const uint8_t key)
{
    USHORT status = GetAsyncKeyState(key);
    return (((status & 0x8000) >> 15) == 1) || ((status & 1) == 1);
}

Keyboard::~Keyboard()
{
    // TODO Auto-generated destructor stub
}
