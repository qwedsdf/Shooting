#include "KEY.h"



KEY::KEY()
{
	for (int i = 0; i < 256; i++){
		Buf[i] = 0;
		cheack[i] = false;
	}
}


KEY::~KEY()
{
}

//�L�[�̍X�V�i���t���[���ʂ�悤�ɂǂ����ɏ����j
void KEY::UpDateKey(){
	for (int i = 0; i < 256; i++){
		cheack[i] = Buf[i];
	}
	//�L�[�̍X�V
	GetHitKeyStateAll(Buf);
}
//�P��������
bool KEY::OnePushKey(char KEY){
	if (Buf[KEY] == 1 && !cheack[KEY]){
		cheack[KEY] = true;
		return true;
	}
	return false;
}
