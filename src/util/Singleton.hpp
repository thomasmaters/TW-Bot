#ifndef SINGLETON_H_INCLUDED
#define SINGLETON_H_INCLUDED

#include "NonCopyable.hpp"
#include "NonMovable.hpp"

class Singleton : public NonMovable, public NonCopyable
{
};

#endif  // SINGLETON_H_INCLUDED
