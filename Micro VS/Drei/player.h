#pragma once

#include<iostream>
#include<graphics.h>
#include<string>
#include<vector>
#include"util.h"


#pragma comment(lib,"MSIMG32.LIB")

class Player
{
public:
	Player() {
		loadimage(&atlas_player, _T("resou/atlas/player.png"));
		loadimage(&atlas_player_r, _T("resou/atlas/player_r.png"));
		loadimage(&atlas_player_shadow, _T("resou/atlas/player_shadow.png"));

	};
	~Player() {

	};



	void ProcessEvent(const ExMessage& msg)
	{
		switch (msg.message)
		{
		case(WM_KEYDOWN):
			switch (msg.vkcode)
			{
			case 87://W
				is_move_up = true;
				break;
			case 83://S
				is_move_down = true;
				break;
			case 65://A
				is_move_left = true;
				break;
			case 68://D
				is_move_right = true;
				break;
			}
			break;

		case (WM_KEYUP):
			switch (msg.vkcode)
			{
			case 87://W
				is_move_up = false;
				break;
			case 83://S
				is_move_down = false;
				break;
			case 65://A
				is_move_left = false;
				break;
			case 68://D
				is_move_right = false;
				break;
			}
			break;
		}
	}



	void Move()
	{
		int dir_x = is_move_right - is_move_left;
		int dir_y = is_move_down - is_move_up;

		double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);
		if (len_dir != 0)
		{
			double normalized_x = dir_x / len_dir;
			double normalized_y = dir_y / len_dir;
			pos.x += (int)(SPEED * normalized_x);
			pos.y += (int)(SPEED * normalized_y);
		}

		if (pos.x < 0) pos.x = 0;
		if (pos.y < 0)pos.y = 0;
		if (pos.x + WIDTH > WINDOW_WIDTH)pos.x = WINDOW_WIDTH - WIDTH;
		if (pos.y + HEIGHT > WINDOW_HEIGHT)pos.y = WINDOW_HEIGHT - HEIGHT;


	}

	void Draw()
	{
		int pos_shadow_x = pos.x + WIDTH / 32;
		int pos_shadow_y = pos.y + HEIGHT/2 - 4;
		putimage_alpha(pos_shadow_x, pos_shadow_y, &atlas_player_shadow);


		static bool facing_left = false;
		int dir_x = is_move_right - is_move_left;
		if (dir_x < 0)facing_left = true;
		else if (dir_x > 0)facing_left = false;

		if (facing_left) putimage_alpha(pos.x, pos.y, &atlas_player);
		else putimage_alpha(pos.x, pos.y, &atlas_player_r);



	}

	const POINT& GetPos() const
	{
		return pos;
	}

private:
	IMAGE atlas_player;
	IMAGE atlas_player_r;
	IMAGE atlas_player_shadow;
	const int SPEED = 6;
	const int WIDTH = 64;
	const int HEIGHT = 64;
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;
	


private:
	POINT pos = { 720 , 400 };
	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_left = false;
	bool is_move_right = false;


};

