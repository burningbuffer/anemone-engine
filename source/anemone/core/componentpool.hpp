#pragma once
#include <array>
#include <cassert>
#include <unordered_map>
#include <optional>
#include <limits>
#include "../utils/common.hpp"
#include "ecimapper.hpp"
#include "../utils/check.hpp"

class IComponentPool
{
public:
	virtual ~IComponentPool() = default;
	virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentPool : public IComponentPool
{
public:
	void InsertData(Entity entity, T component)
	{
		check_assert(mapper.Fetch(entity) == std::nullopt,"Component added to the same entity more than once");

		size_t newIndex = mSize;
		mapper.Insert(entity, newIndex);
		mComponentPool[newIndex] = component;
		++mSize;

	}

	void RemoveData(Entity entity)
	{
		check_assert(mapper.IndexOfEntity(entity) != std::numeric_limits<size_t>::max(), "Removing non existent component !");

		size_t indexOfRemovedEntity = mapper.IndexOfEntity(entity);

		size_t indexOfLastElement = mSize - 1;
		mComponentPool[indexOfRemovedEntity] = mComponentPool[indexOfLastElement];
		mapper.UpdateAndDelete(entity);
		--mSize;
	}

	T& GetData(Entity entity)
	{
		check_assert(mapper.IndexOfEntity(entity) != std::numeric_limits<size_t>::max(), "Retrieving non existent component !");

		return mComponentPool[mapper.IndexOfEntity(entity)];
	}

	void EntityDestroyed(Entity entity) override
	{
		if (mapper.Fetch(entity) != std::nullopt)
		{
			RemoveData(entity);
		}
	}

private:
	std::array<T, MAX_ENTITIES> mComponentPool{};
	ECIMapper mapper;
	size_t mSize{};
};
