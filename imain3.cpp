# include "iGraphics.h"
# include "gl.h"
#include<math.h>

char homepage[100] = "homepage.bmp";
char buttons[2][100] = {"buttonProjectile.bmp", "buttonPendulum.bmp"};

char project_name[200] = "Projectile and Pendulum Simulator";
bool proj = false;
bool pendulum = false;
bool home = true;


double scr_width=1800,scr_height=800;


///variables needed for projectile.
double init_x=450,init_y=10;
double x=init_x, y=init_y, r = 20;
double red=0,green=0,blue=255;
double Pi=acos(-1);
double g=9.81/10;
double v;
bool projectile=0;
double theta;
typedef struct
{
    double x;
    double y;
    double vel;
    double vel_x;
    double vel_y;
    double acc_x;
    double acc_y;
} motion;

typedef struct
{
    double x;
    double y;
} coordinate;

motion *ball=(motion*)malloc(sizeof(motion));
coordinate motion_curve[100];


double object_origin_x;
double object_origin_y;
double obj_line_x;
double obj_line_y;


double mass=1;
double potential;
double kinetic;
double dx,dy;
double dt=1;
double dt_1=1;
char str[100]="Press 's' here to throw the projectile.Press 'p' to pause and 'r' to resume.";
char str1[100]="Adjust your mouse line to set velocity and velocity angle accordingly.";



///variables needed for pendulum

double starting_x = 20;
double starting_y = 10;
double g_pen = 9.81;
double angle = Pi/4;
bool startPendulum = false;
bool reset = false;
double effectiveLength = 400;
double ampAngle = Pi/4;
double timetracker = 0;

typedef struct BOB
{
    double x = 0;
    double y = 0;
    double mass = 1;
    double Amplitude = (effectiveLength)*sin(ampAngle);
    double freq = sqrt(g_pen/effectiveLength);
    double v = freq*sqrt((Amplitude*Amplitude) - (x*x));
    double acc = (-1)*freq*freq*(x);
    double k = (mass*g_pen)/effectiveLength;
    double period = (2*Pi)/freq;
} bob;

bob bob1;

/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
    if(home)
    {
        iClear();
        iShowBMP(0, 0, homepage);
        iShowBMP((scr_width/2 - 300), 100, buttons[0]);
        iShowBMP((scr_width/2 + 140), 100, buttons[1]);
    }

    else if(pendulum)
    {
        iClear();
        iSetColor(255, 255, 255);
        iLine((scr_width-200)/2, (scr_height-50), (scr_width+200)/2, (scr_height-50));
        iLine(scr_width/2, (scr_height-50), (scr_width/2) + bob1.x, (scr_height- 50 - effectiveLength + bob1.y));
        iSetColor(255, 255, 0);
        iLine(scr_width/2, (scr_height-50), scr_width/2, (scr_height-50 - effectiveLength));
        iSetColor(127, 127, 127);
        iFilledCircle((scr_width/2) + bob1.x, (scr_height- 50 - effectiveLength + bob1.y), 15, 1000);
        iSetColor(255, 0, 0);
        iLine((scr_width/2) + bob1.x, (scr_height- 50 - effectiveLength + bob1.y), (scr_width/2), (scr_height- 50 - effectiveLength + bob1.y));
        iSetColor(105, 105, 105);
        iFilledRectangle(50, (scr_height - 350), 200, 300);
    }

    else if(proj)
    {
        iClear();
        iSetColor(red,green,blue);
        iFilledCircle(x,y,r,1000);
        iSetColor(255,255,255);
        if(!projectile)
        {
            iLine(object_origin_x,object_origin_y,obj_line_x,obj_line_y);
            iText(500,700,str,GLUT_BITMAP_HELVETICA_18);
            iText(500,680,str1,GLUT_BITMAP_HELVETICA_18);
        }
        iSetColor(255,255,255);
        iRectangle(10,10,290,900);
        if(projectile)
        {
            iSetColor(255,255,0);
            iFilledRectangle(50,10,80,potential);
            iSetColor(255,0,0);
            iFilledRectangle(150,10,80,kinetic);
        }
    }
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here

    if(home)
    {
        if((my >= 50) && (my <= 130))
        {
            if((mx >= scr_width/2 - 300) && (mx <= scr_width/2 - 140))
            {
                printf("%f %f", mx, my);
                proj = true;
            }
            else if((mx >= scr_width/2 + 140) && (mx <= scr_width/2 + 300))
            {
                printf("%f %f", mx, my);
                pendulum = true;
            }
            home = false;
        }
    }

    else if(proj)
    {
        double m1,m2;
        m1=mx-20;
        m2=my-20;
        if(m1-init_x==0)
        {
            theta=Pi/2;
        }
        else
        {
            theta = atan((m2-init_y)/(m1-init_x));
        }
        obj_line_x=m1;
        obj_line_y=m2;
        object_origin_x=init_x;
        object_origin_y=init_y;
        v=sqrt((m1-init_x)*(m1-init_x)+(m2-init_y)*(m2-init_y))/10;
        dx=v*cos(theta);
        dy=v*sin(theta);
    }
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    /*
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
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
    if(home)
    {
        if(key == '1')
        {
            home = false;
            proj = true;
        }
        else if(key == '2')
        {
            home = false;
            pendulum = true;
        }
    }

    else if(proj)
    {
        if(key == 's')
        {
            projectile=1;

        }
        else if(key == 'p')
        {
            iPauseTimer(0);
            FILE *fp;
            fp=fopen("MOTION.txt","w");
            fprintf(fp,"Velocity of ball:%0.2lf\n",v);
            fprintf(fp,"Angle of projection:%0.2lf\n",theta*180/Pi);
            fprintf(fp,"The current horizontal position of the ball is    : %0.2lf\n",ball->x);
            fprintf(fp,"The current vertical position of the ball is      : %0.2lf\n",ball->y);
            fprintf(fp,"The current horizontal velocity of the ball is    : %0.2lf\n",ball->vel_x);
            fprintf(fp,"The current vertical velocity of the ball is      : %0.2lf\n",ball->vel_y);
            fprintf(fp,"The current horizontal acceleration of the ball is: %0.2lf\n",ball->acc_x);
            fprintf(fp,"The current vertical acceleration of the ball is  : %0.2lf\n",ball->acc_y);
            fprintf(fp,"The highest vertical distance of the ball is      : %0.2lf\n",v*v*sin(theta)*sin(theta)/2*g);
            fclose(fp);

        }
        else if(key == 'r')
        {
            iResumeTimer(0);

        }
    }

    else if(pendulum)
    {
        if(key == 's')
        {
            reset = true;
            startPendulum = false;
            bob1.x = bob1.Amplitude;
            bob1.y = effectiveLength*(1 - cos(ampAngle));
        }
        else if(key == ' ')
        {
            startPendulum = !startPendulum;

        }
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

    if(key == GLUT_KEY_HOME)
    {
        home = true;
        proj = false;
        pendulum = false;
    }

    else if(key == GLUT_KEY_END)
    {
        exit(0);
    }
    //place your codes for other keys here
}


void change()
{
    if(proj)
    {
        if(projectile)
        {
            if(theta>0)x+=dx;
            else x-=dx;
            if(theta!=Pi/2)y=((x-init_x)*tan(theta))-((g*(x-init_x)*(x-init_x))/(2*v*v*cos(theta)*cos(theta)))+init_y;
            else
            {
                y=(v*dt)-(0.5*g*dt*dt)+init_y;
                dt++;
            }
            ball->x=x;
            ball->y=y;
            ball->vel_x=v*cos(theta);
            ball->vel_y=abs(v*sin(theta))-(g*dt_1);
            ball->acc_x=0;
            ball->acc_y=-g;
            ball->vel=sqrt((ball->vel_x*ball->vel_x)+(ball->vel_y*ball->vel_y));
            potential=mass*g*y;
            kinetic=0.5*mass*ball->vel_y*ball->vel_y;
            dt_1++;
            if(y<0)
            {
                x=init_x;
                y=init_y;
                projectile=0;
                dt=1;
                dt_1=1;
            }
        }
    }

    else if(pendulum)
    {
        if(startPendulum)
        {
            bob1.x = bob1.Amplitude * cos((bob1.freq*timetracker));
            bob1.y = effectiveLength - sqrt((effectiveLength*effectiveLength) - (bob1.x*bob1.x));
            timetracker += 1;
        }
        else if(reset)
        {
            timetracker = 0;
            reset = !reset;
        }
    }
}

/*

void change_projectile()
{
    if(projectile)
    {
        if(theta>0)x+=dx;
        else x-=dx;
        if(theta!=Pi/2)y=((x-init_x)*tan(theta))-((g*(x-init_x)*(x-init_x))/(2*v*v*cos(theta)*cos(theta)))+init_y;
        else
        {
            y=(v*dt)-(0.5*g*dt*dt)+init_y;
            dt++;
        }
        ball->x=x;
        ball->y=y;
        ball->vel_x=v*cos(theta);
        ball->vel_y=v*sin(theta)-(g*dt_1);
        ball->acc_x=0;
        ball->acc_y=-g;
        ball->vel=sqrt((ball->vel_x*ball->vel_x)+(ball->vel_y*ball->vel_y));
        potential=mass*g*y;
        kinetic=0.5*g*ball->vel_y*ball->vel_y;
        dt_1++;
        if(y<0)
        {
            x=init_x;
            y=init_y;
            projectile=0;
            dt=1;
            dt_1=1;
        }
    }

}

void change_pendulum()
{

    if(startPendulum)
    {
        bob1.x = bob1.Amplitude * cos((bob1.freq*timetracker));
        bob1.y = effectiveLength - sqrt((effectiveLength*effectiveLength) - (bob1.x*bob1.x));
        timetracker += 1;
    }
    else if(reset)
    {
        timetracker = 0;
        reset = !reset;
    }



}
*/

int main()
{
    //place your own initialization codes here.

/*

    if(pendulum)
    {
        iSetTimer(50, change_pendulum);
        //iInitialize(screen_width, screen_height, "Pendulum Simulator");
    }

    else if(proj)
    {
        iSetTimer(10, change_projectile);
        //iInitialize(scr_width, scr_height, "My main screen");
    }

*/
    iSetTimer(25, change);
    iInitialize(scr_width, scr_height, project_name);


    return 0;
}
