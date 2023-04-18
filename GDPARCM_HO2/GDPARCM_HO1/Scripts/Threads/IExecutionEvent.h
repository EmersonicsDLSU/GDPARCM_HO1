#pragma once
class IExecutionEvent
{
public:
	virtual void OnSearch(int ID) = 0;
	virtual void OnInsert(int ID) = 0;
	virtual void OnDelete(int ID) = 0;

	virtual void onFinishedExecution() = 0;
};

