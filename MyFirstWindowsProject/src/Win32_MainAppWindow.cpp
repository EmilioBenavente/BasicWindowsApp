#include <windows.h>
#include <shobjidl.h> 
//@NOTE(Emilio): stdio.h is currently used for ->
//@TODO(Emilio): 1. Debug Messages
#include <stdio.h>

LRESULT CALLBACK WindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam);
// void PrintDebugAlert(HWND Parent, char* Message, HINSTANCE Instance);


//@NOTE(Emilio): WTF IS IsVisible...WHY!?? When does the user ever set this!??
// INT WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PSTR CMD, INT IsVisible)
// {
//   //@NOTE(Emilio): The Wind Class is a data structure for the OS, _MUST_ declare!  
//   //Also Use EXA if you want to add an icon later to the window itself.
//   WNDCLASSA WindowClass = {};
//   WindowClass.lpfnWndProc = WindowProc;
//   WindowClass.hInstance = Instance;
//   WindowClass.lpszClassName = "MyWindowClass";
  
//   if(RegisterClassA(&WindowClass))
//     {
//       HWND Window =
// 	CreateWindowExA(0,
// 			WindowClass.lpszClassName,
// 			"The Best Windows Application Created!",
// 			WS_OVERLAPPEDWINDOW,
// 			CW_USEDEFAULT, CW_USEDEFAULT,
// 			CW_USEDEFAULT, CW_USEDEFAULT,
// 			0,
// 			0,
// 			Instance,
// 			0);
//       if(Window)
// 	{
// 	  //@NOTE(Emilio): The code that follows is for command line args that edit the window opening
// 	  if(!((int)CMD[0] >= 48 && (int)CMD[0] <= 59))
// 	    {
// 	      CMD[0] = 58;
// 	    }
// 	  char stream[200];
// 	  sprintf(stream, "Info -> %d\n", ((int)CMD[0] - 48));
// 	  // PrintDebugAlert(Window, stream, Instance);
// 	  OutputDebugStringA(stream);
// 	  ShowWindow(Window, ((int)CMD[0] - 48));  
// 	  MSG Message = {};
// 	  while(GetMessage(&Message, 0,0,0))
// 	    {
// 	      TranslateMessage(&Message);
// 	      DispatchMessage(&Message);
// 	    }
// 	  OutputDebugStringA("Working!");
// 	  return EXIT_SUCCESS;
// 	}
//       else
// 	{
// 	  //@TODO(Emilio): GetLastError -> Bad Window Creation
// 	  return EXIT_FAILURE;
// 	}	
//     }

//   else
//     {
//       //@TODO(Emilio): GetLastError -> Bad Window class Initalization
//       return EXIT_FAILURE; 
//     }
// }


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
        FillRect(hdc, &Paint.rcPaint, (HBRUSH) (COLOR_BTNSHADOW + 1));
        EndPaint(Window, &Paint);
      }
      return 0;
    }
  return DefWindowProc(Window, Message, WParam, LParam);
}




//@TODO(Emilio): When we start threading, create your own debug box
//@TODO(Emilio): Create your own printf to work with your debug box

// void PrintDebugAlert(HWND Parent, char* Message, HINSTANCE Instance)
// {
//   WNDCLASSA WindowClass = {};
//   WindowClass.lpfnWndProc = WindowProc;
//   WindowClass.hInstance = Instance;
//   WindowClass.lpszClassName = "MyDebugWindow";

//   if(RegisterClassA(&WindowClass))
//     {
//       HWND Window =
// 	CreateWindowExA(0,
// 			WindowClass.lpszClassName,
// 			Message,
// 			WS_POPUP,
// 			CW_USEDEFAULT, CW_USEDEFAULT,
// 			CW_USEDEFAULT, CW_USEDEFAULT,
// 			0,
// 			0,
// 			Instance,
// 			0);
//       if(Window)
// 	{
// 	  ShowWindow(Window, 10);  
// 	  MSG Message = {};
// 	  while(GetMessage(&Message, 0,0,0))
// 	    {
// 	      TranslateMessage(&Message);
// 	      DispatchMessage(&Message);
// 	    }
// 	  OutputDebugStringA("Working!");
// 	}
//       else
// 	{
// 	  //@TODO(Emilio): GetLastError -> Bad Window Creation
// 	}	
//     } 
// }



//@NOTE(Emilio): This is pulled from MSDN to demonstrate CoInitializeEx
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | 
        COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        IFileOpenDialog *pFileOpen;

        // Create the FileOpenDialog object.
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, 
                IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

        if (SUCCEEDED(hr))
        {
            // Show the Open dialog box.
            hr = pFileOpen->Show(NULL);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hr))
            {
                IShellItem *pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    PWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    // Display the file name to the user.
                    if (SUCCEEDED(hr))
                    {
                        MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
                        CoTaskMemFree(pszFilePath);
                    }
                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
    }
    return 0;
}
