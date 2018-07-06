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
	float radius;//���a
	bool flg;

public:
	bullet(date *d);
	~bullet();

	//���l���o
	double getX(){ return x; }
	double getY(){ return y; }
	bool getFlg(){ return flg; }
	float getRadius(){ return radius; }

	//�@�\�I�֐�
	void action(double rota);
	void setPos(int px, int py, double rota);
	void move();
	void clear_b();//�e���g�O�ɏo�������
	void Draw();

	//�Z�b�g
	void SetFlg(bool lflg);
};

