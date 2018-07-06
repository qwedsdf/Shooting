#pragma once
//#include "Circle.h"
#include"Flow.h"
#include"player.h"
#include"Math.h"
#include "KEY.h"
#include"bullet.h"

class FlowGame:public Flow
{
private:
	KEY *ky;
	//Circle *c[MAX];
	player *p;
	player *p2;
	bullet *tama[256];
	bullet *tama2[256];

	int shottimer;//˜AË‚Ìƒ^ƒCƒ}[
	int back1;//”wŒi‰æ‘œ1
	int back2;//”wŒi‰æ‘œ2
	int num[10];//”š‚ÌƒtƒHƒ“ƒg
	int b_x1, b_y1;//”wŒi‚ÌÀ•W1
	int b_x2, b_y2;//”wŒi‚Ì‰æ‘œ2

public:
	FlowGame(KEY *key, date *fl);
	~FlowGame();

	void bullet_process(int Pad_num, player *Player, bullet *tama[]);
	void Player_Death(player *Player, bullet *tama[]);
	int action();
	void Draw();
};

