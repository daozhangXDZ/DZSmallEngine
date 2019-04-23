#pragma once
#include "MoviePlayer.h"
#include "EngineWindow.h"

/// <summary>
/// 一个默认的客户端播放器【按照电影的方式做引擎，哈哈】
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