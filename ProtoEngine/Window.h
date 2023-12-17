#pragma once
#include <Windows.h>
#include <optional>
#include <string>

class Window {
// Membres publics
public : 
	// Constructeur
	Window(int width, int height, const char* name);

	// Destructeur
	~Window();

	// Méthode statique
	static std::optional<int> ProcessMessages();

// Méthodes privées
private:
	static LRESULT __stdcall WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// Méthode pour créer et attacher le menu
	void InitializeMenu();

// Propriétés privées
private:
	int width;
	int height;
	HWND hWnd;
	const char* windowName = "ProtoEngine Window";
	HINSTANCE hInstance;
	static constexpr int IDM_FILE_NEW = 101;
	static constexpr int IDM_FILE_OPEN = 102;
	static constexpr int IDM_FILE_SAVE = 103;
	static constexpr int IDM_FILE_EXIT = 104;
	static constexpr int IDM_OPTIONS_SETTINGS = 105;
	static constexpr int IDM_WINDOW_TILE = 106;
	static constexpr int IDM_BUILD_COMPILE = 107;
	static constexpr int IDM_HELP_ABOUT = 108;

};