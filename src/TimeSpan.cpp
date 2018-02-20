/*
 * TimeSpan.cpp
 *
 *  Created on: 22 jan. 2017
 *      Author: Thomas
 */

#include "TimeSpan.hpp"

TimeSpan::TimeSpan():
	hour(0),
	minute(0),
	second(0)
{

}

TimeSpan::TimeSpan(uint8_t hour, uint8_t minute, uint8_t second):
	hour(hour),
	minute(minute),
	second(second)
{

}

TimeSpan::TimeSpan(const TimeSpan& timeSpan):
		hour(timeSpan.hour),
		minute(timeSpan.minute),
		second(timeSpan.second)
{

}

TimeSpan& TimeSpan::operator=( const TimeSpan& other)
{
	if(this != &other)
	{
		hour = other.hour;
		minute = other.minute;
		second = other.second;
	}
	return *this;
}

bool TimeSpan::operator>( const TimeSpan& other) const
{
	return hour > other.hour;
}

TimeSpan::~TimeSpan() {
}

