#ifndef TWEVENT_HPP_
#define TWEVENT_HPP_

#include "../TW_Enums.hpp"

class TW_Event
{
public:
    explicit TW_Event(const enum TW_ENUMS::EventPiority aPiority = TW_ENUMS::EventPiority::LOW)
      : piority(aPiority){

      };

    TW_Event(const TW_Event& aEventBase)
    {
        this->piority = aEventBase.piority;
    }

    /*
     * Operators.
     */
    bool operator==(const TW_Event& lhs) const
    {
        return lhs.piority == piority;
    }

    TW_Event& operator=(const TW_Event& aEventBase)
    {
        if (this != &aEventBase)
        {
            this->piority = aEventBase.piority;
        }
        return *this;
    }

    bool operator>(const TW_Event& lhs) const
    {
        return piority > lhs.piority;
    }
    /*
     * Functions.
     */
    const enum TW_ENUMS::EventPiority& getEventPiority() const
    {
        return piority;
    }

    virtual ~TW_Event()
    {
    }

private:
    enum TW_ENUMS::EventPiority piority;
};


#endif /* TWEVENT_HPP_ */
