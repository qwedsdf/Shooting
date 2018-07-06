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


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(/*��*/WINDOW_X,/*�c*/ WINDOW_Y, /*�J���[�r�b�g���[�g*/16,/*�t���[����*/ 256);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	init();
	while (ProcessMessage() != -1){
		
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1 || (GetJoypadInputState(DX_INPUT_PAD1)&PAD_INPUT_10)){
			break;
		}
		// ��ʂ�����������
		ClearDrawScreen();
		//����
		appaction();
		//�`��
		appDrow();
		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();
		//�L�[�̍X�V
		gkey->UpDateKey();

		if (ProcessMessage() < 0)break;
	}

	
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}
