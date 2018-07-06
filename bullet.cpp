#include "bullet.h"


bullet::bullet(date *d)
{
	x = 0; 
	y = 0; 
	flg = false;
	spd = 30;
	rota = 0;
	radius = 15;
	datec = d;
	
}


bullet::~bullet()
{
}

void bullet::action(double rota){
	
}

void bullet::setPos(int px,int py,double p_rota){
	flg = true;
	x = px;
	y = py;
	rota = p_rota;
}

void bullet::move(){
	if (!flg)return;
	x -= cos(rota)*spd;
	y -= sin(rota)*spd;
}

//場外に出たら弾を消す
void bullet::clear_b(){
	if (flg && (x > 800 || x < 0 || y>600 || y < 0)){
		flg = false;
	}
}

void bullet::Draw(){
	if (flg){
		DrawRotaGraph((int)x, (int)y, 1.0, 0.0, datec->GetBulletGraph(), true);
	}
}

//フラグをセットする
void bullet::SetFlg(bool lflg){
	flg = lflg;
}
