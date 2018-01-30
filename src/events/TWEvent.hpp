#ifndef TWEVENT_HPP_
#define TWEVENT_HPP_

#include "../TW_Enums.hpp"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

class TW_Event
{
public:
    explicit TW_Event()
      : tag(boost::uuids::random_generator()()){

      };

    TW_Event(const TW_Event& aEventBase)
    {
        this->tag = aEventBase.tag;
    }

    /*
     * Operators.
     */
    bool operator==(const TW_Event& lhs) const
    {
        return lhs.tag == tag;
    }

    TW_Event& operator=(const TW_Event& aEventBase)
    {
        if (this != &aEventBase)
        {
            this->tag = aEventBase.tag;
        }
        return *this;
    }

    virtual ~TW_Event()
    {
    }

private:
    boost::uuids::uuid tag;
};


#endif /* TWEVENT_HPP_ */
