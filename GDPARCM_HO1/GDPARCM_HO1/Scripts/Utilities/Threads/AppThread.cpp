#include "AppThread.h"

AppThread::AppThread()
{
}

AppThread::~AppThread()
{
}

void AppThread::start()
{
	//detach thread for independent execution. without this, join() function must be called.
	std::thread(&AppThread::run, this).detach();
}

void AppThread::sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

