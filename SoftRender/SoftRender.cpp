// SoftRender.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "SoftRender.h"
#include <iostream>
#include "Vector.h"
#include "Matrix.h"
#include "Vertex.h"
#include "Camera.h"
#include "Triangle.h"
#include "LineDrawer.h"
#include "DrawingManager.h"
#include "Color.h"
#include "ObjLoader.h"

int x_rotate = 0;
int y_rotate = 0;
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
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
    
    // TODO: Place code here.
    
    ObjLoader loader;
    if (loader.load("C:/Users/Administrator/Desktop/african_head.obj")) {
        loader.printInfo();
        std::cout << "hello bb8" << std::endl;
    }
    else {
        std::cerr << "Failed to load OBJ file" << std::endl;
    }
    DrawingManager drawingManager(800, 600);
    

    // 创建三维顶点
    Vertex v1(0, 0, 0, 1, Vector(-1, -1, -1), Color(1, 0, 0));
    Vertex v2(0, 0.5, 0, 1, Vector(-1, 1, -1), Color(1, 0, 0));
    Vertex v3(0.5, 0, 0, 1, Vector(1, -1, -1), Color(1, 0, 0));
    Vertex v4(0.5, 0.5, 0, 1, Vector(1, 1, -1), Color(1, 0, 0));
    Vertex v5(0, 0, 0.5, 1, Vector(-1, -1, 1), Color(0, 1, 0));
    Vertex v6(0, 0.5, 0.5, 1, Vector(-1, 1, 1), Color(0, 1, 0));
    Vertex v7(0.5, 0, 0.5, 1, Vector(1, -1, 1), Color(0, 1, 0));
    Vertex v8(0.5, 0.5, 0.5, 1, Vector(1, 1, 1), Color(0, 1, 0));


    // 添加到绘图管理器
    
    drawingManager.vertices_.emplace_back(v1);
    drawingManager.vertices_.emplace_back(v1);
    drawingManager.vertices_.emplace_back(v2);
    drawingManager.vertices_.emplace_back(v3);
    drawingManager.vertices_.emplace_back(v4);
    drawingManager.vertices_.emplace_back(v5);
    drawingManager.vertices_.emplace_back(v6);
    drawingManager.vertices_.emplace_back(v7);
    drawingManager.vertices_.emplace_back(v8);

    drawingManager.triangles_.emplace_back(1, 2, 5);
    drawingManager.triangles_.emplace_back(1, 3, 2);
    drawingManager.triangles_.emplace_back(1, 5, 3);
    drawingManager.triangles_.emplace_back(3, 5, 7);
    drawingManager.triangles_.emplace_back(2, 6, 5);
    drawingManager.triangles_.emplace_back(2, 3, 4);
    drawingManager.triangles_.emplace_back(3, 7, 4);
    drawingManager.triangles_.emplace_back(2, 4, 6);
    drawingManager.triangles_.emplace_back(5, 6, 7);
    drawingManager.triangles_.emplace_back(4, 7, 8);
    drawingManager.triangles_.emplace_back(4, 8, 6);
    drawingManager.triangles_.emplace_back(6, 8, 7);

    drawingManager.setAmbientLight(Color(0.0f, 0.0f, 0.3f));
    drawingManager.setDirectionalLight(Vector(1, -1, -1).normalize(), Color(0.7f, 0.7f, 0.7f));


    // 初始化变换矩阵
    float worldMatrix[4][4], viewMatrix[4][4], projMatrix[4][4];
    Transformer::createIdentityMatrix(worldMatrix);
    Transformer::createViewMatrix(Vector(-5, 0, 0), Vector(1, 0, 0), Vector(0, 0, 1), viewMatrix);
    Transformer::createPerspectiveProjMatrix(3.1415926f / 4.0f, 800.0f / 600.0f, 0.1f, 100.0f, projMatrix);
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SOFTRENDER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SOFTRENDER));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        InvalidateRect(msg.hwnd, nullptr, FALSE);
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(msg.hwnd, &ps);

       Transformer::createRotationMatrix(x_rotate, y_rotate, worldMatrix);
       drawingManager.drawAll(hdc, worldMatrix, viewMatrix, projMatrix, 800, 600);
        // LineDrawer::drawLine(hdc, 100, 100, 300, 400, RGB(255, 0, 0));
        EndPaint(msg.hwnd, &ps);
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SOFTRENDER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SOFTRENDER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_UP:
            x_rotate++;
            OutputDebugString(_T("Up Arrow Pressed: x_rotate incremented\n"));
            InvalidateRect(hWnd, nullptr, TRUE);
            
            break;
        case VK_DOWN:
            x_rotate--;
            InvalidateRect(hWnd, nullptr, TRUE);
            break;
        case VK_LEFT:
            y_rotate++;
            InvalidateRect(hWnd, nullptr, TRUE);
            break;
        case VK_RIGHT:
            y_rotate--;
            InvalidateRect(hWnd, nullptr, TRUE);
            break;
        }
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
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
            // TODO: Add any drawing code that uses hdc here...
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

// Message handler for about box.
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
