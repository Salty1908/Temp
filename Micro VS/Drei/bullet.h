#pragma once
#include<iostream>
#include<graphics.h>
#include<string>
#include<vector>
#include"util.h"


#pragma comment(lib,"MSIMG32.LIB")

class Bullet
{
public:
	POINT pos = {0,0};

public:
	Bullet() {
		loadimage(&atlas_bullet_b, _T("resou/atlas/bullet_b.png"));
	};
	~Bullet() {
	};

	void Draw() 
	{	
		//setlinecolor(RGB(255, 0, 255));
		//setfillcolor(RGB(200, 50, 200));
		//fillcircle(pos.x, pos.y, r);

		putimage_alpha(pos.x, pos.y, &atlas_bullet_b);
	}

private:
	IMAGE atlas_bullet_b;
	//const int r = 8;
};

