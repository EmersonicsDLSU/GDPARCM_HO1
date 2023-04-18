#pragma once
class IExecutionEvent
{
public:
	virtual void OnSearch() = 0;
	virtual void OnInsert() = 0;
	virtual void OnDelete() = 0;

	virtual void onFinishedExecution() = 0;
};

