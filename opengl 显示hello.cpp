#include <windows.h>
#include <gl/glut.h>
#define MAX_CHAR    128// ASCII字符总共只有0到127，一共128种字符
GLuint TextFont;

void XPrintString(char *s)
{
    glPushAttrib (GL_LIST_BIT);

    //调用每个字符对应的显示列表，绘制每个字符
    for(; *s!='\0'; ++s)
        glCallList(TextFont + *s);

    glPopAttrib ();    
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    glRasterPos3f(0.5, 0.5, 0.0);
    XPrintString("hello!");

    glFlush();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    //申请MAX_CHAR个连续的显示列表编号
    TextFont = glGenLists(MAX_CHAR);
        
    //把每个字符的绘制命令都装到对应的显示列表中
    wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, TextFont);  
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello ");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
