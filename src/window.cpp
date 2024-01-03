#include "window.h"
#include "window_system.h"
using namespace MyUno;

Window::Window(WindowSystem& manager, int id):
    windowSystem(manager), Id(id)
{
}
