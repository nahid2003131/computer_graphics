
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

int X1, Y1, X2, Y2;
bool printedOnce = false;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glPointSize(5.0f);

    int dx = X2 - X1;
    int dy = Y2 - Y1;

    int x = X1;
    int y = Y1;

    int p = 2 * dy - dx;

    bool doPrint = !printedOnce;
    if (doPrint) {
        cout << "\nBresenham Line Drawing (Basic)\n";
        cout << "x\t y\t p\n";
        cout << "-------------------\n";
        printedOnce = true;
    }

    glBegin(GL_POINTS);

    while (x <= X2) {
        glVertex2i(x, y);

        if (doPrint)
            cout << x << "\t " << y << "\t " << p << "\n";

        x++;

        if (p < 0) {
            p = p + 2 * dy;
        } else {
            y++;
            p = p + 2 * dy - 2 * dx;
        }
    }

    glEnd();
    glFlush();
}

void init() {
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 400, 0, 400);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    cout << "Enter first point (x y): ";
    cin >> X1 >> Y1;

    cout << "Enter second point (x y): ";
    cin >> X2 >> Y2;

    if (X2 < X1 || (Y2 - Y1) < 0 || (Y2 - Y1) > (X2 - X1)) {
        cout << "\nERROR:\n";
        cout << "Basic Bresenham works only for:\n";
        cout << "x2 > x1 and 0 <= slope <= 1\n";
        return 0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Basic Bresenham Algorithm");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
