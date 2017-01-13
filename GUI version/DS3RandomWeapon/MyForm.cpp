#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThread]
//void SDL_main(array<String^>^ args)
int _stdcall WinMain(
	struct HINSTANCE__ *hInstance,
	struct HINSTANCE__ *hPrevInstance,
	char               *lpszCmdLine,
	int                 nCmdShow
)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	DS3RandomWeapon::MyForm form;
	Application::Run(%form);

	return 0;
}
