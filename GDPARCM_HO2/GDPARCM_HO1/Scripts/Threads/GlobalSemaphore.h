#pragma once
#include <semaphore>
#include <mutex>
#define MAX 1000

class GlobalSemaphore
{
public:
	GlobalSemaphore(int initial, int max);
	void acquire(int keys = 1);
	void release(int keys = 1);

private:
	int initial = 0;
	int max = 0;
	std::counting_semaphore<MAX>* semaphore;
};