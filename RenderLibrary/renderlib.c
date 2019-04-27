#include <windows.h>
#include <stdio.h>
#include "renderlib.h"

static HWND _hwnd;
static HDC _win_hDC;
static WNDCLASS _win_class;

static int _win_w = 0;
static int _win_h = 0;
static int _buffer_w = 0;
static int _buffer_h = 0;

static int _frames = -1;
static FILETIME _start_frame_time = { 0 };
static FILETIME _start_total_time = { 0 };

static COLOR* _buffer = NULL;
static BITMAPINFO _bmp_info;

LRESULT CALLBACK _window_proc_func(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT wsize;

    if (message == WM_PAINT)
    {
        if (_buffer != NULL)
        {
            GetClientRect(hWnd, &wsize);
            StretchDIBits(_win_hDC, 0, 0, wsize.right, wsize.bottom, 0, 0, _buffer_w, _buffer_h, _buffer, &_bmp_info, DIB_RGB_COLORS, SRCCOPY);
            ValidateRect(_hwnd, NULL);
        }
    }
    else if (message == WM_KEYDOWN)
    {
        if (wParam == VK_ESCAPE)
        {
            renderlib_release();
            ExitProcess(0);
        }
    }
    else if (message == WM_CLOSE)
    {
        renderlib_release();
        ExitProcess(0);
    }
    else
        return (int)DefWindowProc(hWnd, message, wParam, lParam);

    return 1;
}

int renderlib_create_window(WCHAR* title, int width, int height)
{
	int x;
	int y;
    RECT rect;

    _win_class.style = CS_HREDRAW | CS_VREDRAW;
    _win_class.lpfnWndProc = (WNDPROC)_window_proc_func;
    _win_class.cbClsExtra = 0;
    _win_class.cbWndExtra = 0;
    _win_class.hInstance = NULL;
    _win_class.hbrBackground = NULL;
    _win_class.lpszMenuName = NULL;
    _win_class.lpszClassName = title;

    if (RegisterClass(&_win_class) == 0)
        return 1;

    x = (GetSystemMetrics(SM_CXSCREEN) - width) >> 1;
    y = (GetSystemMetrics(SM_CYSCREEN) - height) >> 1;

    _buffer_w = width;
    _buffer_h = height;

    rect.top = y;
    rect.left = x;
    rect.right = x + width;
    rect.bottom = y + height;

    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW | WS_VISIBLE, FALSE);

    _win_w = rect.right - rect.left;
    _win_h = rect.bottom - rect.top;

    _hwnd = CreateWindowEx(
        0,
        title,
        title,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        x, y, _win_w, _win_h,
        NULL,
        NULL,
        NULL,
        NULL);

    if (_hwnd == NULL)
        return 1;

    _buffer = malloc((size_t)_buffer_w * (size_t)_buffer_h * sizeof(COLOR));
    if (_buffer == NULL)
    {
        printf("Failed to allocate color buffer.\n");
        return 1;
    }

    memset(&_bmp_info, 0, sizeof(BITMAPINFO));
    _bmp_info.bmiHeader.biBitCount = 32;
    _bmp_info.bmiHeader.biHeight = -height;
    _bmp_info.bmiHeader.biWidth = width;
    _bmp_info.bmiHeader.biPlanes = 1;
    _bmp_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

    _win_hDC = GetDC(_hwnd);

    ShowWindow(_hwnd, SW_SHOW);
    UpdateWindow(_hwnd);

    return 0;
}

COLOR* renderlib_get_color_buffer()
{
    return _buffer;
}

void renderlib_update()
{
    MSG msg;

    SendMessage(_hwnd, WM_PAINT, 0, 0);

    while (PeekMessage(&msg, _hwnd, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

int renderlib_get_pixel(int x, int y, COLOR* color)
{
    if (_buffer == NULL || color == NULL || x < 0 || y < 0 || x >= _buffer_w || y >= _buffer_h)
        return 0;

    *color = _buffer[y * _buffer_w + x];

    return 1;
}

int renderlib_set_pixel(int x, int y, COLOR color)
{
    if (_buffer == NULL || x < 0 || y < 0 || x >= _buffer_w || y >= _buffer_h)
        return 0;

    _buffer[y * _buffer_w + x] = color;

    return 1;
}

int renderlib_write_bitmap(char* filename)
{
    int x;
    int y;
    FILE* fd;
    BITMAPFILEHEADER fh;

    if (_buffer == NULL)
        return 0;

    if (fopen_s(&fd, filename, "wb") != 0 || fd == NULL)
        return 0;

    fh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    fh.bfReserved1 = 0;
    fh.bfReserved2 = 0;
    fh.bfType = 0x4D42;
    fh.bfSize = fh.bfOffBits + (_buffer_w * _buffer_h * 4);

    _bmp_info.bmiHeader.biHeight = _buffer_h;

    fwrite(&fh, sizeof(fh), 1, fd);
    fwrite(&_bmp_info.bmiHeader, sizeof(_bmp_info.bmiHeader), 1, fd);

    _bmp_info.bmiHeader.biHeight = -_buffer_h;

    for (y = _buffer_h - 1; y >= 0; y--)
    {
        for (x = 0; x < _buffer_w; x++)
            fwrite(_buffer + ((size_t)y * _buffer_w + x), sizeof(COLOR), 1, fd);
    }

    fclose(fd);

    return 1;
}

int renderlib_clear()
{
    if (_buffer == NULL)
        return 0;

    memset(_buffer, 0, (size_t)_buffer_w * (size_t)_buffer_h * sizeof(COLOR));

    return 1;
}

void renderlib_release()
{
    ReleaseDC(_hwnd, _win_hDC);
    DestroyWindow(_hwnd);
    SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, 1, 0, 0);
}

void usleep(long long usec)
{
    HANDLE timer;
    LARGE_INTEGER ft;

    ft.QuadPart = -(10 * usec);

    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    if (timer == 0)
    {
        printf("Call to CreateWaitableTimer failed.\n");
        exit(1);
    }

    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
}

void renderlib_sync_start()
{
    GetSystemTimePreciseAsFileTime(&_start_frame_time);

    if (_start_total_time.dwHighDateTime == 0 && _start_total_time.dwLowDateTime == 0)
        _start_total_time = _start_frame_time;
}

void renderlib_sync_end(int hertz, int print_fps)
{
    FILETIME ft;
    ULARGE_INTEGER start_frame_time;
    ULARGE_INTEGER current_frame_time;
    ULARGE_INTEGER start_total_time;

    GetSystemTimePreciseAsFileTime(&ft);

    start_frame_time.LowPart = _start_frame_time.dwLowDateTime;
    start_frame_time.HighPart = _start_frame_time.dwHighDateTime;

    current_frame_time.LowPart = ft.dwLowDateTime;
    current_frame_time.HighPart = ft.dwHighDateTime;

    start_total_time.LowPart = _start_total_time.dwLowDateTime;
    start_total_time.HighPart = _start_total_time.dwHighDateTime;

    usleep((1000 * 1000 / hertz) - ((current_frame_time.QuadPart - start_frame_time.QuadPart) / 10));

    if (print_fps == 0)
        return;

    if (_frames < 0)
        _frames = 1;
    else
        _frames++;

    if (current_frame_time.QuadPart - start_total_time.QuadPart >= 10000000)
    {
        printf("fps: %d\n", _frames);
        _start_total_time = ft;
        _frames = 0;
    }
}
