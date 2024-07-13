#pragma once
#include <memory>
#include <unordered_map>
#include "../utils/common.hpp"
#include "system.hpp"

class SystemHandler
{
public:
	template<typename T>
	std::shared_ptr<T> CreateSystem()
	{
		const char* typeName = typeid(T).name();

		auto system = std::make_shared<T>();
		mSystems.insert({ typeName, system });
		return system;
	}

	template<typename T>
	void SetSignature(Signature signature)
	{
		const char* typeName = typeid(T).name();

		std::shared_ptr<System>& a = mSystems.find(typeName)->second;
		
		a->mSignature = signature;
	}

	void EntityDestroyed(Entity entity)
	{
		for (auto const& pair : mSystems)
		{
			auto const& system = pair.second;

			system->mEntities.erase(entity);
		}
	}

	void UpdateEntitySignature(Entity entity, Signature entitySignature)
	{

		for (auto const& pair : mSystems)
		{
			auto const& type = pair.first;
			auto const& system = pair.second;
			Signature systemSignature = pair.second->mSignature;

			if ((entitySignature & systemSignature) == systemSignature)
			{
				system->mEntities.insert(entity);
			}
			else
			{
				system->mEntities.erase(entity);
			}
		}
	}

	void UpdateSystems(float DeltaTime)
	{
		for (auto const& pair : mSystems)
		{
			auto const& system = pair.second;
			system->Update(DeltaTime);
		}
	}

	size_t NumberOfSystems()
	{
		return mSystems.size();
	}

private:
	std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};
};
