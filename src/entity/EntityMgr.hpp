#ifndef ENTITYMGR_HPP__
#define ENTITYMGR_HPP__

//#include <sol.hpp>
#include <string>
#include <iostream>
#include "Entity.hpp"
#include <unordered_map>
//extern sol::state lua;

class EntityMgr {
public:
	EntityMgr();
	
	Entity& createEntity();
	bool entityExists(EntityId id);
	Entity* getEntity(EntityId id);
	void removeEntity(EntityId id);
	
private:
	std::unordered_map<EntityId, std::unique_ptr<Entity>> entities;
	EntityId idCounter;
};
#endif
//int main()
//{
	//lua.open_libraries();

	//lua.new_usertype<Entity>("Entity",
	//	"getName", &Entity::getName,
	//	"setName", &Entity::setName,
	//	"getId", &Entity::getId);

	//lua.do_file("safe_reference.lua");

	//EntityMgr entityMgr;
	//auto& entity = entityMgr.createEntity();

	//lua["test"](entity);

	//std::cout << "Testing bad reference" << std::endl;
	//lua["testBadReference"](entity);/
//}
