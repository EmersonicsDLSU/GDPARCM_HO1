#include "PoolWorkerThread.h"

#include "IFinishedTask.h"
#include "IWorkerAction.h"

PoolWorkerThread::PoolWorkerThread(int id, IFinishedTask* finishedTask) : id(id), finishedTask(finishedTask)
{
}

PoolWorkerThread::~PoolWorkerThread()
{
	delete action;
	delete finishedTask;
}

int PoolWorkerThread::GetThreadID()
{
	return id;
}

void PoolWorkerThread::AssignTask(IWorkerAction* action)
{
}

void PoolWorkerThread::run()
{
}
