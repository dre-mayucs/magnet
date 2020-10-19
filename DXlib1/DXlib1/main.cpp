#include "Initialize_component.h"

#define TOP_POS (double)128 - 16
#define UNDER_POS (double)768 - 207

bool rand_obj();
double select_obj();

char keys[256] = { 0 };
char oldkeys[256] = { 0 };

//Grobal class
collision Collision;

void start()
{
	srand(time(NULL));
	op();
	stage();
}

void op()
{
	int start_image = LoadGraph("Resources\\Background\\start.png");

	while (true)
	{
		for (auto i = 0; i < 256; i++) { oldkeys[i] = keys[i]; }
		GetHitKeyStateAll(keys);
		ClearDrawScreen(); //クリア

		DrawGraph(0, 0, start_image, false);
		if (keys[KEY_INPUT_SPACE] && !oldkeys[KEY_INPUT_SPACE])
		{
			break;
		}

		ScreenFlip();
		WaitTimer(20);
		if (ProcessMessage() == -1) { break; }
	}
}

void end()
{
	int game_over_image = LoadGraph("Resources\\Background\\over.png");

	while (true)
	{
		for (auto i = 0; i < 256; i++) { oldkeys[i] = keys[i]; }
		GetHitKeyStateAll(keys);
		ClearDrawScreen(); //クリア

		DrawGraph(0, 0, game_over_image, false);
		if (keys[KEY_INPUT_SPACE] && !oldkeys[KEY_INPUT_SPACE])
		{
			stage();
		}

		ScreenFlip();
		WaitTimer(20);
		if (ProcessMessage() == -1) { break; }
	}
}

void stage()
{
	#pragma region variable
	int player[8];
	int BG = LoadGraph("Resources\\Background\\BG_latest.png");
	int obj = LoadGraph("Resources\\Background\\Obj.png");
	LoadDivGraph("Resources\\chr\\char.png", 8, 8, 1, 96, 96,player);

	bool button = 0;
	int speed_adjust = 0;
	int Display_Score = 0;
	int player_x = 100;
	int player_y = WIN_HEIGHT / 2;

	int animation_frame = 0;

	const int obj_adjust = 8;
	bool obj_flag[obj_adjust];
	double obj_pos_x[obj_adjust];
	double obj_pos_y[obj_adjust];
	double speed = 10;

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
		ClearDrawScreen(); //クリア

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
					obj_pos_x[i] + 16, obj_pos_x[i] + (double)96 - 16, obj_pos_y[i] + 16, obj_pos_y[i] + (double)96 - 16))
			{
				end();
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
					obj_pos_x[i] -= speed;
				}
			}
 		}
		if (keys[KEY_INPUT_SPACE] && !oldkeys[KEY_INPUT_SPACE])
		{
			adjust_count = 0;
			animation_frame = 1;
			player_speed_adjust = 5;
			button = !button;
		}

		if (button == true) 
		{
			if (animation_frame != 0)
			{
				animation_frame++;
			}

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
			if (animation_frame != 0)
			{
				animation_frame++;
			}

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

		if (animation_frame == 7)
		{
			animation_frame = 0;
		}
		DrawGraph(player_x, player_y, player[animation_frame], TRUE);
		speed_adjust += 1;
		Display_Score += 3;

		if (speed_adjust  <= 10800)
		{
			if (speed_adjust % 720 == 0)
			{
				speed += 2;
			}

		}
		SetFontSize( 50);
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", Display_Score);

		ScreenFlip();
		WaitTimer(20);
		if (ProcessMessage() == -1) { break; }
	}
}

bool _r_flag;
bool rand_obj()
{
	_r_flag = false;
	int cache = rand() % 1000;
	
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