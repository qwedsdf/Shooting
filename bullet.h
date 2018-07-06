#pragma once
#include "Dxlib.h"
#include"Flow.h"
#include "Math.h"
class bullet:public Flow
{
private:
	
	double x;
	double y;
	double spd;
	double rota;
	float radius;//半径
	bool flg;

public:
	bullet(date *d);
	~bullet();

	//数値検出
	double getX(){ return x; }
	double getY(){ return y; }
	bool getFlg(){ return flg; }
	float getRadius(){ return radius; }

	//機能的関数
	void action(double rota);
	void setPos(int px, int py, double rota);
	void move();
	void clear_b();//弾が枠外に出たら消す
	void Draw();

	//セット
	void SetFlg(bool lflg);
};

