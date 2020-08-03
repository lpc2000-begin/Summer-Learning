# Summer-Learning
#include <gl/glut.h>

float step = 0.08f; //旋转速度

void Display()  //显示一个三角形旋转
{
    //设置图形旋转
    while(1){
        glRotatef(step,0.0f,0.0f,1.0f); //设置旋转每次在上一个的基础上逆时针旋转step角度

        //绘图
        glClear(GL_COLOR_BUFFER_BIT);   //清空颜色缓冲
        glBegin(GL_TRIANGLES);  //图元是三角形
            glColor3f(1,0,0);   //设置画笔颜色为 红色
            glVertex2f(0,0.8);  
            glColor3f(0,1,0);   //设置画笔颜色为 绿色
            glVertex2f(0.75,-0.5);
            glColor3f(0,0,1);   //设置画笔颜色为 蓝色
            glVertex2f(-0.75,-0.5);
        glEnd();

        //step+=0.00001f;   //旋转速度递增

        glFlush();  //清空并执行缓冲区指令
    }
}
