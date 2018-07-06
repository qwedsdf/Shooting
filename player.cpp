#include "player.h"

player::player(int p_num,date *d)
{
	AllFormat(p_num);

	datec = d;
	if (p_num == 1)graph = LoadGraph("image/sentouki.png");
	if (p_num == 2)graph = LoadGraph("image/yogiki.png");

}


player::~player()
{
}

void player::AllFormat(int num){
	
	size = 0.2;
	lifecount = LIFE;
	px = 270 * num;
	if (num == 1){
		py = 800;
		firstPosY = py;
		resetposY = py - 400;
	}
	else {
		py = -200;
		firstPosY = py;
		resetposY = py + 400;
	}
	resetposX = px;
	deathX = 0;
	deathY = 0;
	pRota = 0;
	rRota = 90 * PI / 180;

	vectorX = 0;
	vectorY = 0;
	m_vectorX = 0;
	m_vectorY = 0;
	saveX = 0;
	if (num == 1)saveY = -1;
	else saveY = 1;//初期状態を上に向かせるために-1とする
	//m==move
	m_saveX = 0;
	m_saveX = 0;
	shottimer = 0;
	anitimer = 0;
	finishtimer = 0;
	shotflg = false;
	keyflg = false;
	respawnflg = false;
	winflg = false;
	firstflg = false;
	lifeflg = true;
	InvincibleTime = 0;
	Rspd = 12.6;
}

void player :: MovePlayer(int PlayerNum){
	if (!lifeflg)return;
	//回転方向を探すための座標
	vectorX = px;
	vectorY = py;
	keyflg = false;

	///////////方向変換と移動を別スティックでするときにコメント外してください///////////////////
	////右アナログを倒したときの処理(角度)
	if (abs(r_InputX) + abs(r_InputY)>800){
		
		//アナログスティックの入力をインプット
		saveX = r_InputX;
		saveY = r_InputY;
		
	}
	//////////////////////////////////////////////////////////////////////////////////////


	if (!winflg&&lifecount != 0 && firstflg){
		//左スティック
		GetJoypadAnalogInput(&InputX, &InputY, PlayerNum);
		//右スティック
		GetJoypadAnalogInputRight(&r_InputX, &r_InputY, PlayerNum);

		//左アナログを倒したときの処理(移動)
		if (abs(InputX) + abs(InputY) > 800){
			//機体を進める
			px -= (int)(cos(moveRota)*SPDX);
			py -= (int)(sin(moveRota)*SPDY);

			checkPos();//ポジションが画面外にならないかチェック

			//アナログスティックの入力をインプット
			m_saveX = InputX;
			m_saveY = InputY;
			//右スティックが押されてなかったら移動方向に向く
			if (abs(r_InputX) + abs(r_InputY) < 800){
				saveX = InputX;
				saveY = InputY;
			}

		}
	}

	//回転に使う座標をインプット
	vectorX = px + saveX;
	vectorY = py + saveY;
	//移動に使う座標をインプット
	m_vectorX = px + m_saveX;
	m_vectorY = py + m_saveY;
	
	//本当の目標角度をセーブする
	save = pRota;
	
	//if (keyflg){
	//機体の回転角を決める
	pRota = atan2((float)(py - vectorY), (float)(px - vectorX));

	//機体の移動角を決める
	moveRota = atan2((float)(py - m_vectorY), (float)(px - m_vectorX));

	//マイナスを消す処理
	if (pRota < 0)pRota=(360 * PI / 180) + pRota;
	save = pRota;
	//}

	//180°以上回転しようとき、角度を変える
	if (rRota - pRota >= PI)pRota = pRota + (360 * PI / 180);//左に180°以上回ることを防ぐ

	else if (pRota - rRota >= PI)pRota = pRota - (360 * PI / 180);//右に180°以上回ることを防ぐ

	//角度が0ラインを通った時に数値を直す
	if (rRota > 360 * PI / 180)rRota -= 360 * PI / 180;//右周り
	if (rRota < 0)rRota += 360 * PI / 180;//左周り


	//回転する方向を探してる
	if (rRota < pRota){
		rRota += ROTASPD * PI / 180;

		if (rRota > pRota)rRota = pRota;
	}

	else if (rRota > pRota){
		rRota -= ROTASPD * PI / 180;

		if (rRota < pRota)rRota = pRota;
	}
	else pRota = save;

}

//最初の挙動
void player::FirstMove(int num){
	if (!firstflg){
		if (num == 1 && py > resetposY){
			py -= Rspd;
			Rspd -= 0.2;
			if (py <= resetposY){
				FirstPosFormat();
			}
		}

		else if (num == 2 && py < resetposY){
			py += Rspd;
			Rspd -= 0.2;
			if (py >= resetposY){
				FirstPosFormat();
			}
		}
	}
	
}

//スタート位置についたときに初期化するやつ
void player::FirstPosFormat(){
	py = resetposY;
	Rspd = 12.6;
	firstflg = true;
}

//機体が枠外に出ないようにする
void player::checkPos(){
	double sizeX = SIZE_X*size / 2;
	double sizeY = SIZE_Y*size / 2;

	if (px < sizeX)px = sizeX;
	if (px > WINDOW_X - sizeX)px = WINDOW_X - sizeX;
	if (py < sizeY)py = sizeY;
	if (py > WINDOW_Y - sizeY)py = WINDOW_Y - sizeY;
}

void player::Draw(){
	//プレイヤーが死んだ時は爆破、生きてるなら機体を書く
	if (!lifeflg){
		if (anitimer / 5 >= 16){
			lifeflg = true;
			if (lifecount != 0){
				respawnflg = true;
				firstflg = false;
			}
			anitimer = 0;
			return;//アニメーションを終えたらいったん抜ける(１フレずれるからそこどーする？いやだったらなんとかしよ。俺はいやじゃない)
		}
		//爆破を描く
		DrawRotaGraph((int)deathX, (int)deathY, 1.0, 0.0, datec->GetExplosionGraph(anitimer / 5), true);
		anitimer++;
	}
	//復帰中
	else if (respawnflg){
		if (lifecount == 0)return;//残機が０になったら画面外で待機
		//爆破で使ったタイマーを使いまわして自機を点滅させながらリスポーンする
		if (anitimer / 10 == 3)PlaySoundMem(datec->GetRespwonSound(), DX_PLAYTYPE_BACK);
		if (anitimer % 10 < 5)DrawRotaGraph((int)px, (int)py, size, rRota, graph, true);
		
		if (firstPosY < 0){
			//完全に復帰したら点滅を無くす。タイマーもリセット
			if (py >= resetposY){
				py = resetposY;
				respawnflg = false;
				InvincibleTime++;
				return;
			}
		}
		if (firstPosY > 0){
			//完全に復帰したら点滅を無くす。タイマーもリセット
			if (py <= resetposY){
				py = resetposY;
				respawnflg = false;
				InvincibleTime++;
				return;
			}
		}
		anitimer++;
	}
	//無敵時間
	else if (InvincibleTime > 0){
		anitimer++;
		InvincibleTime++;
		if (anitimer % 10 < 5)DrawRotaGraph((int)px, (int)py, size, rRota, graph, true);
		if (InvincibleTime > 120){
			InvincibleTime = 0;
			anitimer = 0;
		}
	}

	//復帰後or通常状態
	else DrawRotaGraph((int)px, (int)py, size, rRota, graph, true);

	if (size >= 1 && px == WINDOW_X/2)DrawRotaGraph(WINDOW_X / 2, WINDOW_Y / 2 - 150, 1.0, 0.0, datec->GetWinGraph(), true);
	
}

void player::setShotFlg(bool flg){
	shotflg = flg;
}

void player::setLifeFlg(bool flg){
	lifeflg = flg;
	if (!lifeflg){
		lifecount--;
	}
}

void player::setDeathPos(){
	deathX = px;
	deathY = py;
	//機体を画面外に追い出す
	px = GetRand(700)+50;
	py = firstPosY;
	//ついでに角度も初期化
	rRota = 90 * PI / 180;
	saveX = 0;
	saveY = -(int)firstPosY;//初期状態に向かせるため
}

//勝利演出
void player::WinEffect(){
	winflg = true;
	float half_windowX = WINDOW_X / 2;
	float half_windowY = WINDOW_Y / 2;

	float SenterRota = atan2((float)(py - half_windowY), (float)(px - half_windowX));//中心に行くときに使う角度

	//±5のところに来たら強制的に真ん中の座標にする
	if (px > half_windowX + 5 || px < half_windowX - 5)px -= cos(SenterRota) * 2;
	else px = half_windowX;
	if (py > half_windowY + 5 || py < half_windowY - 5)py -= sin(SenterRota) * 2;
	else py = half_windowY;

	if(size <= 1)size += 0.01;
	saveX = 0;
	saveY = -1000;

	finishtimer++;
}

void player::InvincibleTimeFormat(){
	if (InvincibleTime == 0)return;
	InvincibleTime = 0;
	anitimer = 0;
}