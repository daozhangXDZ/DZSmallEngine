//***************************************************************************************
// GameTimer.h by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#ifndef GAMETIMER_H
#define GAMETIMER_H

class EngineTimer
{
public:
	EngineTimer();

	float TotalTime()const;		// ����Ϸʱ��
	float DeltaTime()const;		// ֡���ʱ��

	void Reset(); // ����Ϣѭ��֮ǰ����
	void Start(); // ��ȡ����ͣ��ʱ�����
	void Stop();  // ����ͣ��ʱ�����
	void Tick();  // ��ÿһ֡��ʱ�����

private:
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime;
	__int64 mPausedTime;
	__int64 mStopTime;
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool mStopped;
};

#endif // GAMETIMER_H