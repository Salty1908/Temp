#include<iostream>
#include<graphics.h>
#include"head.h"

int idx_current_anim = 0;

const int PLAYER_ANIM_NUM = 6;

POINT player_pos = { 400 , 400 };

const int PLAYER_SPEED = 4;

#pragma comment(lib,"MSIMG32.LIB")



int main()
{
	initgraph(1280, 720);

	bool running = true;

	ExMessage msg;

	IMAGE img_background,img_avatar,img_player,img_player_shadow,
		img_frame,img_bullet;


	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_left = false;
	bool is_move_right= false;


	loadimage(&img_background, _T("img/background.png"));
	loadimage(&img_avatar, _T("img/avatar.png"));
	loadimage(&img_player, _T("img/player.png"));
	loadimage(&img_frame, _T("img/frame.png"));
	loadimage(&img_player_shadow, _T("img/player_shadow.png"));
	loadimage(&img_bullet, _T("img/bullet.png"));

	BeginBatchDraw();

	

	while (running)
	{

		DWORD start_time = GetTickCount();
		
		while (peekmessage(&msg))
		{
			if (msg.message == WM_KEYDOWN)
			{
				
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
			}

			if (msg.message == WM_KEYUP)
			{

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
			}
		}

		if (is_move_up)
			player_pos.y -= PLAYER_SPEED;
		if (is_move_down)
			player_pos.y += PLAYER_SPEED;
		if (is_move_left)
			player_pos.x-= PLAYER_SPEED;
		if (is_move_right)
			player_pos.x += PLAYER_SPEED;

		static int counter = 0;
		if ((2 * ++counter) % 5 == 0) 
			idx_current_anim++;

		idx_current_anim = idx_current_anim % PLAYER_ANIM_NUM;


		cleardevice();


		putimage_alpha(0, 0, &img_background);

		putimage_alpha(player_pos.x, player_pos.y, &img_player);

		putimage_alpha(4, 460, &img_avatar);

		putimage_alpha(0, 456, &img_frame);

		line(400, 720, 400, 560);
		line(880, 720, 880, 560);
		line(400, 560, 880, 560);
		line(400, 720, 880, 720);

		circle(1120, 160, 80);


		FlushBatchDraw();


		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;

		if (delta_time < 1000 / 60)
		{
			Sleep(1000 / 60 - delta_time);
		}


	}


	EndBatchDraw();

	return 0;
}					