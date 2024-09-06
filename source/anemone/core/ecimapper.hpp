#include <iostream>
#include <vector>
#include <optional>
#include <limits>
#include "../logger/logger.hpp"
#include "../utils/common.hpp"

class ECIMapper
{
public:
	Entity Fetch(Entity entity)
	{
		for (int i = 0; i < mEciMapperList.size(); i++)
		{
			if (mEciMapperList[i].entity == entity)
			{
				return mEciMapperList[i].entity;
			}
		}
		return std::numeric_limits<Entity>::max();
	}

	void Insert(Entity entity, uint8_t componentIndex)
	{
		Mapper m;
		m.entity = entity;
		m.componentIndex = componentIndex;
		mEciMapperList.push_back(m);
	}

	void UpdateAndDelete(Entity entityToDelete)
	{
		for (int i = 0; i < mEciMapperList.size(); i++)
		{
			if (mEciMapperList[i].entity == entityToDelete)
			{
				mEciMapperList.erase(mEciMapperList.begin()+i);
			}
		}
	}

	size_t IndexOfEntity(Entity entity)
	{
		
		for (int i = 0; i < mEciMapperList.size(); i++)
		{
			if (mEciMapperList[i].entity == entity)
			{
				return mEciMapperList[i].componentIndex;
			}
		}
		return std::numeric_limits<size_t>::max();
	}

	size_t TotalSize()
	{
		return mEciMapperList.size();
	}

private:
	struct Mapper 
	{
		Entity entity;
		uint8_t componentIndex;
	};
	std::vector<Mapper> mEciMapperList;
};