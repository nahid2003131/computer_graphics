#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
  #include <GLUT/glut.h>
  #include <OpenGL/glu.h>
#else
  #include <GL/glut.h>
  #include <GL/glu.h>
#endif

#include <iostream>
#include <cmath>
using namespace std;

float X1, Y1, X2, Y2;

int rounded(float x) {
    return (x >= 0.0f) ? int(x + 0.5f) : int(x - 0.5f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(5.0f);

    float dx = X2 - X1;
    float dy = Y2 - Y1;

    float steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);

    glBegin(GL_POINTS);

    if (steps == 0.0f) {
        glVertex2i(rounded(X1), rounded(Y1));
        glEnd();
        glFlush();
        return;
    }

    float Xinc = dx / steps;
    float Yinc = dy / steps;

    float x = X1;
    float y = Y1;

    for (int i = 0; i <= (int)steps; i++) {
        glVertex2i(rounded(x), rounded(y));
        x += Xinc;
        y += Yinc;
    }

    glEnd();
    glFlush();
}

void resized(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Choose ONE coordinate system:
    gluOrtho2D(0, 400, 0, 400);     // window-like coords
    // gluOrtho2D(-200, 200, -200, 200); // centered coords

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    cout << "Please Enter first point (x y): ";
    cin >> X1 >> Y1;
    cout << "Please Enter second point (x y): ";
    cin >> X2 >> Y2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Line Drawing");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(resized);
    glutMainLoop();
    return 0;
}
