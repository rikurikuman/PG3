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
					Util::SendConsole("�V�K�����o�[��ǉ����܂���\n", Util::ConsoleColor::Green);
					return;
				}
				Util::SendConsole("�������s���ł�\n", Util::ConsoleColor::Red);
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
						Util::SendConsole("�����o�[����ҏW���܂���\n", Util::ConsoleColor::Green);
						return;
					}
					Util::SendConsole("�w�肳�ꂽID�̃����o�[�͑��݂��܂���\n", Util::ConsoleColor::Red);
					return;
				}
				Util::SendConsole("�������s���ł�\n", Util::ConsoleColor::Red);
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
						Util::SendConsole("�����o�[���폜���܂���\n", Util::ConsoleColor::Green);
						return;
					}
					Util::SendConsole("�w�肳�ꂽID�̃����o�[�͑��݂��܂���ł���\n", Util::ConsoleColor::Yellow);
					return;
				}
				Util::SendConsole("�������s���ł�\n", Util::ConsoleColor::Red);
				Util::SendConsole(" -> person delete <id>\n");
				return;
			}
			if (args[1] == "list") {
				Util::SendConsole("[�����o�[�ꗗ]\n", Util::ConsoleColor::White);

				for (auto itr = persons.begin(); itr != persons.end(); itr++) {
					Person& person = *itr;
					Util::SendConsole(person.id + " - " + person.name + "(" + person.classname + ")\n");
				}
				Util::SendConsole("�ȏ�" + std::to_string(persons.size()) + "��\n", Util::ConsoleColor::White);
				return;
			}
		}
		
		Util::SendConsole("[Command: person]\n", Util::ConsoleColor::Purple);

		Util::SendConsole(" person create <id> <name> <classname>\n", Util::ConsoleColor::White);
		Util::SendConsole("   - �����o�[��ǉ����܂�\n", Util::ConsoleColor::White);
		Util::SendConsole("   id : �����o�[������ID���w�肵�܂�\n");
		Util::SendConsole("   name : �����o�[�̖��O���w�肵�܂�\n");
		Util::SendConsole("   classname : �����o�[�̏����N���X�����w�肵�܂�\n");
		Util::SendConsole("\n");
		Util::SendConsole(" person modify <id> <name> <classname>\n", Util::ConsoleColor::White);
		Util::SendConsole("   - �����o�[�̏���ҏW���܂�\n", Util::ConsoleColor::White);
		Util::SendConsole("   id : �ҏW���郁���o�[ID���w�肵�܂�\n");
		Util::SendConsole("   name : �����o�[�̖��O���w�肵�܂�\n");
		Util::SendConsole("   classname : �����o�[�̏����N���X�����w�肵�܂�\n");
		Util::SendConsole("\n");
		Util::SendConsole(" person delete <id>\n", Util::ConsoleColor::White);
		Util::SendConsole("   - �����o�[���폜���܂�\n", Util::ConsoleColor::White);
		Util::SendConsole("   id : �폜���郁���o�[ID���w�肵�܂�\n");
		Util::SendConsole("\n");
		Util::SendConsole(" person list\n", Util::ConsoleColor::White);
		Util::SendConsole("   - �S�����o�[��\�����܂�\n", Util::ConsoleColor::White);
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
							Util::SendConsole("�D��x�ɂ�int�^�ŕ\���鐮���l���w�肵�Ă�������\n", Util::ConsoleColor::Red);
							return;
						}
					}
					if (args.size() >= 7) {
						task.deadline = args[6];
					}

					counter++;
					tasks.push_back(task);
					Util::SendConsole("�V�K�^�X�N��ǉ����܂���\n", Util::ConsoleColor::Green);
					return;
				}
				Util::SendConsole("�������s���ł�\n", Util::ConsoleColor::Red);
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
						Util::SendConsole("ID���s���ł�\n", Util::ConsoleColor::Red);
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
								Util::SendConsole("�D��x�ɂ�int�^�ŕ\���鐮���l���w�肵�Ă�������\n", Util::ConsoleColor::Red);
								return;
							}
						}
						if (args.size() >= 8) {
							task->deadline = args[7];
						}
						Util::SendConsole("�^�X�N����ҏW���܂���\n", Util::ConsoleColor::Green);
						return;
					}
					Util::SendConsole("�w�肳�ꂽID�̃^�X�N�͑��݂��܂���\n", Util::ConsoleColor::Red);
					return;
				}
				Util::SendConsole("�������s���ł�\n", Util::ConsoleColor::Red);
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
						Util::SendConsole("ID���s���ł�\n", Util::ConsoleColor::Red);
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
						Util::SendConsole("�^�X�N���폜���܂���\n", Util::ConsoleColor::Green);
						return;
					}
					Util::SendConsole("�w�肳�ꂽID�̃^�X�N�͑��݂��܂���ł���\n", Util::ConsoleColor::Yellow);
					return;
				}
				Util::SendConsole("�������s���ł�\n", Util::ConsoleColor::Red);
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
						Util::SendConsole("ID���s���ł�\n", Util::ConsoleColor::Red);
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
								Util::SendConsole("�^�X�N�̏�Ԃ��X�V���܂���\n", Util::ConsoleColor::Green);
								return;
							}
							Util::SendConsole("��Ԗ����s���ł�\n", Util::ConsoleColor::Red);
							Util::SendConsole(" - not_started : ������\n");
							Util::SendConsole(" - in_progress : ��ƒ�\n");
							Util::SendConsole(" - finish : ����\n");
							Util::SendConsole(" - impossible : �������낱��I�I�I\n");
							return;
						}
						else {
							Util::SendConsole("ID:" + std::to_string(id) + "�̃^�X�N�̏�Ԃ�");

							if (task->status == Task::Status::NOT_STARTED) {
								Util::SendConsole("������", Util::ConsoleColor::Red);
							}
							else if (task->status == Task::Status::IN_PROGRESS) {
								Util::SendConsole("��ƒ�", Util::ConsoleColor::Yellow);
							}
							else if (task->status == Task::Status::FINISH) {
								Util::SendConsole("����", Util::ConsoleColor::Green);
							}
							else if (task->status == Task::Status::IMPOSSIBLE) {
								Util::SendConsole("�������낱��I�I�I", Util::ConsoleColor::Purple);
							}
							else {
								Util::SendConsole("�s��");
							}
							Util::SendConsole("�ł�\n");
						}
						return;
					}
					Util::SendConsole("�w�肳�ꂽID�̃^�X�N�͑��݂��܂���ł���\n", Util::ConsoleColor::Yellow);
					return;
				}
				Util::SendConsole("�������s���ł�\n", Util::ConsoleColor::Red);
				Util::SendConsole(" -> task status <id>\n");
				return;
			}
			if (args[1] == "list") {
				Util::SendConsole("[�^�X�N�ꗗ]\n", Util::ConsoleColor::White);

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
						Util::SendConsole("  �S����: " + task.picID + "(" + pic->name + ")\n");
					}
					else {
						Util::SendConsole("  �S����: " + task.picID + "(");
						Util::SendConsole("�s���ȃ����o�[", Util::ConsoleColor::Red);
						Util::SendConsole(")\n");
					}

					Util::SendConsole("  �D��x: " + std::to_string(task.priority) + "\n");
					Util::SendConsole("  ����: " + task.deadline + "\n");

					Util::SendConsole("  ���: ");

					if (task.status == Task::Status::NOT_STARTED) {
						Util::SendConsole("������", Util::ConsoleColor::Red);
					}
					else if (task.status == Task::Status::IN_PROGRESS) {
						Util::SendConsole("��ƒ�", Util::ConsoleColor::Yellow);
					}
					else if (task.status == Task::Status::FINISH) {
						Util::SendConsole("����", Util::ConsoleColor::Green);
					}
					else if (task.status == Task::Status::IMPOSSIBLE) {
						Util::SendConsole("�������낱��I�I�I", Util::ConsoleColor::Purple);
					}
					else {
						Util::SendConsole("�s��");
					}
					Util::SendConsole("\n");


				}
				Util::SendConsole("�ȏ�" + std::to_string(tasks.size()) + "�^�X�N\n", Util::ConsoleColor::White);
				return;
			}
		}

		Util::SendConsole("[Command: task]\n", Util::ConsoleColor::Purple);

		Util::SendConsole(" task create <title> <body> <picID> [priority] [deadline]\n", Util::ConsoleColor::White);
		Util::SendConsole("   - �^�X�N��ǉ����܂�\n", Util::ConsoleColor::White);
		Util::SendConsole("   title : �^�X�N�̃^�C�g�����w�肵�܂�\n");
		Util::SendConsole("   body : �^�X�N�̓��e���w�肵�܂�\n");
		Util::SendConsole("   picID : �S���҂��w�肵�܂�\n");
		Util::SendConsole("   priority : �D��x���w�肵�܂�(�C��)\n");
		Util::SendConsole("   deadline : �������w�肵�܂�(�C��)\n");
		Util::SendConsole("\n");
		Util::SendConsole(" task modify <id> <title> <body> <picID> [priority] [deadline]\n", Util::ConsoleColor::White);
		Util::SendConsole("   - �^�X�N�̏���ҏW���܂�\n", Util::ConsoleColor::White);
		Util::SendConsole("   id : �ҏW����^�X�NID���w�肵�܂�\n");
		Util::SendConsole("   title : �^�X�N�̃^�C�g�����w�肵�܂�\n");
		Util::SendConsole("   body : �^�X�N�̓��e���w�肵�܂�\n");
		Util::SendConsole("   picID : �S���҂��w�肵�܂�\n");
		Util::SendConsole("   priority : �D��x���w�肵�܂�(�C��)\n");
		Util::SendConsole("   deadline : �������w�肵�܂�(�C��)\n");
		Util::SendConsole("\n");
		Util::SendConsole(" task delete <id>\n", Util::ConsoleColor::White);
		Util::SendConsole("   - �^�X�N���폜���܂�\n", Util::ConsoleColor::White);
		Util::SendConsole("   id : �폜����^�X�NID���w�肵�܂�\n");
		Util::SendConsole("\n");
		Util::SendConsole(" task status <id> [change]\n", Util::ConsoleColor::White);
		Util::SendConsole("   - �^�X�N�̏�Ԃ��m�F/�ύX���܂�\n", Util::ConsoleColor::White);
		Util::SendConsole("   id : �^�X�N��ID���w�肵�܂�\n");
		Util::SendConsole("   change : �ύX��̏�Ԃ��w�肵�܂�(�C��)\n");
		Util::SendConsole("     - �w��ł����Ԃ͈ȉ��̒ʂ�\n");
		Util::SendConsole("     - not_started : ������\n");
		Util::SendConsole("     - in_progress : ��ƒ�\n");
		Util::SendConsole("     - finish : ����\n");
		Util::SendConsole("     - impossible : �������낱��I�I�I\n");
		Util::SendConsole("\n");
		Util::SendConsole(" task list\n", Util::ConsoleColor::White);
		Util::SendConsole("   - �S�����o�[��\�����܂�\n", Util::ConsoleColor::White);
		Util::SendConsole("\n");
		return;
	}

	Util::SendConsole("�s���ȃR�}���h�ł�\n", Util::ConsoleColor::Red);
	Util::SendConsole("[�R�}���h�ꗗ]\n", Util::ConsoleColor::Purple);
	Util::SendConsole("person : �����o�[�Ǘ��̃R�}���h�ł�\n");
	Util::SendConsole("task : �^�X�N�Ǘ��̃R�}���h�ł�\n");
}
