/*
 * ImageRecognition.cpp
 *
 *  Created on: 12 jan. 2017
 *      Author: Thomas
 */

#include "ImageRecognition.hpp"

#include "Screen.hpp"

#include <iostream>

ImageRecognition::ImageRecognition()
{
}

cv::Rect ImageRecognition::matchTemplate(const std::string& aImageLocation, const std::string& aTemplateLocation, const int aMatchMethode,
                                         const double threshold) const
{
    try
    {
        Screen::takeScreenShot();

        cv::Mat sourceImage   = loadImage(aImageLocation);
        cv::Mat templateImage = loadImage(aTemplateLocation);

        // Make object to save result in.
        int result_cols = sourceImage.cols - templateImage.cols + 1;
        int result_rows = sourceImage.rows - templateImage.rows + 1;
        cv::Mat result  = cv::Mat(result_rows, result_cols, CV_32FC1);

        // Match template and normalize the result.
        cv::matchTemplate(sourceImage, templateImage, result, aMatchMethode);

        cv::Point a;
        if (getBestLocation(a, result, aMatchMethode, threshold))
        {
            throw std::runtime_error("Didn't found template in image.");
        }

        return cv::Rect(a.x, a.y, templateImage.cols, templateImage.rows);
    }
    catch (const std::exception& e)
    {
        throw e;
    }
    return { 0, 0, 0, 0 };
}

std::vector<cv::Rect> ImageRecognition::matchTemplates(const std::string& aImageLocation, const std::string& aTemplateLocation,
                                                       uint8_t amountOfMatches, const int aMatchMethode, const double threshold) const
{
    try
    {
        Screen::takeScreenShot();

        cv::Mat sourceImage   = loadImage(aImageLocation);
        cv::Mat templateImage = loadImage(aTemplateLocation);

        int result_cols = sourceImage.cols - templateImage.cols + 1;
        int result_rows = sourceImage.rows - templateImage.rows + 1;
        cv::Mat result  = cv::Mat(result_rows, result_cols, CV_32FC1);

        // Match template and normalize the result.
        cv::matchTemplate(sourceImage, templateImage, result, aMatchMethode);

        std::vector<cv::Rect> returnVector = std::vector<cv::Rect>();
        for (uint8_t i = 0; i < amountOfMatches; ++i)
        {
            cv::Point matchLocation;
            if (getBestLocation(matchLocation, result, aMatchMethode, threshold))
            {
                returnVector.push_back(cv::Rect(matchLocation.x, matchLocation.y, templateImage.cols, templateImage.rows));
            }
        }

        return returnVector;
    }
    catch (const std::exception& e)
    {
        throw e;
    }
    //    throw std::runtime_error("Matching templates failed, this should not happen!");
}

cv::Rect ImageRecognition::matchTemplateOnScreenshot(const std::string& aTemplateLocation, const int aMatchMethode, const double threshold) const
{
    return matchTemplate(screenshotLocation, aTemplateLocation, aMatchMethode, threshold);
}

ImageRecognition::~ImageRecognition()
{
}

bool ImageRecognition::getBestLocation(cv::Point& aLocation, cv::Mat& aResult, const int aMatchMethode, const double threshold) const
{
    double minVal;
    double maxVal;
    cv::Point minLoc;
    cv::Point maxLoc;
    cv::Point matchLoc;

    // Get minimums and maximums.
    minMaxLoc(aResult, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

    if (aMatchMethode == cv::TM_SQDIFF || aMatchMethode == cv::TM_SQDIFF_NORMED)
    {
        matchLoc = minLoc;
    }
    else
    {
        matchLoc = maxLoc;
    }


    std::cout << minVal << "   " << maxVal << "                    " << minLoc << "-" << maxLoc << std::endl;
    cv::floodFill(aResult, maxLoc, cv::Scalar(0), 0, cv::Scalar(.1), cv::Scalar(1.));

    aLocation = matchLoc;
    // We did not find our template.
    return (threshold != 0 && maxVal < threshold);
}

cv::Mat ImageRecognition::loadImage(const std::string& imageLocation) const
{
    cv::Mat temp = cv::imread(imageLocation, CV_LOAD_IMAGE_COLOR);
    if (temp.empty())
    {
        throw std::runtime_error("Failed to load image.");
    }
    return temp;
}
