# include "iGraphics.h"
# include "gl.h"
#include<math.h>

double x = 0, y =10 , r = 10;
double Pi=acos(-1);
double g=9.81/10;
double v;
double scr_width=1800,scr_height=800;
bool projectile=0;
double theta;
typedef struct {
    double x;
    double y;
    double vel_x;
    double vel_y;
    double acc_x;
    double acc_y;
}motion;

double obj_line_x;
double obj_line_y;

motion *ball;
double dx,dy;
double dt=1;
char str[100]="Press 's' here to throw the projectile.Press 'p' to pause and 'r' to resume.";
char str1[100]="Adjust your mouse line to set velocity and velocity angle accordingly.";

/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
    //place your drawing codes here
    iClear();
    iSetColor(20,200,255);
    iFilledCircle(x,y,r,1000);
    iSetColor(255,255,255);
    iLine(0,0,obj_line_x,obj_line_y);
    iText(700,700,str);
    iText(700,690,str1);
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here
    double m1,m2;
    m1=mx-20;
    m2=my-20;
    theta = atan(m2/m1)*180/Pi;
    obj_line_x=m1;
    obj_line_y=m2;
    v=sqrt(m1*m1+m2*m2)/10;
    dx=v*cos(theta*Pi/180);
    dy=v*sin(theta*Pi/180);
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    /*if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        //printf("x = %d, y= %d\n",mx,my);

    }
    else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        x -= 5;
        y -= 5;
    }
    */
    /*double m1,m2;
    m1=mx-20;
    m2=my-20;
    theta = atan(m2/m1)*180/Pi;
    obj_line_x=m1;
    obj_line_y=m2;
    dx=v*cos(theta*Pi/180);
    dy=v*sin(theta*Pi/180);
    */
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(key == 's')
    {
        projectile=1;
    }
    else if(key == 'p')
    {
        iPauseTimer(0);
    }
    else if(key == 'r')
    {
        iResumeTimer(0);
    }
    /*if(key == GLUT_KEY_UP)
    {
        y++;
    }
    else if(key== GLUT_KEY_DOWN)
    {
        y--;
    }
    else if(key== GLUT_KEY_RIGHT)
    {
        x++;
    }
    else if(key== GLUT_KEY_LEFT)
    {
        x--;
    }
    */
    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }
    //place your codes for other keys here
}

void change()
{
    if(projectile)
    {
        x=dx*dt;
        y=(dy*dt)-(0.5*g*dt*dt);
        dt+=0.5;
        if(y<0)
        {
            x=0;
            y=10;
            dt=1;
            projectile=0;
        }
    }
}

int main()
{
    //place your own initialization codes here.
    iSetTimer(10,change);
    iInitialize(scr_width, scr_height, "My main screen");


    return 0;
}
