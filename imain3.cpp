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
double v=0;
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

bool before_first_throw=0;

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
bool startPendulum = false;
bool reset = false;
double effectiveLength = 400;
double ampAngle = Pi/10;
double timetracker = 0;
char inst1[500] = "Press 's' to set the pendulum at the starting position.";
char inst2[500] = "Press 'Space' to start or pause the simulation.";
char return_to_home[500] = "Press 'Home' to return to Homepage.";
double timedef = 0.5;

typedef struct BOB
{
    double radius = 15;
    double x = 0;
    double y = 0;
    double mass = 1;
    double Amplitude = (effectiveLength)*sin(ampAngle);
    double freq = sqrt(g_pen/effectiveLength);
    double v = 0;
    double acc = 0;
    double k = (mass*g_pen)/effectiveLength;
    double period = (2*Pi)/freq;
    double kineticEnergy = 0;
    double potentialEnergy = 0;
    double totalEnergy = 0;
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
        iText(70, 150, inst1, GLUT_BITMAP_HELVETICA_18);
        iText(70, 120, inst2, GLUT_BITMAP_HELVETICA_18);
        iText(70, 90, return_to_home, GLUT_BITMAP_HELVETICA_18);
        iLine((scr_width-200)/2, (scr_height-50), (scr_width+200)/2, (scr_height-50));
        iLine(scr_width/2, (scr_height-50), (scr_width/2) + bob1.x, (scr_height- 50 - effectiveLength + bob1.y));
        iSetColor(255, 255, 0);
        iLine(scr_width/2, (scr_height-50), scr_width/2, (scr_height-50 - effectiveLength));
        iSetColor(127, 127, 127);
        iFilledCircle((scr_width/2) + bob1.x, (scr_height- 50 - effectiveLength + bob1.y), bob1.radius, 1000);
        iSetColor(255, 0, 0);
        iLine((scr_width/2) + bob1.x, (scr_height- 50 - effectiveLength + bob1.y), (scr_width/2), (scr_height- 50 - effectiveLength + bob1.y));
        iRectangle(50, (scr_height - 350), 550, 320);
        iRectangle((scr_width-600), (scr_height - 380), 550, 350);

        ///showing information here

        iSetColor(255, 255, 255);
        char periodInfo[1000] = "Time Period (in seconds) : ";
        char t_string[200];
        snprintf(t_string, 200, "%0.4lf", bob1.period/10);
        strcat(periodInfo, t_string);
        iText(60, (scr_height - 70), periodInfo, GLUT_BITMAP_HELVETICA_18);
        char sp_cn_Info[1000] = "Spring Constant (in N/m) : ";
        char sp_cn_string[200];
        snprintf(sp_cn_string, 200, "%0.4lf", bob1.k*100);
        strcat(sp_cn_Info, sp_cn_string);
        iText(60, (scr_height - 100), sp_cn_Info, GLUT_BITMAP_HELVETICA_18);
        char displacementInfo[1000] = "Current displacement (in meters) : ";
        char x_string[200];
        snprintf(x_string, 200, "%0.4lf", bob1.x/100);
        strcat(displacementInfo, x_string);
        iText(60, (scr_height - 130), displacementInfo, GLUT_BITMAP_HELVETICA_18);
        char velocityInfo[1000] = "Current velocity (in m/s) : ";
        char v_string[200];
        snprintf(v_string, 200, "%0.4lf", bob1.v/10);
        strcat(velocityInfo, v_string);
        iText(60, (scr_height - 160), velocityInfo, GLUT_BITMAP_HELVETICA_18);
        char accInfo[1000] = "Current acceleration (in m/s*s) : ";
        char a_string[200];
        snprintf(a_string, 200, "%0.4lf", bob1.acc);
        strcat(accInfo, a_string);
        iText(60, (scr_height - 190), accInfo, GLUT_BITMAP_HELVETICA_18);
        char KEInfo[1000] = "Current Kinetic Energy (in Joules) : ";
        char ke_string[200];
        snprintf(ke_string, 200, "%0.4lf", bob1.kineticEnergy);
        strcat(KEInfo, ke_string);
        iText(60, (scr_height - 220), KEInfo, GLUT_BITMAP_HELVETICA_18);
        char PEInfo[1000] = "Current Potential Energy (in Joules) : ";
        char pe_string[200];
        snprintf(pe_string, 200, "%0.4lf", bob1.potentialEnergy);
        strcat(PEInfo, pe_string);
        iText(60, (scr_height - 250), PEInfo, GLUT_BITMAP_HELVETICA_18);
        char TEInfo[1000] = "Current Total Energy (in Joules) : ";
        char te_string[200];
        snprintf(te_string, 200, "%0.4lf", bob1.totalEnergy);
        strcat(TEInfo, te_string);
        iText(60, (scr_height - 280), TEInfo, GLUT_BITMAP_HELVETICA_18);

        char efflen[1000] = "Current Effective Length (in meters) : ";
        char efflenval[200];
        snprintf(efflenval, 200, "%0.2lf", effectiveLength/100);
        strcat(efflen, efflenval);
        iText((scr_width-590), (scr_height - 70), efflen, GLUT_BITMAP_HELVETICA_18);

        iSetColor(255, 255, 0);
        iFilledCircle((scr_width-590), (scr_height - 91), 5, 1000);
        iFilledCircle((scr_width-590), (scr_height - 151), 5, 1000);
        iText((scr_width-580), (scr_height - 100), "Press '+' to increase effective length", GLUT_BITMAP_HELVETICA_18);
        iText((scr_width-580), (scr_height - 130), "by 0.1 meter.", GLUT_BITMAP_HELVETICA_18);
        iText((scr_width-580), (scr_height - 160), "Press '-' to decrease effective length", GLUT_BITMAP_HELVETICA_18);
        iText((scr_width-580), (scr_height - 190), "by 0.1 meter.", GLUT_BITMAP_HELVETICA_18);

        iSetColor(255, 255, 255);

        char massie[1000] = "Current Mass of bob (in kilograms) : ";
        char massieval[200];
        snprintf(massieval, 200, "%0.2lf", bob1.mass);
        strcat(massie, massieval);
        iText((scr_width-590), (scr_height - 230), massie, GLUT_BITMAP_HELVETICA_18);

        iSetColor(255, 255, 0);
        iFilledCircle((scr_width-590), (scr_height - 251), 5, 1000);
        iFilledCircle((scr_width-590), (scr_height - 281), 5, 1000);
        iText((scr_width-580), (scr_height - 260), "Press '*' to increase mass of bob by 0.1 kg.", GLUT_BITMAP_HELVETICA_18);
        iText((scr_width-580), (scr_height - 290), "Press '/' to decrease mass of bob by 0.1 kg.", GLUT_BITMAP_HELVETICA_18);

        iFilledCircle((scr_width-590), (scr_height - 321), 5, 1000);
        iFilledCircle((scr_width-590), (scr_height - 351), 5, 1000);
        iText((scr_width-580), (scr_height - 330), "Press 'UP' to speed up the simulation.", GLUT_BITMAP_HELVETICA_18);
        iText((scr_width-580), (scr_height - 360), "Press 'DOWN' to slow down the simulation.", GLUT_BITMAP_HELVETICA_18);

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
            iText(500,660,return_to_home,GLUT_BITMAP_HELVETICA_18);
        }
        iSetColor(255,255,255);
        iRectangle(10,100,290,670);
        if(projectile)
        {
            iSetColor(255,255,0);
            iFilledRectangle(30,100,80,potential);
            iSetColor(255,0,0);
            iFilledRectangle(180,100,80,kinetic);
        }
        iSetColor(255,0,0);
        iRectangle(1360,520,scr_width-1380,250);
        char str_poten[100]="POTENTIAL";
        char str_kinetic[100]="KINETIC";
        iSetColor(255,255,255);
        iText(5,80,str_poten,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(180,80,str_kinetic,GLUT_BITMAP_TIMES_ROMAN_24);
        ///showing motion infos here.

        iSetColor(255,255,255);
        char x_pos_info[100]="X Coordinate is: ";
        char x_pos[100];
        snprintf(x_pos,100,"%0.2lf",ball->x);
        strcat(x_pos_info,x_pos);
        iText(1370,750,x_pos_info,GLUT_BITMAP_HELVETICA_18);
        char y_pos_info[100]="Y Coordinate is: ";
        char y_pos[100];
        snprintf(y_pos,100,"%0.2lf",ball->y);
        strcat(y_pos_info,y_pos);
        iText(1370,730,y_pos_info,GLUT_BITMAP_HELVETICA_18);
        char vel_x_info[100]="Velocity along x-axis is: ";
        char vel_x[100];
        snprintf(vel_x,100,"%0.2lf",ball->vel_x);
        strcat(vel_x_info,vel_x);
        if(!before_first_throw) iText(1370,710,"Velocity along x-axis is: 0.00",GLUT_BITMAP_HELVETICA_18);
        else iText(1370,710,vel_x_info,GLUT_BITMAP_HELVETICA_18);
        char vel_y_info[100]="Velocity along y-axis is: ";
        char vel_y[100];
        snprintf(vel_y,100,"%0.2lf",ball->vel_y);
        strcat(vel_y_info,vel_y);
        if(!before_first_throw) iText(1370,690,"Velocity along y-axis is: 0.00",GLUT_BITMAP_HELVETICA_18);
        else iText(1370,690,vel_y_info,GLUT_BITMAP_HELVETICA_18);
        char potential_info[100]="The potential energy is:";
        char potential_current[100];
        snprintf(potential_current,100,"%0.2lf",potential);
        strcat(potential_info,potential_current);
        iText(1370,670,potential_info,GLUT_BITMAP_HELVETICA_18);
        char kinetic_info[100]="The kinetic energy is:";
        char kinetic_current[100];
        snprintf(kinetic_current,100,"%0.2lf",kinetic);
        strcat(kinetic_info,kinetic_current);
        iText(1370,650,kinetic_info,GLUT_BITMAP_HELVETICA_18);
        char acceleration_info_x[100]="The acc. along x-axis is:0";
        iText(1370,630,acceleration_info_x,GLUT_BITMAP_HELVETICA_18);
        char acceleration_info_y[100]="The acc. along y-axis is: 0.981";
        iText(1370,610,acceleration_info_y,GLUT_BITMAP_HELVETICA_18);
        char theta_info[100]="The angle of projection is: ";
        char theta_ball[100];
        snprintf(theta_ball,100,"%0.2lf",theta*180/Pi);
        strcat(theta_info,theta_ball);
        iText(1370,590,theta_info,GLUT_BITMAP_HELVETICA_18);
        char maximum_horizon_info[100]="The maximum horizontal distance:";
        char maximum_horizon[100];
        snprintf(maximum_horizon,100,"%0.2lf",v*v*sin(2*theta)/g);
        strcat(maximum_horizon_info,maximum_horizon);
        iText(1370,570,maximum_horizon_info,GLUT_BITMAP_HELVETICA_18);
        char maximum_vertical_info[100]="The maximum vertical distance:";
        char maximum_vertical[100];
        snprintf(maximum_vertical,100,"%0.2lf",v*v*sin(theta)*sin(theta)/2*g);
        strcat(maximum_vertical_info,maximum_vertical);
        iText(1370,550,maximum_vertical_info,GLUT_BITMAP_HELVETICA_18);
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
            before_first_throw=1;
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
            bob1.v = bob1.freq*sqrt((bob1.Amplitude*bob1.Amplitude) - (bob1.x*bob1.x));
            bob1.acc = (-1)*bob1.freq*bob1.freq*(bob1.x);
            bob1.kineticEnergy = 0.5*bob1.mass*bob1.v*bob1.v;
            bob1.potentialEnergy = 0.5*bob1.k*bob1.x*bob1.x;
            bob1.totalEnergy = bob1.kineticEnergy + bob1.potentialEnergy;
        }
        else if(key == ' ')
        {
            startPendulum = !startPendulum;

        }
        else if(key == '+' && effectiveLength < 700)
        {
            effectiveLength += 10;
        }
        else if(key == '-' && effectiveLength > 100)
        {
            effectiveLength -= 10;
        }
        else if(key == '*' && bob1.mass < 4.9)
        {
            bob1.mass += 0.1;
            bob1.radius = 15*bob1.mass;
        }
        else if(key == '/' && bob1.mass > 0.2)
        {
            bob1.mass -= 0.1;
            bob1.radius = 15*bob1.mass;
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

    else if(key == GLUT_KEY_UP)
    {
        if(pendulum && timedef < 1)
        {
            timedef += 0.05;
        }
    }
    else if(key == GLUT_KEY_DOWN)
    {
        if(pendulum && timedef > 0.1)
        {
            timedef -= 0.05;
        }
    }
    //place your codes for other keys here
}


void change()
{
    if(proj)
    {
        if(projectile)
        {
            ball->x=x;
            ball->y=y;
            ball->vel_x=v*cos(theta);
            ball->vel_y=abs(v*sin(theta))-(g*dt_1);
            ball->acc_x=0;
            ball->acc_y=-g;
            ball->vel=sqrt((ball->vel_x*ball->vel_x)+(ball->vel_y*ball->vel_y));
            potential=mass*g*y/2;
            kinetic=0.5*mass*ball->vel*ball->vel/2;
            if(theta>0)x+=dx;
            else x-=dx;
            if(theta!=Pi/2)y=((x-init_x)*tan(theta))-((g*(x-init_x)*(x-init_x))/(2*v*v*cos(theta)*cos(theta)))+init_y;
            else
            {
                y=(v*dt)-(0.5*g*dt*dt)+init_y;
                dt++;
            }
            dt_1++;
            if(y<0)
            {
                x=init_x;
                y=init_y;
                projectile=0;
                dt=1;
                dt_1=1;
                ball->x=x;
                ball->y=y;
                ball->vel_x=0;
                ball->vel_y=0;
                ball->acc_x=0;
                ball->acc_y=-g;
                ball->vel=sqrt((ball->vel_x*ball->vel_x)+(ball->vel_y*ball->vel_y));
                potential=0;
                kinetic=0;
            }
        }
    }

    else if(pendulum)
    {
        if(startPendulum)
        {
            bob1.x = bob1.Amplitude * cos((bob1.freq*timetracker));
            bob1.y = effectiveLength - sqrt((effectiveLength*effectiveLength) - (bob1.x*bob1.x));
            bob1.v = (-1)*bob1.freq * bob1.Amplitude * sin((bob1.freq*timetracker));
            bob1.acc = (-1)*bob1.freq*bob1.freq*(bob1.x);
            bob1.kineticEnergy = (0.5*bob1.mass*bob1.v*bob1.v)/100;
            bob1.potentialEnergy = (0.5*bob1.k*bob1.x*bob1.x)/100;
            bob1.totalEnergy = bob1.kineticEnergy + bob1.potentialEnergy;
            bob1.Amplitude = (effectiveLength)*sin(ampAngle);
            bob1.freq = sqrt(g_pen/effectiveLength);
            bob1.k = (bob1.mass*g_pen)/effectiveLength;
            bob1.period = (2*Pi)/bob1.freq;

            timetracker += timedef;
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
