#include "TaskSystem.h"
#include "Util.h"

void TaskSystem::ExecuteCommand(std::string command)
{
	std::vector<std::string> args = Util::StringSplit(command, " ");

	if (args[0] == "person") {
		if (args.size() >= 2) {
			if (args[1] == "create") {
				if (args.size() >= 5) {
					persons.emplace_back(args[2], args[3], args[4]);
					Util::SendConsole("新規メンバーを追加しました\n", Util::ConsoleColor::Green);
					return;
				}
				Util::SendConsole("引数が不正です\n", Util::ConsoleColor::Red);
				Util::SendConsole(" -> person create <id> <name> <classname>\n");
				return;
			}
			if (args[1] == "modify") {
				if (args.size() >= 5) {
					Person* hoge = nullptr;
					for (auto itr = persons.begin(); itr != persons.end(); itr++) {
						Person& person = *itr;
						if (person.id == args[2]) {
							hoge = &person;
							break;
						}
					}

					if (hoge) {
						hoge->name = args[3];
						hoge->classname = args[4];
						Util::SendConsole("メンバー情報を編集しました\n", Util::ConsoleColor::Green);
						return;
					}
					Util::SendConsole("指定されたIDのメンバーは存在しません\n", Util::ConsoleColor::Red);
					return;
				}
				Util::SendConsole("引数が不正です\n", Util::ConsoleColor::Red);
				Util::SendConsole(" -> person modify <id> <name> <classname>\n");
				return;
			}
			if (args[1] == "delete") {
				if (args.size() >= 3) {
					bool check = false;
					for (auto itr = persons.begin(); itr != persons.end();) {
						Person& person = *itr;
						if (person.id == args[2]) {
							itr = persons.erase(itr);
							check = true;
						}
						else {
							itr++;
						}
					}

					if (check) {
						Util::SendConsole("メンバーを削除しました\n", Util::ConsoleColor::Green);
						return;
					}
					Util::SendConsole("指定されたIDのメンバーは存在しませんでした\n", Util::ConsoleColor::Yellow);
					return;
				}
				Util::SendConsole("引数が不正です\n", Util::ConsoleColor::Red);
				Util::SendConsole(" -> person delete <id>\n");
				return;
			}
			if (args[1] == "list") {
				Util::SendConsole("[メンバー一覧]\n", Util::ConsoleColor::White);

				for (auto itr = persons.begin(); itr != persons.end(); itr++) {
					Person& person = *itr;
					Util::SendConsole(person.id + " - " + person.name + "(" + person.classname + ")\n");
				}
				Util::SendConsole("以上" + std::to_string(persons.size()) + "名\n", Util::ConsoleColor::White);
				return;
			}
		}
		
		Util::SendConsole("[Command: person]\n", Util::ConsoleColor::Purple);

		Util::SendConsole(" person create <id> <name> <classname>\n", Util::ConsoleColor::White);
		Util::SendConsole("   - メンバーを追加します\n", Util::ConsoleColor::White);
		Util::SendConsole("   id : メンバーが持つIDを指定します\n");
		Util::SendConsole("   name : メンバーの名前を指定します\n");
		Util::SendConsole("   classname : メンバーの所属クラス名を指定します\n");
		Util::SendConsole("\n");
		Util::SendConsole(" person modify <id> <name> <classname>\n", Util::ConsoleColor::White);
		Util::SendConsole("   - メンバーの情報を編集します\n", Util::ConsoleColor::White);
		Util::SendConsole("   id : 編集するメンバーIDを指定します\n");
		Util::SendConsole("   name : メンバーの名前を指定します\n");
		Util::SendConsole("   classname : メンバーの所属クラス名を指定します\n");
		Util::SendConsole("\n");
		Util::SendConsole(" person delete <id>\n", Util::ConsoleColor::White);
		Util::SendConsole("   - メンバーを削除します\n", Util::ConsoleColor::White);
		Util::SendConsole("   id : 削除するメンバーIDを指定します\n");
		Util::SendConsole("\n");
		Util::SendConsole(" person list\n", Util::ConsoleColor::White);
		Util::SendConsole("   - 全メンバーを表示します\n", Util::ConsoleColor::White);
		Util::SendConsole("\n");
		return;
	}

	if (args[0] == "task") {
		if (args.size() >= 2) {
			if (args[1] == "create") {
				if (args.size() >= 5) {
					Task task;
					
					task.id = counter;
					task.title = args[2];
					task.body = args[3];
					task.picID = args[4];
					if (args.size() >= 6) {
						try {
							int priority = std::stoi(args[5]);
							task.priority = priority;
						}
						catch (...) {
							Util::SendConsole("優先度にはint型で表せる整数値を指定してください\n", Util::ConsoleColor::Red);
							return;
						}
					}
					if (args.size() >= 7) {
						task.deadline = args[6];
					}

					counter++;
					tasks.push_back(task);
					Util::SendConsole("新規タスクを追加しました\n", Util::ConsoleColor::Green);
					return;
				}
				Util::SendConsole("引数が不正です\n", Util::ConsoleColor::Red);
				Util::SendConsole(" -> task create <title> <body> <picID> [priority] [deadline]\n");
				return;
			}
			if (args[1] == "modify") {
				if (args.size() >= 6) {
					size_t id;

					try {
						id = std::stoi(args[2]);
					}
					catch (...) {
						Util::SendConsole("IDが不正です\n", Util::ConsoleColor::Red);
						return;
					}

					Task* task = nullptr;
					for (auto itr = tasks.begin(); itr != tasks.end(); itr++) {
						Task& _task = *itr;
						if (_task.id ==id) {
							task = &_task;
							break;
						}
					}

					if (task) {
						task->title = args[3];
						task->body = args[4];
						task->picID = args[5];
						if (args.size() >= 7) {
							try {
								int priority = std::stoi(args[6]);
								task->priority = priority;
							}
							catch (...) {
								Util::SendConsole("優先度にはint型で表せる整数値を指定してください\n", Util::ConsoleColor::Red);
								return;
							}
						}
						if (args.size() >= 8) {
							task->deadline = args[7];
						}
						Util::SendConsole("タスク情報を編集しました\n", Util::ConsoleColor::Green);
						return;
					}
					Util::SendConsole("指定されたIDのタスクは存在しません\n", Util::ConsoleColor::Red);
					return;
				}
				Util::SendConsole("引数が不正です\n", Util::ConsoleColor::Red);
				Util::SendConsole(" -> task modify <id> <title> <body> <picID> [priority] [deadline]\n");
				return;
			}
			if (args[1] == "delete") {
				if (args.size() >= 3) {
					size_t id;

					try {
						id = std::stoi(args[2]);
					}
					catch (...) {
						Util::SendConsole("IDが不正です\n", Util::ConsoleColor::Red);
						return;
					}

					bool check = false;
					for (auto itr = tasks.begin(); itr != tasks.end();) {
						Task& task = *itr;
						if (task.id == id) {
							itr = tasks.erase(itr);
							check = true;
						}
						else {
							itr++;
						}
					}

					if (check) {
						Util::SendConsole("タスクを削除しました\n", Util::ConsoleColor::Green);
						return;
					}
					Util::SendConsole("指定されたIDのタスクは存在しませんでした\n", Util::ConsoleColor::Yellow);
					return;
				}
				Util::SendConsole("引数が不正です\n", Util::ConsoleColor::Red);
				Util::SendConsole(" -> task delete <id>\n");
				return;
			}
			if (args[1] == "status") {
				if (args.size() >= 3) {
					size_t id;

					try {
						id = std::stoi(args[2]);
					}
					catch (...) {
						Util::SendConsole("IDが不正です\n", Util::ConsoleColor::Red);
						return;
					}

					Task* task = nullptr;
					for (auto itr = tasks.begin(); itr != tasks.end(); itr++) {
						Task& _task = *itr;
						if (_task.id == id) {
							task = &_task;
							break;
						}
					}

					if (task) {
						if (args.size() >= 4) {
							bool check = false;
							if (args[3] == "not_started") {
								task->status = Task::Status::NOT_STARTED;
								check = true;
							}
							else if (args[3] == "in_progress") {
								task->status = Task::Status::IN_PROGRESS;
								check = true;
							}
							else if (args[3] == "finish") {
								task->status = Task::Status::FINISH;
								check = true;
							}
							else if (args[3] == "impossible") {
								task->status = Task::Status::IMPOSSIBLE;
								check = true;
							}

							if (check) {
								Util::SendConsole("タスクの状態を更新しました\n", Util::ConsoleColor::Green);
								return;
							}
							Util::SendConsole("状態名が不正です\n", Util::ConsoleColor::Red);
							Util::SendConsole(" - not_started : 未着手\n");
							Util::SendConsole(" - in_progress : 作業中\n");
							Util::SendConsole(" - finish : 完了\n");
							Util::SendConsole(" - impossible : 無理だろこれ！！！\n");
							return;
						}
						else {
							Util::SendConsole("ID:" + std::to_string(id) + "のタスクの状態は");

							if (task->status == Task::Status::NOT_STARTED) {
								Util::SendConsole("未着手", Util::ConsoleColor::Red);
							}
							else if (task->status == Task::Status::IN_PROGRESS) {
								Util::SendConsole("作業中", Util::ConsoleColor::Yellow);
							}
							else if (task->status == Task::Status::FINISH) {
								Util::SendConsole("完了", Util::ConsoleColor::Green);
							}
							else if (task->status == Task::Status::IMPOSSIBLE) {
								Util::SendConsole("無理だろこれ！！！", Util::ConsoleColor::Purple);
							}
							else {
								Util::SendConsole("不明");
							}
							Util::SendConsole("です\n");
						}
						return;
					}
					Util::SendConsole("指定されたIDのタスクは存在しませんでした\n", Util::ConsoleColor::Yellow);
					return;
				}
				Util::SendConsole("引数が不正です\n", Util::ConsoleColor::Red);
				Util::SendConsole(" -> task status <id>\n");
				return;
			}
			if (args[1] == "list") {
				Util::SendConsole("[タスク一覧]\n", Util::ConsoleColor::White);

				for (auto itr = tasks.begin(); itr != tasks.end(); itr++) {
					Task& task = *itr;
					
					Util::SendConsole(std::to_string(task.id) + " - " + task.title + "\n " + task.body + "\n", Util::ConsoleColor::White);

					Person* pic = nullptr;
					for (auto itr = persons.begin(); itr != persons.end(); itr++) {
						Person& person = *itr;
						if (person.id == task.picID) {
							pic = &person;
							break;
						}
					}

					if (pic) {
						Util::SendConsole("  担当者: " + task.picID + "(" + pic->name + ")\n");
					}
					else {
						Util::SendConsole("  担当者: " + task.picID + "(");
						Util::SendConsole("不明なメンバー", Util::ConsoleColor::Red);
						Util::SendConsole(")\n");
					}

					Util::SendConsole("  優先度: " + std::to_string(task.priority) + "\n");
					Util::SendConsole("  期限: " + task.deadline + "\n");

					Util::SendConsole("  状態: ");

					if (task.status == Task::Status::NOT_STARTED) {
						Util::SendConsole("未着手", Util::ConsoleColor::Red);
					}
					else if (task.status == Task::Status::IN_PROGRESS) {
						Util::SendConsole("作業中", Util::ConsoleColor::Yellow);
					}
					else if (task.status == Task::Status::FINISH) {
						Util::SendConsole("完了", Util::ConsoleColor::Green);
					}
					else if (task.status == Task::Status::IMPOSSIBLE) {
						Util::SendConsole("無理だろこれ！！！", Util::ConsoleColor::Purple);
					}
					else {
						Util::SendConsole("不明");
					}
					Util::SendConsole("\n");


				}
				Util::SendConsole("以上" + std::to_string(tasks.size()) + "タスク\n", Util::ConsoleColor::White);
				return;
			}
		}

		Util::SendConsole("[Command: task]\n", Util::ConsoleColor::Purple);

		Util::SendConsole(" task create <title> <body> <picID> [priority] [deadline]\n", Util::ConsoleColor::White);
		Util::SendConsole("   - タスクを追加します\n", Util::ConsoleColor::White);
		Util::SendConsole("   title : タスクのタイトルを指定します\n");
		Util::SendConsole("   body : タスクの内容を指定します\n");
		Util::SendConsole("   picID : 担当者を指定します\n");
		Util::SendConsole("   priority : 優先度を指定します(任意)\n");
		Util::SendConsole("   deadline : 期限を指定します(任意)\n");
		Util::SendConsole("\n");
		Util::SendConsole(" task modify <id> <title> <body> <picID> [priority] [deadline]\n", Util::ConsoleColor::White);
		Util::SendConsole("   - タスクの情報を編集します\n", Util::ConsoleColor::White);
		Util::SendConsole("   id : 編集するタスクIDを指定します\n");
		Util::SendConsole("   title : タスクのタイトルを指定します\n");
		Util::SendConsole("   body : タスクの内容を指定します\n");
		Util::SendConsole("   picID : 担当者を指定します\n");
		Util::SendConsole("   priority : 優先度を指定します(任意)\n");
		Util::SendConsole("   deadline : 期限を指定します(任意)\n");
		Util::SendConsole("\n");
		Util::SendConsole(" task delete <id>\n", Util::ConsoleColor::White);
		Util::SendConsole("   - タスクを削除します\n", Util::ConsoleColor::White);
		Util::SendConsole("   id : 削除するタスクIDを指定します\n");
		Util::SendConsole("\n");
		Util::SendConsole(" task status <id> [change]\n", Util::ConsoleColor::White);
		Util::SendConsole("   - タスクの状態を確認/変更します\n", Util::ConsoleColor::White);
		Util::SendConsole("   id : タスクのIDを指定します\n");
		Util::SendConsole("   change : 変更後の状態を指定します(任意)\n");
		Util::SendConsole("     - 指定できる状態は以下の通り\n");
		Util::SendConsole("     - not_started : 未着手\n");
		Util::SendConsole("     - in_progress : 作業中\n");
		Util::SendConsole("     - finish : 完了\n");
		Util::SendConsole("     - impossible : 無理だろこれ！！！\n");
		Util::SendConsole("\n");
		Util::SendConsole(" task list\n", Util::ConsoleColor::White);
		Util::SendConsole("   - 全メンバーを表示します\n", Util::ConsoleColor::White);
		Util::SendConsole("\n");
		return;
	}

	Util::SendConsole("不明なコマンドです\n", Util::ConsoleColor::Red);
	Util::SendConsole("[コマンド一覧]\n", Util::ConsoleColor::Purple);
	Util::SendConsole("person : メンバー管理のコマンドです\n");
	Util::SendConsole("task : タスク管理のコマンドです\n");
}
