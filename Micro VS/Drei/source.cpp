#include<iostream>
#include<graphics.h>
#include<string>
#include<vector>


#include"util.h"
#include"player.h"
//#include"enemy.h"
//#include"bullet.h"
//#include"scene.h"
//#include"scene_manager.h"


int idx_current_anim = 0;

const int PLAYER_ANIM_NUM = 6;



const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;






#pragma comment(lib,"MSIMG32.LIB")


IMAGE atlas_bullet_a, atlas_bullet_a_r,
atlas_bullet_b,
atlas_bullet_c,
atlas_enemy_a,
atlas_enemy_b,
atlas_enemy_bul;

IMAGE img_frame,

img_avatar,
img_avatar_hit,
img_ui_quit_idle,
img_ui_quit_hovered,
img_ui_quit_push,
img_ui_start_idle,
img_ui_start_hovered,
img_ui_start_push;


 










int main()
{
	initgraph(1280, 720);

	bool running = true;

	Player player;
	ExMessage msg;
	IMAGE img_background;

	

	
		AddFontResourceEx(_T("resou/IPix.ttf"), FR_PRIVATE, NULL);

		loadimage(&img_background, _T("resou/img/background.png"));
		loadimage(&img_avatar, _T("resou/img/avatar.png"));
		loadimage(&img_avatar_hit, _T("resou/img/avatar_hit.png"));
		loadimage(&img_frame, _T("resou/img/frame.png"));
		loadimage(&img_ui_quit_idle, _T("resou/img/ui_quit_idle.png"));
		loadimage(&img_ui_quit_hovered, _T("resou/img/ui_quit_hovered.png"));
		loadimage(&img_ui_quit_push, _T("resou/img/ui_quit_push.png"));
		loadimage(&img_ui_start_idle, _T("resou/img/ui_start_idle.png"));
		loadimage(&img_ui_start_hovered, _T("resou/img/ui_start_hovered.png"));
		loadimage(&img_ui_start_push, _T("resou/img/ui_start_push.png"));

		
		//loadimage(&atlas_player, _T("resou/atlas/player.png"));
		//loadimage(&atlas_player_r, _T("resou/atlas/player_r.png"));
		//loadimage(&atlas_player_shadow, _T("resou/atlas/player_shadow.png"));
		loadimage(&atlas_bullet_a, _T("resou/atlas/bullet_a.png"));
		loadimage(&atlas_bullet_a_r, _T("resou/atlas/bullet_a_r.png"));
		loadimage(&atlas_bullet_b, _T("resou/atlas/bullet_b.png"));
		loadimage(&atlas_bullet_c, _T("resou/atlas/bullet_c.png"));
		loadimage(&atlas_enemy_a, _T("resou/atlas/enemy_a.png"));
		loadimage(&atlas_enemy_b, _T("resou/atlas/enemy_b.png"));
		loadimage(&atlas_enemy_bul, _T("resou/atlas/enemy_bul.png"));

		

	

	BeginBatchDraw();

	

	while (running)
	{

		DWORD start_time = GetTickCount();
		
		while (peekmessage(&msg))
		{
			player.ProcessEvent(msg);
			
		}

		player.Move();



		static int counter = 0;
		if ((2 * ++counter) % 5 == 0) 
			idx_current_anim++;

		idx_current_anim = idx_current_anim % PLAYER_ANIM_NUM;

		

		cleardevice();


		putimage_alpha(0, 0, &img_background);

		
		
		player.Draw();



		putimage_alpha(4, 460, &img_avatar);

		putimage_alpha(0, 456, &img_frame);

		
		
		
		
		
		line(490, 720, 490, 620);
		line(790, 720, 790, 620);
		line(470, 720, 790, 720);
		line(470, 620, 790, 620);
		line(470, 720, 470, 620);

		line(800, 720, 864, 720);
		line(800, 620, 864, 620);
		line(800, 720, 864, 620);
		line(864, 720, 800, 620);

		line(1060, 40, 1060, 80);
		line(1060, 80, 980, 80);
		line(980, 80, 980, 40);
		line(980, 40, 1060, 40);



		circle(1160, 120, 80);


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