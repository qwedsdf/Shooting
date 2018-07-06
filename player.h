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
	//���l�ϐ�
	double px;
	double py;
	double resetposX;
	double resetposY;
	double firstPosY;//���A���Ɏg��
	double deathX;
	double deathY;
	double Rspd;//���A���A�X�^�[�g���ɗ^����X�s�[�h
	double vectorX;//�����]���Ɏg��
	double vectorY;
	double m_vectorX;//�ړ��ɂ����x�N�^�[
	double m_vectorY;
	int lifecount;//�c�@��

	double size;//���@�̑傫��

	//�^�C�}�[
	int shottimer;//�A�˂̃^�C�}�[
	int anitimer;//�����G�t�F�N�g�p�^�C�}�[
	int finishtimer;//�Q�[���I����Ƀ^�C�g���ɖ߂�܂łɎg���^�C�}�[
	int InvincibleTime;//���G����

	//�O���t�B�b�N�֘A
	int graph;

	//�t���O
	bool shotflg;//�{�^���̘A�˂Ɏg���t���O
	bool lifeflg;//�����m�F
	bool respawnflg;//���X�|�[���m�F
	bool winflg;//�������Ƃ��̃t���O
	bool firstflg;//�ŏ��̓o�ꂪ�I��������ǂ���

	//�A�i���O�X�e�B�b�N�̓��͂��擾
	int /*���X�e�B�b�N*/InputX, InputY, /*�E�X�e�B�b�N*/r_InputX, r_InputY;
	//�Z�[�u����p�x
	int saveX, saveY, m_saveX, m_saveY;
	double save;//pRota��ۑ�����̂Ɏg��
	double pRota;//�@�̂����������p�x(�ڕW)
	double rRota;//�@�̎��̂��������Ă�p�x
	double moveRota;//�ړ��Ɏg���p�x
	bool keyflg;

public:
	player(int p_num, date *d);
	~player();

	//�Q�b�g�n
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

	//�Z�b�g�n
	void setShotFlg(bool flg);
	void setLifeFlg(bool flg);
	void setDeathPos();
	void InvincibleTimeFormat();
	void FirstPosFormat();

	//�@�\�֐�
	void checkPos();
	void MovePlayer(int playerNum);
	void FirstMove(int num);
	void Draw();

	//�ő�A�ː����߂邽�߂̊֐�
	void shotTimerIn(){	shottimer++;	}//�e���łĂ�܂ł̃^�C�����v���X
	void shotTimerFormat(){	shottimer = 0;	}//�^�C�}�[��������
	void WinEffect();//�������o
	void AllFormat(int num);

	//���̑�
	void exploSoundPlay(){	PlaySoundMem(datec->GetExploSound(), DX_PLAYTYPE_BACK);	}
	void shotSoundPlay(){	PlaySoundMem(datec->GetShotSound(), DX_PLAYTYPE_BACK);	}

};

