#include "GlobalSemaphore.h"

#include <iostream>

GlobalSemaphore::GlobalSemaphore(int initial, int max) : initial(initial), max(max)
{
	this->semaphore = new std::counting_semaphore<MAX>(initial);
}

void GlobalSemaphore::acquire(int keys)
{
	for (int i = 0; i < keys; i++)
	{
		this->semaphore->acquire();
		--initial;
	}
}

void GlobalSemaphore::release(int keys)
{
	// if the release keys will exceed the max number
	if (keys + initial > max)
	{
		std::cout << "Release key is greater than initial" << std::endl;
		throw std::runtime_error("Release key is greater than initial");
	}
	this->semaphore->release(keys);
	initial += keys;
}
