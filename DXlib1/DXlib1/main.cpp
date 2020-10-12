#include "Initialize_component.h"

void stage();
bool rand_obj();
bool select_obj();

char keys[256] = { 0 };
char oldkeys[256] = { 0 };

void start()
{
	srand(time(NULL));
	stage();
}

void stage()
{
	#pragma region variable
	int BG = LoadGraph("Resources\\Background\\BG.png");
	int obj = LoadGraph("Resources\\Background\\Obj.png");
	int player[2];
	LoadDivGraph("Resources\\chr\\char.png", 2, 2, 1, 96, 96,player);
	bool  button = 0;
	int score = 0;
	int Score = 0;

	const int obj_adjust = 8;
	bool obj_flag[obj_adjust];
	double obj_pos_x[obj_adjust];
	double obj_pos_y[obj_adjust];

	int rand_adjust = 0;

	for (auto i = 0; i < obj_adjust; i++)
	{
		obj_flag[i] = false;
		obj_pos_x[i] = WIN_WIDTH;
		obj_pos_y[i] = 0;
	}
	#pragma endregion

	while (true)
	{
		GetHitKeyStateAll(keys);
		for (auto i = 0; i < 256; i++) { oldkeys[i] = keys[i]; }
		ClearDrawScreen(); //ƒNƒŠƒA

		DrawGraph(0, 0, BG, false);
		/*if (rand_adjust == 60)
		{
			for (auto i = 0; i < obj_adjust; i++)
			{
				if (obj_flag[i] == false)
				{
					obj_flag[i] = rand_obj();
				}
			}
			rand_adjust = 0;
		}
		else
		{
			rand_adjust++;
		}*/
		for (auto i = 0; i < obj_adjust; i++)
		{
			if (obj_flag[i] == false)
			{
				obj_flag[i] = rand_obj();
			}
			else
			{
				/*obj_pos_y[i] = select_obj();*/
				DrawGraph(obj_pos_x[i], select_obj(), obj, true);

				if (obj_pos_x[i] < -96)
				{
					obj_flag[i] = false;
					obj_pos_x[i] = WIN_WIDTH;
				}
				else
				{
					obj_pos_x[i] -= 10;
				}
			}
 		}
		//DrawGraph(WIN_WIDTH / 2, 120, obj, true);
		//DrawGraph(WIN_WIDTH / 2, 768 - 215, obj, true);
		if (keys[KEY_INPUT_SPACE])
		{
			button = !button;
		}

		DrawGraph(0, 0, player[button], TRUE);
		score += 1;
		if (score >= 60)
		{
			Score += 100 ;
			score = 0;
		}
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", Score);

		ScreenFlip();
		WaitTimer(20);
		if (ProcessMessage() == -1) { break; }
	}
}

bool _r_flag;
bool rand_obj()
{
	_r_flag = false;
	int cache = rand() % 10000;
	
	if (cache < 10) { _r_flag = true; }

	return _r_flag;
}
int ret_cache;
bool select_obj()
{
	int cache = rand() % 30;
	int ret_cache;

	switch (cache / 10)
	{
		case 0:
			ret_cache = 120;
			break;
		case 1: 
			ret_cache = (762 - 215) / 2;
			break;
		case 2:
			ret_cache = 762 - 215;
			break;
	}

	return ret_cache;
}