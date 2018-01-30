/*
 * Building.cpp
 *
 *  Created on: 2 feb. 2017
 *      Author: Thomas
 */

#include "TemplateObject.hpp"

BuildingTemplateObject::BuildingTemplateObject(const cv::Mat& aPattern, uint8_t aMinLevel, uint8_t aMaxLevel, bool aMatchFound, cv::Rect aMatchLocation)
  : TemplateObject(aPattern, aMatchFound, aMatchLocation), minLevel(aMinLevel), maxLevel(aMaxLevel)
{
}
BuildingTemplateObject::BuildingTemplateObject(const BuildingTemplateObject& other)
  : TemplateObject(other), minLevel(other.minLevel), maxLevel(other.maxLevel)
{
}

BuildingTemplateObject& BuildingTemplateObject::operator=(const BuildingTemplateObject& other)
{
    if (this != &other)
    {
        minLevel = other.minLevel;
        maxLevel = other.maxLevel;
    }
    return *this;
}

TemplateObject::TemplateObject(const cv::Mat& aPattern, bool aMatchFound, cv::Rect aMatchLocation)
  : pattern(aPattern), matchFound(aMatchFound), matchLocation(aMatchLocation)
{
}

TemplateObject::TemplateObject(const TemplateObject& other)
{
    pattern       = other.pattern;
    matchFound    = other.matchFound;
    matchLocation = other.matchLocation;
}

TemplateObject& TemplateObject::operator=(const TemplateObject& other)
{
    if (this != &other)
    {
        pattern       = other.pattern;
        matchFound    = other.matchFound;
        matchLocation = other.matchLocation;
    }
    return *this;
}
