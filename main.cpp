#include <iostream>
#include <vector>
#include <list>

using namespace std;

typedef vector<char> MyString;

MyString ConvertToMyString(const char* str) {
	MyString myStr;

	//�G�ɕϊ�����
	for (size_t i = 0; str[i] != '\0'; i++) {
		myStr.push_back(str[i]);
	}

	return myStr;
}

int main() {
	list<MyString> stations{
		ConvertToMyString("Tokyo"),
		ConvertToMyString("Kanda"),
		ConvertToMyString("Akihabara"),
		ConvertToMyString("Okachimachi"),
		ConvertToMyString("Ueno"),
		ConvertToMyString("Uguisudani"),
		ConvertToMyString("Nippori"),
		ConvertToMyString("Tabata"),
		ConvertToMyString("Komagome"),
		ConvertToMyString("Sugamo"),
		ConvertToMyString("Otsuka"),
		ConvertToMyString("Ikebukuro"),
		ConvertToMyString("Mejiro"),
		ConvertToMyString("Takadanobaba"),
		ConvertToMyString("Shin-Okubo"),
		ConvertToMyString("Shinjuku"),
		ConvertToMyString("Yoyogi"),
		ConvertToMyString("Harajuku"),
		ConvertToMyString("Shibuya"),
		ConvertToMyString("Ebisu"),
		ConvertToMyString("Meguro"),
		ConvertToMyString("Gotanda"),
		ConvertToMyString("Osaki"),
		ConvertToMyString("Shinagawa"),
		ConvertToMyString("Tamachi"),
		ConvertToMyString("Hamamatsucho"),
		ConvertToMyString("Shimbashi"),
		ConvertToMyString("Yurakucho")
	};

	cout << "==============================" << endl;
	cout << "Yamanote Line 1970" << endl;
	cout << "==============================" << endl;

	//�Ԃ��
	for (auto itr = stations.begin(); itr != stations.end(); itr++) {
		MyString str = *itr;
		for (auto itr2 = str.begin(); itr2 != str.end(); itr2++) {
			cout << *itr2;
		}
		cout << endl;
	}

	//�����闢�A�J��
	auto itr = stations.begin();
	//�c�[�܂Ői�߂đ}��
	while (*itr != ConvertToMyString("Tabata")) itr++;
	stations.insert(itr, ConvertToMyString("Nishi-Nippori"));

	cout << "==============================" << endl;
	cout << "Yamanote Line 2019" << endl;
	cout << "==============================" << endl;

	//�Ԃ��
	for (auto itr = stations.begin(); itr != stations.end(); itr++) {
		MyString str = *itr;
		for (auto itr2 = str.begin(); itr2 != str.end(); itr2++) {
			cout << *itr2;
		}
		cout << endl;
	}

	//���փQ�[�g�E�F�C�A�J��
	itr = stations.begin();
	//�c���܂Ői�߂đ}��
	while (*itr != ConvertToMyString("Tamachi")) itr++;
	stations.insert(itr, ConvertToMyString("Takanawa-Gateway"));

	cout << "==============================" << endl;
	cout << "Yamanote Line 2022" << endl;
	cout << "==============================" << endl;

	//�Ԃ��
	for (auto itr = stations.begin(); itr != stations.end(); itr++) {
		MyString str = *itr;
		for (auto itr2 = str.begin(); itr2 != str.end(); itr2++) {
			cout << *itr2;
		}
		cout << endl;
	}

	return 0;
}