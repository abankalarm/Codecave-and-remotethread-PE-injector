#include<windows.h>
#include <cstdio>
    #define FILE_MENU_NEW 1
    #define FILE_MENU_EXIT 2
    #define SAVE_BUTTON 3
    #define BUTTON_CLIQUE_AQUI1 4
    #define BUTTON_CLIQUE_AQUI2 5
    #define BUTTON_CLIQUE_AQUI3 6
    #define BUTTON_CLIQUE_AQUI4 7


    HWND hEdit;
    char location[200];

    void addMenu(HWND hWnd);
    void addElements(HWND hWnd);

    LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

    int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow){

      WNDCLASS wc = {};



      wc.lpszClassName = "My Window Class";
     // wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
      wc.hbrBackground = (HBRUSH)COLOR_HOTLIGHT;
      wc.lpfnWndProc = WindowProcedure;
      wc.hInstance = hInst;

      RegisterClass(&wc);

      CreateWindow(
        wc.lpszClassName,

        "PE INJECTION",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        0, 0, 800, 600,
        NULL, NULL, NULL, NULL
      );

      MSG msg = {};

      while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }

      return 0;
    }

    LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){

      switch (msg){

        case WM_CREATE:
          addMenu(hWnd);
          addElements(hWnd);
          break;

        case WM_COMMAND:
          switch(wp){
            case FILE_MENU_NEW:
              MessageBox(NULL, "Menu New cliked!", "Message", MB_OK);
              break;
            case FILE_MENU_EXIT:
              DestroyWindow(hWnd);
              break;

            case SAVE_BUTTON:
                GetWindowText(hEdit, location, 200);
                break;

            case BUTTON_CLIQUE_AQUI1:
                //GetWindowText(hEdit, location, 200);
                char buf1[100];
                printf("\nstarting!!! \n");
                snprintf(buf1, sizeof(buf1), "codecave_main.exe %s th",location);
                system(buf1);
                printf("\ncompleted!!! \n");
               break;

            case BUTTON_CLIQUE_AQUI2:
                char buf[100];
                printf("\nstarting!!! \n");
                snprintf(buf, sizeof(buf), "codecave_main.exe %s cv",location);
                system(buf);
                printf("\ncompleted!!! \n");
                break;

            case BUTTON_CLIQUE_AQUI3:
                system("notepad.exe 'config file 2.c'");
                break;

            case BUTTON_CLIQUE_AQUI4:
                system("notepad.exe 'config file.c'");
                break;


          }
          break;

        case WM_DESTROY:
          PostQuitMessage(0);
          return 0;
      }

      return DefWindowProc(hWnd, msg, wp, lp);
    }

    void addMenu(HWND hWnd){

      HMENU hMenu = CreateMenu();
      HMENU hFileMenu = CreateMenu();

      AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New");
      AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
      AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

      AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");

      SetMenu(hWnd, hMenu);
    }

    void addElements(HWND hWnd){

        CreateWindowW(
                 L"Static",
                 L"PE DUAL CODE INJECTOR",
                 WS_VISIBLE | WS_CHILD | SS_CENTER  ,
                 100, 30, 610, 30,
                 hWnd,
                 NULL,NULL,NULL

                 );




                     CreateWindow(
        "Static",
        "The Portable Executable (PE) format is a file format for executables, object code, DLLs and others used in 32-bit and 64-bit versions of Windows operating systems. The PE format is a data structure that encapsulates the information necessary for the Windows OS loader to manage the wrapped executable code.\nThis project is a result of collaborative effort by karan bamal, surbhi goyal, and priyanka biswas and is aimed at leveraging this data structure to inject code that is not part of the original application.",
        WS_VISIBLE | WS_CHILD | SS_CENTER,
        100, 50, 610, 120,
        hWnd,
        NULL, NULL, NULL
      );



        CreateWindowW(
                     L"Static",
                     L"Please enter the location of the file to inject code:",
                     WS_VISIBLE | WS_CHILD | SS_CENTER,
                     100, 180, 610, 20,
                     hWnd,
                     NULL,NULL,NULL

                     );

                      hEdit = CreateWindow(
       "Edit",
        "",
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
        100, 210, 500, 20,
        hWnd,
        NULL, NULL, NULL
      );
        CreateWindow(
        "Button",

        "Save location",
        WS_VISIBLE | WS_CHILD,
        610, 210, 100, 20,
        hWnd,
        (HMENU)SAVE_BUTTON, NULL, NULL
      );


      CreateWindow(
        "Static",
        "What do you want to do?",
        WS_VISIBLE | WS_CHILD | SS_CENTER,
        100, 260, 610, 20,
        hWnd,
        NULL, NULL, NULL
      );


      CreateWindow(
        "Button",
        //"Clique aqui",
        "Execute remote thread injection (default x64)",
        WS_VISIBLE | WS_CHILD,
        100, 330, 300, 50,
        hWnd,
        (HMENU)BUTTON_CLIQUE_AQUI1, NULL, NULL
      );
      CreateWindow(
        "Button",
        //"Clique aqui",
        "Execute Code cave (default x32)",
        WS_VISIBLE | WS_CHILD,
        410, 330, 300, 50,
        hWnd,
        (HMENU)BUTTON_CLIQUE_AQUI2, NULL, NULL
      );
      CreateWindow(
        "Button",
        //"Clique aqui",
        "Configure remote thread",
        WS_VISIBLE | WS_CHILD,
        100, 390, 300, 50,
        hWnd,
        (HMENU)BUTTON_CLIQUE_AQUI3, NULL, NULL
      );
      CreateWindow(
        "Button",
        //"Clique aqui",
        "Configure code cave",
        WS_VISIBLE | WS_CHILD,
        410, 390, 300, 50,
        hWnd,
        (HMENU)BUTTON_CLIQUE_AQUI4, NULL, NULL
      );

    }