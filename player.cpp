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
	else saveY = 1;//������Ԃ���Ɍ������邽�߂�-1�Ƃ���
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
	//��]������T�����߂̍��W
	vectorX = px;
	vectorY = py;
	keyflg = false;

	///////////�����ϊ��ƈړ���ʃX�e�B�b�N�ł���Ƃ��ɃR�����g�O���Ă�������///////////////////
	////�E�A�i���O��|�����Ƃ��̏���(�p�x)
	if (abs(r_InputX) + abs(r_InputY)>800){
		
		//�A�i���O�X�e�B�b�N�̓��͂��C���v�b�g
		saveX = r_InputX;
		saveY = r_InputY;
		
	}
	//////////////////////////////////////////////////////////////////////////////////////


	if (!winflg&&lifecount != 0 && firstflg){
		//���X�e�B�b�N
		GetJoypadAnalogInput(&InputX, &InputY, PlayerNum);
		//�E�X�e�B�b�N
		GetJoypadAnalogInputRight(&r_InputX, &r_InputY, PlayerNum);

		//���A�i���O��|�����Ƃ��̏���(�ړ�)
		if (abs(InputX) + abs(InputY) > 800){
			//�@�̂�i�߂�
			px -= (int)(cos(moveRota)*SPDX);
			py -= (int)(sin(moveRota)*SPDY);

			checkPos();//�|�W�V��������ʊO�ɂȂ�Ȃ����`�F�b�N

			//�A�i���O�X�e�B�b�N�̓��͂��C���v�b�g
			m_saveX = InputX;
			m_saveY = InputY;
			//�E�X�e�B�b�N��������ĂȂ�������ړ������Ɍ���
			if (abs(r_InputX) + abs(r_InputY) < 800){
				saveX = InputX;
				saveY = InputY;
			}

		}
	}

	//��]�Ɏg�����W���C���v�b�g
	vectorX = px + saveX;
	vectorY = py + saveY;
	//�ړ��Ɏg�����W���C���v�b�g
	m_vectorX = px + m_saveX;
	m_vectorY = py + m_saveY;
	
	//�{���̖ڕW�p�x���Z�[�u����
	save = pRota;
	
	//if (keyflg){
	//�@�̂̉�]�p�����߂�
	pRota = atan2((float)(py - vectorY), (float)(px - vectorX));

	//�@�̂̈ړ��p�����߂�
	moveRota = atan2((float)(py - m_vectorY), (float)(px - m_vectorX));

	//�}�C�i�X����������
	if (pRota < 0)pRota=(360 * PI / 180) + pRota;
	save = pRota;
	//}

	//180���ȏ��]���悤�Ƃ��A�p�x��ς���
	if (rRota - pRota >= PI)pRota = pRota + (360 * PI / 180);//����180���ȏ��邱�Ƃ�h��

	else if (pRota - rRota >= PI)pRota = pRota - (360 * PI / 180);//�E��180���ȏ��邱�Ƃ�h��

	//�p�x��0���C����ʂ������ɐ��l�𒼂�
	if (rRota > 360 * PI / 180)rRota -= 360 * PI / 180;//�E����
	if (rRota < 0)rRota += 360 * PI / 180;//������


	//��]���������T���Ă�
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

//�ŏ��̋���
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

//�X�^�[�g�ʒu�ɂ����Ƃ��ɏ�����������
void player::FirstPosFormat(){
	py = resetposY;
	Rspd = 12.6;
	firstflg = true;
}

//�@�̂��g�O�ɏo�Ȃ��悤�ɂ���
void player::checkPos(){
	double sizeX = SIZE_X*size / 2;
	double sizeY = SIZE_Y*size / 2;

	if (px < sizeX)px = sizeX;
	if (px > WINDOW_X - sizeX)px = WINDOW_X - sizeX;
	if (py < sizeY)py = sizeY;
	if (py > WINDOW_Y - sizeY)py = WINDOW_Y - sizeY;
}

void player::Draw(){
	//�v���C���[�����񂾎��͔��j�A�����Ă�Ȃ�@�̂�����
	if (!lifeflg){
		if (anitimer / 5 >= 16){
			lifeflg = true;
			if (lifecount != 0){
				respawnflg = true;
				firstflg = false;
			}
			anitimer = 0;
			return;//�A�j���[�V�������I�����炢�����񔲂���(�P�t������邩�炻���ǁ[����H���₾������Ȃ�Ƃ�����B���͂��₶��Ȃ�)
		}
		//���j��`��
		DrawRotaGraph((int)deathX, (int)deathY, 1.0, 0.0, datec->GetExplosionGraph(anitimer / 5), true);
		anitimer++;
	}
	//���A��
	else if (respawnflg){
		if (lifecount == 0)return;//�c�@���O�ɂȂ������ʊO�őҋ@
		//���j�Ŏg�����^�C�}�[���g���܂킵�Ď��@��_�ł����Ȃ��烊�X�|�[������
		if (anitimer / 10 == 3)PlaySoundMem(datec->GetRespwonSound(), DX_PLAYTYPE_BACK);
		if (anitimer % 10 < 5)DrawRotaGraph((int)px, (int)py, size, rRota, graph, true);
		
		if (firstPosY < 0){
			//���S�ɕ��A������_�ł𖳂����B�^�C�}�[�����Z�b�g
			if (py >= resetposY){
				py = resetposY;
				respawnflg = false;
				InvincibleTime++;
				return;
			}
		}
		if (firstPosY > 0){
			//���S�ɕ��A������_�ł𖳂����B�^�C�}�[�����Z�b�g
			if (py <= resetposY){
				py = resetposY;
				respawnflg = false;
				InvincibleTime++;
				return;
			}
		}
		anitimer++;
	}
	//���G����
	else if (InvincibleTime > 0){
		anitimer++;
		InvincibleTime++;
		if (anitimer % 10 < 5)DrawRotaGraph((int)px, (int)py, size, rRota, graph, true);
		if (InvincibleTime > 120){
			InvincibleTime = 0;
			anitimer = 0;
		}
	}

	//���A��or�ʏ���
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
	//�@�̂���ʊO�ɒǂ��o��
	px = GetRand(700)+50;
	py = firstPosY;
	//���łɊp�x��������
	rRota = 90 * PI / 180;
	saveX = 0;
	saveY = -(int)firstPosY;//������ԂɌ������邽��
}

//�������o
void player::WinEffect(){
	winflg = true;
	float half_windowX = WINDOW_X / 2;
	float half_windowY = WINDOW_Y / 2;

	float SenterRota = atan2((float)(py - half_windowY), (float)(px - half_windowX));//���S�ɍs���Ƃ��Ɏg���p�x

	//�}5�̂Ƃ���ɗ����狭���I�ɐ^�񒆂̍��W�ɂ���
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