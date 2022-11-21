#include <iostream>
#include <string>

class SceneManager final {
private:
	SceneManager() = default;
	~SceneManager() = default;
	SceneManager(const SceneManager& o) = delete;
	SceneManager& operator=(const SceneManager& o) = delete;

	int nowSceneNo = 0;

public:
	static SceneManager* GetInstance() {
		static SceneManager instance;
		return &instance;
	}

	constexpr static int maxSceneNo = 3;

	bool ChangeScene(int sceneNo) {
		if (sceneNo > maxSceneNo) {
			nowSceneNo = -1;
			return false;
		}
		nowSceneNo = sceneNo;
		return true;
	}

	int GetNowSceneNo() {
		return nowSceneNo;
	}

	std::string GetNowSceneName() {
		switch (nowSceneNo) {
		case 0:
			return "Title";
		case 1:
			return "NewGame";
		case 2:
			return "GamePlay";
		case 3:
			return "GameClear";
		default:
			return "ErrorScene";
		}
	}
};

int main() {
	SceneManager* sceneManager = SceneManager::GetInstance();

	while (true) {
		std::cout << std::to_string(sceneManager->GetNowSceneNo()) + " : " + sceneManager->GetNowSceneName() + "\n";
		std::cin.get();
		if (sceneManager->GetNowSceneNo() + 1 > sceneManager->maxSceneNo) {
			sceneManager->ChangeScene(0);
		}
		else {
			sceneManager->ChangeScene(sceneManager->GetNowSceneNo() + 1);
		}
	}

	return 0;
}