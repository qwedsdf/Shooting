#include "Circle.h"
#include "DxLib.h"
#include"math.h"


Circle::Circle()
{
	flg = true;
	kan = LoadSoundMem("bo.mp3");
	radius = N_SIZE;
	x = GetRand(500) + 40;
	y = GetRand(400) + 80;
	s_X = 10;
	s_Y = -10;
	R = 255;
	G = 0;
	B = 0;
}



Circle::~Circle()
{
}

void Circle ::Draw(){
	if (!flg)return;
	DrawCircle(x, y, (int)radius, GetColor(R, G, B), FALSE);
}

void Circle::MoveBall(){
	if (!flg)return;
	x += s_X;
	y += s_Y;
}

void Circle::c_hit(){
	if (!flg)return;
	//壁に当たったら反射
	if (x < radius){
		PlaySoundMem(kan, DX_PLAYTYPE_BACK);
		/*R = GetRand(255);
		G = GetRand(255);
		B = GetRand(255);*/
		x = (int)radius+1;
		s_X = s_X*-1;
	}
	if (x > MAX_X - radius){
		PlaySoundMem(kan, DX_PLAYTYPE_BACK);
		/*R = GetRand(255);
		G = GetRand(255);
		B = GetRand(255);*/
		x = MAX_X - (int)radius - 1;
		s_X = s_X*-1;
	}

	if (y < radius){
		PlaySoundMem(kan, DX_PLAYTYPE_BACK);
		/*R = GetRand(255);
		G = GetRand(255);
		B = GetRand(255);*/
		y = (int)radius + 1;
		s_Y = s_Y*-1;
	}
	if (y > MAX_Y - radius){
		PlaySoundMem(kan, DX_PLAYTYPE_BACK);
		/*R = GetRand(255);
		G = GetRand(255);
		B = GetRand(255);*/
		y = MAX_Y - (int)radius - 1;
		s_Y = s_Y*-1;
	}
}
//反射
void Circle::Reflection(){
	//PlaySoundMem(kan, DX_PLAYTYPE_BACK);
	//R = GetRand(255);
	//G = GetRand(255);
	//B = GetRand(255);
	s_X = s_X*-1;
	x += s_X;
	s_Y = s_Y*-1;
	y += s_Y;
}

//フラグをセット
void Circle::SetFlg(bool lflg){
	flg = lflg;
}


