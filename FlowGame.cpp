#include "FlowGame.h"



FlowGame::FlowGame(KEY *key, date *fli)
{

	p = new player(1,fli);
	p2 = new player(2, fli);
	/*for (int i = 0; i < MAX; i++){
		c[i] = new Circle();
	}*/
	for (int i = 0; i < 256; i++){
		tama[i] = new bullet(fli);
		tama2[i] = new bullet(fli);
	}
	shottimer = 0;

	//画像
	back1 = LoadGraph("image/back1a.png");
	back2 = LoadGraph("image/back2a.png");
	LoadDivGraph("image/number.png", 10, 5, 2, 310 / 5, 220 / 2, num);

	b_x1 = 0;
	b_x2 = 0;
	b_y1 = 800 - 1600;
	b_y2 = 800 - 3200;
	ky = key;
	datec = fli;
}


FlowGame::~FlowGame()
{
}


int FlowGame::action(){
	
	int Pad1 = GetJoypadInputState(DX_INPUT_PAD1);
	int Pad2 = GetJoypadInputState(DX_INPUT_PAD2);

	p->MovePlayer(DX_INPUT_PAD1);
	p2->MovePlayer(DX_INPUT_PAD2);

	p->FirstMove(1);
	p2->FirstMove(2);

	bullet_process(Pad1, p, tama);
	bullet_process(Pad2, p2, tama2);
	
	
	//弾発射後の処理
	for (int i = 0; i < 256; i++){
		tama[i]->clear_b();//画面外に出たら削除
		tama[i]->move();//弾の移動
		tama2[i]->clear_b();//画面外に出たら削除
		tama2[i]->move();//弾の移動
	}

	//下まできたら画像を上げる
	if (b_y1 == 600)b_y1 = (600 - 1600) - 1600;
	if (b_y2 == 600)b_y2 = (600 - 1600) - 1600;

	//背景をスクロール
	b_y1 += 10;
	b_y2 += 10;

	

	//弾が当たったら死
	if (p->GetRespawnflg() || p2->GetRespawnflg() || p->GetInvincibleTime()>0 || p2->GetInvincibleTime()>0)return FLOW_GAME;//どちらかがリスポーン中だったらこれより下の処理はいらない
	//プレイヤー１の死亡
	Player_Death(p, tama2);

	//プレイヤー２の死亡
	Player_Death(p2, tama);


	//シーン移行
	if (p->GetFinishTimer()>180 || p2->GetFinishTimer() > 180){
		p->AllFormat(1);
		p2->AllFormat(2);
		datec->SoundStop();
		datec->PlayTitleBGM();
		return FLOW_TITLE;
	}
	//決着後
	if (p->GetLifeCount() == 0 && p2->GetLifeCount() == 0){
		p->AllFormat(1);
		p2->AllFormat(2);
		datec->SoundStop();
		datec->PlayTitleBGM();
		return FLOW_TITLE;//引き分け時のエフェクト出来次第入れて！
	}
	else if (p->GetLifeCount() == 0) p2->WinEffect();
	else if (p2->GetLifeCount() == 0) p->WinEffect();

	return FLOW_GAME;
}

//弾が発射させた後の処理
void FlowGame::bullet_process(int Pad_num, player *Player, bullet *Bullet[]){
	//R1を押したら弾発射
	if (((Pad_num&PAD_INPUT_6)||ky->OnePushKey(KEY_INPUT_LSHIFT))&&!Player->GetRespawnflg() && Player->GetLifeflg()){
		if (!Player->GetShotflg())Player->shotTimerFormat();
		Player->InvincibleTimeFormat();
		Player->setShotFlg(true);
		Player->shotTimerIn();
		if (Player->GetTimer() % KANKAKU == 1){
			Player->shotSoundPlay();
			for (int i = 0; i < 256; i++){
				//フラグを確認して空いてたら弾のデータを入れる
				if (!Bullet[i]->getFlg()){
					Bullet[i]->setPos((int)Player->Getpx(), (int)Player->Getpy(), Player->GetRota());
					break;
				}
			}
		}
	}
	//ボタンを押してないときはフラグを初期化
	else Player->setShotFlg(false);
}
//プレイヤーが死んだときの処理

void FlowGame::Player_Death(player *Player, bullet *Bullet[]){
	for (int i = 0; i < 256; i++){
		//ここから下を関数化して
		if (!Bullet[i]->getFlg())continue;
		if ((Player->Getpx() - Bullet[i]->getX())*(Player->Getpx() - Bullet[i]->getX()) +
			(Player->Getpy() - Bullet[i]->getY())*(Player->Getpy() - Bullet[i]->getY()) <=
			Bullet[i]->getRadius()*Bullet[i]->getRadius()){
			Player->setDeathPos();
			Player->exploSoundPlay();
			Player->setLifeFlg(false);
			break;
		}
	}
}

void FlowGame::Draw(){
	
	//背景
	DrawGraph(b_x1, b_y1, back1, false);
	DrawGraph(b_x2, b_y2, back2, false);

	//たま
	for (int i = 0; i < 256; i++){
		tama[i]->Draw();
		tama2[i]->Draw();
	}
	//プレイヤー
	p->Draw();
	p2->Draw();

	DrawGraph(0, 0, num[p->GetLifeCount()],true);
	DrawGraph(800 - 310 / 5, 0, num[p2->GetLifeCount()], true);
}
