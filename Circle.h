
#pragma once

#define N_SIZE 30
#define MAX 5//�G�̍ő吔
#define MAX_X 800//��ʂ̍ő�lX
#define MAX_Y 600//��ʂ̍ő�lY

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
		//�Z�b�g
		void SetFlg(bool flg);
		Circle();
		Circle(float r);//�T�C�Y�w��
		~Circle();
};



