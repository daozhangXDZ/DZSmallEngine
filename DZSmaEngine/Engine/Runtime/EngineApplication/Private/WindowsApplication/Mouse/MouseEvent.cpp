#include "WindowsApplication/Mouse/MouseEvent.h"

MouseEvent::MouseEvent()
	:
	type(EventType::Invalid),
	x(0),
	y(0)
{}

MouseEvent::MouseEvent(EventType type, int x, int y)
	:
	type(type),
	x(x),
	y(y)
{}

MouseEvent::MouseEvent(EventType type, int x, int y, int delX, int delY)
	:
	type(type),
	x(x),
	y(y),
	delatX(delX),
	delatY(delY)
{}

bool MouseEvent::IsValid() const
{
	return this->type != EventType::Invalid;
}

MouseEvent::EventType MouseEvent::GetType() const
{
	return this->type;
}

MousePoint MouseEvent::GetPos() const
{
	return{ this->x,this->y };
}

MousePoint MouseEvent::GetdelPos() const
{
	return{ this->delatX,this->delatY };
}

int MouseEvent::GetPosX() const
{
	return this->x;
}

int MouseEvent::GetPosY() const
{
	return this->y;
}

int MouseEvent::GetDelPosX() const
{
	return this->delatX;
}

int MouseEvent::GetDelPosY() const
{
	return this->delatY;
}