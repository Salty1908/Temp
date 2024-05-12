#pragma once
#include<iostream>
#include<graphics.h>
#include<string>
#include<vector>
#include"enemy.h"

void TryGenEnemy(std::vector<Enemy*>& enemy_list)
{
	const int INTER = 100;
	static int counter = 0;
	if ((++counter) % INTER == 0)
		enemy_list.push_back(new Enemy());
}