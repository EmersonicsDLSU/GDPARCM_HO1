#include "BaseWindow/BaseWindow.h"

int main()
{
    BaseWindow* base_window = BaseWindow::GetInstance();
    base_window->Run();
    delete base_window;
    return 0;
}