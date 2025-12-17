#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int round(float x)
{
    return (x >= 0.0f) ? int(x + 0.5f) : int(x - 0.5f);
}

void point_conversion(float x , float y)
{
    int a , b ;
     
    //rounding
    a = round(x);
    b = round(y);

    /* Scan convert a point */
    glBegin(GL_POINTS);
        glVertex2i(a, b);   // Point at (x, y)
    glEnd();
   
}

/* Display callback */
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); //buffer shape--> windowsize 

    /* Set point color (Red) */
    glColor3f(1.0f, 0.0f, 0.0f);

    /* Set point size */
    glPointSize(15.0f);
   
    /* Scan convert a point */
    point_conversion(3.5,4.5);

    glFlush();
}

/* Window resize */
void resized(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);   // 2D coordinate system
    glMatrixMode(GL_MODELVIEW);
}

/* Main function */
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // hardware resources allocation check
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); //one parameter via OR; 16var
    glutInitWindowSize(400, 400); // WxH
    glutInitWindowPosition(100, 100); // X-> Y!
    glutCreateWindow("Point Scan Conversion");

    glClearColor(1.0, 1.0, 1.0, 1.0); // White background for clearing
                //(r,g,b,opacity)


    glutDisplayFunc(display); // used for rendering glutDisplayFunc(function)
    glutReshapeFunc(resized); //called while resizing

    glutMainLoop(); // used for making window live . it does not run functions of main every time
    return 0;
}
