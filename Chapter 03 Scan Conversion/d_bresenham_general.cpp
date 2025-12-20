#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
  #include <GLUT/glut.h>
  #include <OpenGL/glu.h>
#else
  #include <GL/glut.h>
  #include <GL/glu.h>
#endif

#include <iostream>
#include <cstdlib>  
using namespace std;

int X1, Y1, X2, Y2;
bool printedOnce = false;

// Easier sign function
int sgn(int v) {
    if (v > 0) return 1;
    if (v < 0) return -1;
    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glPointSize(5.0f);

    //calculate differences
    int dx0 = X2 - X1;
    int dy0 = Y2 - Y1;

    //decide direction using sgn()
    int sx = sgn(dx0);   // decides left (+1) or right (-1)
    int sy = sgn(dy0);   // decides up (+1) or down (-1

    int dx = abs(dx0);
    int dy = abs(dy0);

    int x = X1;
    int y = Y1;

    bool doPrint = !printedOnce;
    if (doPrint) {
        cout << "\nGeneral Bresenham Line Drawing (All Slopes)\n";
        cout << "x\t y\t p\n";
        cout << "-------------------\n";
        printedOnce = true;
    }

    glBegin(GL_POINTS);

    if (dx >= dy) {
        // |slope| <= 1 : step in x
        int p = 2 * dy - dx;

        for (int i = 0; i <= dx; i++) {
            glVertex2i(x, y);
            if (doPrint) cout << x << "\t " << y << "\t " << p << "\n";

            x += sx;

            if (p < 0) {
                p += 2 * dy;
            } else {
                y += sy;
                p += 2 * dy - 2 * dx;
            }
        }
    } else {
        // |slope| > 1 : step in y
        int p = 2 * dx - dy;

        for (int i = 0; i <= dy; i++) {
            glVertex2i(x, y);
            if (doPrint) cout << x << "\t " << y << "\t " << p << "\n";

            y += sy;

            if (p < 0) {
                p += 2 * dx;
            } else {
                x += sx;
                p += 2 * dx - 2 * dy;
            }
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

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(400, 400);
    glutCreateWindow("General Bresenham (All Slopes)");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
