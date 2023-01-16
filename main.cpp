#include <iostream>
#include <string>
#include "List.h"
#include "Enemy.h"

using namespace std;

int main() {
	
	Enemy enemy1 = Enemy(1);
	Enemy enemy2 = Enemy(2);
	Enemy enemy3 = Enemy(3);

	while (true) {
		cout << "Enemy ID:1 は " << (enemy1.IsAlive() ? "生存" : "死亡") << "しています\n";
		cout << "Enemy ID:2 は " << (enemy2.IsAlive() ? "生存" : "死亡") << "しています\n";
		cout << "Enemy ID:3 は " << (enemy3.IsAlive() ? "生存" : "死亡") << "しています\n";

		if (!enemy1.IsAlive() && !enemy2.IsAlive() && !enemy3.IsAlive()) {
			cout << "全ての敵を破壊しました\n";
			break;
		}

		cout << "攻撃するEnemyのIDを指定してください\n";

		string _input;
		getline(cin, _input);

		int input;
		try {
			input = stoi(_input);
		}
		catch (...) {
			input = -1;
		}

		switch (input) {
		case 1:
			enemy1.Kill();
			break;
		case 2:
			enemy2.Kill();
			break;
		case 3:
			enemy3.Kill();
			break;
		}
	}
	
	system("pause");
	return 0;
}