/*
 * Building.hpp
 *
 *  Created on: 2 feb. 2017
 *      Author: Thomas
 */

#ifndef TEMPLATEOBJECT_HPP_
#define TEMPLATEOBJECT_HPP_

#include <opencv2/core/mat.hpp>

#include <cstdint>
#include <string>


class TemplateObject
{
public:
    TemplateObject(const cv::Mat& aPattern, bool aMatchFound = false, cv::Rect aMatchLocation = { 0, 0, 0, 0 });

    TemplateObject(const TemplateObject& other);
    TemplateObject& operator=(const TemplateObject& other);

    virtual ~TemplateObject(){};

    bool isMatchFound() const
    {
        return matchFound;
    }

    const cv::Rect& getMatchLocation() const
    {
        return matchLocation;
    }

protected:
    cv::Mat pattern;
    bool matchFound;
    cv::Rect matchLocation;
};

class BuildingTemplateObject : public TemplateObject
{
public:
    BuildingTemplateObject(const cv::Mat& aPattern, uint8_t aMinLevel = 0, uint8_t aMaxLevel = 0, bool aMatchFound = false,
                           cv::Rect aMatchLocation = { 0, 0, 0, 0 });
    BuildingTemplateObject(const BuildingTemplateObject& other);
    BuildingTemplateObject& operator=(const BuildingTemplateObject& other);

    virtual ~BuildingTemplateObject(){};

private:
    uint8_t minLevel;
    uint8_t maxLevel;
};

#endif /* TEMPLATEOBJECT_HPP_ */
