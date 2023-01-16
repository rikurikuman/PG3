#pragma once
#include <iostream>
#include <string>

class Enemy
{
public:
	int id;
	void(Enemy::* actionFunc)();

	Enemy(int id) : id(id), isAlive(true), actionFunc(&Enemy::Melee) {}

	bool IsAlive() {
		return isAlive;
	}

	void Update() {
		std::cout << "Enemy ID:" << id << " ‚Í " << (IsAlive() ? "¶‘¶" : "Ž€–S") << "‚µ‚Ä‚¢‚Ü‚·\n";
		if (IsAlive()) {
			(this->*actionFunc)();
		}
	}

	void Kill() {
		isAlive = false;
	}

	void Melee() {
		std::cout << "Enemy ID:" << id << " ‚Í ‹ßÚUŒ‚‚ðs‚¤I\n";
		actionFunc = &Enemy::Ranged;
	}

	void Ranged() {
		std::cout << "Enemy ID:" << id << " ‚Í ŽËŒ‚UŒ‚‚ðs‚¤I\n";
		actionFunc = &Enemy::Escape;
	}

	void Escape() {
		std::cout << "Enemy ID:" << id << " ‚Í ‚»‚Ìê‚ð—£’E‚·‚éI\n";
		actionFunc = &Enemy::Melee;
	}

private:
	bool isAlive = false;
};

