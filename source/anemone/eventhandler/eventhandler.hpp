#pragma once
#include "event.hpp"
#include "memberfunction.hpp"
#include "logger/logger.hpp"
#include <map>
#include <typeindex>

class EventHandler
{
public:

    EventHandler(){}
    ~EventHandler(){Clear();}

    void Clear()
    {
        subscribers.clear();
    }

    template<typename TEvent,typename TBase>
    void SubscribeToEvent(TBase* baseClass, void (TBase::*callbackFunction)(TEvent&))
    {
        if(!subscribers[typeid(TEvent)].get())
        {
            subscribers[typeid(TEvent)] = std::make_unique<availableFunctionList>();
        }

        auto subscriber = std::make_unique<MemberFunction<TBase, TEvent>>(baseClass, callbackFunction);
        subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
    }

    template<typename TEvent, typename ...TArgs>
    void TriggerEvent(TArgs&& ...args)
    {
        auto handlers = subscribers[typeid(TEvent)].get();
        if (handlers) {
            for (auto it = handlers->begin(); it != handlers->end(); it++) {
                auto handler = it->get();
                TEvent event(std::forward<TArgs>(args)...);
                handler->Execute(event);
            }
        }
    }

private:
    std::map<std::type_index, std::unique_ptr<availableFunctionList>> subscribers;
};