#include "stdafx.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <windows.h>
#include <glut.h>  

void Initialize()
{
    glClearColor(0, 0, 0, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    /*
    glColor3f(1.0, 1.0, 1.0); 
    glBegin(GL_POLYGON);
    glVertex3f(0.05, 0.05, 0.0); 
    glVertex3f(0.95, 0.05, 0.0);
    glVertex3f(0.95, 0.95, 0.0);
    glVertex3f(0.05, 0.95, 0.0);
    glEnd();
    
    glBegin(GL_POINTS);
    for (int i = 0; i < 10; ++i) {
        glColor3f(0.0, 1.0, 0.0);
        //glVertex3f(0.25 + 1. * i / 100, 0.5, 0.0);
    }
    glEnd();
    */
    //glFlush()
    Scene scene;
    scene.input();
    scene.paint();
    glFlush();
}

//Войти в главный цикл
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);	//Позиция окна
    glutInitWindowSize(500, 500);
    glutCreateWindow("Ray Tracing");		//Имя окна
    Initialize();						//Вызов функции Initialize
    glutDisplayFunc(Draw);				//Вызов функции отрисовки
    glutMainLoop();

    return 0;
}
/*
#include <windowsx.h>

#define RED RGB(255,0,0)
#define GRN RGB(0,255,0)
#define BLU RGB(0,0,255)

#define BLK RGB(0,0,0)
#define WHT RGB(255,255,255)

HPEN  getPen(int iPEN_STYLE, int iPEN_SIZE, int iCOLORREF);
COORD setCordScale(COORD POS, RECT pRECT);

int main()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.25, 0.25, 0.0);
    glVertex3f(0.75, 0.25, 0.0);
    glVertex3f(0.75, 0.75, 0.0);
    glVertex3f(0.25, 0.75, 0.0);
    glEnd();
    glFlush();

    HWND hWnd = GetForegroundWindow();
    HPEN    RPEN = getPen(PS_SOLID, 2, RED);
    HPEN    GPEN = getPen(PS_SOLID, 2, GRN);
    HPEN    BPEN = getPen(PS_SOLID, 2, BLU);
    HPEN    WPEN = getPen(PS_SOLID, 3, WHT);
    RECT    pRECT = { 0 };
    COORD   POS = { 0 };
    COORD   BGN = setCordScale(POS, pRECT);
    GetWindowRect(hWnd, &pRECT);
    HDC hDC = GetWindowDC(hWnd);
    SetPixel(hDC, 50, 50, RED);
    /*
    if (hDC)
    {
        SetBkMode(hDC, TRANSPARENT);
        SetPoint(hDC, WPEN, BGN);
        POS.X = BGN.X + 50;
        POS.Y = BGN.Y + 100;

        PlotRect(hDC, BPEN, BGN, POS);
        PlotLine(hDC, RPEN, BGN, POS);
        SetPoint(hDC, WPEN, BGN);

        BGN = POS;
        POS.X = BGN.X + 100;
        POS.Y = BGN.Y + 100;
        PlotCirc(hDC, GPEN, BGN, POS);
        
    }
    
    Scene a;
    a.input();
    a.paint(hDC);
    system("pause");
    
    return 0;
}

HPEN getPen(int iPEN_STYLE, int iPEN_SIZE, int iCOLORREF)
{
    return CreatePen(iPEN_STYLE, iPEN_SIZE, iCOLORREF);
}

COORD setCordScale(COORD POS, RECT pRECT)
{
    if (POS.X == 0)
        POS.X = 1;
    if (POS.Y == 0)
        POS.Y = 1;

    int nROWS = 25;
    int nCOLS = 80;

    double CX = (pRECT.right - pRECT.left) / nCOLS;
    double CY = (pRECT.bottom - pRECT.top) / nROWS;

    POS.X *= CX;
    POS.Y *= CY;

    int xBORDER = GetSystemMetrics(SM_CXBORDER);
    int yBORDER = GetSystemMetrics(SM_CYMENU);  
    int xDRAG = GetSystemMetrics(SM_CXDRAG);  
    int yDRAG = GetSystemMetrics(SM_CYDRAG);  

    POS.X += xBORDER + xDRAG;
    POS.Y += yBORDER + yDRAG;
    return POS;
}      */      