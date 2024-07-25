#ifndef ENTITY_HPP__
#define ENTITY_HPP__
//#include <sol.hpp>
#include <string>
#include <iostream>


using EntityId = int;

class Entity {
public:
	explicit Entity(EntityId id);

	inline const std::string& getName() const { return name; }
	inline void setName(const std::string& n) { name = n; }
	inline EntityId getId() const { return id; }
private:
	std::string name;
	EntityId id;
};
#endif