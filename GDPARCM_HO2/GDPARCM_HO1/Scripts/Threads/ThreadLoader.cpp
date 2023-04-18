#include "ThreadLoader.h"

#include "IExecutionEvent.h"
#include "Utilities/Manager/TextureManager.h"
#include "Utilities/Utils/StringUtils.h"

ThreadLoader::ThreadLoader(int ID, SID_ENUM enumType, IExecutionEvent* executionEvent)
{
	this->ID = ID;
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
		std::cout << "ID: " << ID << std::endl;
		execEvent->OnSearch(ID);
		break;
	case SID_ENUM::INSERT:
		execEvent->OnInsert(ID);
		break;
	case SID_ENUM::DELETE:
		execEvent->OnDelete(ID);
		break;
	}

	// delete after being done
	delete this;
}

