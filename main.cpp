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
		cout << "Enemy ID:1 ‚Í " << (enemy1.IsAlive() ? "¶‘¶" : "Ž€–S") << "‚µ‚Ä‚¢‚Ü‚·\n";
		cout << "Enemy ID:2 ‚Í " << (enemy2.IsAlive() ? "¶‘¶" : "Ž€–S") << "‚µ‚Ä‚¢‚Ü‚·\n";
		cout << "Enemy ID:3 ‚Í " << (enemy3.IsAlive() ? "¶‘¶" : "Ž€–S") << "‚µ‚Ä‚¢‚Ü‚·\n";

		if (!enemy1.IsAlive() && !enemy2.IsAlive() && !enemy3.IsAlive()) {
			cout << "‘S‚Ä‚Ì“G‚ð”j‰ó‚µ‚Ü‚µ‚½\n";
			break;
		}

		cout << "UŒ‚‚·‚éEnemy‚ÌID‚ðŽw’è‚µ‚Ä‚­‚¾‚³‚¢\n";

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