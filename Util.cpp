#include "Util.h"
#include <windows.h>
#include <math.h>
#include <iostream>

using namespace std;

bool Util::debugBool = false;
int Util::debugInt = 0;
std::bitset<64> Util::debugBit(0);

float Util::AngleToRadian(float angle)
{
	return angle * (PI / 180);
}

float Util::RadianToAngle(float radian)
{
	return radian * (180 / PI);
}

vector<string> Util::StringSplit(string s, string separator)
{
	vector<string> result;

	//��؂蕶���̒�����0�Ȃ��؂�킯���Ȃ��̂ł��̂܂ܕԂ�
	if (separator.length() == 0) {
		result.push_back(s);
		return result;
	}

	auto offset = string::size_type(0);
	while (1) {
		//��؂蕶�����o������ʒu���擾
		auto find = s.find(separator, offset);

		//������̏I�_�܂ōs������
		if (find == string::npos) {
			//�c��S�������Ă����܂�
			result.push_back(s.substr(offset));
			break;
		}

		//�����łȂ��Ȃ��؂��ĉ�����
		result.push_back(s.substr(offset, find - offset));

		//�����ς݂̏��܂ŃC�e���[�^��i�߂�
		offset = find + separator.length();
	}

	return result;
}

int Util::Clamp(int i, int min, int max) {
	if (i < min) { return min; }
	if (i > max) { return max; }
	return i;
}

float Util::Clamp(float f, float min, float max) {
	if (f < min) { return min; }
	if (f > max) { return max; }
	return f;
}

double Util::Clamp(double d, double min, double max) {
	if (d < min) { return min; }
	if (d > max) { return max; }
	return d;
}

wstring Util::ConvertStringToWString(string str) {
	//�K�v��wchar_t�z�񒷂𓾂�
	int _arraySize = MultiByteToWideChar(CP_ACP, 0, str.c_str()
		, -1, (wchar_t*)NULL, 0);

	//�z���p�ӂ���
	wchar_t* wArray = new wchar_t[_arraySize];

	//�ϊ�����wchar_t�̔z��ɂԂ�����
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wArray
		, _arraySize);

	//wstring�ɂ���
	std::wstring wStr(wArray, wArray + _arraySize - 1);

	//�z��͍ߐ[�����Ƃ�new���Ă��܂����̂�delete����
	delete[] wArray;

	//�����܂�
	return wStr;
}

int Util::GetRand(int min, int max)
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<> distr(min, max);
	return distr(eng);
}

float Util::GetRand(float min, float max)
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<float> distr(min, max);
	return distr(eng);
}

double Util::GetRand(double min, double max)
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<double> distr(min, max);
	return distr(eng);
}

void Util::SendConsole(std::string str, ConsoleColor color)
{
	std::cout << StringFormat("\x1b[%dm", color);
	std::cout << str;
	std::cout << "\x1b[0m";
}
