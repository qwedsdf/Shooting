#include "title.h"



title::title(date *fli)
{
	backX = 0;
	backY = 0;
	backgraph = LoadGraph("image/titleback.png");
	datec = fli;
	datec->PlayTitleBGM();
}


title::~title()
{
}

int title::action(){
	Pad1 = GetJoypadInputState(DX_INPUT_PAD1);
	Pad2 = GetJoypadInputState(DX_INPUT_PAD2);
	if (Pad1 || Pad2||CheckHitKey(KEY_INPUT_SPACE)){
		datec->SoundStop();
		datec->PlayGameBGM();
		return FLOW_GAME;
	}
	return FLOW_TITLE;
}

void title::Draw(){
	DrawGraph(backX, backY,backgraph,true);
}
