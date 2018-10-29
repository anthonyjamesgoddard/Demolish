#ifndef _GAMETIMER
#define _GAMETIMER
typedef unsigned int UINT;


namespace demolish{
    class GameTimer;
}

class demolish::GameTimer
{
public:
	GameTimer();
	float GameTime();
	float DeltaTime();
	void Reset(); //this is to be called before message loop
	void Start(); // when unpaused
	void Stop();  // when paused
	void Tick();  //every frame

private:
	double deltaTime;

	struct timespec baseTime;
	struct timespec pausedTime;
	struct timespec stopTime;
	struct timespec prevTime;
	struct timespec currTime;

	bool stopped;
};

#endif 
