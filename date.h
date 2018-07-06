#pragma once

#include"DxLib.h"
class date
{
private:
	int titleBGM;
	int gameBGM;
	int explosion[16];
	int wingraph;
	int explosound;
	int shotsound;
	int respwonsound;
	int bulletgraph;

public:
	date();
	~date();
	void PlayTitleBGM();
	void PlayGameBGM();
	void SoundStop();

	//ƒQƒbƒg
	//bulletŠÖŒW
	int GetBulletGraph(){ return bulletgraph; }
	//playerŠÖŒW
	int GetExplosionGraph(int num){ return explosion[num]; }
	int GetExploSound(){ return explosound; }
	int GetShotSound(){ return shotsound; }
	int GetRespwonSound(){ return respwonsound; }
	int GetWinGraph(){ return wingraph; }
};

