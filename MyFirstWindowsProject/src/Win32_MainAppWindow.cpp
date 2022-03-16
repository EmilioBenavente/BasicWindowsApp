#include <windows.h>

LRESULT CALLBACK WindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam);


INT WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PSTR CMD, INT IsVisible)
{

  WNDCLASSA WindowClass = {};
  WindowClass.lpfnWndProc = WindowProc;
  WindowClass.hInstance = Instance;
  WindowClass.lpszClassName = "Window Class";

  RegisterClassA(&WindowClass);

  //@NOTE(Emilio): Creating the Window
  HWND Window = CreateWindowExA(0, WindowClass.lpszClassName, "Learning to Program Window!", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, Instance, 0);

  if(!Window)
    {
      OutputDebugString("Error!");
      return 0;
    }

  ShowWindow(Window, IsVisible);
  
  MSG Message = {};
  while(GetMessage(&Message, 0,0,0))
    {
      TranslateMessage(&Message);
      DispatchMessage(&Message);
    }
  OutputDebugStringA("Working!");
  return 0;
}


LRESULT CALLBACK WindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
  switch(Message)
    {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    case WM_PAINT:
      {
        PAINTSTRUCT Paint;
        HDC hdc = BeginPaint(Window, &Paint);
        FillRect(hdc, &Paint.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
        EndPaint(Window, &Paint);
      }
      return 0;
    }
  return DefWindowProc(Window, Message, WParam, LParam);
}
