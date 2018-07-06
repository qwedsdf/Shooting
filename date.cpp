#include "date.h"


date::date()
{
	titleBGM = LoadSoundMem("sound/title.mp3");
	gameBGM = LoadSoundMem("sound/battle.mp3");

	wingraph = LoadGraph("image/win.png");
	//�����֌W
	LoadDivGraph("image/hit.png", 16, 4, 4, 640 / 4, 640 / 4, explosion);
	explosound = LoadSoundMem("sound/explosion.wav");
	//�e
	shotsound = LoadSoundMem("sound/shot.mp3");
	//���X�|�[��
	respwonsound = LoadSoundMem("sound/respown.mp3");
	bulletgraph = LoadGraph("image/tama01.png");
	wingraph = LoadGraph("image/win.png");
}


date::~date()
{
}

void date::PlayTitleBGM(){
	PlaySoundMem(titleBGM, DX_PLAYTYPE_BACK);
}

void date::PlayGameBGM(){
	PlaySoundMem(gameBGM, DX_PLAYTYPE_BACK);
}

void date::SoundStop(){
	StopSoundMem(titleBGM);
	StopSoundMem(gameBGM);
}