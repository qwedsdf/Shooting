#include "DxLib.h"
//#include "Circle.h"
#include"player.h"
#include"KEY.h"
#include"title.h"
#include"FlowGame.h"
#include"Math.h"

int flowID;

KEY *gkey;
FlowGame *game;
title *ti;
date *date1;


void init(){
	flowID = FLOW_TITLE;
	date1 = new date();
	gkey = new KEY();
	game = new FlowGame(gkey, date1);
	ti = new title(date1);
}

void appaction(){
	switch (flowID)
	{
	case FLOW_TITLE:
		flowID=ti->action();
		break;
	case FLOW_GAME:
		flowID = game->action();
		break;
	default:
		break;
	}
}

void appDrow(){
	switch (flowID)
	{
	case FLOW_TITLE:
		ti->Draw();
		break;
	case FLOW_GAME:
		game->Draw();
		break;
	default:
		break;
	}
}


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(/*横*/WINDOW_X,/*縦*/ WINDOW_Y, /*カラービットレート*/16,/*フレーム数*/ 256);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	init();
	while (ProcessMessage() != -1){
		
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1 || (GetJoypadInputState(DX_INPUT_PAD1)&PAD_INPUT_10)){
			break;
		}
		// 画面を初期化する
		ClearDrawScreen();
		//動き
		appaction();
		//描画
		appDrow();
		// 裏画面の内容を表画面に反映させる
		ScreenFlip();
		//キーの更新
		gkey->UpDateKey();

		if (ProcessMessage() < 0)break;
	}

	
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
