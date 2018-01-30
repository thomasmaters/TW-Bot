/*
 * TimeSpan.hpp
 *
 *  Created on: 22 jan. 2017
 *      Author: Thomas
 */

#ifndef TIMESPAN_HPP_
#define TIMESPAN_HPP_

#include <cstdint>

/*
 * A simple class to represent a time
 */
class TimeSpan
{
public:
	TimeSpan();
	TimeSpan(uint8_t hour, uint8_t minute, uint8_t second);
	TimeSpan(const TimeSpan& timeSpan);

	TimeSpan& operator=( const TimeSpan& other);
	bool operator>( const TimeSpan& other) const;

	virtual ~TimeSpan();
private:
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
};

#endif /* TIMESPAN_HPP_ */
