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
		std::cout << "Enemy ID:" << id << " は " << (IsAlive() ? "生存" : "死亡") << "しています\n";
		if (IsAlive()) {
			(this->*actionFunc)();
		}
	}

	void Kill() {
		isAlive = false;
	}

	void Melee() {
		std::cout << "Enemy ID:" << id << " は 近接攻撃を行う！\n";
		actionFunc = &Enemy::Ranged;
	}

	void Ranged() {
		std::cout << "Enemy ID:" << id << " は 射撃攻撃を行う！\n";
		actionFunc = &Enemy::Escape;
	}

	void Escape() {
		std::cout << "Enemy ID:" << id << " は その場を離脱する！\n";
		actionFunc = &Enemy::Melee;
	}

private:
	bool isAlive = false;
};

