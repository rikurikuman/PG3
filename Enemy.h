#pragma once
class Enemy
{
public:
	static bool destroyFlag;

	int id;

	Enemy(int id) : id(id), isAlive(true) {}

	bool IsAlive() {
		return !destroyFlag && isAlive;
	}

	void Kill() {
		isAlive = false;
		destroyFlag = true;
	}

private:
	bool isAlive = false;
};

