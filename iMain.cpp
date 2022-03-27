# include "iGraphics.h"
# include "gl.h"

int screen_width = 1000;
int screen_height = 640;

//variables needed for pendulum
double starting_x = 20;
double starting_y = 10;
double Pi = 3.1416;
double g = 9.81;
double v = 20;
double angle = Pi/4;
double H = (v*v)/(2*g);

int r = 15;

double x = 20, y = 10;

//variables needed for pendulum
bool pendulum = true;
bool startPendulum = false;
bool reset = false;
double effectiveLength = 100;
double ampAngle = Pi/4;
double timetracker = 0;

typedef struct BOB
{
    double x = 0;
    double y = 0;
    double mass = 1;
    double Amplitude = (effectiveLength)*sin(ampAngle);
    double freq = sqrt(g/effectiveLength);
    double v = freq*sqrt((Amplitude*Amplitude) - (x*x));
    double acc = (-1)*freq*freq*(x);
    double k = (mass*g)/effectiveLength;
    double period = (2*Pi)/freq;
} bob;

bob bob1;

/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
    //place your drawing codes here
    iClear();

    if(pendulum)
    {
        iSetColor(255, 255, 255);
        iLine((screen_width-200)/2, (screen_height-50), (screen_width+200)/2, (screen_height-50));
        iLine(screen_width/2, (screen_height-50), (screen_width/2) + bob1.x, (screen_height- 50 - effectiveLength + bob1.y));
        iSetColor(255, 255, 0);
        iLine(screen_width/2, (screen_height-50), screen_width/2, (screen_height-50 - effectiveLength));
        iSetColor(127, 127, 127);
        iFilledCircle((screen_width/2) + bob1.x, (screen_height- 50 - effectiveLength + bob1.y), 15, 1000);
    }

    else
    {
        iSetColor(20,200,255);
        iFilledCircle(x, y, r);
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

}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    //if(mx==x) x+=mx;
    //else if(my==y) y+=my;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        //printf("x = %d, y= %d\n",mx,my);

    }
    else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        //x -= 5;
        //y -= 5;
    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(key == 's')
    {
        reset = true;
        bob1.x = bob1.Amplitude;
        bob1.y = effectiveLength*(1 - cos(ampAngle));
    }
    else if(key == ' ')
    {
        startPendulum = !startPendulum;
        /*
        if(!startPendulum)
        {
            bob1.x = bob1.Amplitude;
            bob1.y = effectiveLength*(1 - cos(ampAngle));
            startPendulum = true;
        }
        else
        {
            startPendulum = false;
        }
        */

    }
    else if(key == GLUT_KEY_UP)
    {
        //y++;
    }
    else if(key== GLUT_KEY_DOWN)
    {
        //y--;
    }
    else if(key== GLUT_KEY_RIGHT)
    {
        //x++;
    }
    else if(key== GLUT_KEY_LEFT)
    {
        //x--;
    }
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
    if(pendulum)
    {
        if(startPendulum)
        {
            bob1.x = bob1.Amplitude * cos((bob1.freq*timetracker));
            bob1.y = effectiveLength - sqrt((effectiveLength*effectiveLength) - (bob1.x*bob1.x));
            timetracker += 1;
        }
        if(reset)
        {
            timetracker = 0;
            reset = !reset;
        }

    }
}

int main()
{
    //place your own initialization codes here.
    printf("%f", bob1.period);
    iSetTimer(50, change);
    iInitialize(screen_width, screen_height, "Demo!");

    return 0;
}

