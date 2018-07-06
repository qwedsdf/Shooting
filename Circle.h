
#pragma once

#define N_SIZE 30
#define MAX 5//敵の最大数
#define MAX_X 800//画面の最大値X
#define MAX_Y 600//画面の最大値Y

class Circle
{
	private:
		bool flg;
		float radius;
		int x;
		int y;
		int s_X;
		int s_Y;
		int kan;
		int R, G, B;
	public:
		void Draw();
		void MoveBall();
		void c_hit();
		void Reflection();
		int GetX(){ return x; }
		int GetY(){ return y; }
		bool getFlg(){ return flg; }
		//セット
		void SetFlg(bool flg);
		Circle();
		Circle(float r);//サイズ指定
		~Circle();
};



