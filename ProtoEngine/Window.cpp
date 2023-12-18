#include "Window.h"

Window::Window(int width, int height, const char* name)
	:
	width(width),
	height(height),
	hInstance(GetModuleHandle(nullptr))
{
	WNDCLASSEX wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.lpfnWndProc = WindowProc;
	wcex.hInstance = hInstance;
	wcex.lpszClassName = windowName;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(36, 36, 36));

	wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);

	RegisterClassEx(&wcex);

	RECT winRect;
	winRect.left = 0;
	winRect.right = width + winRect.left;
	winRect.top = 0;
	winRect.bottom = height + winRect.top;
	AdjustWindowRect(&winRect, WS_CAPTION | WS_SYSMENU | WS_THICKFRAME, FALSE);

	hWnd = CreateWindow(
		windowName, name,
		WS_OVERLAPPEDWINDOW |
		WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, winRect.right - winRect.left, winRect.bottom - winRect.top,
		nullptr, nullptr, hInstance, this
	);

	// Initialiser le menu
	InitializeMenu();

	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	UnregisterClass(windowName, hInstance);
	DestroyWindow(hWnd);
}

std::optional<int> Window::ProcessMessages()
{
	MSG msg = {};
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return msg.wParam;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return {};
}

LRESULT __stdcall Window::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);

			// Gérer les sélections de menu ici
			switch (wmId)
			{
			case IDM_FILE_NEW:
				// Code pour le menu "New"
				break;
			case IDM_FILE_OPEN:
			{
				// Code pour le menu "Open"
				OPENFILENAMEW ofn;
				
				wchar_t szFile[MAX_PATH] = L"";

				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lStructSize = sizeof(ofn);
				ofn.hwndOwner = hWnd;
				ofn.lpstrFile = szFile;
				ofn.lpstrFile[0] = L'\0';
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter = L"Skymunt Project Files (*.skmtp)\0*.skmtp\0All Files (*.*)\0*.*\0";
				ofn.nFilterIndex = 1;
				ofn.lpstrTitle = L"Select a Skymunt Project File";
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

				if (GetOpenFileNameW(&ofn) == TRUE)
				{
					// 
				}
			}
			break;
			case IDM_FILE_SAVE:
			{
				// Code pour le menu "Save"
				OPENFILENAMEW ofn;

				wchar_t szFile[MAX_PATH] = L"";

				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lStructSize = sizeof(ofn);
				ofn.hwndOwner = hWnd;
				ofn.lpstrFile = szFile;
				ofn.lpstrFile[0] = L'\0';
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter = L"Skymunt Project Files (*.skmtp)\0*.skmtp\0All Files (*.*)\0*.*\0";
				ofn.nFilterIndex = 1;
				ofn.lpstrTitle = L"Select a Skymunt Project File";
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

				if (GetSaveFileNameW(&ofn) == TRUE)
				{
					// Vérifie si l'extension est déjà présente dans le nom de fichier
					wchar_t desiredExtension[] = L".skmtp";
					size_t extensionLength = wcslen(desiredExtension);

					size_t filenameLength = wcslen(szFile);
					bool hasExtension = (filenameLength >= extensionLength &&
						wcscmp(szFile + filenameLength - extensionLength, desiredExtension) == 0);

					// Si l'extension n'est pas présente, l'ajouter
					if (!hasExtension)
					{
						wcscat_s(szFile, MAX_PATH, desiredExtension);
					}

					// Utilisez le chemin d'accès récupéré pour enregistrer votre fichier
					// Utilisez szFile modifié pour inclure l'extension
					// Exemple : Ouverture du fichier pour écriture
					FILE* file;
					_wfopen_s(&file, szFile, L"wb"); // Utilisation de "wb" pour une écriture binaire, ajustez selon votre besoin

					if (file != nullptr)
					{
						// Écriture dans le fichier si nécessaire
						fclose(file); // Assurez-vous de fermer le fichier après avoir terminé
					}
					else
					{
						// Gestion des erreurs lors de l'ouverture du fichier
					}
				}


			}
			break;
			case IDM_FILE_EXIT:
				// Code pour le menu "Exit"
				PostQuitMessage(0);
				break;
			default:
				return DefWindowProc(hWnd, msg, wParam, lParam);
			}
		}
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void Window::InitializeMenu()
{
	HMENU hMenu = CreateMenu();

	HMENU hFileMenu = CreateMenu();
	AppendMenu(hFileMenu, MF_STRING, IDM_FILE_NEW, "New");
	AppendMenu(hFileMenu, MF_STRING, IDM_FILE_OPEN, "Open");
	AppendMenu(hFileMenu, MF_STRING, IDM_FILE_SAVE, "Save");
	AppendMenu(hFileMenu, MF_SEPARATOR, 0, nullptr);
	AppendMenu(hFileMenu, MF_STRING, IDM_FILE_EXIT, "Exit");

	HMENU hOptionsMenu = CreateMenu();
	AppendMenu(hOptionsMenu, MF_STRING, IDM_OPTIONS_SETTINGS, "Settings");

	HMENU hWindowMenu = CreateMenu();
	AppendMenu(hWindowMenu, MF_STRING, IDM_WINDOW_TILE, "Tile Windows");

	HMENU hBuildMenu = CreateMenu();
	AppendMenu(hBuildMenu, MF_STRING, IDM_BUILD_COMPILE, "Compile");

	HMENU hHelpMenu = CreateMenu();
	AppendMenu(hHelpMenu, MF_STRING, IDM_HELP_ABOUT, "About");

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hOptionsMenu, "Options");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hWindowMenu, "Window");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hBuildMenu, "Build");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, "Help");

	SetMenu(hWnd, hMenu);
}