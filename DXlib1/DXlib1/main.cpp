#include "Initialize_component.h"

void stage();
bool rand_obj();

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
	int player = LoadGraph("Resources\\chr\\char.png");

	const int obj_adjust = 8;
	bool obj_flag[obj_adjust];
	double obj_pos[obj_adjust];

	int rand_adjust = 0;

	for (auto i = 0; i < obj_adjust; i++)
	{
		obj_flag[i] = false;
		obj_pos[i] = WIN_WIDTH;
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
				DrawGraph(obj_pos[i], 120, obj, true);

				if (obj_pos[i] < -96)
				{
					obj_flag[i] = false;
					obj_pos[i] = WIN_WIDTH;
				}
				else
				{
					obj_pos[i] -= 20;
				}
			}
		}
		//DrawGraph(WIN_WIDTH / 2, 120, obj, true);
		//DrawGraph(WIN_WIDTH / 2, 768 - 215, obj, true);

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
	if (cache < 250) { _r_flag = true; }

	return _r_flag;
}