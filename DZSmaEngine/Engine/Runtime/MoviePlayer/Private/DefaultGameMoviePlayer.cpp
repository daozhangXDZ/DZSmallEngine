#include "DefaultGameMoviePlayer.h"
#include "GameEngine.h"

DefaultGameMoviePlayer* DefaultGameMoviePlayer::mMoviePlayer = nullptr;

void DefaultGameMoviePlayer::Create()
{
	if (mMoviePlayer == nullptr)
	{
		mMoviePlayer = new DefaultGameMoviePlayer();
	}
}

void DefaultGameMoviePlayer::Clear()
{

}

DefaultGameMoviePlayer* DefaultGameMoviePlayer::get()
{
	return mMoviePlayer;
}


void DefaultGameMoviePlayer::Initialize()
{
	EngineWindow* GameWindow = GameEngine::CreateGameWindow();
	GameMainWindow = GameWindow;
}

bool DefaultGameMoviePlayer::WaitForMovieToFinish()
{
	return GameMainWindow->Run();
}

