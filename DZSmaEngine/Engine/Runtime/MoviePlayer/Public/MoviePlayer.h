#pragma once

/** An interface to the movie player we will use for loading screens and gameplay movies */
class IGameMoviePlayer
{
public:
	virtual void Initialize() = 0;
	virtual bool WaitForMovieToFinish() = 0;
};

class MoviePlayer
{

};


void CreateMoviePlayer();

IGameMoviePlayer* GetMoviePlayer();