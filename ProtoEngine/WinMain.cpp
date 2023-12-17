#include "Window.h"

int __stdcall WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	Window window(1280, 720, "ProtoEngine Window");

    while (true) {
        if (const auto msgCode = Window::ProcessMessages())
            return *msgCode;
    }
}