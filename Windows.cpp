#define UNICODE
#include <SDL2/SDL.h>
#include <windows.h>
#include "Game.h"
#include "MainLoop.h"
// Isso e uma bagunça, experimentos usando o window.h
HWND button;
// Isso abaixo e como se posse uma thead separada os itens em WindowProc rodam independente o WinMain
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    SDL_Window *sdlWindow;
    gameWin game;
    mainLoop masterBehaviour;
    std::string alert;
    int status;
    switch (uMsg)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == 1)
        {
            EnableWindow(button, FALSE);
            sdlWindow = SDL_CreateWindowFrom(hwnd);
            game.OpenGame(sdlWindow);
            game.OpenRender();
            status = masterBehaviour.gameLoop(game.window, game.renderer);
            game.CloseGame();
            MessageBox(hwnd, L"Jogo encerrado", L"Encerrado", MB_OK);
            EnableWindow(button, TRUE);
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"GameLaucher";
    const wchar_t WINDOW_NAME[] = L"Fruit Rain SDL Edition for Windows";
    // Registrar a classe da janela
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);
    // Criar a janela
    HWND hwnd = CreateWindow(CLASS_NAME,
                             WINDOW_NAME,
                             WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX,
                             CW_USEDEFAULT,
                             CW_USEDEFAULT,
                             200,
                             200,
                             NULL,
                             NULL,
                             hInstance,
                             NULL);
    HWND label = CreateWindowEx(
        0,                     // Estilo estendido
        L"STATIC",             // Classe de controle
        L"Iniciar Jogo",       // Texto do rótulo
        WS_VISIBLE | WS_CHILD, // Estilo do rótulo
        30, 10,                // Posição do rótulo
        200, 20,               // Tamanho do rótulo
        hwnd,                  // Identificador da janela pai
        NULL,                  // Identificador do menu (não usado para rótulos)
        hInstance,             // Instância do aplicativo
        NULL                   // Dados adicionais (não usado)
    );
    button = CreateWindowEx(
        0,                     // Estilo estendido
        L"BUTTON",             // Classe de controle
        L"Start",              // Texto do botão
        WS_VISIBLE | WS_CHILD, // Estilo do botão
        30, 100,               // Posição do botão
        100, 30,               // Tamanho do botão
        hwnd,                  // Identificador da janela pai
        (HMENU)1,              // Identificador do menu (não usado para botões)
        hInstance,             // Instância do aplicativo
        NULL                   // Dados adicionais (não usado)
    );
    // Exibir a janela
    ShowWindow(hwnd, nCmdShow);
    // Loop de mensagens
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}