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

	int shottimer;//�A�˂̃^�C�}�[
	int back1;//�w�i�摜1
	int back2;//�w�i�摜2
	int num[10];//�����̃t�H���g
	int b_x1, b_y1;//�w�i�̍��W1
	int b_x2, b_y2;//�w�i�̉摜2

public:
	FlowGame(KEY *key, date *fl);
	~FlowGame();

	void bullet_process(int Pad_num, player *Player, bullet *tama[]);
	void Player_Death(player *Player, bullet *tama[]);
	int action();
	void Draw();
};

