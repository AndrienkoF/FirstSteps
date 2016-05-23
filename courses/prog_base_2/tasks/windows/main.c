#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <tchar.h>
#include <CommCtrl.h>
#include "leading.h"



// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
                   HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow
                  )
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;
    const char g_szClassName[] = "myWindowClass";

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Windows task",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    HINSTANCE hInst = GetModuleHandle(NULL);
	static HWND hButtonCheck;
	static HWND hStaticName, hStaticSurname, hStaticRadio, hStaticSalary;
    static HWND hStaticName2, hStaticSurname2, hStaticRadio2, hStaticSalary2;
	static HWND hEditName, hEditSurname, hEditRadio, hEditSalary;

    char buffName[100];
    char buffSurname[100];
    char buffRadio[100];
    char buffSalary[100];

	static leading_t * newLeading[100];
	int curIndex;
    enum {
        BUTTON_CHECK = 1,
        STATIC_NAME,
        STATIC_SURNAME,
        STATIC_NUMRADIOPROGRAMS,
        STATIC_SALARY,
        STATIC_NAME2,
        STATIC_SURNAME2,
        STATIC_NUMRADIOPROGRAMS2,
        STATIC_SALARY2,
        EDIT_NAME,
        EDIT_SURNAME,
        EDIT_RADIO,
        EDIT_SALARY,
    };

    switch(msg){
        case WM_CREATE: {

		// "check" button
		hButtonCheck = CreateWindowEx(0,
			WC_BUTTON,
			"CHECK",
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
			50, 300, 100, 25,
			hwnd,
			(HMENU)BUTTON_CHECK,
			hInst,
			NULL);

		// name lable
		hStaticName = CreateWindowEx(0,
			WC_STATIC,
			"",
			WS_CHILD | WS_VISIBLE,
			50, 50, 100, 25,
			hwnd,
			(HMENU)STATIC_NAME,
			hInst,
			NULL);
		SetWindowText(hStaticName, "Name:");

		// surname lable
		hStaticSurname = CreateWindowEx(0,
			WC_STATIC,
			"",
			WS_CHILD | WS_VISIBLE,
			50, 100, 100, 25,
			hwnd,
			(HMENU)STATIC_SURNAME,
			hInst,
			NULL);
		SetWindowText(hStaticSurname, "Surname:");

		// num Radio Programs lable
		hStaticRadio = CreateWindowEx(0,
			WC_STATIC,
			"",
			WS_CHILD | WS_VISIBLE,
			50, 150, 100, 25,
			hwnd,
			(HMENU)STATIC_NUMRADIOPROGRAMS,
			hInst,
			NULL);
		SetWindowText(hStaticRadio, "numRadioPrograms:");

		// salary lable
		hStaticSalary = CreateWindowEx(0,
			WC_STATIC,
			"",
			WS_CHILD | WS_VISIBLE,
			50, 200, 100, 25,
			hwnd,
			(HMENU)STATIC_SALARY,
			hInst,
			NULL);
		SetWindowText(hStaticSalary, "Salary:");

        //name
        hEditName = CreateWindowEx(0,
            WC_EDIT,
            "",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
			175, 50, 100, 25,
            hwnd,
            (HMENU)EDIT_NAME,
            hInst,
            NULL);

        //surname
        hEditSurname = CreateWindowEx(0,
            WC_EDIT,
            "",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
			175, 100, 100, 25,
            hwnd,
            (HMENU)EDIT_SURNAME,
            hInst,
            NULL);

        //numRadioStation
        hEditRadio = CreateWindowEx(0,
            WC_EDIT,
            "",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
			175, 150, 100, 25,
            hwnd,
            (HMENU)EDIT_RADIO,
            hInst,
            NULL);

        //salary
        hEditSalary = CreateWindowEx(0,
            WC_EDIT,
            "",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
			175, 200, 100, 25,
            hwnd,
            (HMENU)EDIT_SALARY,
            hInst,
            NULL);

        // name lable2
		hStaticName2 = CreateWindowEx(0,
			WC_STATIC,
			"",
			WS_CHILD | WS_VISIBLE,
			300, 50, 100, 25,
			hwnd,
			(HMENU)STATIC_NAME2,
			hInst,
			NULL);
		SetWindowText(hStaticName2, "--");

		// surname lable2
		hStaticSurname2 = CreateWindowEx(0,
			WC_STATIC,
			"",
			WS_CHILD | WS_VISIBLE,
			300, 100, 100, 25,
			hwnd,
			(HMENU)STATIC_SURNAME2,
			hInst,
			NULL);
		SetWindowText(hStaticSurname2, "--");

		// num Radio Programs lable2
		hStaticRadio2 = CreateWindowEx(0,
			WC_STATIC,
			"",
			WS_CHILD | WS_VISIBLE,
			300, 150, 100, 25,
			hwnd,
			(HMENU)STATIC_NUMRADIOPROGRAMS2,
			hInst,
			NULL);
		SetWindowText(hStaticRadio2, "--");

		// salary lable2
		hStaticSalary2 = CreateWindowEx(0,
			WC_STATIC,
			"",
			WS_CHILD | WS_VISIBLE,
			300, 200, 100, 25,
			hwnd,
			(HMENU)STATIC_SALARY2,
			hInst,
			NULL);
		SetWindowText(hStaticSalary2, "--");


		curIndex = 0;

		for (int i = 0; i < 100; i++) {
			newLeading[i] = leading_new();
		}

		break;
	}

	case WM_COMMAND: {
		switch (LOWORD(wParam)) {

		case BUTTON_CHECK: {

            GetWindowText(hEditName, buffName, sizeof(buffName));
            GetWindowText(hEditSurname, buffSurname, sizeof(buffSurname));
            GetWindowText(hEditRadio, buffRadio, sizeof(buffRadio));
            GetWindowText(hEditSalary, buffSalary, sizeof(buffSalary));

            if((atoi(buffName) != 0) || (atoi(buffSurname) != 0) || (atoi(buffRadio) == 0) || (atoi(buffSalary) == 0)){
                MessageBox (NULL, TEXT ("WARNING!"), TEXT ("Help"), 0) ;
            }else{
                SetWindowText(hStaticName2, TEXT(buffName));
                SetWindowText(hStaticSurname2, TEXT(buffSurname));
                SetWindowText(hStaticRadio2, TEXT(buffRadio));
                SetWindowText(hStaticSalary2, TEXT(buffSalary));
                leading_fill(newLeading[curIndex], buffName, buffSurname,atoi(buffRadio), atoi(buffSalary));
                curIndex++;
            }
			break;
		}

		}
		break;
	}
    case WM_CLOSE: {
		DestroyWindow(hButtonCheck);

		DestroyWindow(hStaticName);
		DestroyWindow(hStaticSurname);
		DestroyWindow(hStaticRadio);
		DestroyWindow(hStaticSalary);

		DestroyWindow(hStaticName2);
		DestroyWindow(hStaticSurname2);
		DestroyWindow(hStaticRadio2);
		DestroyWindow(hStaticSalary2);

		DestroyWindow(hEditName);
		DestroyWindow(hEditSalary);
		DestroyWindow(hEditRadio);
		DestroyWindow(hEditSalary);

        DestroyWindow(hwnd);

		for (int i = 0; i < 100; i++) {
			leading_free(newLeading[i]);
		}
		break;
	}

	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}

	default: {
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	}
    return 0;
}
