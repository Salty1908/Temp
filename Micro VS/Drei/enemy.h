
#pragma once
#include<iostream>
#include<graphics.h>
#include<string>
#include<vector>
#include<random>
#include<ctime>
#include"util.h"
#include"bullet.h"
#include"player.h"

#pragma comment(lib,"MSIMG32.LIB")




class Enemy
{
public:
	Enemy() {
		loadimage(&atlas_enemy_a, _T("resou/atlas/enemy_a.png"));
		loadimage(&atlas_enemy_shadow, _T("resou/atlas/player_shadow.png"));
	
		enum class Spawnedge
		{
			up = 0,
			down,
			left,
			right
		};
		
		std::srand(std::time(nullptr));

		Spawnedge edge = (Spawnedge)(std::rand() % 4);
		switch (edge)
		{
		case Spawnedge::up:
			pos.x = rand() % WINDOW_WIDTH;
			pos.y = -HEIGHT;
			break;
		case Spawnedge::down:
			pos.x = rand() % WINDOW_WIDTH;
			pos.y = WINDOW_HEIGHT;
			break;
		case Spawnedge::left:
			pos.x = -WIDTH;
			pos.y = rand()%WINDOW_HEIGHT;
			break;
		case Spawnedge::right:
			pos.x = WINDOW_WIDTH;
			pos.y = rand() % WINDOW_HEIGHT;
			break;
		default:
			break;
		}

	};

	bool BulCol(const Bullet& bullet)
	{
		bool is_overlap_x = bullet.pos.x >= pos.x && bullet.pos.x <= pos.x + WIDTH;
		bool is_overlap_y = bullet.pos.y >= pos.y && bullet.pos.y <= pos.y + HEIGHT;

		return is_overlap_x && is_overlap_y;
	}

	bool PlaCol(const Player& player)
	{
		POINT check_pos = { pos.x + WIDTH / 2,pos.y + HEIGHT / 2 };
		POINT player_pos = player.GetPos();

		bool is_overlap_x = check_pos.x >= player_pos.x && check_pos.x <= player_pos.x + 64;
		bool is_overlap_y = check_pos.y >= player_pos.y && check_pos.y <= player_pos.y + 64;

		return is_overlap_x && is_overlap_y;
	}


	


	void Move(const Player& player)
	{
		const POINT& player_pos = player.GetPos();
		int dir_x = player_pos.x - pos.x;
		int dir_y = player_pos.y - pos.y;
		double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);
		if (len_dir != 0)
		{
			double normalized_x = dir_x / len_dir;
			double normalized_y = dir_y / len_dir;
			pos.x += (int)(SPEED * normalized_x);
			pos.y += (int)(SPEED * normalized_y);
		}

		if (dir_x < 0)facing_left = true;
		else if (dir_x > 0)facing_left = false;

	}



	void Draw()
	{
		int pos_shadow_x = pos.x ;
		int pos_shadow_y = pos.y + HEIGHT/2 - 4;
		putimage_alpha(pos_shadow_x, pos_shadow_y, &atlas_enemy_shadow);

		if (facing_left) putimage_alpha(pos.x, pos.y, &atlas_enemy_a);
		else putimage_alpha(pos.x, pos.y, &atlas_enemy_a);

	}

	


	~Enemy() {

	};


	void Hurt()
	{
		hp--;
		if (hp <= 0)alive = false;
	}


	bool CheckAlive()
	{
		return alive;
	}



private:
	const int SPEED = 4;
	const int WIDTH = 64;
	const int HEIGHT = 64;
	
private:
	const int FULL_HP = 4;
	int hp = FULL_HP;
	bool alive = true;

private:
	IMAGE atlas_enemy_a;
	IMAGE atlas_enemy_shadow;
	POINT pos = { 0,0 };
	bool facing_left = false;
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;
};





