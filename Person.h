#pragma once
#include <string>

class Person
{
public:
	std::string id;
	std::string name;
	std::string classname;

	Person(std::string id, std::string name, std::string classname)
		: id(id), name(name), classname(classname) {}
};

