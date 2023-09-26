#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#define SPEED 30.0

int radius=0;
static int submenu;
static int mainmenu;
static int value = -1;
static int day = 1, night = 0, car=0;
int cloudX = 0; 
GLint carpos1 = -500, carpos2 = 500, carpos3 = 500, carpos4 = -500;
GLint carposY = -1000;
GLfloat carScale = 1.5f;
static int red = 0, green = 0;
bool isMoving = false;

void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(0.0,0.0,1.0);
	glPointSize(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
        gluOrtho2D(-1000, 1000, -1000, 1000);
}

void drawhead(float x, float y, float z, char *string)
{
    glColor3f(1, 1, 1);
    glRasterPos3f(x, y, z);

    for (char *c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}

void drawsubhead(float x, float y, float z, char *string)
{
    glColor3f(1, 1, 1);
    glRasterPos3f(x, y, z);

    for (char *c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}

void draw_pixel(GLfloat xc, GLfloat yc)
{
        glPointSize(9.0);
        glBegin(GL_POINTS);
                glVertex2f(xc,yc);
        glEnd();
}

void plotpixels(GLint Xplot ,GLint Yplot, GLint x,GLint y)
{
        draw_pixel(x+Xplot,y+Yplot);     // Q1
        draw_pixel(-x+Xplot,y+Yplot);    // Q2
        draw_pixel(x+Xplot,-y+Yplot);    // Q4
        draw_pixel(-x+Xplot,-y+Yplot);   // Q3

        draw_pixel(y+Xplot,x+Yplot);     // Q1
        draw_pixel(-y+Xplot,x+Yplot);    // Q2
        draw_pixel(y+Xplot,-x+Yplot);    // Q4
        draw_pixel(-y+Xplot,-x+Yplot);   // Q3
}

void draw_circle(GLint Xplot, GLint Yplot, GLint r)
{
        GLint Pk=1-r, x=0, y=r;
        while(y>x)
        {
                plotpixels(Xplot,Yplot,x,y);
                if(Pk < 0)
                        Pk += 2*x+3;
                else
                {
                        Pk += 2*(x-y)+5;
                        --y;
                }
                ++x;
        }
        plotpixels(Xplot,Yplot,x,y);
}

void drawCloud(int x1, int x2, int x3, int x4, int y)
{
	
        for(radius=0;radius<=50;radius++)
        {
                draw_circle(x1+cloudX,y,radius);
        }
        for(radius=0;radius<=90;radius++)
        {
                draw_circle(x2+cloudX,y,radius);
        }
        for(radius=0;radius<=75;radius++)
        {
                draw_circle(x3+cloudX,y,radius);
        }
        for(radius=0;radius<=45;radius++)
        {
                draw_circle(x4+cloudX,y,radius);
        } 
}

void drawLeaves(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5)
{
        for(radius=0;radius<=30;radius++)
        {
                draw_circle(x1,y1,radius);

        }
        for(radius=0;radius<=55;radius++)
        {
                draw_circle(x2,y2,radius);
        }
        for(radius=0;radius<=65;radius++)
        {
                draw_circle(x3,y3,radius);
        }
        for(radius=0;radius<=60;radius++)
        {
                draw_circle(x4,y4,radius);
        }
        for(radius=0;radius<=40;radius++)
        {
                draw_circle(x5,y5,radius);
        }
}

void drawGrass(int x1, int x2, int x3)
{
        for(radius=0;radius<=50;radius++)
                draw_circle(x1,530,radius);
        for(radius=0;radius<=75;radius++)
                draw_circle(x2,560,radius);
        for(radius=0;radius<=75;radius++)
                draw_circle(x3,500,radius);
}

void drawLargeGrass(int x1, int x2, int x3, int x4, int x5)
{
        for(radius=0;radius<=30;radius++)
                draw_circle(x1,500,radius);
        for(radius=0;radius<=55;radius++)
                draw_circle(x2,530,radius);
        for(radius=0;radius<=55;radius++)
                draw_circle(x3,580,radius);
        for(radius=0;radius<=60;radius++)
                draw_circle(x4,550,radius);
        for(radius=0;radius<=30;radius++)
                draw_circle(x5,520,radius);
}

void drawSmallBuilding(int x)
{
        glColor3f(0.0f,0.5f,0.5f); // Teal color
        glBegin(GL_POLYGON);
        glVertex2f(x,500);
        glVertex2f(x+100,500);
        glVertex2f(x+100,650);
        glVertex2f(x,650);
        glEnd();

        glColor3f(0.52f,0.78f,0.78f); // Light Mint color         
        for(int y=620; y>=550; y=y-50)
        {
                for(int i=20, j=0;j<2;i=i+40,j++)
                    {
                            glBegin(GL_POLYGON);
                            glVertex2f(x+i,y);
                            glVertex2f(x+i+20,y);
                            glVertex2f(x+i+20,y-20);
                            glVertex2f(x+i,y-20);
                            glEnd();
                    }
         }
}

void drawLargeBuilding(int x)
{
        glColor3f(0.25f,0.61f,0.61f); // Mint color
        glBegin(GL_POLYGON);
        glVertex2f(x,500);
        glVertex2f(x+150,500);
        glVertex2f(x+150,730);
        glVertex2f(x,730);
        glEnd();

        glColor3f(0.52f,0.78f,0.78f); // Light Mint color
        for(int y=700; y>=550; y=y-50)
        {
                for(int i=20,j=0;j<3;i=i+42,j++)
                    {
                            glBegin(GL_POLYGON);
                            glVertex2f(x+i,y);
                            glVertex2f(x+i+22,y);
                            glVertex2f(x+i+22,y-22);
                            glVertex2f(x+i,y-22);
                            glEnd();
                    }
         }
}

void drawHorizontalCrossing()
{
        for(int x=-980; x<=980; x=x+240)
        {
                glBegin(GL_POLYGON);
                glVertex2d(x,350);
                glVertex2d(x+150,350);
                glVertex2d(x+140,365);
                glVertex2d(x-10,365);
                glEnd();
        }
}

void drawtyre()
{
	float rad = 3.142/180, r = 30;
	glColor3f(0.0f,0.0f,0.0f);
	glBegin(GL_POLYGON);
	for(int i=0; i<360; i++)
	{
		float degInRad = i*rad;
		glVertex2f(r*cos(degInRad),r*sin(degInRad));
	}
	glEnd();
}

void draw_car1()
{
	glBegin(GL_POLYGON);         // draw car
	glVertex2f(0,325);
	glVertex2f(0,375);
	glVertex2f(60,375);
	glVertex2f(120,435);
	glVertex2f(250,435);
	glVertex2f(310,375);
	glVertex2f(370,375);
	glVertex2f(370,325);
	glEnd();

	glColor3f(0.89f,0.89f,0.88f);      // Platinum 
        glBegin(GL_POLYGON);
        glVertex2f(90,380);
        glVertex2f(130,425);
        glVertex2f(175,425);
        glVertex2f(175,380);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(190,380);
        glVertex2f(190,425);
        glVertex2f(240,425);
        glVertex2f(270,380);
        glEnd();
	
	glPushMatrix();
	glTranslatef(60,325,0);       // move the first tyre in x direction
	drawtyre();                   // display the translated tyre
	glPopMatrix();

	glPushMatrix();
	glTranslatef(300,325,0);      // move the second tyre in x direction
	drawtyre();                   //display the translated tyre
	glPopMatrix();
}

void draw_car2()
{
        glBegin(GL_POLYGON);         // draw car
        glVertex2f(0,325);
        glVertex2f(0,375);
        glVertex2f(60,375);
        glVertex2f(120,435);
        glVertex2f(250,435);
        glVertex2f(310,375);
        glVertex2f(370,375);
        glVertex2f(370,325);
        glEnd();

	glColor3f(0.89f,0.89f,0.88f);      // Platinum
	glBegin(GL_POLYGON);
	glVertex2f(100,380);
	glVertex2f(130,425);
	glVertex2f(175,425);
	glVertex2f(175,380);
	glEnd();
	glBegin(GL_POLYGON);
        glVertex2f(190,380);
        glVertex2f(190,425);
        glVertex2f(235,425);
        glVertex2f(275,380);
        glEnd();

        glPushMatrix();
        glTranslatef(60,320,0);       // move the first tyre in x direction
        drawtyre();                   // display the translated tyre
        glPopMatrix();

        glPushMatrix();
        glTranslatef(300,320,0);      // move the second tyre in x direction
        drawtyre();                   //display the translated tyre
        glPopMatrix();
}

void DrawTyre()
{
	glBegin(GL_POLYGON);
	glVertex2f(-190,-800);
	glVertex2f(-120,-800);
	glVertex2f(-120,-880);
	glVertex2f(-155,-887);
	glVertex2f(-190,-880);
	glEnd();
}

void drawCar()
{
	glColor3ub(189,125,189);	// Light purple
	glBegin(GL_POLYGON);		// car main body
	glVertex2f(-250,-800+carposY);
	glVertex2f(250,-800+carposY);
	glVertex2f(250,-650+carposY);
	glVertex2f(200,-650+carposY);
	glVertex2f(150,-500+carposY);
	glVertex2f(-150,-500+carposY);
	glVertex2f(-200,-650+carposY);
	glVertex2f(-250,-650+carposY);
	glEnd();

	glColor3f(0.82f,0.82f,0.82f);     // light grey
	glBegin(GL_POLYGON);              // Window
	glVertex2f(-130,-530+carposY);
	glVertex2f(130,-530+carposY);
	glVertex2f(160,-630+carposY);
	glVertex2f(-160,-630+carposY);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(-230,-670+carposY);
	glVertex2f(-170,-670+carposY);
	glVertex2f(-170,-720+carposY);
	glVertex2f(-230,-720+carposY);
	glEnd();

	glBegin(GL_POLYGON);
        glVertex2f(230,-670+carposY);
        glVertex2f(170,-670+carposY);
        glVertex2f(170,-720+carposY);
        glVertex2f(230,-720+carposY);
        glEnd();

	glColor3f(0.0f,0.0f,0.0f);     // Black

	glPushMatrix();               // First Tyre
	glTranslatef(0,carposY,0);
	DrawTyre();
	glPopMatrix();

	glPushMatrix();
        glTranslatef(320,carposY,0);      
        DrawTyre();                   //display the translated tyre
        glPopMatrix();
}

void mytimer(int n)
{
	carpos1 -= 30, carpos2 -= 40, carpos3 += 40, carpos4 += 30;
	glutPostRedisplay();
	glutTimerFunc(200,mytimer,0);
}

void drawObject()
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPointSize(1.0);

	if(day == 1)
	{
		//----------Drawing sky----------

        	glColor3f(0.5f,0.8f,0.9f); // Light Blue
        	glBegin(GL_POLYGON);
      		glVertex2f(-1000,500);
        	glVertex2f(1000,500);
       		glVertex2f(1000,1000);
        	glVertex2f(-1000,1000);
        	glEnd();

        	// Drawing Sun

        	for(radius=0;radius<=80;radius++)
        	{
                	glColor3f(1.0,0.9,0.0);
                	draw_circle(-800,850,radius);
        	}

        	// Drawing cloud

        	glColor3f(1.0,1.0,1.0);
        	drawCloud(-980,-900,-800,-740,860);
        	drawCloud(-240,-180,-80,0,860);
	}

	if(night == 1 && day == 0)
	{

		//----------Drawing Night Sky----------

                glColor3f(0.04f,0.07f,0.27f); 
                glBegin(GL_POLYGON);
                glVertex2f(-1000,500);
                glVertex2f(1000,500);
                glVertex2f(1000,1000);
                glVertex2f(-1000,1000);
                glEnd();

		//-------------Drawing Stars-----------

                int posX = 0, posY = 750, count = 0;
                glColor3f(1.0f,1.0f,1.0f);
                for(posX=-950; posX<=950; posX=posX+100)
                {
                        if(posY>=750 && posY<= 995)
                        {
                                glPointSize(3.0);
                                glBegin(GL_POINTS);
                                glVertex2f(posX,posY);
                                glEnd();
                                count += 1;
                        }

                        if( count%10 == 0 && posY >= 750)
                                posY = posY - 30;
                        else if(count%2 == 0 && posY >= 750)
                                posY = posY - 100;
                        else
                                if(posY <= 990)
                                        posY = posY + 90;
                }

		//--------------Drawing Moon-----------
		
		for(radius=0;radius<=80;radius++)
                {
                        glColor3f(0.96f,0.96f,0.83f);
                        draw_circle(-100,850,radius);
                }
		for(radius=0;radius<=70;radius++)
                {
                        glColor3f(0.04f,0.07f,0.27f);
                        draw_circle(-70,905,radius);
                }

	}

        //-----------Drawing Grass-------------

        glColor3f(0.22f,0.5f,0.02f); // Green
        drawGrass(-160,-220,-280);
        drawGrass(190,250,320);
        glColor3f(0.25f,0.69f,0.37f);  // Light Green
        drawLargeGrass(-110,-50,0,60,130);

        //----------Drawing land-------------

        glColor3f(0,0.6,0);  // Green  
        glBegin(GL_POLYGON);
        glVertex2d(-1000,500);
        glVertex2d(1000,500);
        glVertex2d(1000,-1000);
        glVertex2d(-1000,-1000);
        glEnd();

	//----------Drawing Border---------

        glColor3f(0.95f,0.8f,0.0f);    // Yellow
        glBegin(GL_POLYGON);
        glVertex2d(-1000,450);
        glVertex2d(1000,450);
        glVertex2d(1000,440);
        glVertex2d(-1000,440);
        glEnd();

        glColor3f(1.0f,1.0f,1.0f);     // White
        glBegin(GL_POLYGON);
        glVertex2d(-1000,440);
        glVertex2d(1000,440);
        glVertex2d(1000,430);
        glVertex2d(-1000,430);
        glEnd();

        //-----------Drawing Road-----------

        glColor3f(0.95f,0.8f,0.0f);   // Yellow  
        glBegin(GL_POLYGON);          // Vertical
        glVertex2d(-210,500);
        glVertex2d(210,500);
        glVertex2d(1200,-1000);
        glVertex2d(-1200,-1000);
        glEnd();
	glBegin(GL_POLYGON);          // Horizontal
        glVertex2d(-1000,190);
        glVertex2d(1000,190);
        glVertex2d(1000,210);
        glVertex2d(-1000,210);
        glEnd();


        glColor3f(1.0f,1.0f,1.0f);    // White   
        glBegin(GL_POLYGON);
        glVertex2d(-195,500);         // Vertical
        glVertex2d(195,500);
        glVertex2d(1125,-1000);
        glVertex2d(-1125,-1000);
        glEnd();
	glBegin(GL_POLYGON);          // Horizontal
        glVertex2d(-1000,210);
        glVertex2d(1000,210);
        glVertex2d(1000,225);
        glVertex2d(-1000,225);
        glEnd();

        glColor3f(0.3f,0.3f,0.3f); // Grey
        glBegin(GL_POLYGON);
        glVertex2d(-175,500);   // Vertical
        glVertex2d(175,500);
        glVertex2d(1075,-1000);
        glVertex2d(-1075,-1000);
        glEnd();
        glBegin(GL_POLYGON);   // Horizontal
        glVertex2d(-1000,430);
        glVertex2d(1000,430);
        glVertex2d(1000,225);
        glVertex2d(-1000,225);
        glEnd();

        //-----------Drawing Crossings------------

	glColor3f(1.0f,1.0f,1.0f);   // White
	drawHorizontalCrossing();     // Horizontal
      
        glBegin(GL_POLYGON);          // Vertical 1
        glVertex2f(-350,150);
        glVertex2f(-290,150);
        glVertex2f(-480,-250);
        glVertex2f(-580,-250);
        glEnd();

	glBegin(GL_POLYGON);          // Vertical 2
        glVertex2f(-230,150);
        glVertex2f(-165,150);
        glVertex2f(-280,-250);
        glVertex2f(-375,-250);
        glEnd();

        glBegin(GL_POLYGON);         // Vertical 3
        glVertex2f(-35,150);
        glVertex2f(-105,150);
        glVertex2f(-160,-250);
        glVertex2f(-70,-250);
        glEnd();

        glBegin(GL_POLYGON);         // Vertical 4
        glVertex2f(35,150);
        glVertex2f(105,150);
        glVertex2f(160,-250);
        glVertex2f(70,-250);
        glEnd();

        glBegin(GL_POLYGON);         // Vertical 5
        glVertex2f(230,150);
        glVertex2f(165,150);
        glVertex2f(280,-250);
        glVertex2f(375,-250);
        glEnd();

        glBegin(GL_POLYGON);         // Vertical 6
        glVertex2f(350,150);
        glVertex2f(290,150);
        glVertex2f(480,-250);
        glVertex2f(580,-250);
        glEnd();

	//--------------Drawing Buildings---------------

        drawSmallBuilding(-900);
        drawSmallBuilding(-650);
        drawSmallBuilding(450);
        drawLargeBuilding(-800);
        drawLargeBuilding(-550);
        drawLargeBuilding(550);

       //------------------Drawing Tree------------------

        glColor3f(0.58f,0.29f,0.0f); // Brown
        glBegin(GL_POLYGON);
        glVertex2f(850,500);
        glVertex2f(883,500);
        glVertex2f(883,680);
        glVertex2f(850,680);
        glEnd();

        glColor3f(0.0,0.6,0.0); // Green
        drawLeaves(840,600,810,650,860,690,920,650,900,600);

        //-----------------Drawing Cars---------------

	glPushMatrix();
        if(carpos3 >= 1500)
                carpos3 = -1000;
        glTranslatef(carpos3,100,0);     // move the third car
        glColor3ub(241,192,185);         // Rose quartz
        draw_car2();
        glPopMatrix();

        glPushMatrix();
        if(carpos4 >= 1500)
                carpos4 = -1000;
        glTranslatef(carpos4,80,0);    // move the fourth car
        glColor3ub(255,240,77);        // light yellow
        draw_car2();
        glPopMatrix();
	
	glPushMatrix();
	if(carpos1 <= -1500)
		carpos1 = 1000;
	glTranslatef(carpos1,-30,0);    // move the first car
	glColor3f(0,1.0f,1.0f);         // blue
	draw_car1();
	glPopMatrix();

	glPushMatrix();
	if(carpos2 <= -1500)
		carpos2 = 1000;
	glTranslatef(carpos2,-50,0);    // move the second car
	glColor3f(0.63f,0.92f,0.69f);         // Neon green
	draw_car1();
	glPopMatrix();

	if(car == 1)
	{
		glPushMatrix();
		glScalef(carScale,carScale,1.0f);
		drawCar();
		glPopMatrix();
	}

	//---------------Drawing Signal ----------------
	
	glColor3f(1.0f,1.0f,1.0f);    // Grey
	glBegin(GL_POLYGON);
	glVertex2f(-800,700);
	glVertex2f(-650,700);
	glVertex2f(-650,300);
	glVertex2f(-800,300);
	glEnd();

	glColor3f(0.0f,0.0f,0.0f);      // Black
	glBegin(GL_POLYGON);
	glVertex2f(-790,690);
	glVertex2f(-660,690);
	glVertex2f(-660,310);
	glVertex2f(-790,310);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(-710,300);
	glVertex2f(-740,300);
	glVertex2f(-740,-100);
	glVertex2f(-710,-100);
	glEnd();

	for(radius=0;radius<=30;radius++)
	{
		glColor3f(0.7f,0.7f,0.7f);        
		if(red == 1)                       // For Red light
			glColor3f(1.0f,0.0f,0.0f);
		draw_circle(-725,620,radius);

		glColor3f(1.0,1.0,0.0);            // For Yellow light
		draw_circle(-725,500,radius);  

		glColor3f(0.7f,0.7f,0.7f);        
		if(green == 1)                     // For Green light
			glColor3f(0.01f,0.75f,0.23f);
		draw_circle(-725,380,radius);
	}

        glFlush();
}

void display()
{
    glClearColor(0,0,0,1);

    if (value == -1)
    {
        char clgName[] = "ST JOSEPH ENGINEERING COLLEGE";
        drawhead(-350, 850, 0, clgName);
        char placeName[] = "VAMANJOOR, MANGALURU - 575028, KARNATAKA, INDIA";
        drawsubhead(-300, 785, 0, placeName);

        char deptName[] = "DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING";
        drawhead(-590, 575, 0, deptName);

        char project[] = "COMPUTER GRAPHICS MINI PROJECT";
        drawhead(-350, 375, 0, project);
        char on[] = "ON";
        drawhead(-20, 275, 0, on);
        char projectName[] = "ROAD TRAFFIC SIMULATION";
        drawhead(-300, 175, 0, projectName);

        char proBy[] = "PROJECT BY: ";
        drawhead(-100, -25, 0, proBy);

        char p1[] = "Ralweena Rishal Lobo";
        drawhead(-700, -175, 0, p1);
        char p1Usn[] = "4SO20CS119";
        drawhead(550, -175, 0, p1Usn);

        char p2[] = "Rencita Monteiro";
        drawhead(-700, -275, 0, p2);
        char p2Usn[] = "4SO20CS124";
        drawhead(550, -275, 0, p2Usn);

        char gb[] = "Under the guidance of ";
        drawhead(-170, -475, 0, gb);

        char guidedBy[] = "Mr. Anirudhan Adukkathayar C";
        drawhead(-250, -600, 0, guidedBy);
        char d1[] = "ASSISTANT PROFESSOR, CSE DEPARTMENT";
        drawsubhead(-200, -675, 0, d1);

        char in[] = "PRESS ENTER TO CONTINUE";
        drawsubhead(-120, -850, 0, in);

        glutSwapBuffers();
        glutDetachMenu(GLUT_RIGHT_BUTTON);
    }

    if(value == 0)
    {
        char projectName[] = "ROAD TRAFFIC SIMULATION";
        drawhead(-300, 750, 0, projectName);

        char border[] = "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *";
        drawhead(-700, 550, 0, border);

        char red[] = "Press 'r' or 'R' to change the signal light to red.";
        drawhead(-400, 350, 0, red);
        char green[] = "Press 'g' or 'G' to change the signal light to green.";
        drawhead(-400, 230, 0, green);

        char day[] = "Press 'd' or 'D' to make it day.";
        drawhead(-400, 110, 0, day);
        char night[] = "Press 'n' or 'N' to make it night.";
        drawhead(-400, -30, 0, night);

        char car[] = "Press 'c' or 'C' cars to arrive at the junction.";
        drawhead(-400, -150, 0, car);

        char menu[] = "Click RIGHT MOUSE BUTTON to display menu.";
        drawhead(-400, -270, 0, menu);

        char quit[] = "Click LEFT MOUSE BUTTON to quit.";
        drawhead(-400, -390, 0, quit);

        char in[] = "Press 's' or 'S' to Continue";
        drawhead(-400, -510, 0, in);

        glutSwapBuffers();
        glutDetachMenu(GLUT_RIGHT_BUTTON);
    }

    if(value == 1)
    {
            drawObject();
    }
}

void idle()
{
	if(day == 1)
		cloudX += SPEED/30;

	if(cloudX > 1000)
		cloudX = -1000;

	if(red == 1 && carposY == 800)
		isMoving = false;

	if(green == 1 && carposY == 800)
		isMoving = true;

	if(car == 0)
	{
		carposY = -1000;
                carScale = 1.5f;
	}

	if(car == 1)
	{
		if(isMoving)
		{
			carposY += SPEED;
			carScale -= 0.01f;
		}

		if(carposY >= 1500)	
			car = 0;
	}

	glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
	    case 's' :
	    case 'S' : value = 1;
		       glClear(GL_COLOR_BUFFER_BIT);
		       glutPostRedisplay();
		       break;
	    case 'd' :
	    case 'D' : day = 1;
		       night = 0;
		       glClear(GL_COLOR_BUFFER_BIT);
		       glutPostRedisplay();
		       break;
	    case 'n' :
	    case 'N' : day = 0;
		       night = 1;
		       glClear(GL_COLOR_BUFFER_BIT);
   		       glutPostRedisplay();
		       break;
	    case 'c' : 
 	    case 'C' : car = 1;
		       isMoving = true;
		       glClear(GL_COLOR_BUFFER_BIT);
		       glutPostRedisplay();
		       break;
	    case 'r' : 
	    case 'R' : red = 1;
		       green = 0;
		       glClear(GL_COLOR_BUFFER_BIT);
                       glutPostRedisplay();
                       break;
	    case 'g' :
            case 'G' : green = 1;
		       red = 0;
                       glClear(GL_COLOR_BUFFER_BIT);
                       glutPostRedisplay();
                       break;
    }

    if (key == 13)
    {
        value = 0;
        glClear(GL_COLOR_BUFFER_BIT);
        glutPostRedisplay();
    }

}

void mouse(int btn,int state,int x,int y)
{
        if(btn == GLUT_LEFT_BUTTON && state==GLUT_UP)
		exit(0);
}

int main(int argc,char **argv)
{
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(1000,900);
        glutInitWindowPosition(400,0);
        glutCreateWindow("Road Traffic Simulation");
        init();
        glutDisplayFunc(display);
	glutTimerFunc(20,mytimer,0);
	glutIdleFunc(idle);
        glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
        glutMainLoop();
	return 0;
}
    


