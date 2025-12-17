#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
  #include <GLUT/glut.h>
  #include <OpenGL/glu.h>
#else
  #include <GL/glut.h>
  #include <GL/glu.h>
#endif
#include <iostream>
using namespace std;

float X1, Y1, X2, Y2;

int rounded(float x) {
    return (x >= 0.0f) ? int(x + 0.5f) : int(x - 0.5f);
}

void point_conversion(float p, float q) {
    glBegin(GL_POINTS);
        glVertex2i(rounded(p), rounded(q));
    glEnd();
}

// y = m*x + c
float y_from_x(float x, float m, float c) { return m * x + c; }
// x = (y - c)/m
float x_from_y(float y, float m, float c) { return (y - c) / m; }

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(7.0f);

    // vertical line
    if (X2 == X1) {
        float ys = (Y1 < Y2) ? Y1 : Y2;
        float ye = (Y1 > Y2) ? Y1 : Y2;
        for (float y = ys; y <= ye; y += 1.0f) point_conversion(X1, y);
        glFlush();
        return;
    }

    float m = (Y2 - Y1) / (X2 - X1);
    float c = Y1 - m * X1;
    float abs_m = (m >= 0.0f) ? m : -m;

    if (abs_m <= 1.0f) {
        float xs = (X1 < X2) ? X1 : X2;
        float xe = (X1 > X2) ? X1 : X2;
        for (float x = xs; x <= xe; x += 1.0f)
            point_conversion(x, y_from_x(x, m, c));
    } else {
        float ys = (Y1 < Y2) ? Y1 : Y2;
        float ye = (Y1 > Y2) ? Y1 : Y2;
        for (float y = ys; y <= ye; y += 1.0f)
            point_conversion(x_from_y(y, m, c), y);
    }

    glFlush();
}

void resized(int w, int h) {
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

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
    glutCreateWindow("Point Scan Conversion");

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glutDisplayFunc(display);
    glutReshapeFunc(resized);

    glutMainLoop();
    return 0;
}
