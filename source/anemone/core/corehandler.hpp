#pragma once
#include <array>
#include <queue>
#include <memory>
#include <set>
#include "../utils/common.hpp"
#include "componenthandler.hpp"
#include "systemhandler.hpp"
#include "../logger/logger.hpp"

class CoreHandler
{
public:
	void Init()
	{
		InitEntityQueue();
		mComponentHandler = std::make_unique<ComponentHandler>();
		mSystemHandler = std::make_unique<SystemHandler>();
	}

	void InitEntityQueue()
	{
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			mAvailableEntities.push(entity);
		}
	}

	Entity CreateEntity()
	{

		check_assert(mEntityActiveCount < MAX_ENTITIES, "Too Many entities ! ");
	
		Entity id = mAvailableEntities.front();
		mAvailableEntities.pop();
		++mEntityActiveCount;

		Logger::Log("Entity Created ! ");

		return id;
	}

	void DestroyEntity(Entity entity)
	{
		check_assert(entity < MAX_ENTITIES, "Entity non existent ! ");
		
		mSignatureList[entity].reset();
		mAvailableEntities.push(entity);
		--mEntityActiveCount;

		mComponentHandler->EntityDestroyed(entity);

		mSystemHandler->EntityDestroyed(entity);
		
		Logger::Log("Entity Destroyed ! ");
	}

	void setSignature(Entity entity, Signature signature)
	{
		check_assert(entity < MAX_ENTITIES, "Entity non existent ! ");

		mSignatureList[entity] = signature;
	}

	Signature GetSignature(Entity entity)
	{
		check_assert(entity < MAX_ENTITIES, "Entity nont existent ! ");

		return mSignatureList[entity];
	}

	template<typename T>
	void CreateComponent()
	{
		mComponentHandler->CreateComponent<T>();
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		return mComponentHandler->GetComponent<T>(entity);
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		return mComponentHandler->GetComponentType<T>();
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		mComponentHandler->AddComponent(entity, component);

		auto signature = GetSignature(entity);
		signature.set(mComponentHandler->GetComponentType<T>(), true);
		setSignature(entity, signature);

		mSystemHandler->UpdateEntitySignature(entity, signature);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		mComponentHandler->RemoveComponent<T>(entity);

		auto signature = GetSignature(entity);
		signature.set(mComponentHandler->GetComponentType<T>(), false);
		setSignature(entity, signature);

		mSystemHandler->UpdateEntitySignature(entity, signature);
	}

	template<typename T>
	bool HasComponent(Entity entity)
	{
		// verify if the entity has a component
		return mComponentHandler->HasComponent<T>(entity);
	}

	template<typename T>
	std::shared_ptr<T> CreateSystem()
	{
		return mSystemHandler->CreateSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(Signature signature)
	{
		mSystemHandler->SetSignature<T>(signature);
	}

	void UpdateSystems(float DeltaTime)
	{
		mSystemHandler->UpdateSystems(DeltaTime);
	}

	template<size_t T>
	void PrintSignature(const std::bitset<T>& bits) {
		for (size_t i = 0; i < bits.size(); ++i) {
			std::cout << bits[i];
		}
		std::cout << std::endl;
	}

	void NumberOfSystems()
	{
		Logger::Log("Number of systems is " + std::to_string(mSystemHandler->NumberOfSystems()));
	}

	void BatchRemoveEntities()
	{
		for(auto entt : mEntitiesToRemove)
		{
			DestroyEntity(entt);
		}

		mEntitiesToRemove.clear();
	}

	void addToRemoveEntity(Entity entity)
	{
		mEntitiesToRemove.insert(entity);
	}

	void Update()
	{
		BatchRemoveEntities();
	}

private:

	std::set<Entity> mEntitiesToRemove;

	std::unique_ptr<ComponentHandler> mComponentHandler;
	std::unique_ptr<SystemHandler> mSystemHandler;

	std::queue<Entity> mAvailableEntities;
	std::array<Signature, MAX_ENTITIES> mSignatureList{};
	uint32_t mEntityActiveCount{};
};