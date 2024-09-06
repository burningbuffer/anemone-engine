#pragma once
#include <functional>
#include <list>
#include "event.hpp"

class IMemberFunction
{
public:
    virtual ~IMemberFunction() = default;

    void Execute(Event& e)
    {
        Call(e);
    }
private:
    virtual void Call(Event& e) = 0;

};

template<typename TBase, typename TEvent>
class MemberFunction : public IMemberFunction
{

private:

    typedef void (TBase::*CallbackFunction)(TEvent&);

    virtual void Call(Event& e) override 
    {
        std::invoke(mCallbackFunction, mBaseClass, static_cast<TEvent&>(e));
    }

    TBase* mBaseClass;

    CallbackFunction mCallbackFunction;

public:

    MemberFunction(TBase* baseClass, CallbackFunction callbackFunction)
    {
        this->mBaseClass = baseClass;
        this->mCallbackFunction = callbackFunction;
    }

    virtual ~MemberFunction() override = default;
};

typedef std::list<std::unique_ptr<IMemberFunction>> availableFunctionList;