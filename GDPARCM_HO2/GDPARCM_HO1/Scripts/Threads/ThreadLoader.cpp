#include "ThreadLoader.h"

#include "IExecutionEvent.h"
#include "Utilities/Manager/TextureManager.h"
#include "Utilities/Utils/StringUtils.h"

ThreadLoader::ThreadLoader(SID_ENUM enumType, IExecutionEvent* executionEvent)
{
	this->enumType = enumType;
	execEvent = executionEvent;
}

ThreadLoader::~ThreadLoader()
{
	//std::cout << "Destroying stream asset loader. " << std::endl;
}

void ThreadLoader::OnStartTask()
{
	switch (enumType)
	{
	case SID_ENUM::SEARCH:
		execEvent->OnSearch();
		break;
	case SID_ENUM::INSERT:
		execEvent->OnInsert();
		break;
	case SID_ENUM::DELETE:
		execEvent->OnDelete();
		break;
	}

	// delete after being done
	delete this;
}

