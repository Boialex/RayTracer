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

Scene scene;

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    scene.paint();
    glutSwapBuffers();
    glutPostRedisplay();
    glFlush();
}

int main(int argc, char **argv)
{
    std::string s;
    //std::cout << "File name: ";
    //std::cin >> s;
    int widht = 1600;
    int height = 1200;
    //std::cin >> widht >> height;
    Reader * reader = new Reader("spheres_pure.rt");
    std::ios::sync_with_stdio(false);
    reader->read(scene);
    delete reader;

    scene.render(widht, height);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);	
    glutInitWindowSize(widht, height);
    glutCreateWindow("Ray Tracing");		
    Initialize();						
    glutDisplayFunc(Draw);				
    glutMainLoop();

    return 0;
}    