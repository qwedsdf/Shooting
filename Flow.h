#pragma once

#define FLOW_TITLE 0
#define FLOW_GAME 1
#define FLOW_OVER 2
#define SIZE_X 101
#define SIZE_Y 200
#define WINDOW_X 800
#define WINDOW_Y 600


#include"DxLib.h"
#include"date.h"

class Flow
{
private:
	int titleBGM;
	int gameBGM;
protected:
	date *datec;
public:
	Flow();
	~Flow();
};

