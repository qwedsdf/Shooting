#pragma once
#include "DxLib.h"
class KEY
{
private:

public:
	//�ϐ�
	char Buf[256];
	bool cheack[256];
	//�֐�
	void UpDateKey();
	bool OnePushKey(char Key);
	KEY();
	~KEY();
};



