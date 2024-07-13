#pragma once
#include <set>
#include "../utils/common.hpp"

class System
{
public:
	std::set<Entity> mEntities;
	Signature mSignature;

	virtual void Update(float DeltaTime) = 0;
};
