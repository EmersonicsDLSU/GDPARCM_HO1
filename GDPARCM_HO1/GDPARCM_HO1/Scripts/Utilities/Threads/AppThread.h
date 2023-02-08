#pragma once
#include <iostream>
#include <thread>

class AppThread
{
public:
	AppThread();
	~AppThread();

	void start(); //schedules thread execution
	static void sleep(int ms);

protected:
	virtual void run() = 0;
};

