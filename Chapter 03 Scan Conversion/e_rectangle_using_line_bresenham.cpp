
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

int ax,ay,bx,by,cx,cy,dx,dy;

// Easier sign function
int sgn(int v) {
    if (v > 0) return 1;
    if (v < 0) return -1;
    return 0;
}

void Bresenham_line(int X1, int Y1, int X2, int Y2){
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

    glBegin(GL_POINTS);

    if (dx >= dy) {
        // |slope| <= 1 : step in x
        int p = 2 * dy - dx;

        for (int i = 0; i <= dx; i++) {
            glVertex2i(x, y);
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
            y += sy;

            if (p < 0) {
                p += 2 * dx;
            } else {
                x += sx;
                p += 2 * dx - 2 * dy;
            }
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glPointSize(5.0f);
    //ab
    Bresenham_line(ax,ay,bx,by);
    //cd
    Bresenham_line(cx,cy,dx,dy);
    //ad
    Bresenham_line(ax,ay,dx,dy);
   //bc
    Bresenham_line(bx,by,cx,cy);

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
    
    //opposite corners (x1,y1) & (x2,y2)  (70,90) , (120,150)
   //bottom_right = (x2, y1)
   //top_left = (x1, y2);

    cout << "Enter Bottom-left corner point (x y): ";
    cin >> ax >> ay;

    cout << "Enter Top-right corner point (x y): ";
    cin >> cx >> cy;
    bx=cx;
    by=ay;
    dx=ax;
    dy=cy;
  
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(400, 400);
    glutCreateWindow("General Bresenham (All Slopes)");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
