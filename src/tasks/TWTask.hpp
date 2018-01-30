/*
 * BotTasks.hpp
 *
 *  Created on: 12 jan. 2017
 *      Author: Thomas
 */

#ifndef TWTASK_HPP_
#define TWTASK_HPP_

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

class TW_Task : public std::enable_shared_from_this<TW_Task>
{
public:
    TW_Task() : tag(boost::uuids::random_generator()()){};

    TW_Task(const TW_Task& other) : std::enable_shared_from_this<TW_Task>(), tag(other.tag)
    {
    }

    std::shared_ptr<TW_Task> getFoo()
    {
        return shared_from_this();
    }

    TW_Task& operator=(const TW_Task& other)
    {
        if (this != &other)
        {
            this->tag = other.tag;
        }
        return *this;
    }

    bool operator==(const TW_Task& other) const
    {
        return tag == other.tag;
    }

    bool operator!=(const TW_Task& other) const
    {
        return !(*this == other);
    }

    virtual bool preBotTask() const
    {
        return true;
    }
    virtual bool executeBotTask() const = 0;
    virtual bool postBotTask() const
    {
        return true;
    }

    virtual ~TW_Task(){};

private:
    boost::uuids::uuid tag;
};

#endif /* TWTASK_HPP_ */
