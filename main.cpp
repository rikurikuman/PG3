#include <iostream>
#include <string>
#include "Util.h"
#include "TaskSystem.h"

using namespace std;

int main() {
	TaskSystem taskSystem;

	Util::SendConsole("�D������ɃR�}���h����͂��Ă����ȁI�I�I\n", Util::ConsoleColor::Green);

	while (true) {
		Util::SendConsole("> ", Util::ConsoleColor::White);
        string inputstr;
        getline(cin, inputstr);

		taskSystem.ExecuteCommand(inputstr);
	}

	system("pause");
	return 0;
}