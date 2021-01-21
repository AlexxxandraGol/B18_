#define _USE_MATH_DEFINE
#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<Windowsx.h>
#include<tchar.h>
#include <cmath>
#define M_PI_2 1.57079632679489661923
#define ID_EDIT 5
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
HWND htext1, htext2, htext3, htext4;
HINSTANCE hinst;
int* fun(float t) {
	int x = 90 * sin(t) ;
	int y = 10 * cos(t) ;
	int result[2] = { x, y };
	return result;
}
int APIENTRY _tWinMain(HINSTANCE This, HINSTANCE hinstanse, LPTSTR cmd, int mode)
{
	HWND hWnd; //Дескриптор главного окна программы
	hinst = hinstanse;
	MSG msg; //Структура для хранения сообщения
	WNDCLASS wc;//Класс окна
	//Определение класса окна
	wc.hInstance = This;
	wc.lpszClassName = WinName; //Имя класса окна
	wc.lpfnWndProc = WndProc; //Имя класса окна
	wc.style = CS_HREDRAW | CS_VREDRAW; //Стиль окна
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //Стандартная иконка
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Стандартный курсор
	wc.lpszMenuName = NULL; //Нет меню
	wc.cbClsExtra = 0; //Нет дополнительных данных класса
	wc.cbWndExtra = 0; //Нет дополнительных данных окна
	//Заполнение окна белым цветом
	wc.hbrBackground = (HBRUSH)(GetStockObject(BLACK_BRUSH));
	if (!RegisterClass(&wc)) return 0;//Регистрация класса окна
	//Создание окна
	hWnd = CreateWindow(WinName,//Имя класса окна
		_T("B18"),//Заголовок окна
		WS_OVERLAPPEDWINDOW, //Стиль окна
		CW_USEDEFAULT,//x
		CW_USEDEFAULT,//y Размеры окна
		256,//Width
		256,//Height
		HWND_DESKTOP,//Дескриптор родительской информации нет
		NULL,//Нет меню
		This,//Дескриптор приложения
		NULL);//Дополнительной информации нет
	ShowWindow(hWnd, mode);//Показать окно
	//Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//Функция трансляции кодов нажатой клавиши
		DispatchMessage(&msg);//Посылает сообщение функции WndProc()
	}
	return 0;

}
//Оконная функция вызывается операционной системой
//и получает сообщения из очереди для данного приложения
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static float t = 0;
	HDC hdc;
	PAINTSTRUCT ps;
	static int sx, sy;
	static int a, b, c, d;
	char A[4], B[4], C[4], D[4];
	int x, y;
	int* result;
	//Обработчик сообщений
	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 80, NULL);
		htext1 = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | ES_READONLY, 10, 10, 40, 20, hWnd, (HMENU)ID_EDIT, hinst, NULL); // Имя класса, Имя окна, Стиль окна, 
		//начальное горизонтальное и вертикальное положение, ширина и высота, 
		// дескриптор родительского или окна владельца, дескриптор меню или ID дочернего окна, дескриптор экземпляра приложения, указатель на данные создания окна  
		htext2 = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | ES_READONLY, 10, 30, 40, 20, hWnd, (HMENU)ID_EDIT, hinst, NULL);
		htext3 = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | ES_READONLY, 10, 50, 40, 20, hWnd, (HMENU)ID_EDIT, hinst, NULL);
		htext4 = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | ES_READONLY, 10, 70, 40, 20, hWnd, (HMENU)ID_EDIT, hinst, NULL);
		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetMapMode(hdc, MM_ANISOTROPIC);
		SetWindowExtEx(hdc, sx, -sy, NULL);
		SetViewportExtEx(hdc, sx / 2, sy / 2, NULL);
		SetViewportOrgEx(hdc, sx / 2, sy / 2, NULL);
		result = fun(t);
		x = result[0];
		y = result[1];
		a = x / 2;
		b = y / 2;
		c = x / 2 + 60;
		d = y / 2 + 60;
		SetBkColor(hdc, RGB(255, 255, 255));
		SelectBrush(hdc, CreateSolidBrush(RGB(255, 228, 181)));
		Rectangle(hdc, a, b, c, d);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_TIMER:
		t += 0.02f;
		_itoa(a, A, 10); //Преобразует целое число в строку. Число, которое требуется преобразовать. Буфер, содержащий результат преобразования. 
		// Основание, используемое для преобразования значения, которое должно находиться в диапазоне 2 - 36.
		_itoa(b, B, 10);
		_itoa(c, C, 10);
		_itoa(d, D, 10);
		SetWindowText(htext1, A); //Изменяет текст строки заголовка указанного окна, Дескриптор окна или элемента управления, текст которого нужно изменить, Новый заголовок или контрольный текст.
		SetWindowText(htext2, B);
		SetWindowText(htext3, C);
		SetWindowText(htext4, D);
		InvalidateRect(hWnd, NULL, FALSE);
		return 0;
	case WM_DESTROY:KillTimer(hWnd, 1); PostQuitMessage(0);
		break;//Завершение программы
		//Обработка сообщений по умолчанию
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}