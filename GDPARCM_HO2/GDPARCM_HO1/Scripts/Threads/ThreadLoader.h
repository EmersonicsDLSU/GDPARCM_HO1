#pragma once
#include "IETThread.h"
#include "IWorkerAction.h"

enum class SID_ENUM
{
	SEARCH = 0,
	INSERT,
	DELETE
};

class IExecutionEvent;

class ThreadLoader : public IWorkerAction
{
private:
	typedef std::string String;
public:
	ThreadLoader(int ID, SID_ENUM enumType, IExecutionEvent* executionEvent);
	~ThreadLoader();
private:
	void OnStartTask() override;

	int ID = 0;
	SID_ENUM enumType;
	IExecutionEvent* execEvent;
};

