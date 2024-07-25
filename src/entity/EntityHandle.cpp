#include <pch.hpp>
#include "EntityHandle.hpp"
#include "EntityMgr.hpp"

EntityHandle::EntityHandle(EntityId id, EntityMgr* entityMgr)
: id(id)
, entityMgr(entityMgr)
{}

Entity* EntityHandle::operator->() const
{
	return get();
}



		Entity* EntityHandle::get() const {
			assert(entityMgr->entityExists(id));
			return entityMgr->getEntity(id);
		}

