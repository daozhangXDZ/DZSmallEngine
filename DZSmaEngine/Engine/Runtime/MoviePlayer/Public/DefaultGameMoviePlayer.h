#pragma once
#include "MoviePlayer.h"
#include "EngineWindow.h"

/// <summary>
/// һ��Ĭ�ϵĿͻ��˲����������յ�Ӱ�ķ�ʽ�����棬������
/// </summary>
/// <seealso cref="MoviePlayer" />
class DefaultGameMoviePlayer : public IGameMoviePlayer
{
public:
	static void Create();
	static void Clear();

	static DefaultGameMoviePlayer* get();

public:
	virtual void Initialize() override;
	virtual bool WaitForMovieToFinish() override;
private:
	static DefaultGameMoviePlayer* mMoviePlayer;
	EngineWindow* GameMainWindow;
};