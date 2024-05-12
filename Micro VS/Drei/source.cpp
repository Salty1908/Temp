#include<iostream>
#include<graphics.h>
#include<string>
#include<vector>
#include<windows.h>
#include<mmsystem.h>
#include <easyx.h>


#include"util.h"
#include"player.h"
#include"enemy.h"
#include"bullet.h"
#include"UI.h"
//#include"scene.h"
//#include"scene_manager.h"
#include"gen.h"


int idx_current_anim = 0;

const int PLAYER_ANIM_NUM = 6;



const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int BUTTON_WIDTH = 192;
const int BUTTON_HEIGHT= 75;

bool running = true;
bool is_game_started = false;


#pragma comment(lib,"WINMM.LIB")
#pragma comment(lib,"MSIMG32.LIB")



IMAGE atlas_bullet_c,

atlas_enemy_b,
atlas_enemy_bul;

IMAGE img_frame,
img_avatar,
img_avatar_hit;
//IMAGE img_ui_quit_idle,
//img_ui_quit_hovered,
//img_ui_quit_push,
//img_ui_start_idle,
//img_ui_start_hovered,
//img_ui_start_push;

void UpdateBul(std::vector<Bullet>& bullet_list,const Player& player)
{
	const double TAN_SPEED = 0.0055;
	double radian_interval = 2 * 3.14159 / bullet_list.size();
	POINT player_pos = player.GetPos();
	double radius = 128;
	for (size_t i = 0; i < bullet_list.size(); i++)
	{
		double radian = GetTickCount() * TAN_SPEED + radian_interval * i;
		bullet_list[i].pos.x = player_pos.x + 32 + (int)(radius * sin(radian));
		bullet_list[i].pos.y = player_pos.y + 32 + (int)(radius * cos(radian));
	}
}
 
void DrawTp(int tp) {
	static TCHAR text[64];
	_stprintf_s(text, _T("Tp:%d"),  tp);

	setbkmode(TRANSPARENT);
	settextcolor((RGB(255, 85, 255)));
	outtextxy(1080, 120, text);

}

void DrawSco(int sco) {
	static TCHAR text[64];
	_stprintf_s(text, _T("Current Sco:%d"), sco);

	setbkmode(TRANSPARENT);
	settextcolor((RGB(255, 85, 255)));
	outtextxy(80, 40, text);

}

void DrawAva(bool checkhit) {
	if (checkhit ==true) putimage_alpha(4, 460, &img_avatar_hit);
	else putimage_alpha(4, 460, &img_avatar);
}

class StartGameButton :public Button {
public:
	StartGameButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
		:Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {}
	~StartGameButton() = default;

protected:
	void OnClick() {
		is_game_started = true;
		mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);
	}
};

class QuitGameButton :public Button {
public:
	QuitGameButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
		:Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {}
	~QuitGameButton() = default;

protected:
	void OnClick() {
		running = false;
	}
};




int main()
{
	initgraph(1280, 720);

	mciSendString(_T("open recou/mus/bgm.mp3 alias bgm"), NULL, 0, NULL);

	mciSendString(_T("open recou/wav/hit.wav alias hit"), NULL, 0, NULL);
	



	Player player;
	ExMessage msg;
	IMAGE img_background;
	IMAGE img_menu;
	std::vector<Enemy*> enemy_list;
	std::vector<Bullet> bullet_list(3);
	RECT region_btn_sta, region_btn_qui;


	region_btn_sta.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
	region_btn_sta.right = region_btn_sta.left + BUTTON_WIDTH;
	region_btn_sta.top = 430;
	region_btn_sta.bottom = region_btn_sta.top + BUTTON_HEIGHT;

	region_btn_qui.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
	region_btn_qui.right = region_btn_qui.left + BUTTON_WIDTH;
	region_btn_qui.top = 550;
	region_btn_qui.bottom = region_btn_qui.top + BUTTON_HEIGHT;

	StartGameButton btn_sta = StartGameButton(region_btn_sta,
		_T("resou/img/ui_start_idle.png"), _T("resou/img/ui_start_hovered.png"), _T("resou/img/ui_start_pushed.png"));
	QuitGameButton btn_qui = QuitGameButton(region_btn_qui,
		_T("resou/img/ui_quit_idle.png"), _T("resou/img/ui_quit_hovered.png"), _T("resou/img/ui_quit_pushed.png"));
	
	
	int sco = 0;
    int tp = 180;
	bool checkhit=false;

	
		AddFontResourceEx(_T("resou/IPix.ttf"), FR_PRIVATE, NULL);

		loadimage(&img_background, _T("resou/img/background.png"));
		loadimage(&img_menu, _T("resou/img/menu.png"));
		loadimage(&img_avatar, _T("resou/img/avatar.png"));
		loadimage(&img_avatar_hit, _T("resou/img/avatar_hit.png"));
		loadimage(&img_frame, _T("resou/img/frame.png"));
		//loadimage(&img_ui_quit_idle, _T("resou/img/ui_quit_idle.png"));
		//loadimage(&img_ui_quit_hovered, _T("resou/img/ui_quit_hovered.png"));
		//loadimage(&img_ui_quit_push, _T("resou/img/ui_quit_pushed.png"));
		//loadimage(&img_ui_start_idle, _T("resou/img/ui_start_idle.png"));
		//loadimage(&img_ui_start_hovered, _T("resou/img/ui_start_hovered.png"));
		//loadimage(&img_ui_start_push, _T("resou/img/ui_start_pushed.png"));

		
		//loadimage(&atlas_player, _T("resou/atlas/player.png"));
		//loadimage(&atlas_player_r, _T("resou/atlas/player_r.png"));
		//loadimage(&atlas_player_shadow, _T("resou/atlas/player_shadow.png"));
		//loadimage(&atlas_bullet_a, _T("resou/atlas/bullet_a.png"));
		//loadimage(&atlas_bullet_a_r, _T("resou/atlas/bullet_a_r.png"));
		//loadimage(&atlas_bullet_b, _T("resou/atlas/bullet_b.png"));
		//loadimage(&atlas_bullet_c, _T("resou/atlas/bullet_c.png"));
		//loadimage(&atlas_enemy_a, _T("resou/atlas/enemy_a.png"));
		//loadimage(&atlas_enemy_b, _T("resou/atlas/enemy_b.png"));
		//loadimage(&atlas_enemy_bul, _T("resou/atlas/enemy_bul.png"));

		

	

	BeginBatchDraw();

	

	while (running)
	{

		DWORD start_time = GetTickCount();
		
		while (peekmessage(&msg))
		{
			if(is_game_started)
			player.ProcessEvent(msg);
			else {
				btn_sta.ProcessEvent(msg);
				btn_qui.ProcessEvent(msg);
			}
			
		}

		if (is_game_started) {

			TryGenEnemy(enemy_list);

			player.Move();
			UpdateBul(bullet_list, player);

			for (Enemy* enemy : enemy_list)
				enemy->Move(player);
			for (Enemy* enemy : enemy_list)
			{
				if (enemy->PlaCol(player))
				{
					mciSendString(_T("play hit from 0"), NULL, 0, NULL);
					checkhit = true;
					tp -= 60;

				}
			}

			if (tp <= 0) {
				static TCHAR text[128];
				_stprintf_s(text, _T("Score: %d"), sco);
				MessageBox(GetHWnd(), text, _T("Game Over"), MB_OK);
				running = false;
				break;
			}

			for (Enemy* enemy : enemy_list) {
				for (const Bullet& bullet : bullet_list) {
					if (enemy->BulCol(bullet)) {
						mciSendString(_T("play hit from 0"), NULL, 0, NULL);
						enemy->Hurt();

					}
				}
			}

			for (size_t i = 0; i < enemy_list.size(); i++) {
				Enemy* enemy = enemy_list[i];
				if (!enemy->CheckAlive()) {
					std::swap(enemy_list[i], enemy_list.back());
					enemy_list.pop_back();
					delete enemy;
					sco++;
				}
			}



			static int counter = 0;
			if ((2 * ++counter) % 5 == 0)
				idx_current_anim++;

			idx_current_anim = idx_current_anim % PLAYER_ANIM_NUM;

		}

		cleardevice();



		if (is_game_started) {
			putimage_alpha(0, 0, &img_background);



			player.Draw();
			for (Enemy* enemy : enemy_list)
				enemy->Draw();
			for (Bullet& bullet : bullet_list)
				bullet.Draw();
			//DrawTp(tp);
			DrawSco(sco);


			//putimage_alpha(4, 460, &img_avatar);
			DrawAva(checkhit);

			putimage_alpha(0, 456, &img_frame);






			//line(490, 720, 490, 620);
			//line(790, 720, 790, 620);
			//line(470, 720, 790, 720);
			//line(470, 620, 790, 620);
			//line(470, 720, 470, 620);

			//line(800, 720, 864, 720);
			//line(800, 620, 864, 620);
			//line(800, 720, 864, 620);
			//line(864, 720, 800, 620);

			//line(1060, 40, 1060, 80);
			//line(1060, 80, 980, 80);
			//line(980, 80, 980, 40);
			//line(980, 40, 1060, 40);



			//circle(1160, 120, 80);
		}
		else
		{
			putimage(0, 0, &img_menu);
			btn_sta.Draw();
			btn_qui.Draw();
		}

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