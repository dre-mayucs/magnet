#include "Initialize_component.h"

#define TOP_POS (double)128
#define UNDER_POS (double)768 - 190

void stage();
bool rand_obj();
double select_obj();

char keys[256] = { 0 };
char oldkeys[256] = { 0 };

//Grobal class
collision Collision;

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
	LoadDivGraph("Resources\\chr\\char2.png", 2, 2, 1, 64, 64,player);
	bool  button = 0;
	int score = 0;
	int Score = 0;
	int player_x = 100;
	int player_y = WIN_HEIGHT / 2;

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

	#pragma region adjust_var
	short player_speed_adjust = 0;
	short adjust_count = 0;
	#pragma endregion

	while (true)
	{
		
		for (auto i = 0; i < 256; i++) { oldkeys[i] = keys[i]; }
		GetHitKeyStateAll(keys);
		ClearDrawScreen(); //ƒNƒŠƒA

		DrawGraph(0, 0, BG, false);
		for (auto i = 0; i < obj_adjust; i++)
		{
			if (obj_flag[i] == false)
			{
				obj_flag[i] = rand_obj();
				obj_pos_y[i] = select_obj();
			}
			else if (obj_flag[i] == true && Collision.box_Fanc(
					player_x, player_x + (double)64, player_y, player_y + (double)64,
					obj_pos_x[i], obj_pos_x[i] + (double)96, obj_pos_y[i], obj_pos_y[i] + (double)96))
			{
				return;
			}
			else
			{
				DrawGraph(obj_pos_x[i], obj_pos_y[i], obj, true);

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
		if (keys[KEY_INPUT_SPACE] && !oldkeys[KEY_INPUT_SPACE])
		{
			adjust_count = 0;
			player_speed_adjust = 5;
			button = !button;
		}

		if (button == true) 
		{
			if (adjust_count >= 20)
			{
				player_speed_adjust++;
			}
			else
			{
				adjust_count++;
			}

			for (auto i = 0; i < player_speed_adjust; i++)
			{
				if (player_y != TOP_POS)
				{
					player_y--;
				}
				else 
				{ 
					adjust_count = 0;
					player_speed_adjust = 1;
					break;
				}
			}
		}
		if (button == false) 
		{
			if (adjust_count >= 20)
			{
				player_speed_adjust++;
			}
			else
			{
				adjust_count++;
			}

			for (auto i = 0; i < player_speed_adjust; i++)
			{
				if (player_y != UNDER_POS)
				{
					player_y++;
				}
				else
				{
					adjust_count = 0;
					player_speed_adjust = 1;
					break;
				}
			}
		}

		DrawGraph(player_x, player_y, player[button], TRUE);
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
	int cache = rand() % 2000;
	
	if (cache < 10) { _r_flag = true; }

	return _r_flag;
}
int ret_cache = 0;
double select_obj()
{
	int cache = rand() % 300;
	int ret_cache;

	switch (cache / 100)
	{
		case 0:
			return (double)120;
			break;
		case 1: 
			return (double)((762 - (245 / 2)) / 2);
			break;
		case 2:
			return (double)762 - 215;
			break;
	}
}