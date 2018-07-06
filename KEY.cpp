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

//キーの更新（毎フレーム通るようにどこかに書く）
void KEY::UpDateKey(){
	for (int i = 0; i < 256; i++){
		cheack[i] = Buf[i];
	}
	//キーの更新
	GetHitKeyStateAll(Buf);
}
//単押し判定
bool KEY::OnePushKey(char KEY){
	if (Buf[KEY] == 1 && !cheack[KEY]){
		cheack[KEY] = true;
		return true;
	}
	return false;
}
