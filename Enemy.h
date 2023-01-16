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
		std::cout << "Enemy ID:" << id << " �� " << (IsAlive() ? "����" : "���S") << "���Ă��܂�\n";
		if (IsAlive()) {
			(this->*actionFunc)();
		}
	}

	void Kill() {
		isAlive = false;
	}

	void Melee() {
		std::cout << "Enemy ID:" << id << " �� �ߐڍU�����s���I\n";
		actionFunc = &Enemy::Ranged;
	}

	void Ranged() {
		std::cout << "Enemy ID:" << id << " �� �ˌ��U�����s���I\n";
		actionFunc = &Enemy::Escape;
	}

	void Escape() {
		std::cout << "Enemy ID:" << id << " �� ���̏�𗣒E����I\n";
		actionFunc = &Enemy::Melee;
	}

private:
	bool isAlive = false;
};

