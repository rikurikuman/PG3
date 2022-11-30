#include <iostream>
#include <string>
#include "List.h"

using namespace std;

int main() {
	enum Scene {
		Main,
		View,
		View_All,
		View_Select,
		Insert,
		Edit,
		Delete,
		Swap
	};

	List<std::string> list;
	int state = 0;

	while (true) {
		if (state == Main) {
			cout << "[�v�f�̑���]\n";
			cout << "1.�v�f�̕\��\n";
			cout << "2.�v�f�̑}��\n";

			if (!list.Empty()) {
				cout << "3.�v�f�̕ҏW\n";
				cout << "4.�v�f�̍폜\n";
			}

			cout << "----------------------------------------\n";
			cout << "�����I�����Ă�������\n";

			string _input;
			getline(cin, _input);

			int input;
			try {
				input = stoi(_input);
			}
			catch (...) {
				input = -1;
			}

			if (input == 1) {
				state = View;
			}
			if (input == 2) {
				state = Insert;
			}
			if (!list.Empty()) {
				if (input == 3) {
					state = Edit;
				}
				if (input == 4) {
					state = Delete;
				}
			}
		}
		else if (state == View) {
			cout << "[�v�f�̕\��]\n";
			cout << "1.�v�f�̈ꗗ�\��\n";
			cout << "2.�ʒu���w�肵�ėv�f��\��\n";
			cout << "0.�v�f�̑���ɖ߂�\n";
			cout << "----------------------------------------\n";
			cout << "�����I�����Ă�������\n";

			string _input;
			getline(cin, _input);

			int input;
			try {
				input = stoi(_input);
			}
			catch (...) {
				input = -1;
			}

			if (input == 1) {
				state = View_All;
			}
			if (input == 2) {
				state = View_Select;
			}
			if (input == 0) {
				state = Main;
			}
		}
		else if (state == View_All) {
			cout << "[�v�f�̈ꗗ�\��]\n";
			cout << "�v�f�ꗗ: {\n";

			int i = 0;
			for (auto itr = list.Begin(); itr != list.End(); itr++) {
				cout << "  " << i << ": \"" << *itr << "\"";
				if (i != list.Size()) {
					cout << ",";
				}
				cout << "\n";
				i++;
			}

			cout << "}\n";
			cout << "�v�f��: " << list.Size() << "\n";
			cout << "----------------------------------------\n";
			cout << "1.�v�f�̕\���ɖ߂�\n";
			cout << "2.�v�f�̑���ɖ߂�\n";

			while (true) {
				string _input;
				getline(cin, _input);

				int input;
				try {
					input = stoi(_input);
				}
				catch (...) {
					input = -1;
				}

				if (input == 1) {
					state = View;
					break;
				}
				if (input == 2) {
					state = Main;
					break;
				}
			}
		}
		else if (state == View_Select) {
			cout << "�\���������v�f�̔ԍ����w�肵�Ă�������\n";

			string input;
			getline(cin, input);

			bool ok = true;
			int index;
			try {
				index = stoi(input);
			}
			catch (...) {
				ok = false;
				cout << "�s���Ȓl���w�肳��܂���\n";
			}

			if (ok) {
				auto itr = list.At(index);
				if (itr != list.End()) {
					cout << " " << input << ": \"" << *itr << "\"\n";
				}
				else {
					cout << "�w��ԍ��̗v�f�͂���܂���\n";
				}
			}

			cout << "----------------------------------------\n";
			cout << "1.�v�f�̕\���ɖ߂�\n";
			cout << "2.�v�f�̑���ɖ߂�\n";

			while (true) {
				string _input;
				getline(cin, _input);

				int input;
				try {
					input = stoi(_input);
				}
				catch (...) {
					input = -1;
				}

				if (input == 1) {
					state = View;
					break;
				}
				if (input == 2) {
					state = Main;
					break;
				}
			}
		}
		else if (state == Insert) {
			cout << "�v�f��ǉ�����ꏊ���w�肵�Ă��������B�Ō���ɒǉ�����ꍇ�͉������͂��Ȃ��ł�������\n";

			string input;
			getline(cin, input);

			bool ok = true;
			bool back = false;
			size_t index = 0;

			if (input.empty()) {
				back = true;
			}
			else {
				try {
					index = stoull(input);
					if (index >= list.Size()) {
						ok = false;
						cout << "���X�g�͈̔͊O���w�肳��܂���\n";
					}
				}
				catch (...) {
					ok = false;
					cout << "�s���Ȓl���w�肳��܂���\n";
				}
			}

			if (ok) {
				cout << "�ǉ�����v�f�̒l���w�肵�Ă�������\n";

				string str;
				getline(cin, str);

				if (back) {
					list.PushBack(str);
					cout << "�v�f\"" << str << "\"�����X�g�̖����ɑ}������܂���\n";
				}
				else {
					auto itr = list.At(index);
					if (itr != list.End()) {
						list.Insert(itr, str);
						cout << "�v�f\"" << str << "\"��" << index << "�Ԗڂɑ}������܂���\n";
					}
					else {
						cout << index << "�Ԗڂ͑��݂��܂���\n";
					}
				}
			}
			
			cout << "----------------------------------------\n";
			cout << "Enter.�߂�\n";

			string _input;
			getline(cin, _input);
			state = Main;
		}
		else if (state == Edit) {
			cout << "�ҏW�������v�f�̔ԍ����w�肵�Ă�������\n";

			string input;
			getline(cin, input);

			bool ok = true;
			int index;
			try {
				index = stoi(input);
			}
			catch (...) {
				ok = false;
				cout << "�s���Ȓl���w�肳��܂���\n";
			}

			if (ok) {
				auto itr = list.At(index);
				if (itr != list.End()) {
					cout << "�ύX����v�f�̒l���w�肵�Ă�������\n";

					string str;
					getline(cin, str);
					*itr = str;
					cout << index << "�Ԗڂ̗v�f�̒l��\"" << *itr << "\"�ɕύX����܂���\n";
				}
				else {
					cout << "�w��ԍ��̗v�f�͂���܂���\n";
				}
			}

			cout << "----------------------------------------\n";
			cout << "Enter.�߂�\n";

			string _input;
			getline(cin, _input);
			state = Main;
		}
		else if (state == Delete) {
			cout << "�폜�������v�f�̔ԍ����w�肵�Ă�������\n";

			string input;
			getline(cin, input);

			bool ok = true;
			int index;
			try {
				index = stoi(input);
			}
			catch (...) {
				ok = false;
				cout << "�s���Ȓl���w�肳��܂���\n";
			}

			if (ok) {
				auto itr = list.At(index);
				if (itr != list.End()) {
					string save = *itr;
					list.Erase(itr);
					cout << index << "�Ԗڂ̗v�f\"" << save << "\"���폜���܂���\n";
				}
				else {
					cout << "�w��ԍ��̗v�f�͂���܂���\n";
				}
			}

			cout << "----------------------------------------\n";
			cout << "Enter.�߂�\n";

			string _input;
			getline(cin, _input);
			state = Main;
		}

		cout << "\n\n\n";
	}

	return 0;
}