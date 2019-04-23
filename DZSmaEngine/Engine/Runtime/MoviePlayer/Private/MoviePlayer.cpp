#include "MoviePlayer.h"
#include "DefaultGameMoviePlayer.h"


void CreateMoviePlayer()
{
	// Do not create the movie player if it already exists
	if (!GetMoviePlayer())
	{
		return DefaultGameMoviePlayer::Create();
	}
}

IGameMoviePlayer* GetMoviePlayer()
{
	return DefaultGameMoviePlayer::get();
}