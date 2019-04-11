#pragma once
struct MousePoint
{
	int x;
	int y;
};

class MouseEvent
{
public:
	enum EventType
	{
		LPress,
		LRelease,
		RPress,
		RRelease,
		MPress,
		MRelease,
		WheelUp,
		WheelDown,
		Move,
		RAW_MOVE,
		Invalid
	};
private:
	EventType type;
	int x;
	int y;
	int delatX;
	int delatY;
public:
	MouseEvent();
	MouseEvent(const EventType type, const int x, const int y);
	MouseEvent(const EventType type, const int x, const int y, const int delx, const int dely);
	bool IsValid() const;
	EventType GetType() const;
	MousePoint GetPos() const;
	MousePoint GetdelPos() const;
	int GetPosX() const;
	int GetPosY() const;
	int GetDelPosX() const;
	int GetDelPosY() const;
};