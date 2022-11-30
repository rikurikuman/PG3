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
			cout << "[要素の操作]\n";
			cout << "1.要素の表示\n";
			cout << "2.要素の挿入\n";

			if (!list.Empty()) {
				cout << "3.要素の編集\n";
				cout << "4.要素の削除\n";
			}

			cout << "----------------------------------------\n";
			cout << "操作を選択してください\n";

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
			cout << "[要素の表示]\n";
			cout << "1.要素の一覧表示\n";
			cout << "2.位置を指定して要素を表示\n";
			cout << "0.要素の操作に戻る\n";
			cout << "----------------------------------------\n";
			cout << "操作を選択してください\n";

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
			cout << "[要素の一覧表示]\n";
			cout << "要素一覧: {\n";

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
			cout << "要素数: " << list.Size() << "\n";
			cout << "----------------------------------------\n";
			cout << "1.要素の表示に戻る\n";
			cout << "2.要素の操作に戻る\n";

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
			cout << "表示したい要素の番号を指定してください\n";

			string input;
			getline(cin, input);

			bool ok = true;
			int index;
			try {
				index = stoi(input);
			}
			catch (...) {
				ok = false;
				cout << "不正な値が指定されました\n";
			}

			if (ok) {
				auto itr = list.At(index);
				if (itr != list.End()) {
					cout << " " << input << ": \"" << *itr << "\"\n";
				}
				else {
					cout << "指定番号の要素はありません\n";
				}
			}

			cout << "----------------------------------------\n";
			cout << "1.要素の表示に戻る\n";
			cout << "2.要素の操作に戻る\n";

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
			cout << "要素を追加する場所を指定してください。最後尾に追加する場合は何も入力しないでください\n";

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
						cout << "リストの範囲外が指定されました\n";
					}
				}
				catch (...) {
					ok = false;
					cout << "不正な値が指定されました\n";
				}
			}

			if (ok) {
				cout << "追加する要素の値を指定してください\n";

				string str;
				getline(cin, str);

				if (back) {
					list.PushBack(str);
					cout << "要素\"" << str << "\"がリストの末尾に挿入されました\n";
				}
				else {
					auto itr = list.At(index);
					if (itr != list.End()) {
						list.Insert(itr, str);
						cout << "要素\"" << str << "\"が" << index << "番目に挿入されました\n";
					}
					else {
						cout << index << "番目は存在しません\n";
					}
				}
			}
			
			cout << "----------------------------------------\n";
			cout << "Enter.戻る\n";

			string _input;
			getline(cin, _input);
			state = Main;
		}
		else if (state == Edit) {
			cout << "編集したい要素の番号を指定してください\n";

			string input;
			getline(cin, input);

			bool ok = true;
			int index;
			try {
				index = stoi(input);
			}
			catch (...) {
				ok = false;
				cout << "不正な値が指定されました\n";
			}

			if (ok) {
				auto itr = list.At(index);
				if (itr != list.End()) {
					cout << "変更する要素の値を指定してください\n";

					string str;
					getline(cin, str);
					*itr = str;
					cout << index << "番目の要素の値が\"" << *itr << "\"に変更されました\n";
				}
				else {
					cout << "指定番号の要素はありません\n";
				}
			}

			cout << "----------------------------------------\n";
			cout << "Enter.戻る\n";

			string _input;
			getline(cin, _input);
			state = Main;
		}
		else if (state == Delete) {
			cout << "削除したい要素の番号を指定してください\n";

			string input;
			getline(cin, input);

			bool ok = true;
			int index;
			try {
				index = stoi(input);
			}
			catch (...) {
				ok = false;
				cout << "不正な値が指定されました\n";
			}

			if (ok) {
				auto itr = list.At(index);
				if (itr != list.End()) {
					string save = *itr;
					list.Erase(itr);
					cout << index << "番目の要素\"" << save << "\"を削除しました\n";
				}
				else {
					cout << "指定番号の要素はありません\n";
				}
			}

			cout << "----------------------------------------\n";
			cout << "Enter.戻る\n";

			string _input;
			getline(cin, _input);
			state = Main;
		}

		cout << "\n\n\n";
	}

	return 0;
}