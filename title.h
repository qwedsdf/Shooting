#pragma once

#include"DxLib.h"
#include"Flow.h"
class title :public Flow
{
private:
	int backX;
	int backY;
	int backgraph;
	int Pad1, Pad2;
public:
	title(date *fl);
	~title();
	void Draw();
	int action();
};

