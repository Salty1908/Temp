#ifndef UI.h
#define UI.h

#include<graphics.h>

class Button
{
public:
	Button()=default;
	~Button()=default;

private:
	enum class Status
	{
		Idle = 0,
		Hovered,
		Pushed

};

private:
	RECT region;
	IMAGE img_idle;
	IMAGE img_hovered;
	IMAGE img_pushed;
	Status status = Status::Idle;
	




};






#endif