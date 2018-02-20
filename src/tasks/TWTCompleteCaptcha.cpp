/*
 * TWTCompleteCaptcha.cpp
 *
 *  Created on: 10 feb. 2018
 *      Author: Thomas Maters
 */

#include "TWTCompleteCaptcha.hpp"
#include "../BotManager.hpp"
#include "../GameManager.hpp"
#include "../Mouse.hpp"

TWTCompleteCaptcha::TWTCompleteCaptcha()
{
}

bool TWTCompleteCaptcha::executeBotTask() const
{
    try
    {
        BotManager::getInstance().scheduleTask(CAPTCHA_CHECK_INTERVAL, std::shared_ptr<TW_Task>(new TWTCompleteCaptcha()));

        // If this function throws, no captcha has been found!
        cv::Rect templatePos = GameManager::getInstance().getTemplatePositionOnScreen("captcha", "A");

        Mouse::moveMouse(templatePos.x + CAPTCHA_BUTTON_OFFSET_X, templatePos.y + CAPTCHA_BUTTON_OFFSET_Y, CAPTCHA_BUTTON_SIZE_X,
                         CAPTCHA_BUTTON_SIZE_Y);
        Mouse::mouseClick();
    }
    catch (std::exception& e)
    {
        std::cerr << __PRETTY_FUNCTION__ << ": " << e.what() << std::endl;
        return true;
    }
    return true;
}

TWTCompleteCaptcha::~TWTCompleteCaptcha()
{
}
