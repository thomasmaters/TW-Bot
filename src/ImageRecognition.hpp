/*
 * ImageRecognition.hpp
 *
 *  Created on: 12 jan. 2017
 *      Author: Thomas
 */

#ifndef IMAGERECOGNITION_HPP_
#define IMAGERECOGNITION_HPP_

#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <vector>

class ImageRecognition
{
public:
    ImageRecognition();

    /**
     * Matches a template on a image.
     * Throws a runtime error when the best match is lower then the threshold.
     * @param aImageLocation
     * @param aTemplateLocation
     * @param aMatchMethode
     * @param threshold
     * @return Location of the found match.
     */
    cv::Rect matchTemplate(const std::string& aImageLocation, const std::string& aTemplateLocation, const int aMatchMethode = 0,
                           const double threshold = 0) const;

    /**
     * Matches a template on a image as much as possible.
     * @param aImageLocation
     * @param aTemplateLocation
     * @param amountOfMatches
     * @param aMatchMethode
     * @param threshold
     * @return Vector of found locations.
     */
    std::vector<cv::Rect> matchTemplates(const std::string& aImageLocation, const std::string& aTemplateLocation, uint8_t amountOfMatches,
                                         int aMatchMethode = 0, const double threshold = 0) const;

    /**
     * Matches a template on the latest screenshot.
     * @param aTemplateLocation
     * @param aMatchMethode
     * @param threshold
     * @return
     */
    cv::Rect matchTemplateOnScreenshot(const std::string& aTemplateLocation, const int aMatchMethode = 0, const double threshold = 0) const;

    virtual ~ImageRecognition();

private:
    /**
     * Returns true if found result is greater then the threshold. Stores result in aLocation.
     * @param aLocation Stores found location.
     * @param aImage
     * @param aMatchMethode
     * @param threshold
     * @return
     */
    bool getBestLocation(cv::Point& aLocation, cv::Mat& aImage, const int aMatchMethode = 0, const double threshold = 0) const;

    /**
     * Loads a image from a file location.
     * Will throw a runtime error if it failed to load/find the template.
     * @param imageLocation
     * @return
     */
    cv::Mat loadImage(const std::string& imageLocation) const;
};

#endif /* IMAGERECOGNITION_HPP_ */
