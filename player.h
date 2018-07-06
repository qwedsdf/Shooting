#include "Dxlib.h"
#include"math.h"
#include"Flow.h"
#include"date.h"
//#include"OnlyOne.h"

#define PI    3.1415926535897932384626433832795
#define KANKAKU 10
#define SPDX 10
#define SPDY 10
#define ROTASPD 20
#define LIFE 3
#define MUTEKITIME 2




#pragma once
class player:public Flow
{
private:
	//数値変数
	double px;
	double py;
	double resetposX;
	double resetposY;
	double firstPosY;//復帰時に使う
	double deathX;
	double deathY;
	double Rspd;//復帰時、スタート時に与えるスピード
	double vectorX;//方向転換に使う
	double vectorY;
	double m_vectorX;//移動につかうベクター
	double m_vectorY;
	int lifecount;//残機数

	double size;//自機の大きさ

	//タイマー
	int shottimer;//連射のタイマー
	int anitimer;//爆発エフェクト用タイマー
	int finishtimer;//ゲーム終了後にタイトルに戻るまでに使うタイマー
	int InvincibleTime;//無敵時間

	//グラフィック関連
	int graph;

	//フラグ
	bool shotflg;//ボタンの連射に使うフラグ
	bool lifeflg;//生存確認
	bool respawnflg;//リスポーン確認
	bool winflg;//勝ったときのフラグ
	bool firstflg;//最初の登場が終わったかどうか

	//アナログスティックの入力を取得
	int /*左スティック*/InputX, InputY, /*右スティック*/r_InputX, r_InputY;
	//セーブする角度
	int saveX, saveY, m_saveX, m_saveY;
	double save;//pRotaを保存するのに使う
	double pRota;//機体が向きたい角度(目標)
	double rRota;//機体自体が今向いてる角度
	double moveRota;//移動に使う角度
	bool keyflg;

public:
	player(int p_num, date *d);
	~player();

	//ゲット系
	double Getpx(){ return px; }
	double Getpy(){ return py; }
	double GetRota(){ return pRota; }
	bool GetShotflg(){ return shotflg; }
	bool GetRespawnflg(){ return respawnflg; }
	bool GetLifeflg() {	return lifeflg; }
	int GetTimer(){ return shottimer; }
	int GetLifeCount(){ return lifecount; }
	int GetFinishTimer(){ return finishtimer; }
	int GetInvincibleTime(){ return InvincibleTime; }

	//セット系
	void setShotFlg(bool flg);
	void setLifeFlg(bool flg);
	void setDeathPos();
	void InvincibleTimeFormat();
	void FirstPosFormat();

	//機能関数
	void checkPos();
	void MovePlayer(int playerNum);
	void FirstMove(int num);
	void Draw();

	//最大連射数を定めるための関数
	void shotTimerIn(){	shottimer++;	}//弾が打てるまでのタイムをプラス
	void shotTimerFormat(){	shottimer = 0;	}//タイマーを初期化
	void WinEffect();//勝利演出
	void AllFormat(int num);

	//その他
	void exploSoundPlay(){	PlaySoundMem(datec->GetExploSound(), DX_PLAYTYPE_BACK);	}
	void shotSoundPlay(){	PlaySoundMem(datec->GetShotSound(), DX_PLAYTYPE_BACK);	}

};

