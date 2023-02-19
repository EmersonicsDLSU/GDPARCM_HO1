#include "ThreadPool.h"

#include "PoolWorkerThread.h"

ThreadPool::ThreadPool(String name, int numWorkers) : name(name), numWorkers(numWorkers)
{
	for (int i = 0; i < numWorkers; ++i)
	{
		PoolWorkerThread* tempWorker = new PoolWorkerThread(i, this);
		inactiveThreads.push(tempWorker);
	}
}

ThreadPool::~ThreadPool()
{
	StopScheduler();
	activeThreads.clear();
	while (!inactiveThreads.empty())
	{
		inactiveThreads.pop();
	}
}

void ThreadPool::StartScheduler()
{
	running = true;
	start();
}

void ThreadPool::StopScheduler()
{
}

void ThreadPool::ScheduleTask(IWorkerAction* action)
{
}

void ThreadPool::run()
{
}

void ThreadPool::OnFinished(int threadID)
{
}
