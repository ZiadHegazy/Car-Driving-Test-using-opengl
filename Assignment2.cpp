//#include <math.h>
//#include <stdio.h>
//#include <string>
//#include <stdlib.h>
//#include "TextureBuilder.h"
//#include <glut.h>
//#include <GLTexture.h>
//#include <iostream>
//#include <iostream>
//using namespace std;
//
//#define GLUT_KEY_ESCAPE 27
//#define DEG2RAD(a) (a * 0.0174532925)
//GLuint tex;
//GLTexture tex_ground;
//bool win = false ;
//bool lose = false;
//double goalx = 4;
//int t = 0;
//double goaly = 0.05;
//double goalz = 2;
//double goalZdim = 0.2;
//double goalXdim = 0.2;
//bool hold = false;
//bool rotated = false;
//void* currentfont;
//double pendlumAngle = 0;
//double playerx = 1;
//double playery = 0.45;
//double playerz = 1;
//double flampx = 1;
//double flampy = 0.1;
//double flampz = 3;
//double flampAngle = 0;
//double flampZdim = 0.03;
//double flampXdim = 0.03;
//double chair2x=3;
//double chair2y=0.21;
//double chair2z=2;
//double chair2Angle = 0;
//double chair2Zdim =0.22 ;
//double chair2Xdim = 0.2;
//double chairx= 1.0;
//double chairy= 0.21;
//double chairz= 1.55;
//double chairAngle = 90;
//double chairZdim = 0.22;
//double chairXdim = 0.2;
//double comodx = 3;
//double comody = 0.1;
//double comodz = 3;
//double comodAngle = 90;
//double comodXdim = 0.6;
//double comodZdim = 0.2;
//double x=178.5;
//double sofa2z = 3;
//double sofa2y = 0.2;
//double sofa2x = 2;
//double sofa2Angle = 180;
//double sofa2Xdim = 0.5;
//double sofa2Zdim = 0.4;
//double sofa1z = 3;
//double sofa1Angle = 0;
//double sofa1y = 0.2;
//double sofa1x = 1;
//double sofa1Xdim = 0.5;
//double sofa1Zdim = 0.4;
//double tablex=1;
//double tabley;
//double tablez=3.5;
//double tableAngle=0;
//double tableXdim = 0.6;
//double tableZdim = 0.6;
//double fanx = 2.3;
//double fany = 0.2;
//double fanz = 3;
//double fanAngle = 0;
//double fanXdim = 0.05;
//double fanZdim = 0.05;
//double y=178.5;
//double z=178.5;
//char* dir = "front";
//int pendlumdT = 2;
//int fanAngle2 = 2;
//void drawSofa(int angle);
//void drawFan();
//static bool collideWithObjects();
//void drawPhoto();
//void drawGoal();
//void Timer(int t);
//void Timer2(int t);
//void drawPlayer();
//void drawFloorLamp();
//void movePlayer();
//void drawTableLeg(double thick, double len);
//void drawChair();
//void drawCeilLamp();
//void drawComod();
//void setCameraBehind();
//void drawString(float x, float y, const char* string);
//void setFont(void* font);
//void setupLights();
//class Vector3f {
//public:
//	float x, y, z;
//
//	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
//		x = _x;
//		y = _y;
//		z = _z;
//	}
//
//	Vector3f operator+(Vector3f& v) {
//		return Vector3f(x + v.x, y + v.y, z + v.z);
//	}
//
//	Vector3f operator-(Vector3f& v) {
//		return Vector3f(x - v.x, y - v.y, z - v.z);
//	}
//
//	Vector3f operator*(float n) {
//		return Vector3f(x * n, y * n, z * n);
//	}
//
//	Vector3f operator/(float n) {
//		return Vector3f(x / n, y / n, z / n);
//	}
//
//	Vector3f unit() {
//		return *this / sqrt(x * x + y * y + z * z);
//	}
//
//	Vector3f cross(Vector3f v) {
//		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
//	}
//};
//
//class Camera {
//public:
//	Vector3f eye, center, up;
//
//	Camera(float eyeX = playerx+0.6, float eyeY = playery+0.15, float eyeZ = playerz, float centerX = playerx-0.5, float centerY = 0.182216f, float centerZ = playerz , float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
//		eye = Vector3f(eyeX, eyeY, eyeZ);
//		center = Vector3f(centerX, centerY, centerZ);
//		up = Vector3f(upX, upY, upZ);
//	}
//
//	void moveX(float d) {
//		Vector3f right = up.cross(center - eye).unit();
//		eye = eye + right * d;
//		center = center + right * d;
//	}
//
//	void moveY(float d) {
//		eye = eye + up.unit() * d;
//		center = center + up.unit() * d;
//	}
//
//	void moveZ(float d) {
//		Vector3f view = (center - eye).unit();
//		eye = eye + view * d;
//		center = center + view * d;
//	}
//
//	void rotateX(float a) {
//		Vector3f view = (center - eye).unit();
//		Vector3f right = up.cross(view).unit();
//		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
//		up = view.cross(right);
//		center = eye + view;
//	}
//
//	void rotateY(float a) {
//		Vector3f view = (center - eye).unit();
//		Vector3f right = up.cross(view).unit();
//		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
//		right = view.cross(up);
//		center = eye + view;
//	}
//
//	void look() {
//
//		gluLookAt(
//			eye.x, eye.y, eye.z,
//			center.x, center.y, center.z,
//			up.x, up.y, up.z
//		);
//
//	}
//};
//
//Camera camera;
//void print(int x, int y, char* string)
//{
//	int len, i;
//
//	//set the position of the text in the window using the x and y coordinates
//	glRasterPos2f(x, y);
//
//	//get the length of the string to display
//	len = (int)strlen(string);
//
//	//loop to display character by character
//	for (i = 0; i < len; i++)
//	{
//		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
//	}
//}
//void Timer2(int t) {
//	
//	/*glutPostRedisplay();
//	glutTimerFunc(1000, Timer2, 0);*/
//}
//void setFont(void* font)
//{
//	currentfont = font;                      // Set the currentfont to the font
//}
//void drawString(float x, float y, const char* string) {
//	glRasterPos2f(x, y);
//
//	for (const char* c = string; *c != '\0'; c++) {
//		glutBitmapCharacter(currentfont, *c);  // Updates the position
//	}
//}
//void setCameraBehind() {
//	if (dir == "front") {
//		camera.eye.x = playerx + 0.6;
//		camera.eye.y = playery + 0.15;
//		camera.eye.z = playerz;
//		camera.center.x = playerx - 0.5;
//		camera.center.y = 0.182216f;
//		camera.center.z = playerz;
//		camera.up.x = 0;
//		camera.up.y = 1;
//		camera.up.z = 0;
//	}
//	else if (dir == "back") {
//		camera.eye.x = playerx - 0.6;
//		camera.eye.y = playery + 0.15;
//		camera.eye.z = playerz;
//		camera.center.x = playerx + 0.5;
//		camera.center.y = 0.182216f;
//		camera.center.z = playerz;
//		camera.up.x = 0;
//		camera.up.y = 1;
//		camera.up.z = 0;
//	}
//	else if (dir == "left") {
//		camera.eye.x = playerx;
//		camera.eye.y = playery + 0.15;
//		camera.eye.z = playerz - 0.6;
//		camera.center.x = playerx;
//		camera.center.y = 0.182216f;
//		camera.center.z = playerz+0.5;
//		camera.up.x = 0;
//		camera.up.y = 1;
//		camera.up.z = 0;
//
//	}
//	else if (dir == "right") {
//		camera.eye.x = playerx;
//		camera.eye.y = playery + 0.15;
//		camera.eye.z = playerz + 0.6;
//		camera.center.x = playerx;
//		camera.center.y = 0.182216f;
//		camera.center.z = playerz - 0.5;
//		camera.up.x = 0;
//		camera.up.y = 1;
//		camera.up.z = 0;
//
//	}
//	//camera.eye.x=playerx
//	//float eyeX = playerx + 0.6, float eyeY = playery + 0.15, float eyeZ = playerz, float centerX = playerx - 0.5, float centerY = 0.182216f, float centerZ = playerz, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f
//}
//void Timer(int t1) {
//	setupLights();
//	printf(dir);
//	t += 40;
//	if (fanAngle2 >= 360)
//		fanAngle2 = 2;
//	if (pendlumAngle >= 45) {
//		pendlumdT = -2;
//	}
//	if (pendlumAngle <= -45) {
//		pendlumdT = 2;
//	}
//	if (hold) {
//		if ((playerx >= tablex - tableXdim && playerx <= tablex + tableXdim+0 && playerz >= tablez - tableZdim-0 && playerz <= tablez + tableZdim+0) || 
//			(tableAngle>0 && playerz >= tablez - tableXdim*sin(tableAngle) && playerz <= tablez + tableXdim * sin(tableAngle) && playerx >= tablex - tableZdim*sin(tableAngle) && playerx <= tablex + tableZdim * sin(tableAngle))) {
//			tablex = playerx;
//			tablez = playerz;
//		}
//		else if (playerx >= goalx - goalXdim - 0 && playerx <= goalx + goalXdim && playerz >= goalz - goalZdim && playerz <= goalz + goalZdim) {
//			win = true;
//		}
//		else if ((playerx >= chairx - chairXdim - 0 && playerx <= chairx + chairXdim + 0 && playerz >= chairz - chairZdim - 0 && playerz <= chairz + chairZdim + 0) ||
//			(chairAngle > 0 && playerz >= chairz - chairXdim * sin(chairAngle) && playerz <= chairz + chairXdim * sin(chairAngle) && playerx >= chairx - chairZdim * sin(chairAngle) && playerx <= chairx + chairZdim * sin(chairAngle))) {
//			chairx = playerx;
//			chairz = playerz;
//		}
//		else if ((playerx >= chair2x - chair2Xdim - 0 && playerx <= chair2x + chair2Xdim + 0 && playerz >= chair2z - chair2Zdim - 0 && playerz <= chair2z + chair2Zdim + 0) ||
//			(chair2Angle > 0 && playerz >= chair2z - chair2Xdim * sin(chair2Angle) && playerz <= chair2z + chair2Xdim * sin(chair2Angle) && playerx >= chair2x - chair2Zdim * sin(chair2Angle) && playerx <= chair2x + chair2Zdim * sin(chair2Angle))) {
//			chair2x = playerx;
//			chair2z = playerz;
//		}
//		else if ((playerx >= sofa1x - sofa1Xdim - 0 && playerx <= sofa1x + sofa1Xdim + 0 && playerz >= sofa1z - sofa1Zdim - 0 && playerz <= sofa1z + sofa1Zdim + 0) ||
//			(sofa1Angle > 0 && playerz >= sofa1z - sofa1Xdim * sin(sofa1Angle) && playerz <= sofa1z + sofa1Xdim * sin(sofa1Angle) && playerx >= sofa1x - sofa1Zdim * sin(sofa1Angle) && playerx <= sofa1x + sofa1Zdim * sin(sofa1Angle))) {
//			sofa1x = playerx;
//			sofa1z = playerz;
//		}
//		else if ((playerx >= sofa2x - sofa2Xdim - 0 && playerx <= sofa2x + sofa2Xdim + 0 && playerz >= sofa2z - sofa2Zdim - 0 && playerz <= sofa2z + sofa2Zdim + 0) ||
//			(sofa2Angle > 0 && playerz >= sofa2z - sofa2Xdim * sin(sofa2Angle) && playerz <= sofa2z + sofa2Xdim * sin(sofa2Angle) && playerx >= sofa2x - sofa2Zdim * sin(sofa2Angle) && playerx <= sofa2x + sofa2Zdim * sin(sofa2Angle))) {
//			sofa2x = playerx;
//			sofa2z = playerz;
//		}
//		else if ((playerx >= flampx - flampXdim - 0 && playerx <= flampx + flampXdim + 0 && playerz >= flampz - flampZdim - 0 && playerz <= flampz + flampZdim + 0) ||
//			(flampAngle > 0 && playerz >= flampz - flampXdim * sin(flampAngle) && playerz <= flampz + flampXdim * sin(flampAngle) && playerx >= flampx - flampZdim * sin(flampAngle) && playerx <= flampx + flampZdim * sin(flampAngle))) {
//			flampx = playerx;
//			flampz = playerz;
//		}
//		else if ((playerx >= fanx - fanXdim - 0 && playerx <= fanx + fanXdim + 0 && playerz >= fanz - fanZdim - 0 && playerz <= fanz + fanZdim + 0) ||
//			(fanAngle > 0 && playerz >= fanz - fanXdim * sin(fanAngle) && playerz <= fanz + fanXdim * sin(fanAngle) && playerx >= fanx - fanZdim * sin(fanAngle) && playerx <= fanx + fanZdim * sin(fanAngle))) {
//			fanx = playerx;
//			fanz = playerz;
//		}
//		else if ((playerx >= comodx - comodXdim - 0 && playerx <= comodx + comodXdim + 0 && playerz >= comodz - comodZdim - 0 && playerz <= comodz + comodZdim + 0) ||
//			(comodAngle > 0 && playerz >= comodz - comodXdim * sin(comodAngle) && playerz <= comodz + comodXdim * sin(comodAngle) && playerx >= comodx - comodZdim * sin(comodAngle) && playerx <= comodx + comodZdim * sin(comodAngle))) {
//			comodx = playerx;
//			comodz = playerz;
//		}
//	}
//	else if (rotated) {
//		if ((playerx >= tablex - tableXdim - 0 && playerx <= tablex + tableXdim + 0 && playerz >= tablez - tableZdim - 0 && playerz <= tablez + tableZdim + 0) ||
//			(tableAngle > 0 && playerz >= tablez - tableXdim * sin(tableAngle) && playerz <= tablez + tableXdim * sin(tableAngle) && playerx >= tablex - tableZdim * sin(tableAngle) && playerx <= tablex + tableZdim * sin(tableAngle))) {
//			printf("%f",tableAngle);
//			tableAngle += 30;
//			if (tableAngle >= 360)
//				tableAngle = 0;
//		}
//		else if ((playerx >= chairx - chairXdim - 0 && playerx <= chairx + chairXdim + 0 && playerz >= chairz - chairZdim - 0 && playerz <= chairz + chairZdim + 0) ||
//			(chairAngle > 0 && playerz >= chairz - chairXdim * sin(chairAngle) && playerz <= chairz + chairXdim * sin(chairAngle) && playerx >= chairx - chairZdim * sin(chairAngle) && playerx <= chairx + chairZdim * sin(chairAngle))) {
//			printf("%f", comodAngle);
//			chairAngle += 30;
//			if (chairAngle >= 360)
//				chairAngle = 0;
//		}
//		else if ((playerx >= chair2x - chair2Xdim - 0 && playerx <= chair2x + chair2Xdim + 0 && playerz >= chair2z - chair2Zdim - 0 && playerz <= chair2z + chair2Zdim + 0) ||
//			(chair2Angle > 0 && playerz >= chair2z - chair2Xdim * sin(chair2Angle) && playerz <= chair2z + chair2Xdim * sin(chair2Angle) && playerx >= chair2x - chair2Zdim * sin(chair2Angle) && playerx <= chair2x + chair2Zdim * sin(chair2Angle))) {
//			printf("%f", fanAngle);
//			chair2Angle += 30;
//			if (chair2Angle >= 360)
//				chair2Angle = 0;
//		}
//		else if ((playerx >= sofa1x - sofa1Xdim - 0 && playerx <= sofa1x + sofa1Xdim + 0 && playerz >= sofa1z - sofa1Zdim - 0 && playerz <= sofa1z + sofa1Zdim + 0) ||
//			(sofa1Angle > 0 && playerz >= sofa1z - sofa1Xdim * sin(sofa1Angle) && playerz <= sofa1z + sofa1Xdim * sin(sofa1Angle) && playerx >= sofa1x - sofa1Zdim * sin(sofa1Angle) && playerx <= sofa1x + sofa1Zdim * sin(sofa1Angle))) {
//			printf("%f", flampAngle);
//			sofa1Angle += 30;
//			if (sofa1Angle >= 360)
//				sofa1Angle = 0;
//		}
//		else if ((playerx >= sofa2x - sofa2Xdim - 0 && playerx <= sofa2x + sofa2Xdim + 0 && playerz >= sofa2z - sofa2Zdim - 0 && playerz <= sofa2z + sofa2Zdim + 0) ||
//			(sofa2Angle > 0 && playerz >= sofa2z - sofa2Xdim * sin(sofa2Angle) && playerz <= sofa2z + sofa2Xdim * sin(sofa2Angle) && playerx >= sofa2x - sofa2Zdim * sin(sofa2Angle) && playerx <= sofa2x + sofa2Zdim * sin(sofa2Angle))) {
//			printf("%f", chairAngle);
//			sofa2Angle += 30;
//			if (sofa2Angle >= 360)
//				sofa2Angle = 0;
//		}
//		else if ((playerx >= flampx - flampXdim - 0 && playerx <= flampx + flampXdim + 0 && playerz >= flampz - flampZdim - 0 && playerz <= flampz + flampZdim + 0) ||
//			(flampAngle > 0 && playerz >= flampz - flampXdim * sin(flampAngle) && playerz <= flampz + flampXdim * sin(flampAngle) && playerx >= flampx - flampZdim * sin(flampAngle) && playerx <= flampx + flampZdim * sin(flampAngle))) {
//			printf("%f", chair2Angle);
//			flampAngle += 30;
//			if (flampAngle >= 360)
//				flampAngle = 0;
//		}
//		else if ((playerx >= fanx - fanXdim - 0 && playerx <= fanx + fanXdim + 0 && playerz >= fanz - fanZdim - 0 && playerz <= fanz + fanZdim + 0) ||
//			(fanAngle > 0 && playerz >= fanz - fanXdim * sin(fanAngle) && playerz <= fanz + fanXdim * sin(fanAngle) && playerx >= fanx - fanZdim * sin(fanAngle) && playerx <= fanx + fanZdim * sin(fanAngle))) {
//			printf("%f", sofa1Angle);
//			fanAngle += 30;
//			if (fanAngle >= 360)
//				fanAngle = 0;
//		}
//		else if ((playerx >= comodx - comodXdim - 0 && playerx <= comodx + comodXdim + 0 && playerz >= comodz - comodZdim - 0 && playerz <= comodz + comodZdim + 0) ||
//			(comodAngle > 0 && playerz >= comodz - comodXdim * sin(comodAngle) && playerz <= comodz + comodXdim * sin(comodAngle) && playerx >= comodx - comodZdim * sin(comodAngle) && playerx <= comodx + comodZdim * sin(comodAngle))) {
//			printf("%f", sofa2Angle);
//			comodAngle += 30;
//			if (comodAngle >= 360)
//				comodAngle = 0;
//		}
//	}
//	fanAngle2 += 2;
//	pendlumAngle += pendlumdT;
//	if (t >= 50000) {
//		//lose = true;
//	}
//	
//	
//	glutPostRedisplay();
//	glutTimerFunc(40, Timer, 0);
//}
//static bool collideWithObjects(double x,double z) {
//	if ((x >= tablex - tableXdim/2 && x <= tablex + tableXdim/2 && z >= tablez - tableZdim /2/2 && z <= tablez + tableZdim /2/2) ||
//		(tableAngle>0 && z >= tablex - tableXdim/2 && z <= tablex + tableXdim/2 && x >= tablez - tableZdim /2/2 && x <= tablez + tableZdim /2/2)) {
//		return true;
//	}
//	if ((x >= fanx - fanXdim /2 && x <= fanx + fanXdim /2 && z >= fanz - fanZdim /2 && z <= fanz + fanZdim /2) ||
//		(fanAngle > 0 &&  z >= fanx - fanXdim /2 && z <= fanx + fanXdim /2 && x >= fanz - fanZdim /2 && x <= fanz + fanZdim /2)) {
//		return true;
//	}
//	if ((x >= flampx - flampXdim /2 && x <= flampx + flampXdim /2 && z >= flampz - flampZdim /2 && z <= flampz + flampZdim /2) ||
//		(flampAngle > 0 && z >= flampx - flampXdim /2 && z <= flampx + flampXdim /2 && x >= flampz - flampZdim /2 && x <= flampz + flampZdim /2)) {
//		return true;
//	}
//	if ((x >= chair2x - chair2Xdim /2 && x <= chair2x + chair2Xdim /2 && z >= chair2z - chair2Zdim /2 && z <= chair2z + chair2Zdim /2) ||
//		(chair2Angle > 0 && z >= chair2x - chair2Xdim /2 && z <= chair2x + chair2Xdim /2 && x >= chair2z - chair2Zdim /2 && x <= chair2z + chair2Zdim /2)) {
//		return true;
//	}
//	if ((x >= chairx - chairXdim /2 && x <= chairx + chairXdim /2 && z >= chairz - chairZdim /2 && z <= chairz + chairZdim /2) ||
//		(chairAngle > 0 && z >= chairx - chairXdim /2 && z <= chairx + chairXdim /2 && x >= chairz - chairZdim /2 && x <= chairz + chairZdim /2)) {
//		return true;
//	}
//	if ((x >= sofa2x - sofa2Xdim /2 && x <= sofa2x + sofa2Xdim /2 && z >= sofa2z - sofa2Zdim /2 && z <= sofa2z + sofa2Zdim /2) ||
//		(sofa2Angle > 0 && z >= sofa2x - sofa2Xdim /2 && z <= sofa2x + sofa2Xdim /2 && x >= sofa2z - sofa2Zdim /2 && x <= sofa2z + sofa2Zdim /2)) {
//		return true;
//	}
//	if ((x >= sofa1x - sofa1Xdim /2 && x <= sofa1x + sofa1Xdim /2 && z >= sofa1z - sofa1Zdim /2 && z <= sofa1z + sofa1Zdim /2) ||
//		(sofa1Angle > 0 && z >= sofa1x - sofa1Xdim /2 && z <= sofa1x + sofa1Xdim /2 && x >= sofa1z - sofa1Zdim /2 && x <= sofa1z + sofa1Zdim /2)) {
//		return true;
//	}
//	if ((x >= comodx - comodXdim /2 && x <= comodx + comodXdim /2 && z >= comodz - comodZdim /2 && z <= comodz + comodZdim /2) ||
//		(comodAngle > 0 && z >= comodx - comodXdim /2 && z <= comodx + comodXdim /2 && x >= comodz - comodZdim /2 && x <= comodz + comodZdim /2)) {
//		return true;
//	}
//	if ((x >= fanx - fanXdim /2 && x <= fanx + fanXdim /2 && z >= fanz - fanZdim /2 && z <= fanz + fanZdim /2) ||
//		(fanAngle > 0 && z >= fanx - fanXdim /2 && z <= fanx + fanXdim /2 && x >= fanz - fanZdim /2 && x <= fanz + fanZdim /2)) {
//		return true;
//	}
//	return false;
//}
//void drawGoal() {
//	glPushMatrix();
//	glColor3f(1, 1, 0);
//	//base
//	glTranslated(goalx, goaly, goalz);
//	glPushMatrix();
//	glTranslated(0, 0, 0);
//	glScaled(1, 0.25, 1);
//	glutSolidSphere(0.1, 15, 15);
//	glPopMatrix();
//	//cone
//
//	glPushMatrix();
//	glTranslated(0, 0.2-goaly, 0);
//	glRotated(90, 1, 0, 0);
//	glutSolidCone(0.1,0.3, 15, 15);
//	glPopMatrix();
//
//	//wedna
//	glPushMatrix();
//	glTranslated(-0.1, 0.13-goaly, 2-goalz);
//	glScaled(1, 1, 0.25);
//	glutSolidSphere(0.05, 15, 15);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslated(0.1, 0.13-goaly, 2-goalz);
//	glScaled(1, 1, 0.25);
//	glutSolidSphere(0.05, 15, 15);
//	glPopMatrix();
//
//	glPopMatrix();
//	glColor3f(0.7, 0.7, 0.7);
//}
//void drawFan() {
//	glPushMatrix();
//	glTranslated(fanx, fany, fanz);
//	glRotated(fanAngle, 0, 1, 0);
//	//3mood
//	glColor3f(1, 0, 1);
//
//	glPushMatrix();
//	glTranslated(0, 0,0);
//	glScaled(0.25, 3.5, 0.25);
//	glutSolidCube(0.2);
//	glPopMatrix();
//
//	//center
//	glColor3f(0, 1, 0);
//
//	glPushMatrix();
//	glTranslated(0, 0.6-fany,-0.04);
//	glScaled(1, 1, 0.5);
//	glutSolidSphere(0.05,15,15);
//	glPopMatrix();
//
//	//resha1
//	glPushMatrix();
//	glColor3f(0, 0, 1);
//	glTranslated(0, 0.6-fany, -0.04);
//	glScaled(1.7, 1, 0.5);
//	glRotated(-90, 1, 0, 0);
//	glRotated(fanAngle2, 0, 1, 0);
//	glutSolidCone(0.02, 0.3, 15, 15);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslated(0, 0.6 - fany, -0.04);
//
//	glScaled(0.9, 1.8, 0.5);
//	glRotated(-90, 1, 0, 0);
//	glRotated(120, 0, 1, 0);
//	glRotated(fanAngle2, 0, 1, 0);
//	glutSolidCone(0.02, 0.3, 15, 15);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslated(0, 0.6 - fany, -0.04);
//
//
//	glScaled(0.9, 1.8, 0.5);
//	glRotated(-90, 1, 0, 0);
//	glRotated(-120, 0, 1, 0);
//	glRotated(fanAngle2, 0, 1, 0);
//	glutSolidCone(0.02, 0.3, 15, 15);
//	glPopMatrix();
//
//	glPopMatrix();
//	glPopMatrix();
//	glColor3f(0.7, 0.7, 0.7);
//}
//
//void drawSofa(int angle) {
//	glPushMatrix();
//	//gesm
//	glRotated(angle, 0, 1, 0);
//	glColor3f(1, 1, 0);
//	glPushMatrix();
//	glTranslated(0.1, 0.05, 0);
//	glScaled(0.5, 1.5, 4);
//
//	glutSolidCube(0.1);
//	glPopMatrix();  
//
//	glPushMatrix();
//	glTranslated(0.15, -0.05, 0);
//	glRotated(90, 0, 0, 1);
//	glScaled(0.5, 1.5, 4);
//
//	glutSolidCube(0.1);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslated(0.15, -0.1, 0.175);
//
//	glScaled(1.5, 1.1, 0.5);
//
//	glutSolidCube(0.1);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslated(0.15, -0.1, -0.175);
//
//	glScaled(1.5, 1.1, 0.5);
//	glutSolidCube(0.1);
//	glPopMatrix();
//
//	glPopMatrix();
//	glColor3f(0.7, 0.7, 0.7);
//}
//void drawComod() {
//	glPushMatrix();
//	//mirror
//	glTranslated(comodx, comody, comodz);
//	glRotated(comodAngle, 0, 1, 0);
//	glColor3f(0.7, 0.5, 0.3);
//	glPushMatrix();
//	glTranslated(0, 0, 0);
//	glScaled(3, 3, 1);
//	glutSolidCube(0.2);
//	glPopMatrix();
//
//	//fasel
//	glColor3f(0, 0, 0);
//	glPushMatrix();
//	glTranslated(0, 0.1, -0.1);
//	glScaled(3, 0.2, 0.02);
//	glutSolidCube(0.2);
//	glPopMatrix();
//
//	//m2abed
//	glPushMatrix();
//	glTranslated(0, 0.2, -0.1);
//	glutSolidSphere(0.02,15,15);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslated(0, 0.03, -0.1);
//	glutSolidSphere(0.02, 15, 15);
//	glPopMatrix();
//	glColor3f(0.9, 0.9, 0.9);
//	//mraya
//	glPushMatrix();
//	glTranslated(0, 0.3, 0.05);
//	glScaled(1.5, 3, 0.2);
//	glutSolidSphere(0.2, 15, 15);
//	glPopMatrix();
//
//	glPopMatrix();
//	glColor3f(0.7, 0.7, 0.7);
//}
//void drawPendlum() {
//
//	glPushMatrix();
//	glPushMatrix();
//	glColor3f(0, 0, 1);
//	glTranslated(0, 0.7, 2);
//	glScaled(0.25, 1, 1);
//	glutSolidCube(0.2);
//	glPopMatrix();
//
//	glPushMatrix();
//	glPushMatrix();
//	glColor3f(0, 1, 0);
//	glTranslated(0, 0.72, 2);
//	glRotated(pendlumAngle, 1, 0, 0);
//	glScaled(1, 1.3, 0.25);
//	glutSolidCube(0.1);
//	glPopMatrix();
//	glPopMatrix();
//
//	glPopMatrix();
//	glColor3f(0.7, 0.7, 0.7);
//}
//void drawFloorLamp() {
//	glPushMatrix();
//	glTranslated(flampx, flampy, flampz);
//	glRotated(flampAngle,0,1,0);
//	//gesm 
//	glColor3f(0, 0, 0);
//	glPushMatrix();
//	glTranslated(0, 0.1-flampy, 0);
//	glScaled(0.1, 4, 0.1);
//	glutSolidCube(0.3);
//	glPopMatrix();
//
//	//upCone
//	glPushMatrix();
//	glColor3f(1, 1, 1);
//	glTranslated(0, 0.72-flampy, 0);
//	glRotated(90, 1, 0, 0);
//	glutSolidCone(0.06, 0.05, 15, 15);
//	glPopMatrix();
//
//	//lamp
//	glPushMatrix();
//	glColor3f(1, 1, 0);
//	glTranslated(0, 0.74-flampy, 0);
//	glutSolidSphere(0.03, 15, 15);
//	glPopMatrix();
//
//	glPopMatrix();
//	glColor3f(0.7, 0.7, 0.7);
//}
//void drawCeilLamp() {
//	glPushMatrix();
//	//selk
//	glColor3f(0, 0, 0);
//	glPushMatrix();
//	glTranslated(2.5, 1, 2.5);
//	glScaled(0.5, 2.5, 0.5);
//	glutSolidCube(0.05);
//	glPopMatrix();
//
//	//gesm lamp
//	glPushMatrix();
//	glColor3f(1, 0, 1);
//	glTranslated(2.5, 0.8, 2.5);
//	glRotatef(-90, 1, 0, 0);
//	glutSolidCone(0.05, 0.2, 15, 15);
//	glPopMatrix();
//
//	//lamp
//
//	glPushMatrix();
//	glColor3f(1, 1, 0);
//	glTranslated(2.5, 0.8, 2.5);
//	glutSolidSphere(0.02, 15, 15);
//	glPopMatrix();
//
//	glPopMatrix();
//	glColor3f(0.7, 0.7, 0.7);
//}
//void drawChair(int angle) {
//	glPushMatrix();
//	glRotated(angle, 0, 1, 0);
//
//	glPushMatrix();
//	glColor3f(0.0f, 1.0f, 0.0f);
//
//	glScaled(2.0, 0.4, 2.2);
//	glutSolidCube(0.1);
//	glColor3f(0.7f, 0.7f, 0.7f);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslated(-0.1, -0.18, 0.11);
//	glColor3f(0.7, 0.5, 0.3);
//	drawTableLeg(0.02, 0.2);
//	glColor3f(0.7, 0.7, 0.7);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslated(0.1, -0.18, 0.11);
//	glColor3f(0.7, 0.5, 0.3);
//	drawTableLeg(0.02, 0.2);
//	glColor3f(0.7, 0.7, 0.7);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslated(0.1, -0.18, -0.11);
//	glColor3f(0.7, 0.5, 0.3);
//	drawTableLeg(0.02, 0.2);
//	glColor3f(0.7, 0.7, 0.7);
//	glPopMatrix();
//
//	glPushMatrix();
//	glColor3f(0.7, 0.5, 0.3);
//	glTranslated(-0.1, -0.18, -0.11);
//	drawTableLeg(0.02, 0.2);
//	glColor3f(0.7, 0.7, 0.7);
//	glPopMatrix();
//	
//	glPushMatrix();
//	glTranslated(-0.1, 0.15, 0);
//	glColor3f(0.7, 0.5, 0.3);
//	glScaled(0.2, 2.8, 2.2);
//	glutSolidCube(0.1);
//	glPopMatrix();
//
//	glColor3f(0.7, 0.7, 0.7);
//	glPopMatrix();
//
//}
//
//void drawWall(double thickness) {
//	glPushMatrix();
//	glTranslated(0.5, 0.5 * thickness, 0.5);
//	glScaled(1.0, thickness, 1.0);
//	glutSolidCube(1);
//	glPopMatrix();
//}
//void drawTableLeg(double thick, double len) {
//	glPushMatrix();
//	glColor3f(0.7, 0.5, 0.3);
//	glTranslated(0, len / 2, 0);
//	glScaled(thick, len, thick);
//	glutSolidCube(1.0);
//	glPopMatrix();
//	glColor3f(0.7, 0.7, 0.7);
//}
//void drawJackPart() {
//	glPushMatrix();
//	glScaled(0.2, 0.2, 1.0);
//	glutSolidSphere(1, 150, 250);
//	glPopMatrix();
//	glPushMatrix();
//	glTranslated(0, 0, 1.2);
//	glutSolidSphere(0.2, 15, 15);
//	glTranslated(0, 0, -2.4);
//	glutSolidSphere(0.2, 15, 15);
//	glPopMatrix();
//}
//void drawJack() {
//	glPushMatrix();
//	drawJackPart();
//	glRotated(90.0, 0, 1, 0);
//	drawJackPart();
//	glRotated(90.0, 1, 0, 0);
//	drawJackPart();
//	glPopMatrix();
//}
//void drawTable(double topWid, double topThick, double legThick, double legLen) {
//	glPushMatrix();
//	glTranslated(tablex, legLen, tablez);
//	glRotated(tableAngle,0,1,0);
//	glPushMatrix();
//	glScaled(topWid, topThick, topWid);
//	glColor3f(1, 1, 0);
//	glutSolidCube(1.0);
//	glPopMatrix();
//	glColor3f(0.7, 0.7, 0.7);
//	
//	glPushMatrix();
//	glTranslated(topWid/2, -legLen, topWid/2);
//	drawTableLeg(legThick, legLen);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslated(-topWid/2, -legLen, topWid/2);
//	drawTableLeg(legThick, legLen);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslated(-topWid/2, -legLen , -topWid/2);
//	drawTableLeg(legThick, legLen);
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslated(topWid/2, -legLen, -topWid/2);
//	drawTableLeg(legThick, legLen);
//	glPopMatrix();
//
//	glPopMatrix();
//}
//void drawPlayer() {
//	glPushMatrix();
//
//	glTranslated(playerx, playery, playerz);
//	if (dir == "back") {
//		glRotatef(180, 0, 1, 0);
//
//	}
//	else if (dir == "right") {
//		glRotatef(90, 0, 1, 0);
//
//	}
//	else if (dir == "left") {
//		glRotatef(-90, 0, 1, 0);
//
//	}
//	glutSolidSphere(0.05, 15, 15);
//	//neck
//	glPushMatrix();
//	glTranslated(0, -0.07, 0);
//	glScaled(0.5, 1, 0.5);
//	glutSolidCube(0.06);
//	glPopMatrix();
//	//body
//	glPushMatrix();
//	glTranslated(0, -0.15, 0);
//	glScaled(1, 3, 1.5);
//	glutSolidCube(0.06);
//	glPopMatrix();
//
//	//left arm
//	glPushMatrix();
//	glTranslated(0, -0.14, 0.05);
//	glRotatef(-45, 1, 0, 0);
//	glScaled(0.5, 2.5, 0.5);
//	glutSolidCube(0.06);
//	glPopMatrix();
//
//	//right arm
//	glPushMatrix();
//	glRotated(180, 0, 1, 0);
//	glTranslated(0, -0.14, 0.05);
//	glRotatef(-45, 1, 0, 0);
//	glScaled(0.5, 2.5, 0.5);
//	glutSolidCube(0.06);
//	glPopMatrix();
//
//	// left leg
//	glPushMatrix();
//	glTranslated(0, -0.25, 0.03);
//	glRotated(-10, 1, 0, 0);
//	glScaled(0.5, 7, 0.5);
//	glutSolidCube(0.06);
//	glPopMatrix();
//
//	//right leg
//	glPushMatrix();
//	glRotated(180, 0, 1, 0);
//	glTranslated(0, -0.25, 0.03);
//	glRotated(-10, 1, 0, 0);
//	glScaled(0.5, 7, 0.5);
//	glutSolidCube(0.06);
//	glPopMatrix();
//
//	glPopMatrix();
//}
//void setupLights() {
//	GLfloat ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
//	GLfloat diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//	GLfloat specular[] = { 0.7f, 0.7f, 0.7f, 1.0f };
//	GLfloat shininess[] = { 50 };
//	/*glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
//	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
//	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);*/
//
//	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
//	GLfloat lightIntensity1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//
//	GLfloat lightPosition[] = { 2.5f, 1.0f, 2.5f, 0.0f };
//	
//	/*if (dir == "left") {
//		lightPosition1[0]=playerx;
//		lightPosition1[1] = playery+1;
//		lightPosition1[2] = playerz-2;
//	}*/
//
//	GLfloat 
// _Ka[] = { 1.0f,0.0f,0.0f,1.0f };
//	GLfloat light1_Kd[] = { 1.0f,0.0f,0.0f,1.0f };
//	GLfloat light1_Kspec[] = { 1,0,0,0 };
//	GLfloat light1_spotDirection[] = { 0, -1,0};
//	GLfloat lightPosition1[] = { playerx, playery + 1, playerz, 1 };
//
//	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
//	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
//	glLightfv(GL_LIGHT0, GL_SHININESS, shininess);
//	const GLfloat x= 30;
//	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
//	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF,25.0 ) ;
//	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_spotDirection);
//	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_Ka);
//	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_Kd);
//	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_Kspec);
//}
//void setupCamera() {
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(60, 800 / 500, 0.001, 100);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	camera.look();
//}
//
//void Display() {
//	glOrtho(-50, 50, -50, 50, -100, 100);
//
//	setupCamera();
//	setupLights();
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	if (win) {
//		playerx = 1;
//		playerz = 1;
//		dir = "front";
//		setCameraBehind();
//		glColor3f(0, 1, 0);
//		glPushMatrix();
//		glTranslated(0, 0.2, 1.2);
//		glRotated(-20, 1, 0, 0);
//		glScaled(1, 4, 1);
//		glutSolidCube(0.1);
//		glPopMatrix();
//
//		glPushMatrix();
//		glTranslated(0, 0.14, 1);
//		glRotated(-70, 1, 0, 0);
//		glScaled(1, 6, 1);
//		glutSolidCube(0.1);
//		glPopMatrix();
//	}
//	else if (lose) {
//		glColor3f(1, 0, 0);
//		playerx = 1;
//		playerz = 1;
//		dir = "front";
//		setCameraBehind();
//		glPushMatrix();
//		glTranslated(0, 0.2, 1);
//		glRotated(30, 1, 0, 0);
//		glScaled(1, 5, 1);
//		glutSolidCube(0.1);
//		glPopMatrix();
//
//		glPushMatrix();
//		glTranslated(0, 0.2, 1);
//		glRotated(-30, 1, 0, 0);
//		glScaled(1, 5, 1);
//		glutSolidCube(0.1);
//		glPopMatrix();
//	}
//	else {
//		glPushMatrix();
//		glPushMatrix();
//		glTranslated(0.4, 0.4, 0.6);
//		glRotated(45, 0, 0, 1);
//		glScaled(0.08, 0.08, 0.08);
//		glPopMatrix();
//		glPushMatrix();
//		glTranslated(0.6, 0.38, 0.5);
//		glRotated(30, 0, 1, 0);
//		glPopMatrix();
//		glPushMatrix();
//		glTranslated(0.25, 0.42, 0.35);
//		glPopMatrix();
//		glPushMatrix();
//		glTranslated(0.4, 0.0, 0.4);
//		drawTable(0.6, 0.02, 0.02, 0.3);
//		glPopMatrix();
//		//ground
//
//		glPushMatrix();
//		glScaled(5, 2, -5);
//		glTranslated(0, 0, -1);
//		drawWall(0.02);
//		glPopMatrix();
//		//glDisable(GL_LIGHTING);	// Disable lighting 
//
//		//glColor3f(0.7, 0.7, 0.7);	// Dim the ground texture a bit
//
//		//glEnable(GL_TEXTURE_2D);	// Enable 2D texturing
//
//		//glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture
//
//		//glPushMatrix();
//		//glBegin(GL_QUADS);
//		//glNormal3f(0, 1, 0);	// Set quad normal direction.
//		//glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
//		//glVertex3f(-20, 0, -20);
//		//glTexCoord2f(5, 0);
//		//glVertex3f(20, 0, -20);
//		//glTexCoord2f(5, 5);
//		//glVertex3f(20, 0, 20);
//		//glTexCoord2f(0, 5);
//		//glVertex3f(-20, 0, 20);
//		//glEnd();
//		//glPopMatrix();
//
//		////glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.
//
//		//glColor3f(0.7, 0.7, 0.7);
//
//		//
//
//
//		//left wall
//		glPushMatrix();
//		glColor3f(x / 255.0, y / 255.0, z / 255.0);
//		glRotated(90, 0, 0, 1.0);
//		glScaled(1, 2, 5);
//		drawWall(0.02);
//		glPopMatrix();
//		glColor3f(0.7, 0.7, 0.7);
//		//
//		//front wall
//
//		glPushMatrix();
//		glRotated(-90, 1.0, 0.0, 0.0);
//		glScaled(5, 2, 1);
//		glColor3f(x / 255.0, y / 255.0, z / 255.0);
//
//		drawWall(0.02);
//		glPopMatrix();
//		glColor3f(0.7, 0.7, 0.7);
//
//		//
//		//right wall
//
//		glPushMatrix();
//		glTranslated(5, 0, 0);
//		glRotated(90, 0, 0, 1.0);
//		glScaled(1, 2, 5);
//		glColor3f(x / 255.0, y / 255.0, z / 255.0);
//		drawWall(0.02);
//		glPopMatrix();
//		glColor3f(0.7, 0.7, 0.7);
//
//		//
//		//back wall
//
//
//		glPushMatrix();
//		glTranslated(0, 0, 5);
//		glRotated(-90, 1, 0, 0);
//		glScaled(5, 2, 1);
//		glColor3f(x / 255.0, y / 255.0, z / 255.0);
//
//		drawWall(0.02);
//		glPopMatrix();
//		//
//		glColor3f(0.7, 0.7, 0.7);
//		// ceil wall
//		glPushMatrix();
//		glTranslated(0, 1, 0);
//		glScaled(5, 1, 5);
//		drawWall(0.02);
//		glPopMatrix();
//		// player
//
//		glPopMatrix();
//		
//
//		glPushMatrix();
//		glTranslated(chairx, chairy, chairz);
//		drawChair(chairAngle);
//		glPopMatrix();
//
//		glPushMatrix();
//		glTranslated(chair2x, chair2y, chair2z);
//		drawChair(chair2Angle);
//		glPopMatrix();
//
//		drawCeilLamp();
//		drawFloorLamp();
//		drawPendlum();
//		glPushMatrix();
//		glTranslated(sofa1x, sofa1y, sofa1z);
//		drawSofa(sofa1Angle);
//		glPopMatrix();
//		glPushMatrix();
//		glTranslated(sofa2x, sofa2y, sofa2z);
//		drawSofa(sofa2Angle);
//		glPopMatrix();
//		drawFan();
//		drawGoal();
//		drawComod();
//		glPushMatrix();
//		glColor3f(0.8, 0, 0);
//		drawPlayer();
//		glColor3f(0.7, 0.7, 0.7);
//		glPopMatrix();
//	}
//	
//	glFlush();
//}
//void KeyboardDown(unsigned char key, int x, int y) {
//	switch (key) {
//	case ' ':
//		hold = false;
//		break;
//	case 'r':
//		rotated = false;
//		break;
//	}
//
//}
//
//void Keyboard(unsigned char key, int x1, int y1) {
//	float d = 0.05;
//	
//	switch (key) {
//	case 'w':
//		camera.moveY(d);
//		break;
//	case 's':
//		camera.moveY(-d);
//		break;
//	case 'a':
//		camera.moveX(d);
//		break;
//	case 'd':
//		camera.moveX(-d);
//		break;
//	case 'q':
//		camera.moveZ(d);
//		break;
//	case 'e':
//		camera.moveZ(-d);
//		break;
//	case 'i':
//		if (dir == "left") {
//			if (playerz < 4.8)
//				playerz += 0.1;
//		}
//		else if (dir == "right") {
//			if (playerz > 0.1)
//				playerz -= 0.1;
//		}
//		else if (dir == "back") {
//			if (playerx < 4.8)
//				playerx += 0.1;
//		}
//		else {
//			if (playerx > 0.1) //&& !collideWithObjects(playerx-0.1,playerz)
//				playerx -= 0.1;
//		}
//		setCameraBehind();
//		break;
//	case 'k':
//		if (dir == "front") {
//			dir = "back";
//		
//		}
//		else if (dir == "back") {
//			dir = "front";
//			
//		}
//		else if (dir == "right") {
//			dir = "left";
//			
//		}
//		else if (dir == "left") {
//			dir = "right";
//			
//		}
//		setCameraBehind();
//		break;
//	case 'j':
//		if (dir == "front") {
//			dir = "left";
//			
//		}
//		else if (dir == "right") {
//			dir = "front";
//		}
//		else if (dir == "left") {
//			dir = "back";
//		}
//		else if (dir == "back") {
//			dir = "right";
//		}
//		setCameraBehind();
//		break;
//	case 'l':
//		if (dir == "front") {
//			dir = "right";
//		}
//		else if (dir == "back") {
//			dir = "left";
//		}
//		else if (dir == "right") {
//			dir = "back";
//		}
//		else if (dir == "left") {
//			dir = "front";
//		}
//		setCameraBehind();
//		break;
//	case 't': //top
//
//		camera.eye.x = 1.575204;
//		camera.eye.y = 1;
//		camera.eye.z = 1.540765;
//		camera.center.x = 1.010193;
//		camera.center.y = 0.168120;
//		camera.center.z = 1.546742;
//		camera.up.x = -0.825016;
//		camera.up.y = 0.565042;
//		camera.up.z = 0.008728;
//		break;
//	case 'y'://side view
//
//		camera.eye.x = 2.403903;
//		camera.eye.y = 0.583943;
//		camera.eye.z = 0.124015;
//		camera.center.x = 2.409233;
//		camera.center.y = 0.303346;
//		camera.center.z = 1.083826;
//		camera.up.x = 0.000000;
//		camera.up.y = 1.000000;
//		camera.up.z = 0.000000;
//		break;
//	case 'u': //front view
//		camera.eye.x = 0.190825;
//		camera.eye.y = 0.606377;
//		camera.eye.z = 2.460068;
//		camera.center.x = 1.154089;
//		camera.center.y = 0.338108;
//		camera.center.z = 2.447667;
//		camera.up.x = 0.000000;
//		camera.up.y = 1.000000;
//		camera.up.z = 0.000000;
//		break;
//	case ' ':
//		hold = true;
//		break;
//	case 'r':
//		rotated = true;
//		break;
//	case 'c':
//		x = rand() % 255 +1;
//		y = rand() % 255+1;
//		z = rand() % 255+1;
//		break;
//	case GLUT_KEY_ESCAPE:
//		exit(EXIT_SUCCESS);
//	}
//
//	glutPostRedisplay();
//}
//void Special(int key, int x, int y) {
//	float a = 1.0;
//
//	switch (key) {
//	case GLUT_KEY_UP:
//		camera.rotateX(a);
//		break;
//	case GLUT_KEY_DOWN:
//		camera.rotateX(-a);
//		break;
//	case GLUT_KEY_LEFT:
//		camera.rotateY(a);
//		break;
//	case GLUT_KEY_RIGHT:
//		camera.rotateY(-a);
//		break;
//	}
//
//	glutPostRedisplay();
//}
//
//void main(int argc, char** argv) {
//	glutInit(&argc, argv);
//
//	glutInitWindowSize(800, 500);
//	glutInitWindowPosition(150, 50);
//
//	glutCreateWindow("Lab 5");
//	glutDisplayFunc(Display);
//	glutKeyboardFunc(Keyboard);
//	glutKeyboardUpFunc(KeyboardDown);
//	glutSpecialFunc(Special);
//
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//	glEnable(GL_LIGHT1);
//	glEnable(GL_NORMALIZE);
//	glEnable(GL_COLOR_MATERIAL);
//	glutTimerFunc(0, Timer, 0);
//	glutTimerFunc(0, Timer2, 0);
//	glShadeModel(GL_SMOOTH);
//	tex_ground.Load("Textures/ground.bmp");
//
//	glutMainLoop();
//}
