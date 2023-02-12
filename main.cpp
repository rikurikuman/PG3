#include <iostream>
#include <string>
#include "Util.h"
#include "TaskSystem.h"

using namespace std;

int main() {
	TaskSystem taskSystem;

	Util::SendConsole("好き勝手にコマンドを入力してくれよな！！！\n", Util::ConsoleColor::Green);

	while (true) {
		Util::SendConsole("> ", Util::ConsoleColor::White);
        string inputstr;
        getline(cin, inputstr);

		taskSystem.ExecuteCommand(inputstr);
	}

	system("pause");
	return 0;
}