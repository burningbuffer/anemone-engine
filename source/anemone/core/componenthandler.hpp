#pragma once
#include <any>
#include <memory>
#include <cassert>
#include <unordered_map>
#include "../utils/common.hpp"
#include "../utils/check.hpp"
#include "componentpool.hpp"
#include "../logger/logger.hpp"

class ComponentHandler
{
public:
	template<typename T>
	void CreateComponent()
	{
		const char* typeName = typeid(T).name();

		check_assert(mComponentTypes.find(typeName) == mComponentTypes.end(), "Component alrealdy created !");

		mComponentTypes.insert({ typeName, mNextComponentIndex });
		mComponentPools.insert({ typeName, std::make_shared<ComponentPool<T>>() });
		++mNextComponentIndex;
		Logger::Log("Component Created");
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		const char* typeName = typeid(T).name();

		check_assert(mComponentTypes.find(typeName) != mComponentTypes.end(), "Component not created yet!");

		return mComponentTypes[typeName];
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		GetComponentPool<T>()->InsertData(entity, component);
		Logger::Log("Component Added");
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		GetComponentPool<T>()->RemoveData(entity);
		Logger::Log("Component Removed");
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		return GetComponentPool<T>()->GetData(entity);
	}

	template<typename T>
	bool HasComponent(Entity entity)
	{
		return GetComponentPool<T>()->HasEntity(entity);
	}

	void EntityDestroyed(Entity entity)
	{
		for (auto const& pair : mComponentPools)
		{
			auto const& component = pair.second;
			component->EntityDestroyed(entity);
		}
	}

private:

	template<typename T>
	std::shared_ptr<ComponentPool<T>> GetComponentPool()
	{
		const char* typeName = typeid(T).name();

		check_assert(mComponentTypes.find(typeName) != mComponentTypes.end(), "Component not created yet!");
		
		return std::static_pointer_cast<ComponentPool<T>>(mComponentPools[typeName]);
	}


	std::unordered_map<const char*, ComponentType> mComponentTypes{};
	std::unordered_map<const char*, std::shared_ptr<IComponentPool>> mComponentPools{};
	ComponentType mNextComponentIndex{};
};
