/*
 * Listener.hpp
 *
 *  Created on: 27 jan. 2017
 *      Author: Thomas
 */

#ifndef LISTENER_HPP_
#define LISTENER_HPP_

#include "events/TWEBuildingUpgradeFinished.hpp"
#include "events/TWEBuildingUpgradeStarted.hpp"
#include "events/TWESwitchedToVillage.hpp"
#include "events/TWETroopDataParsed.hpp"
#include "events/TWEUnitRecruitmentFinished.hpp"
#include "events/TWEUnitRecruitmentStarted.hpp"
#include "events/TWEUnitResearchFinished.hpp"
#include "events/TWEUnitResearchStarted.hpp"
#include "events/TWEVillageDataParsed.hpp"
#include "events/TWETaskFailed.hpp"
#include "events/TWEvent.hpp"

#include <algorithm>
#include <vector>

#include <boost/signals2.hpp>

class Dispatcher
{
public:
    Dispatcher()
    {
    }

    virtual ~Dispatcher()
    {
    }
    boost::signals2::signal<void(const TWE_VillageDataParsed)> TWE_VillageDataParsedHandler;
    boost::signals2::signal<void(const TWE_TroopDataParsed)> TWE_TroopDataParsedHandler;
    boost::signals2::signal<void(const TWE_BuildingUpgradeStarted)> TWE_BuildingUpgradeStartedHandler;
    boost::signals2::signal<void(const TWE_BuildingUpgradeFinished)> TWE_BuildingUpgradeFinishedHandler;
    boost::signals2::signal<void(const TWE_SwitchedToVillage)> TWE_SwitchedToVillageHandler;
    boost::signals2::signal<void(const TWE_UnitResearchStarted)> TWE_UnitResearchStartedHandler;
    boost::signals2::signal<void(const TWE_UnitResearchFinished)> TWE_UnitResearchFinishedHandler;
    boost::signals2::signal<void(const TWE_UnitRecruitmentStarted)> TWE_UnitRecruitmentStartedHandler;
    boost::signals2::signal<void(const TWE_UnitRecruitmentFinished)> TWE_UnitRecruitmentFinishedHandler;
    boost::signals2::signal<void(const TWE_TaskFailed)> TWE_TaskFailedHandler;


    // public:
    //	template<class T = TW_Event>
    //	class Listener
    //	{
    //	public:
    //		Listener()
    //		{
    //		}
    //
    //		void filterEvent(TW_Event& event)
    //		{
    //			//Try a cast, if it succeeds trigger the event.
    //			T* specialEvent = dynamic_cast<T*>(&event);
    //			if (specialEvent != NULL)
    //			{
    //				this->OnEvent(*specialEvent);
    //			}
    //		}
    //		virtual void OnEvent(const T& event) const = 0;
    //
    //		virtual ~Listener()
    //		{
    //		}
    //	};
    //
    //	void Reg(std::shared_ptr<Listener<TW_Event>> listener)
    //	{
    //		if (listeners.end()
    //				!= std::find(listeners.begin(), listeners.end(), listener))
    //			return;
    //
    //		listeners.push_back(listener);
    //	}
    //
    //    	void Unreg(ListenerPtr listener)
    //    	{
    //    		auto iter = std::find(listeners.begin(), listeners.end(), listener);
    //    		if (listeners.end() == iter)
    //    			return;
    //
    //    		listeners.erase(iter);
    //    	}
    //
    //	void Dispatch(TW_Event& event)
    //	{
    //		for( std::shared_ptr<Listener<TW_Event>>& a : listeners)
    //		{
    //			a->filterEvent(event);
    //		}
    //	}
    // protected:
    //	std::vector<std::shared_ptr<Listener<TW_Event>>> listeners;
};

#endif /* LISTENER_HPP_ */
