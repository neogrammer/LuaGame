#ifndef ENTITYHANDLE_HPP__
#define ENTITYHANDLE_HPP__
#include "Entity.hpp"
class EntityMgr;

struct EntityHandle
{
	EntityId id;
	EntityMgr* entityMgr;

	EntityHandle(EntityId id, EntityMgr* entityMgr);
	

	Entity* operator->() const;
	
	Entity* get() const;

};

#endif