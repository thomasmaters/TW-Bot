/*
 * TWTCompleteCaptcha.hpp
 *
 *  Created on: 10 feb. 2018
 *      Author: Thomas Maters
 */

#ifndef TWTCOMPLETECAPTCHA_HPP_
#define TWTCOMPLETECAPTCHA_HPP_

#define CAPTCHA_BUTTON_OFFSET_X 15
#define CAPTCHA_BUTTON_OFFSET_Y 25
#define CAPTCHA_BUTTON_SIZE_X 35
#define CAPTCHA_BUTTON_SIZE_Y 46
#define CAPTCHA_CHECK_INTERVAL 20000

#include "TWTask.hpp"

class TWTCompleteCaptcha : public TW_Task
{
public:
    TWTCompleteCaptcha();

    bool executeBotTask() const;

    virtual ~TWTCompleteCaptcha();
};


#endif /* TWTCOMPLETECAPTCHA_HPP_ */
