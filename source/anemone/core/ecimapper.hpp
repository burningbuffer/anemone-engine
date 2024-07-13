#include <iostream>
#include <vector>
#include <optional>
#include <limits>
#include "../logger/logger.hpp"
#include "../utils/common.hpp"

class ECIMapper
{
public:
	std::optional<Entity> Fetch(Entity entity)
	{
		for (int i = 0; i < eciMapperList.size(); i++)
		{
			if (eciMapperList[i].entity == entity)
			{
				return eciMapperList[i].entity;
			}
		}
		return std::nullopt;
	}

	void Insert(Entity entity, uint8_t componentIndex)
	{
		Mapper m;
		m.entity = entity;
		m.componentIndex = componentIndex;
		eciMapperList.push_back(m);
	}

	void UpdateAndDelete(Entity entityToDelete)
	{
		for (int i = 0; i < eciMapperList.size(); i++)
		{
			if (eciMapperList[i].entity == entityToDelete)
			{
				eciMapperList.erase(eciMapperList.begin()+i);
			}
		}
	}

	size_t IndexOfEntity(Entity entity)
	{
		
		for (int i = 0; i < eciMapperList.size(); i++)
		{
			if (eciMapperList[i].entity == entity)
			{
				return eciMapperList[i].componentIndex;
			}
		}
		return std::numeric_limits<size_t>::max();
	}

	size_t TotalSize()
	{
		return eciMapperList.size();
	}

private:
	struct Mapper {
		Entity entity;
		uint8_t componentIndex;
	};
	std::vector<Mapper> eciMapperList;
};