#pragma once
#include "DxLib.h"
class KEY
{
private:

public:
	//•Ï”
	char Buf[256];
	bool cheack[256];
	//ŠÖ”
	void UpDateKey();
	bool OnePushKey(char Key);
	KEY();
	~KEY();
};



