// zadanie11.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "zadanie11.h"
#include "Windows.h"
#include "commdlg.h"
#include <string>
#define MAX_LOADSTRING 100
// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
COLORREF dColors[16];
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ZADANIE11, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ZADANIE11));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    
    wcex.style          = CS_HREDRAW | CS_VREDRAW|CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ZADANIE11));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ZADANIE11);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

#define ID_COLOR_BUTTON 1001
#define ID_FIND_BUTTON 1488

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   HWND hComboBox = CreateWindowW(L"ComboBox", L"Пример comboBox", WS_VISIBLE | WS_CHILD|CBS_DROPDOWN,
       20, 20, 250, 100, hWnd, nullptr, hInstance, nullptr);
   if (!hComboBox)
   {
       return false;
   }

   HWND hSysLine = CreateWindowW(L"STATIC", L"Пример гиперссылкиылки", WS_VISIBLE | WS_CHILD|SS_NOTIFY,
       20, 50, 150, 20, hWnd, nullptr, hInstance, nullptr);
   if (!hSysLine)
   {
       return false;
   }
   SetWindowText(hSysLine, L"Hi bro");


   HWND hButton = CreateWindowW(L"BUTTON", L"Пример кнопки", WS_VISIBLE | WS_CHILD,
       20, 75, 150, 30, hWnd, nullptr, hInstance, nullptr);
   if (!hButton)
   {
       return false;
   }

   HWND hEdit= CreateWindowW(L"SysIPAddress32", nullptr, WS_VISIBLE | WS_CHILD | WS_BORDER,
       20, 120, 150, 30, hWnd, nullptr, hInstance, nullptr);
   if (!hEdit)
   {
       return false;
   }

   HWND hButtonColor = CreateWindowW(L"BUTTON", L"Выбери цвет", WS_VISIBLE | WS_CHILD,
       20, 160, 150, 30, hWnd, (HMENU)ID_COLOR_BUTTON, hInstance, nullptr);
   if (!hButtonColor)
   {
       return false;
   }
   SendMessage(hButtonColor, BM_SETSTATE, FALSE, 0);
   SetWindowText(hButtonColor, L"Выбрать цвет");
   HWND hButtonFind = CreateWindowW(L"BUTTON", L"Поиск", WS_VISIBLE | WS_CHILD,
       20, 200, 150, 30, hWnd, (HMENU)ID_FIND_BUTTON, hInstance, nullptr);
   if (!hButtonFind)
   {
       return false;
   }
   SendMessage(hButtonFind, BM_SETSTATE, FALSE, 0);
   SetWindowText(hButtonFind, L"Поиск");


   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

    bool down = false;
    bool up = false;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    CHOOSECOLOR cc = { sizeof(CHOOSECOLOR) };
    FINDREPLACE ft = { sizeof(FINDREPLACE) };
    WCHAR saveText[256] = { 0 };
    switch (message)
    {
        case WM_CHAR:
            MessageBox(hWnd, L"WM_CHAR", L"WM_CHAR", MB_OK|MB_ICONINFORMATION);
            break;

        case WM_KEYDOWN:
            MessageBox(hWnd, L"WM_KEYDOWN", L"WM_KEYDOWN", MB_OK | MB_ICONINFORMATION);
            break;

            case WM_LBUTTONDBLCLK:
            MessageBox(hWnd, L"WM_LBUTTONDBLCLK", L"WM_LBUTTONDBLCLK", MB_OK | MB_ICONINFORMATION);
            break;

        case WM_LBUTTONDOWN:
            if (!down)
            {
            MessageBox(hWnd, L"WM_LBUTTONDOWN", L"WM_LBUTTONDOWN", MB_OK | MB_ICONINFORMATION);
            down = true;
            }
            break;

        case WM_LBUTTONUP:
            if (!up)
            {
            MessageBox(hWnd, L"WM_LBUTTONUP", L"WM_LBUTTONUP", MB_OK | MB_ICONINFORMATION);
            up = true;
            }
            break;

        //case WM_MOUSEMOVE:
        //    MessageBox(hWnd, L"WM_MOUSEMOVE", L"WM_MOUSEMOVE", MB_OK | MB_ICONINFORMATION);
        //    break;

        case WM_MOVE:
            MessageBox(hWnd, L"WM_MOVE", L"WM_MOVE", MB_OK | MB_ICONINFORMATION);
            break;
        case WM_COMMAND:
            {
                int wmId = LOWORD(wParam);
                // Разобрать выбор в меню:
                switch (wmId)
                {
                case IDM_ABOUT:
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                    break;
                case IDM_EXIT:
                    DestroyWindow(hWnd);
                    break;
                case ID_COLOR_BUTTON:
                    cc.Flags = CC_RGBINIT | CC_FULLOPEN;
                    cc.hInstance = NULL;
                    cc.hwndOwner = hWnd;
                    cc.lCustData = 0L;
                    cc.lpCustColors = dColors; //массив пользовательских цветов
                    cc.lpfnHook = NULL;
                    cc.lpTemplateName = NULL;
                    cc.lStructSize = sizeof(cc); //sizeof() - возвращает размер любой структуры данных - часть языка СИ
                    cc.rgbResult = RGB(255, 0, 0); //цвет, заданный для диалога по умолчанию
                    if (ChooseColor(&cc) != FALSE){
                    }
                    break;
                case ID_FIND_BUTTON:
                    ZeroMemory(&ft, sizeof(ft));
                    ft.lStructSize = sizeof(FINDREPLACEA);
                    ft.hInstance = hInst;
                    ft.hwndOwner = hWnd;
                    ft.lpstrFindWhat = saveText;
                    ft.wFindWhatLen = 256;

                    if (FindText(&ft) != FALSE) {
                    }
                
                    break;

                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
                }
            }
            break;
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);
                // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
                EndPaint(hWnd, &ps);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}