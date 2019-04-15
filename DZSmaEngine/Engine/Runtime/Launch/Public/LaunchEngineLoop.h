#pragma once
class FEngineLoop
{
public:

	FEngineLoop();

	virtual ~FEngineLoop() { }

public:	
	/// <summary>
	/// Pres the initialize.
	/// </summary>
	/// <returns></returns>
	int PreInit();

	/// <summary>
/// Initializes this instance.
/// </summary>
/// <returns></returns>
	virtual int Init();
	
	/// <summary>
	/// Exits this instance.
	/// </summary>
	/// <returns></returns>
	int Exit();
	
	/// <summary>
	/// Ticks this instance.
	/// </summary>
	/// <returns></returns>
	virtual int Tick();


	void CalculateFrameStats();
};

extern FEngineLoop GEngineLoop;