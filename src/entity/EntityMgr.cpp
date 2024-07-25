#include <pch.hpp>
#include "EntityMgr.hpp"

EntityMgr::EntityMgr() 
	: idCounter(0) 
{
}

Entity& EntityMgr::createEntity()
{
	auto id = idCounter;
	++idCounter;
	auto inserted = entities.emplace(id, std::make_unique<Entity>(id));
	auto it = inserted.first; // iterator to created id/Entity pair
	auto& e = *it->second; // created entity
	//lua["createHandle"](e);
	return e;
}

bool EntityMgr::entityExists(EntityId id)
{
	return (entities.find(id) != entities.end());
}

Entity* EntityMgr::getEntity(EntityId id)
{
	return entities.at(id).get();
}

void EntityMgr::removeEntity(EntityId id)
{
	//lua["onEntityRemoved"](id);
	entities.erase(id);
}

