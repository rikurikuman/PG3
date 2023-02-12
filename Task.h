#pragma once
#include <string>

class Task
{
public:
	enum class Status {
		NOT_STARTED,
		IN_PROGRESS,
		FINISH,
		IMPOSSIBLE
	};

	size_t id;
	std::string title;
	std::string body;
	int priority = 0;
	std::string deadline = "‚È‚µ";
	Status status = Status::NOT_STARTED;
	std::string picID;
};

