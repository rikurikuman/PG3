#pragma once
#include "Person.h"
#include "Task.h"
#include <list>

class TaskSystem
{
private:
	std::list<Person> persons;
	std::list<Task> tasks;
	size_t counter = 0;

public:
	void ExecuteCommand(std::string command);

};

