#include <string>
#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <math.h>
#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
#define DEG2RAD(a) (a * 0.0174532925)



bool level1 = true;
bool level2 = false;
bool winLevel1 = false;
bool loseGame = false;
bool light = true;
bool played[7] = { false,false,false,false,false,false,false };
int life = 3;
int level = 1;
int timer = 50;
int score = 0;
bool backward = false;
bool forward = true;
char* direction = "front";
int WIDTH = 1280;
int HEIGHT = 720;
bool keystates[256];
bool camera3rd = true;
bool camera1st = false;
void setCameraPosition();
void InitLightSource();
void* currentfont;
void drawstring(float x, float y, float z, const char* string);
int Score();
int ringChecks[7] = { 0,0,0,0,0,0,0 };
//methods

bool collided = false;
GLTexture tex_hazoum;
//methods 
GLuint tex;
GLuint sandGround;
//GLuint tex;
GLuint texTire;
GLuint carTexture;
GLuint glassTexture;
GLuint tex2;
GLuint tex3;

char title[] = "3D Model Loader Sample";
// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 100;


void setfont(void* font) {
	currentfont = font;
}

class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	//================================================================================================//
	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
	//================================================================================================//
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};

Vector Eye(20, 5, 20);
Vector At(0, 0, 0);
Vector Up(0, 1, 0);

int cameraZoom = 0;



class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f& v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f& v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

Vector3f getPerpendicular(Vector3f dir);
float CheckCollide(int index);


class plane3f {
public:
	float x, y, z, t;

	plane3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _t = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
		t = _t;
	}

	plane3f operator+(plane3f& v) {
		return plane3f(x + v.x, y + v.y, z + v.z, t + v.t);
	}

	plane3f operator-(plane3f& v) {
		return plane3f(x - v.x, y - v.y, z - v.z, t - v.t);
	}

	plane3f operator*(float n) {
		return plane3f(x * n, y * n, z * n, t * n);
	}

	plane3f operator/(float n) {
		return plane3f(x / n, y / n, z / n, t / n);
	}

	plane3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	plane3f cross(plane3f v) {
		return plane3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};
Vector3f position(16, 0, 14);  //16,0,14
class Car {

public:
	Vector3f position, direction, perpendicular, size;


	char* TireDirection = "";
	double theta = -1;
	double angle = 180;
	float carHeight = 2;
	float carWidth = 3.5;
	float carLength = 6;

	Car(Vector3f Position) {
		position = Position;
		direction = Vector3f(cos(DEG2RAD(angle)), 0, -sin(DEG2RAD(angle)));
		perpendicular = Vector3f(sin(DEG2RAD(angle)), 0, cos(DEG2RAD(angle)));
		size = Vector3f(carLength, carHeight, carWidth);
	}

	void DrawCar() {
		glPushMatrix();

		//glColor3f(1, 0, 0);

		if (CheckCollide(-1) != -1) {
			position = position.operator-(direction.operator*(0.5));
		}

		UpdateDir();
		glTranslated(position.x, position.y, position.z);
		glTranslated(0, size.y / 2 + 1, 0);
		glRotated(angle, 0, 1, 0);

		//carBody
		glPushMatrix();
		glScaled(size.x, size.y, size.z);
		glPushMatrix();
		GLUquadricObj* cube;
		cube = gluNewQuadric();
		glBindTexture(GL_TEXTURE_2D, carTexture);
		gluQuadricTexture(cube, true);
		gluQuadricNormals(cube, GL_SMOOTH);
		glTranslated(0, 0.5, 0);
		glRotated(45, 0, 1, 0);
		glRotated(90, 1, 0, 0);
		gluCylinder(cube, 0.7, 0.7, 1, 4, 4);
		gluDeleteQuadric(cube);
		glPopMatrix();

		glPushMatrix();
		GLUquadricObj* cube2;
		cube2 = gluNewQuadric();
		glBindTexture(GL_TEXTURE_2D, carTexture);
		gluQuadricTexture(cube2, true);
		gluQuadricNormals(cube2, GL_SMOOTH);
		glTranslated(0, 0, -0.5);
		//glRotated(45, 0, 1, 0);
		glRotated(45, 0, 0, 1);
		gluCylinder(cube2, 0.7, 0.7, 1, 4, 4);
		gluDeleteQuadric(cube2);
		glColor3f(1, 1, 1);

		glPopMatrix();

		//glutSolidCube(1);
		glPopMatrix();

		//// el body el fo22
		glPushMatrix();
		glColor3f(0.9, 0.2, 0.2);
		glTranslated(1, 1.3, 0);
		glRotated(25, 0, 0, 1);
		glScaled(1, 1, 1.4);
		glutSolidCube(2);

		glPopMatrix();

		glPushMatrix();
		glColor3f(0.9, 0.2, 0.2);
		glTranslated(-1, 1.3, 0);
		glRotated(-25, 0, 0, 1);
		glScaled(1, 1, 1.4);
		glutSolidCube(2);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.9, 0.2, 0.2);
		glTranslated(0, 1.6, 0);
		glScaled(1.5, 1, 1.4);
		glutSolidCube(2);
		glPopMatrix();
		// ezaaaaaaaaaaaz texture
		glPushMatrix();
		glColor3f(1, 1, 1);
		GLUquadricObj* glass1;
		glass1 = gluNewQuadric();
		glBindTexture(GL_TEXTURE_2D, glassTexture);
		gluQuadricTexture(glass1, true);
		gluQuadricNormals(glass1, GL_SMOOTH);
		glTranslated(-0.7, 2.2, 0);
		glScaled(0.4, 1, 1);
		glRotated(45, 0, 1, 0);
		glRotated(90, 1, 0, 0);
		gluCylinder(glass1, 2.05, 2.05, 1.5, 4, 4);
		gluDeleteQuadric(glass1);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 1, 1);
		GLUquadricObj* glass2;
		glass2 = gluNewQuadric();
		glBindTexture(GL_TEXTURE_2D, glassTexture);
		gluQuadricTexture(glass2, true);
		gluQuadricNormals(glass2, GL_SMOOTH);
		glTranslated(0.7, 2.2, 0);
		glScaled(0.4, 1, 1);
		glRotated(45, 0, 1, 0);
		glRotated(90, 1, 0, 0);
		gluCylinder(glass2, 2.05, 2.05, 1.5, 4, 4);
		gluDeleteQuadric(glass2);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 1, 1);
		GLUquadricObj* glass3;
		glass3 = gluNewQuadric();
		glBindTexture(GL_TEXTURE_2D, glassTexture);
		gluQuadricTexture(glass3, true);
		gluQuadricNormals(glass3, GL_SMOOTH);
		glTranslated(0, 2.5, 0);
		glScaled(1.9, 1, 1);
		glRotated(-45, 0, 1, 0);
		glRotated(90, 1, 0, 0);
		gluCylinder(glass3, 1.2, 1.7, 1.5, 4, 4);
		gluDeleteQuadric(glass3);
		glPopMatrix();


		/// /3agaaallllllllllllllll
		glPushMatrix();
		glColor3f(0.5, 0.5, 0.5);
		glTranslated(2, -1.1, 1.5);
		glRotated(-5, 1, 0, 0);
		glScaled(0.5, 0.6, 0.2);

		GLUquadricObj* Tire0;
		Tire0 = gluNewQuadric();
		glBindTexture(GL_TEXTURE_2D, texTire);
		gluQuadricTexture(Tire0, true);
		gluQuadricNormals(Tire0, GL_SMOOTH);
		gluSphere(Tire0, 1.5, 10, 15);
		gluDeleteQuadric(Tire0);

		glColor3f(1, 0, 0);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.5, 0.5, 0.5);
		glTranslated(2, -1.1, -1.5);
		glRotated(5, 1, 0, 0);
		glScaled(0.5, 0.6, 0.2);

		GLUquadricObj* Tire1;
		Tire1 = gluNewQuadric();
		glBindTexture(GL_TEXTURE_2D, texTire);
		gluQuadricTexture(Tire1, true);
		gluQuadricNormals(Tire1, GL_SMOOTH);
		gluSphere(Tire1, 1.5, 10, 15);
		gluDeleteQuadric(Tire1); glColor3f(1, 0, 0);

		glPopMatrix();

		glPushMatrix();
		glColor3f(0.5, 0.5, 0.5);
		glTranslated(-2, -1.1, 1.5);
		glRotated(-5, 1, 0, 0);
		glScaled(0.5, 0.6, 0.2);
		GLUquadricObj* Tire2;
		Tire2 = gluNewQuadric();
		glBindTexture(GL_TEXTURE_2D, texTire);
		gluQuadricTexture(Tire2, true);
		gluQuadricNormals(Tire2, GL_SMOOTH);
		gluSphere(Tire2, 1.5, 10, 15);
		gluDeleteQuadric(Tire2); glColor3f(1, 0, 0);
		glColor3f(1, 0, 0);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.5, 0.5, 0.5);
		glTranslated(-2, -1.1, -1.5);
		glRotated(-5, 1, 0, 0);
		glScaled(0.5, 0.6, 0.2);
		GLUquadricObj* Tire3;
		Tire3 = gluNewQuadric();
		glBindTexture(GL_TEXTURE_2D, texTire);
		gluQuadricTexture(Tire3, true);
		gluQuadricNormals(Tire3, GL_SMOOTH);
		gluSphere(Tire3, 1.5, 10, 15);
		gluDeleteQuadric(Tire3); glColor3f(1, 0, 0);
		glColor3f(1, 0, 0);
		glPopMatrix();

		//sa2f
		glPushMatrix();
		glDisable(GL_LIGHTING);	// Disable lighting 

		glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

		glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

		glBindTexture(GL_TEXTURE_2D, tex_hazoum.texture[0]);	// Bind the ground texture

		glPushMatrix();
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);	// Set quad normal direction.
		glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
		glVertex3f(-1.5, 2.65, -1.45);
		glTexCoord2f(1, 0);
		glVertex3f(1.5, 2.65, -1.45);
		glTexCoord2f(1, 1);
		glVertex3f(1.5, 2.65, 1.45);
		glTexCoord2f(0, 1);
		glVertex3f(-1.5, 2.65, 1.45);
		glEnd();
		glPopMatrix();

		glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

		glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
		glPopMatrix();


		/// kashaaaafaaat odam foo2
		glPushMatrix();
		glColor3f(0, 0, 1);
		glTranslated(3.1, 0.5, 1.3);
		glRotated(90, 1, 0, 0);
		glRotated(-90, 0, 1, 0);
		glutSolidCone(0.4, 1, 60, 60);
		glColor3f(1, 0, 0);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0, 0, 1);
		glTranslated(3.1, 0.5, 1.3);
		glScaled(0.1, 1, 1);
		glutSolidSphere(0.4, 15, 15);
		glColor3f(1, 0, 0);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0, 0, 1);
		glTranslated(3.1, 0.5, -1.3);
		glRotated(90, 1, 0, 0);
		glRotated(-90, 0, 1, 0);
		glutSolidCone(0.4, 1, 60, 60);
		glColor3f(1, 0, 0);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0, 0, 1);
		glTranslated(3.1, 0.5, -1.3);
		glScaled(0.1, 1, 1);
		glutSolidSphere(0.4, 15, 15);
		glColor3f(1, 0, 0);
		glPopMatrix();

		////////////kashafat odam t7t

		glPushMatrix();
		glColor3f(0.9764, 0.6862, 0.1882);
		glTranslated(3., -0.3, -1.3);
		glScaled(0.1, 0.3, 0.5);
		glutSolidCube(1);
		glColor3f(1, 0, 0);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.9764, 0.6862, 0.1882);
		glTranslated(3., -0.3, 1.3);
		glScaled(0.1, 0.3, 0.5);
		glutSolidCube(1);
		glColor3f(1, 0, 0);
		glPopMatrix();

		////////////kashafat waraaaa
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslated(-3., 0.2, 1.3);
		glScaled(0.1, 1, 0.3);
		glutSolidCube(1);
		glColor3f(1, 0, 0);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslated(-3., 0.2, -1.3);
		glScaled(0.1, 1, 0.3);
		glutSolidCube(1);
		glColor3f(1, 0, 0);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.9764, 0.6862, 0.1882);
		glTranslated(-3., -0.5, 1.3);
		glScaled(0.1, 0.3, 0.3);
		glutSolidCube(1);
		glColor3f(1, 0, 0);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.9764, 0.6862, 0.1882);
		glTranslated(-3., -0.5, -1.3);
		glScaled(0.1, 0.3, 0.3);
		glutSolidCube(1);
		glColor3f(1, 0, 0);
		glPopMatrix();






		glColor3f(0.7, 0.7, 0.7);

		glPopMatrix();
	}
	void Move(float d) {

		if (keystates['w'] || keystates['s']) {

			if (CheckCollide(-1) != -1) {
			}

			else {

				if (keystates['w'] && !keystates['s'])
				{
					forward = true;
					backward = false;

					if (keystates['d'] && !keystates['a'])
						angle += theta;

					else if (keystates['a'] && !keystates['d'])
						angle += theta;

					position = position.operator+(direction.operator*(d));

				}
				else if (keystates['s'] && !keystates['w']) {
					forward = false;
					backward = true;

					if (keystates['d'] && !keystates['a'])
						angle -= theta;

					else if (keystates['a'] && !keystates['d'])
						angle -= theta;

					position = position.operator+(direction.operator*(d));
				}
				else if (keystates['s'] && keystates['w'] && (keystates['d'] || keystates['a'])) {


					if (keystates['d'] && !keystates['a'])
						angle -= theta;

					else if (keystates['a'] && !keystates['d'])
						angle -= theta;

					position = position.operator-(direction.operator*(0.2));
				}

			}
			setCameraPosition();
			InitLightSource();
			int index = -1;
			index = Score();
			if (index != -1) {
				ringChecks[index] = 10;
				
			}

		}

	}
	void UpdateDir() {
		if (keystates['w'] && !keystates['s']) {
			direction = Vector3f(cos(DEG2RAD(angle)), 0, -sin(DEG2RAD(angle)));
		}
		else if (!keystates['w'] && keystates['s']) {

			direction = Vector3f(-cos(DEG2RAD(angle)), 0, sin(DEG2RAD(angle)));
		}
		else if (keystates['w'] && keystates['s'] && (keystates['d'] || keystates['a'])) {
			direction = Vector3f(cos(DEG2RAD(angle)), 0, -sin(DEG2RAD(angle)));

		}
		perpendicular = getPerpendicular(direction);
	}

	void UpdateDir2() {
		direction = Vector3f(cos(DEG2RAD(angle)), 0, -sin(DEG2RAD(angle)));

		perpendicular = getPerpendicular(direction);

	}
	Vector3f* generateCarPoints() {

		Vector3f FaceCenter = position.operator+(direction.operator*(size.x / 2));
		Vector3f FaceLP = FaceCenter.operator-(perpendicular.operator*(size.z / 2));
		Vector3f FaceRP = FaceCenter.operator+(perpendicular.operator*(size.z / 2));

		Vector3f BackCenter = position.operator-(direction.operator*(size.x / 2));
		Vector3f BackLP = BackCenter.operator-(perpendicular.operator*(size.z / 2));
		Vector3f BackRP = BackCenter.operator+(perpendicular.operator*(size.z / 2));

		Vector3f Center = position;
		Vector3f CenterLP = position.operator-(perpendicular.operator*(size.z / 2));
		Vector3f CenterRP = position.operator+(perpendicular.operator*(size.z / 2));

		Vector3f* carpoints = new Vector3f[12]{ Center,CenterLP,CenterRP,FaceCenter ,FaceLP ,FaceRP,BackCenter,BackLP,BackRP };

		return carpoints;

	}


};

Car car = Car(position);



class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = car.position.x - 5 * car.direction.x, float eyeY = 15.0f, float eyeZ = car.position.z - 5 * car.direction.z, float centerX = car.position.x + 5 * car.direction.x, float centerY = 5.0f, float centerZ = car.position.z + 5 * car.direction.z, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;

	}
	void backtoDefault() {
		eye = Vector3f(7.0f, 15.0f, 5.0f);
		center = Vector3f(3.0f, 10.0f, 3.0f);
		up = Vector3f(0.0f, 1.0f, 0.0f);
		camera3rd = false;
		camera1st = false;
	}
	void lookAtTop() {
		eye = Vector3f(4.0f, 8.0f, 6.0f);
		center = Vector3f(3.9f, 0.0f, 6.0f);
		up = Vector3f(0.0f, 1.0f, 0.0f);

	}
	void lookAtSide() {
		eye = Vector3f(4.0f, 3.0f, 0.0f);
		center = Vector3f(4.0f, 3.0f, 1.0f);
		up = Vector3f(0.0f, 2.0f, 0.0f);

	}
	void lookAtFront() {
		eye = Vector3f(7.9, 3.0f, 4.0f);
		center = Vector3f(7.0f, 3.0f, 4.0f);
		up = Vector3f(0.0f, 1.0f, 0.0f);
	}
	void lookAtSide2() {
		eye = Vector3f(4.0f, 3.0f, 11.9f);
		center = Vector3f(4.0f, 3.0f, 10.90f);
		up = Vector3f(0.0f, 2.0f, 0.0f);

	}
	boolean isAtLeftSide() {
		if ((eye.x - center.x) < 0.5 && center.z - eye.z > 0.5) {

			return true;
		}
		return false;
	}
	boolean isAtRightSide() {
		if ((eye.x - center.x) < 0.5 && eye.z - center.z > 0.5) {

			return true;
		}
		return false;
	}
	boolean isAtUpSide() {
		if ((eye.z - center.z) < 0.5 && (eye.x - center.x) > 0.5) {
			return true;
		}
		return false;
	}
	boolean isAtDownSide() {
		if ((eye.z - center.z) < 0.5 && (center.x - eye.x) > 0.5) {
			return true;
		}
		return false;
	}
	boolean iscameraTop() {
		if (eye.x - center.x < 1 && eye.y - center.y>1 && eye.z == center.z) {
			return true;
		}
		return false;
	}
	void PlayerlookingAtFront() {
		eye = Vector3f(12.0f, eye.y, eye.z);
		center = Vector3f(-8.0f, -3.5f, center.z);
		up = Vector3f(up.x, up.y, up.z);
	}
	void look() {

		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};

Camera camera;


//-------------------------------Car Class ----------------------------------




class Cone {

public:
	Vector3f position, direction, perpendicular, size;


	char* TireDirection = "";
	double theta = -1;
	double angle = 0;

	Cone(Vector3f Position, Vector3f Size) {
		position = Position;
		direction = Vector3f(cos(DEG2RAD(angle)), 0, -sin(DEG2RAD(angle)));
		perpendicular = Vector3f(sin(DEG2RAD(angle)), 0, cos(DEG2RAD(angle)));
		size = Size;
	}

	void DrawCone() {
		glPushMatrix();

		//glColor3f(1, 0, 0);


		glTranslated(position.x, position.y, position.z);
		glTranslated(0, size.y / 2, 0);
		glRotated(angle, 0, 1, 0);


		glPushMatrix();

		glRotated(-90, 1, 0, 0);
		glScaled(size.x, size.y, size.z);
		glPushMatrix();

		GLUquadricObj* qobj2;
		qobj2 = gluNewQuadric();
		glBindTexture(GL_TEXTURE_2D, tex2);
		gluQuadricTexture(qobj2, true);
		gluQuadricNormals(qobj2, GL_SMOOTH);
		gluCylinder(qobj2, 1, 0.1, 2, 15, 15);
		gluDeleteQuadric(qobj2);
		glPopMatrix();

		glPopMatrix();




		glColor3f(0.7, 0.7, 0.7);

		glPopMatrix();
	}

	Vector3f* generateConePoints() {

		Vector3f FaceCenter = position.operator+(direction.operator*(size.x / 2));
		Vector3f FaceLP = FaceCenter.operator-(perpendicular.operator*(size.z / 2));
		Vector3f FaceRP = FaceCenter.operator+(perpendicular.operator*(size.z / 2));

		Vector3f BackCenter = position.operator-(direction.operator*(size.x / 2));
		Vector3f BackLP = BackCenter.operator-(perpendicular.operator*(size.z / 2));
		Vector3f BackRP = BackCenter.operator+(perpendicular.operator*(size.z / 2));

		Vector3f Center = position;
		Vector3f CenterLP = position.operator-(perpendicular.operator*(size.z / 2));
		Vector3f CenterRP = position.operator+(perpendicular.operator*(size.z / 2));

		Vector3f* Conepoints = new Vector3f[12]{ Center,CenterLP,CenterRP,FaceCenter ,FaceLP ,FaceRP,BackCenter,BackLP,BackRP };

		return Conepoints;

	}


};
////////////////////////////////////////////////////////////////////////////
Vector3f Cone1position(-5, 0, -8);
Vector3f Cone1size(2, 1, 2);
Cone Cone1 = Cone(Cone1position, Cone1size);

Vector3f Cone2position(2, 0, -8);
Vector3f Cone2size(2, 1, 2);
Cone Cone2 = Cone(Cone2position, Cone2size);

Vector3f Cone3position(10, 0, -8);
Vector3f Cone3size(2, 1, 2);
Cone Cone3 = Cone(Cone3position, Cone3size);

Vector3f Cone4position(18, 0, -8);
Vector3f Cone4size(2, 1, 2);
Cone Cone4 = Cone(Cone4position, Cone4size);
///////////////////////////////////////////////////////////////////////////////////////

Vector3f Cone5position(18, 0, -18);
Vector3f Cone5size(2, 1, 2);
Cone Cone5 = Cone(Cone5position, Cone5size);

Vector3f Cone6position(10, 0, -18);
Vector3f Cone6size(2, 1, 2);
Cone Cone6 = Cone(Cone6position, Cone6size);

Vector3f Cone7position(2, 0, -18);
Vector3f Cone7size(2, 1, 2);
Cone Cone7 = Cone(Cone7position, Cone7size);

Vector3f Cone8position(-6, 0, -18);
Vector3f Cone8size(2, 1, 2);
Cone Cone8 = Cone(Cone8position, Cone8size);

Vector3f Cone9position(-14, 0, -18);
Vector3f Cone9size(2, 1, 2);
Cone Cone9 = Cone(Cone9position, Cone9size);
////////////////////////////////////////////////////////////////////////////////////


Vector3f Cone11position(-18, 0, -8);
Vector3f Cone11size(2, 1, 2);
Cone Cone11 = Cone(Cone11position, Cone11size);

////////////////////////////////////////////////////////////////////////////////////
Vector3f Cone13position(-6, 0, -2);
Vector3f Cone13size(2, 1, 2);
Cone Cone13 = Cone(Cone13position, Cone13size);

Vector3f Cone14position(-6, 0, 4);
Vector3f Cone14size(2, 1, 2);
Cone Cone14 = Cone(Cone14position, Cone14size);

Vector3f Cone18position(-6, 0, 10);
Vector3f Cone18size(2, 1, 2);
Cone Cone18 = Cone(Cone18position, Cone18size);
/////////////////////////////////////////////////////////////////////////////////////

Vector3f Cone10position(-18, 0, -14);
Vector3f Cone10size(2, 1, 2);
Cone Cone10 = Cone(Cone10position, Cone10size);

Vector3f Cone12position(-18, 0, -2);
Vector3f Cone12size(2, 1, 2);
Cone Cone12 = Cone(Cone12position, Cone12size);

Vector3f Cone15position(-18, 0, 4);
Vector3f Cone15size(2, 1, 2);
Cone Cone15 = Cone(Cone15position, Cone15size);

Vector3f Cone16position(-18, 0, 10);
Vector3f Cone16size(2, 1, 2);
Cone Cone16 = Cone(Cone16position, Cone16size);

Vector3f Cone17position(-18, 0, 16);
Vector3f Cone17size(2, 1, 2);
Cone Cone17 = Cone(Cone17position, Cone17size);
////////////////////////////////////////////////////////////////////////////////
Vector3f Cone19position(-14, 0, 18);
Vector3f Cone19size(2, 1, 2);
Cone Cone19 = Cone(Cone19position, Cone19size);

Vector3f Cone20position(-6, 0, 18);
Vector3f Cone20size(2, 1, 2);
Cone Cone20 = Cone(Cone20position, Cone20size);

Vector3f Cone21position(2, 0, 18);
Vector3f Cone21size(2, 1, 2);
Cone Cone21 = Cone(Cone21position, Cone21size);


Vector3f Cone25position(8, 0, 18);
Vector3f Cone25size(2, 1, 2);
Cone Cone25 = Cone(Cone25position, Cone25size);

Vector3f Cone26position(8, 0, 10);
Vector3f Cone26size(2, 1, 2);
Cone Cone26 = Cone(Cone26position, Cone26size);





////////////////////////////////////////////////////////////////////////////////
Vector3f Cone22position(2, 0, 10);
Vector3f Cone22size(2, 1, 2);
Cone Cone22 = Cone(Cone22position, Cone22size);

//////////////////////////////level2Cone/////////////

Vector3f Cone1Level2position(6, 0, 19);
Vector3f Cone1Level2size(2, 1, 2);
Cone cone1Level2 = Cone(Cone1Level2position, Cone1Level2size);


Vector3f Cone2level2position(17, 0, 19);
Vector3f Cone2level2size(2, 1, 2);
Cone cone2Level2 = Cone(Cone2level2position, Cone2level2size);

////////////////////////////

Vector3f Cone3Level2position(6, 0, 16);
Vector3f Cone3Level2size(2, 1, 2);
Cone cone3Level2 = Cone(Cone3Level2position, Cone3Level2size);


Vector3f Cone4level2position(17, 0, 16);
Vector3f Cone4level2size(2, 1, 2);
Cone cone4Level2 = Cone(Cone4level2position, Cone4level2size);


////////////////////////////////

Vector3f Cone5Level2position(4, 0, 13);
Vector3f Cone5Level2size(2, 1, 2);
Cone cone5Level2 = Cone(Cone5Level2position, Cone5Level2size);


Vector3f Cone6level2position(15, 0, 13);
Vector3f Cone6level2size(2, 1, 2);
Cone cone6Level2 = Cone(Cone6level2position, Cone6level2size);


/////////////////////////////


Vector3f Cone7Level2position(2, 0, 10);
Vector3f Cone7Level2size(2, 1, 2);
Cone cone7Level2 = Cone(Cone7Level2position, Cone7Level2size);


Vector3f Cone8level2position(13, 0, 10);
Vector3f Cone8level2size(2, 1, 2);
Cone cone8Level2 = Cone(Cone8level2position, Cone8level2size);


//////////////////////////

Vector3f Cone9Level2position(1, 0, 7);
Vector3f Cone9Level2size(2, 1, 2);
Cone cone9Level2 = Cone(Cone9Level2position, Cone9Level2size);


Vector3f Cone10level2position(12, 0, 7);
Vector3f Cone10level2size(2, 1, 2);
Cone cone10Level2 = Cone(Cone10level2position, Cone10level2size);

/////////////////////////

Vector3f Cone11Level2position(3, 0, 4);
Vector3f Cone11Level2size(2, 1, 2);
Cone cone11Level2 = Cone(Cone11Level2position, Cone11Level2size);


Vector3f Cone12level2position(14, 0, 4);
Vector3f Cone12level2size(2, 1, 2);
Cone cone12Level2 = Cone(Cone12level2position, Cone12level2size);

/////////////////////////////

Vector3f Cone13Level2position(5, 0, 1);
Vector3f Cone13Level2size(2, 1, 2);
Cone cone13Level2 = Cone(Cone13Level2position, Cone13Level2size);


Vector3f Cone14level2position(16, 0, 1);
Vector3f Cone14level2size(2, 1, 2);
Cone cone14Level2 = Cone(Cone14level2position, Cone14level2size);


/////////////////////////
Vector3f Cone15Level2position(6, 0, -2);
Vector3f Cone15Level2size(2, 1, 2);
Cone cone15Level2 = Cone(Cone15Level2position, Cone15Level2size);


Vector3f Cone16level2position(18, 0, -2);
Vector3f Cone16level2size(2, 1, 2);
Cone cone16Level2 = Cone(Cone16level2position, Cone16level2size);


///////////////////////////////////////
Vector3f Cone17Level2position(4, 0, -5);
Vector3f Cone17Level2size(2, 1, 2);
Cone cone17Level2 = Cone(Cone17Level2position, Cone17Level2size);


Vector3f Cone18level2position(17, 0, -5);
Vector3f Cone18level2size(2, 1, 2);
Cone cone18Level2 = Cone(Cone18level2position, Cone18level2size);


//////////////////////
Vector3f Cone19Level2position(2, 0, -8);
Vector3f Cone19Level2size(2, 1, 2);
Cone cone19Level2 = Cone(Cone19Level2position, Cone19Level2size);


Vector3f Cone20level2position(16, 0, -8);
Vector3f Cone20level2size(2, 1, 2);
Cone cone20Level2 = Cone(Cone20level2position, Cone20level2size);


////////////////////
Vector3f Cone21level2position(13, 0, -12);
Vector3f Cone21level2size(2, 1, 2);
Cone cone21Level2 = Cone(Cone21level2position, Cone21level2size);

///////////////////////////

Vector3f Cone22level2position(10, 0, -15);
Vector3f Cone22level2size(2, 1, 2);
Cone cone22Level2 = Cone(Cone22level2position, Cone22level2size);

/////////////////////////////


Vector3f Cone23level2position(7, 0, -18);
Vector3f Cone23level2size(2, 1, 2);
Cone cone23Level2 = Cone(Cone23level2position, Cone23level2size);

//////////////////////////////


Vector3f Cone24level2position(2, 0, -18);
Vector3f Cone24level2size(2, 1, 2);
Cone cone24Level2 = Cone(Cone24level2position, Cone24level2size);

////////////////////

Vector3f Cone25level2position(-3, 0, -18);
Vector3f Cone25level2size(2, 1, 2);
Cone cone25Level2 = Cone(Cone25level2position, Cone25level2size);

////////////////////////
Vector3f Cone26level2position(-8, 0, -17);
Vector3f Cone26level2size(2, 1, 2);
Cone cone26Level2 = Cone(Cone26level2position, Cone26level2size);

Vector3f Cone27level2position(-3, 0, -8);
Vector3f Cone27level2size(2, 1, 2);
Cone cone27Level2 = Cone(Cone27level2position, Cone27level2size);


/////////////////////////
Vector3f Cone28level2position(-12, 0, -14);
Vector3f Cone28level2size(2, 1, 2);
Cone cone28Level2 = Cone(Cone28level2position, Cone28level2size);

Vector3f Cone29level2position(-5, 0, -5);
Vector3f Cone29level2size(2, 1, 2);
Cone cone29Level2 = Cone(Cone29level2position, Cone29level2size);

///////////////////////////////////////////////////////////////////
Vector3f Cone30level2position(-15, 0, -10);
Vector3f Cone30level2size(2, 1, 2);
Cone cone30Level2 = Cone(Cone30level2position, Cone30level2size);

Vector3f Cone31level2position(-6, 0, -1);
Vector3f Cone31level2size(2, 1, 2);
Cone cone31Level2 = Cone(Cone31level2position, Cone31level2size);

/////////////////////////
Vector3f Cone32level2position(-17, 0, -6);
Vector3f Cone32level2size(2, 1, 2);
Cone cone32Level2 = Cone(Cone32level2position, Cone32level2size);

Vector3f Cone33level2position(-6, 0, 3);
Vector3f Cone33level2size(2, 1, 2);
Cone cone33Level2 = Cone(Cone33level2position, Cone33level2size);

/////////////////////////
Vector3f Cone34level2position(-18, 0, -2);
Vector3f Cone34level2size(2, 1, 2);
Cone cone34Level2 = Cone(Cone34level2position, Cone34level2size);

Vector3f Cone35level2position(-18, 0, 2);
Vector3f Cone35level2size(2, 1, 2);
Cone cone35Level2 = Cone(Cone35level2position, Cone35level2size);


///////////////////////////
Vector3f Cone36level2position(-16, 0, 6);
Vector3f Cone36level2size(2, 1, 2);
Cone cone36Level2 = Cone(Cone36level2position, Cone36level2size);

Vector3f Cone37level2position(-4, 0, 6);
Vector3f Cone37level2size(2, 1, 2);
Cone cone37Level2 = Cone(Cone37level2position, Cone37level2size);


/////////////////////////////levelCone2//////////////


////////////////////////////////////Ring Class//////////////////////////////////
class Ring {

public:
	Vector3f position, direction, perpendicular, size;


	char* TireDirection = "";
	double theta = -1;
	double angle = 0;

	Ring(Vector3f Position, Vector3f Size) {
		position = Position;
		direction = Vector3f(cos(DEG2RAD(angle)), 0, -sin(DEG2RAD(angle)));
		perpendicular = Vector3f(sin(DEG2RAD(angle)), 0, cos(DEG2RAD(angle)));
		size = Size;
	}

	void DrawRing() {
		glPushMatrix();

		//glColor3f(1, 0, 0);


		glTranslated(position.x, position.y, position.z);
		glTranslated(0, size.y / 2, 0);
		glRotated(angle, 0, 1, 0);


		glPushMatrix();
		glRotated(-90, 1, 0, 0);
		glScaled(size.x, size.y, size.z);
		GLUquadricObj* qobj3;
		qobj3 = gluNewQuadric();
		glBindTexture(GL_TEXTURE_2D, tex3);
		gluQuadricTexture(qobj3, true);
		gluQuadricNormals(qobj3, GL_SMOOTH);
		glRotated(90, 1, 0, 0);
		glRotated(90, 0, 1, 0);
		gluDisk(qobj3, 4.5, 5, 15, 15);

		gluDeleteQuadric(qobj3);

		glPopMatrix();




		glColor3f(0.7, 0.7, 0.7);

		glPopMatrix();
	}

	Vector3f* generateRingPoints() {

		Vector3f FaceCenter = position.operator+(direction.operator*(size.x / 2));
		Vector3f FaceLP = FaceCenter.operator-(perpendicular.operator*(size.z / 2));
		Vector3f FaceRP = FaceCenter.operator+(perpendicular.operator*(size.z / 2));

		Vector3f BackCenter = position.operator-(direction.operator*(size.x / 2));
		Vector3f BackLP = BackCenter.operator-(perpendicular.operator*(size.z / 2));
		Vector3f BackRP = BackCenter.operator+(perpendicular.operator*(size.z / 2));

		Vector3f Center = position;
		Vector3f CenterLP = position.operator-(perpendicular.operator*(size.z / 2));
		Vector3f CenterRP = position.operator+(perpendicular.operator*(size.z / 2));

		Vector3f* Ringpoints = new Vector3f[12]{ Center,CenterLP,CenterRP,FaceCenter ,FaceLP ,FaceRP,BackCenter,BackLP,BackRP };

		return Ringpoints;

	}


};
Vector3f Ringposition(2, 1, 14);
Vector3f Ringsize(1, 1, 2);
Ring ring = Ring(Ringposition, Ringsize);

Vector3f Ring2position(-10, 1, 14);
Vector3f Ring2size(3, 1, 2);
Ring ring2 = Ring(Ring2position, Ring2size);

Vector3f Ring3position(-12, 1, 0);
Vector3f Ring3size(1, 1, 2);
Ring ring3 = Ring(Ring3position, Ring3size);

Vector3f Ring4position(-12, 1, -12);
Vector3f Ring4size(1, 1, 2);
Ring ring4 = Ring(Ring4position, Ring4size);

Vector3f Ring5position(8, 1, -14);
Vector3f Ring5size(1, 1, 2);
Ring ring5 = Ring(Ring5position, Ring5size);

Vector3f Ring1Level2position(9, 1, 14);
Vector3f Ring1Level2size(1, 1, 2);
Ring ring1Level2 = Ring(Ring1Level2position, Ring1Level2size);

Vector3f Ring2Level2position(8, 1, 5);
Vector3f Ring2Level2size(1, 1, 2);
Ring ring2Level2 = Ring(Ring2Level2position, Ring2Level2size);

Vector3f Ring3Level2position(11, 1, -3);
Vector3f Ring3Level2size(1, 1, 2);
Ring ring3Level2 = Ring(Ring3Level2position, Ring3Level2size);

Vector3f Ring4Level2position(7, 1, -10);
Vector3f Ring4Level2size(1, 1, 2);
Ring ring4Level2 = Ring(Ring4Level2position, Ring4Level2size);

Vector3f Ring5Level2position(0, 1, -15);
Vector3f Ring5Level2size(1, 1, 2);
Ring ring5Level2 = Ring(Ring5Level2position, Ring5Level2size);


Vector3f Ring6Level2position(-8, 1, -10);
Vector3f Ring6Level2size(1, 1, 2);
Ring ring6Level2 = Ring(Ring6Level2position, Ring6Level2size);



Vector3f Ring7Level2position(-12, 1, 0);
Vector3f Ring7Level2size(1, 1, 2);
Ring ring7Level2 = Ring(Ring7Level2position, Ring7Level2size);



Vector3f Ring20position(8, 0, 14);
Vector3f Ring20size(1, 1, 2);
Ring ring20 = Ring(Ring20position, Ring20size);

///////////////////////////////////////////////////////////////////////////////

void drawLabel() {

	glPushMatrix();

	glTranslated(-25, 12, 0);
	glScaled(0.1, 2, 2);
	glutSolidCube(5);
	glPopMatrix();

	/*glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0, 4, 0);
	glScaled(0.2, 1.7, 0.2);
	glutSolidCube(5);
	glPopMatrix();
	*/




	glColor3f(0.7, 0.7, 0.7);
}
void drawLabelLevel2() {

	glPushMatrix();
	glTranslated(0, 18, -25);
	glScaled(2, 2, 0.1);
	glutSolidCube(5);
	glPopMatrix();






	glColor3f(0.7, 0.7, 0.7);
}

//void Score() {
//	float x1 = car.generateCarPoints()[3].x;
//	float x2 = car.generateCarPoints()[6].x;
//	float z1 = car.generateCarPoints()[3].z;
//	float z2 = car.generateCarPoints()[6].z;
//	float xmin = x1;
//	float xmax = 0;
//	float zmin = z1;
//	float zmax = 0;
//	if (x2 < xmin) {
//		xmin = x2;
//		xmax = x1;
//	}
//	else {
//		xmin = x1;
//		xmax = x2;
//	}
//	if (z2 < zmin) {
//		zmin = z2;
//		zmax = z1;
//	}
//	else {
//		zmin = z1;
//		zmax = z2;
//	}
//
//	if (xmin<=ring.position.x && xmax >= ring.position.x && zmin <= ring.position.z && zmax >= ring.position.z) {
//		score += 10;
//	}
//}
Vector3f* generatePoints(Vector3f position, Vector3f size, Vector3f dir) {
	Vector3f perpendicular = getPerpendicular(dir);

	Vector3f FaceCenter = position.operator+(dir.operator*(size.x / 2));
	Vector3f FaceLP = FaceCenter.operator-(perpendicular.operator*(size.z / 2));
	Vector3f FaceRP = FaceCenter.operator+(perpendicular.operator*(size.z / 2));

	Vector3f BackCenter = position.operator-(dir.operator*(size.x / 2));
	Vector3f BackLP = BackCenter.operator-(perpendicular.operator*(size.z / 2));
	Vector3f BackRP = BackCenter.operator+(perpendicular.operator*(size.z / 2));

	Vector3f Center = position;
	Vector3f CenterLP = position.operator-(perpendicular.operator*(size.z / 2));
	Vector3f CenterRP = position.operator+(perpendicular.operator*(size.z / 2));

	Vector3f* points = new Vector3f[12]{ Center,CenterLP,CenterRP,FaceCenter ,FaceLP ,FaceRP,BackCenter,BackLP,BackRP };

	return points;

}

int Score() {
	if (level1 == true) {



		//array of positions for all objects

		Vector3f positions[] = { ring.position,ring2.position,ring3.position,ring4.position ,ring5.position,ring20.position };
		Vector3f sizes[] = { ring.size,ring2.size,ring3.size,ring4.size,ring5.size,ring20.size };
		Vector3f directions[] = { ring.direction,ring2.direction,ring3.direction,ring4.direction,ring5.direction,ring20.direction };


		bool collideX = false;
		bool collideY = false;

		Vector3f* carPoints = car.generateCarPoints();

		int size = 6;
		for (int i = 0; i < size; i++) {


			for (int j = 0; j < 9; j++) {
				if (
					(carPoints[j].x >= positions[i].x - (sizes[i].x / 2)) &&
					(carPoints[j].x <= positions[i].x + (sizes[i].x / 2))
					) {
					collideX = true;
				}
				if (
					(carPoints[j].z >= positions[i].z - (sizes[i].z / 2)) &&
					(carPoints[j].z <= positions[i].z + (sizes[i].z / 2))
					) {
					collideY = true;
				}

				if (collideX && collideY) {
					
					printf("ff");
					return i;
				}
				else {
					collideX = false;
					collideY = false;
				}
			}

			for (int p = 0; p < size; p++) {

				Vector3f* Points = generatePoints(positions[p], sizes[p], directions[p]);
				for (int z = 0; z < 9; z++) {

					if (
						(Points[z].x >= car.position.x - (car.direction.x * car.size.x / 2)) &&
						(Points[z].x <= car.position.x + (car.direction.x * car.size.x / 2))
						) {
						collideX = true;
					}
					if (
						(Points[z].z >= car.position.z - (car.direction.z * car.size.z / 2)) &&
						(Points[z].z <= car.position.z + (car.direction.z * car.size.z / 2))
						) {
						collideY = true;
					}


					if (collideX && collideY) {
						
						return i;
					}
					else {
						collideX = false;
						collideY = false;
					}

				}
			}

		}
		return -1;
	}
	else if (level2 == true)
	{

		Vector3f positions[] = { ring1Level2.position,ring2Level2.position ,ring3Level2.position,ring4Level2.position,ring5Level2.position,ring6Level2.position,ring7Level2.position };
		Vector3f sizes[] = {     ring1Level2.size,    ring2Level2.size, ring3Level2.size,    ring4Level2.size,    ring5Level2.size,    ring6Level2.size ,   ring7Level2.size };
		Vector3f directions[] = { ring1Level2.direction,ring2Level2.direction,ring3Level2.direction, ring4Level2.direction, ring5Level2.direction, ring6Level2.direction,ring7Level2.direction };


		bool collideX = false;
		bool collideY = false;

		Vector3f* carPoints = car.generateCarPoints();

		int size = 7;
		for (int i = 0; i < size; i++) {


			for (int j = 0; j < 9; j++) {
				if (
					(carPoints[j].x >= positions[i].x - (sizes[i].x / 2)) &&
					(carPoints[j].x <= positions[i].x + (sizes[i].x / 2))
					) {
					collideX = true;
				}
				if (
					(carPoints[j].z >= positions[i].z - (sizes[i].z / 2)) &&
					(carPoints[j].z <= positions[i].z + (sizes[i].z / 2))
					) {
					collideY = true;
				}

				if (collideX && collideY && ringChecks[i] == 0) {
					printf("ff1 :%d \n",i);
					return i;
				}
				else {
					collideX = false;
					collideY = false;
				}
			}

			for (int p = 0; p < size; p++) {

				Vector3f* Points = generatePoints(positions[p], sizes[p], directions[p]);
				for (int z = 0; z < 9; z++) {

					if (
						(Points[z].x >= car.position.x - (car.direction.x * car.size.x / 2)) &&
						(Points[z].x <= car.position.x + (car.direction.x * car.size.x / 2))
						) {
						collideX = true;
					}
					if (
						(Points[z].z >= car.position.z - (car.direction.z * car.size.z / 2)) &&
						(Points[z].z <= car.position.z + (car.direction.z * car.size.z / 2))
						) {
						collideY = true;
					}


					if (collideX && collideY && ringChecks[p]==0 ) {
						printf("ff2: %d \n",i);
						return p;
					}
					else {
						collideX = false;
						collideY = false;
					}

				}
			}

		}
		return -1;
	}
}


///////////////////////////////////////////////////////////////////////////////

void drawstring(float x, float y, float z, const char* string) {
	glRasterPos3f(x, y, z);

	for (const char* c = string; *c != '\0'; c++) {
		glutBitmapCharacter(currentfont, *c);  // Updates the position
	}
}

Vector3f getPerpendicular(Vector3f dir) {
	return Vector3f(-dir.z, dir.y, dir.x);
}


float CheckCollide(int index) {
	if (level1 == true) {

		//array of positions for all objects
		Vector3f wall1 = Vector3f(22, 0, 0);
		Vector3f sizeWall1 = Vector3f(2, 20, 25);
		Vector3f directionWall1 = Vector3f(0, 0, 1);

		Vector3f wall2 = Vector3f(0, 0, 22);
		Vector3f sizeWall2 = Vector3f(25, 20, 2);
		Vector3f directionWall2 = Vector3f(1, 0, 0);

		Vector3f wall3 = Vector3f(-22, 0, 0);
		Vector3f sizeWall3 = Vector3f(2, 0, 25);

		Vector3f wall4 = Vector3f(0, 0, -22);
		Vector3f sizeWall4 = Vector3f(2, 0, 25);

		Vector3f positions[] = { wall1,wall2, Cone1.position,Cone2.position,Cone3.position,Cone4.position,Cone5.position,Cone6.position,Cone7.position,Cone8.position,Cone9.position,Cone10.position,Cone11.position,Cone12.position,Cone13.position,Cone14.position,Cone15.position,Cone16.position,Cone17.position,Cone18.position,Cone19.position,Cone20.position,Cone21.position,Cone22.position,Cone25.position,Cone26.position };
		Vector3f sizes[] = { sizeWall1,sizeWall2,Cone1.size,Cone2.size,Cone3.size,Cone4.size,Cone5.size,Cone6.size ,Cone7.size ,Cone8.size,Cone9.size,Cone10.size,Cone11.size,Cone12.size,Cone13.size,Cone14.size,Cone15.size,Cone16.size,Cone17.size,Cone18.size,Cone19.size,Cone20.size,Cone21.size,Cone22.size ,Cone25.size,Cone26.size};
		Vector3f directions[] = { directionWall1,directionWall2,Cone1.direction,Cone2.direction,Cone3.direction,Cone4.direction,Cone5.direction,Cone6.direction ,Cone7.direction ,Cone8.direction,Cone9.direction,Cone10.direction,Cone11.direction,Cone12.direction,Cone13.direction,Cone14.direction,Cone15.direction,Cone16.direction,Cone17.direction,Cone18.direction,Cone19.direction,Cone20.direction,Cone21.direction,Cone22.direction ,Cone25.direction,Cone26.direction};


		bool collideX = false;
		bool collideY = false;

		Vector3f* carPoints = car.generateCarPoints();

		int size = 27;
		for (int i = 0; i < size; i++) {
			if (i != index) {

				for (int j = 0; j < 9; j++) {
					if (
						(carPoints[j].x >= positions[i].x - (sizes[i].x / 2)) &&
						(carPoints[j].x <= positions[i].x + (sizes[i].x / 2))
						) {
						collideX = true;
					}
					if (
						(carPoints[j].z >= positions[i].z - (sizes[i].z / 2)) &&
						(carPoints[j].z <= positions[i].z + (sizes[i].z / 2))
						) {
						collideY = true;
					}

					if (collideX && collideY) {
						collided = true;
						PlaySound(TEXT("CollisionSound"), NULL, SND_ASYNC | SND_FILENAME | SND_NOWAIT);
						life -= 1;
						if (index == -1) {
							return 1;

						}
					}
					else {
						collideX = false;
						collideY = false;
					}
				}

				for (int p = 0; p < size; p++) {

					Vector3f* Points = generatePoints(positions[p], sizes[p], directions[p]);
					for (int z = 0; z < 9; z++) {

						if (
							(Points[z].x >= car.position.x - (car.direction.x * car.size.x / 2)) &&
							(Points[z].x <= car.position.x + (car.direction.x * car.size.x / 2))
							) {
							collideX = true;
						}
						if (
							(Points[z].z >= car.position.z - (car.direction.z * car.size.z / 2)) &&
							(Points[z].z <= car.position.z + (car.direction.z * car.size.z / 2))
							) {
							collideY = true;
						}


						if (collideX && collideY) {
							PlaySound(TEXT("CollisionSound"), NULL, SND_ASYNC | SND_FILENAME | SND_NOWAIT);

							if (index == -1) {
								return 1;
							}
						}
						else {
							collideX = false;
							collideY = false;
						}

					}
				}
			}
		}


		return -1;
	}
	else if (level2 == true) {

		//array of positions for all objects
		Vector3f wall1 = Vector3f(-22, 0, 0);
		Vector3f sizeWall1 = Vector3f(2, 20, 25);
		Vector3f directionWall1 = Vector3f(0, 0, 1);

		Vector3f wall2 = Vector3f(0, 0, 22);
		Vector3f sizeWall2 = Vector3f(25, 20, 2);
		Vector3f directionWall2 = Vector3f(1, 0, 0);


		Vector3f positions[] = { wall1,wall2,cone1Level2.position,cone2Level2.position,cone3Level2.position,cone4Level2.position,cone5Level2.position,cone6Level2.position ,cone7Level2.position,cone8Level2.position, cone9Level2.position,cone10Level2.position,cone11Level2.position,cone12Level2.position,cone13Level2.position,cone14Level2.position,cone15Level2.position,cone16Level2.position,cone17Level2.position,cone18Level2.position,cone19Level2.position,cone20Level2.position ,cone21Level2.position,cone22Level2.position,cone23Level2.position,cone24Level2.position,cone25Level2.position,cone26Level2.position,cone27Level2.position ,cone28Level2.position,cone29Level2.position ,cone30Level2.position,cone31Level2.position,cone32Level2.position,cone34Level2.position,cone35Level2.position,cone36Level2.position,cone37Level2.position };
		Vector3f sizes[] = { sizeWall1,sizeWall2,cone1Level2.size,cone2Level2.size,cone3Level2.size,cone4Level2.size,cone5Level2.size,cone6Level2.size,cone7Level2.size,cone8Level2.size,cone9Level2.size,cone10Level2.size,cone11Level2.size,cone12Level2.size,cone13Level2.size,cone14Level2.size,cone15Level2.size,cone16Level2.size,cone17Level2.size,cone18Level2.size,cone19Level2.size,cone20Level2.size,cone21Level2.size,cone22Level2.size,cone23Level2.size,cone24Level2.size ,cone25Level2.size,cone26Level2.size ,cone27Level2.size ,cone28Level2.size ,cone29Level2.size,cone30Level2.size,cone31Level2.size,cone32Level2.size ,cone34Level2.size,cone35Level2.size,cone36Level2.size,cone37Level2.size };
		Vector3f directions[] = { directionWall1,directionWall2,cone1Level2.direction ,cone2Level2.direction,cone3Level2.direction,cone4Level2.direction,cone5Level2.direction,cone6Level2.direction,cone7Level2.direction,cone8Level2.direction , cone9Level2.direction,cone10Level2.direction,cone11Level2.direction,cone12Level2.direction,cone13Level2.direction,cone14Level2.direction,cone15Level2.direction,cone16Level2.direction ,cone17Level2.direction,cone18Level2.direction ,cone19Level2.direction,cone20Level2.direction,cone21Level2.direction,cone22Level2.direction ,cone23Level2.direction,cone24Level2.direction,cone25Level2.direction,cone26Level2.direction,cone27Level2.direction ,cone28Level2.direction,cone29Level2.direction,cone30Level2.direction,cone31Level2.direction,cone32Level2.direction ,cone34Level2.direction,cone35Level2.direction,cone36Level2.direction,cone37Level2.direction };


		bool collideX = false;
		bool collideY = false;

		Vector3f* carPoints = car.generateCarPoints();

		int size = 37;
		for (int i = 0; i < size; i++) {
			if (i != index) {

				for (int j = 0; j < 9; j++) {
					if (
						(carPoints[j].x >= positions[i].x - (sizes[i].x / 2)) &&
						(carPoints[j].x <= positions[i].x + (sizes[i].x / 2))
						) {
						collideX = true;
					}
					if (
						(carPoints[j].z >= positions[i].z - (sizes[i].z / 2)) &&
						(carPoints[j].z <= positions[i].z + (sizes[i].z / 2))
						) {
						collideY = true;
					}

					if (collideX && collideY) {
						PlaySound(TEXT("CollisionSound"), NULL, SND_ASYNC | SND_FILENAME | SND_NOWAIT);
						if (index == -1) {
							return 1;
						}
					}
					else {
						collideX = false;
						collideY = false;
					}
				}

				for (int p = 0; p < size; p++) {

					Vector3f* Points = generatePoints(positions[p], sizes[p], directions[p]);
					for (int z = 0; z < 9; z++) {

						if (
							(Points[z].x >= car.position.x - (car.direction.x * car.size.x / 2)) &&
							(Points[z].x <= car.position.x + (car.direction.x * car.size.x / 2))
							) {
							collideX = true;
						}
						if (
							(Points[z].z >= car.position.z - (car.direction.z * car.size.z / 2)) &&
							(Points[z].z <= car.position.z + (car.direction.z * car.size.z / 2))
							) {
							collideY = true;
						}


						if (collideX && collideY) {
							PlaySound(TEXT("CollisionSound"), NULL, SND_ASYNC | SND_FILENAME | SND_NOWAIT);
							if (index == -1) {
								return 1;
							}
						}
						else {
							collideX = false;
							collideY = false;
						}

					}
				}
			}
		}


		return -1;
	}
}

// Model Variables
Model_3DS model_house;
Model_3DS model_tree;

// Textures
GLTexture tex_ground;

//=======================================================================
// Lighting Configuration Function
//=======================================================================
//void setupLights() {
//	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
//	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
//
//	// Define Light source 0 diffuse light
//	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
//
//	// Define Light source 0 Specular light
//	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
//
//	// Finally, define light source 0 position in World Space
//	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//	
//	/*if (dir == "left") {
//		lightPosition1[0]=playerx;
//		lightPosition1[1] = playery+1;
//		lightPosition1[2] = playerz-2;
//	}*/
//
//	GLfloat light1_Ka[] = { 1.0f,1.0f,0.0f,1.0f };
//	GLfloat light1_Kd[] = { 1.0f,1.0f,0.0f,1.0f };
//	GLfloat light1_Kspec[] = { 1,1,0,0 };
//	GLfloat light1_spotDirection[] = { 0,-1,0};
//	GLfloat lightPosition1[] = { car.position.x+3*car.direction.x, car.position.y+100, car.position.z+3*car.direction.z, 1 };
//	GLfloat light1_spotDirection1[] = { car.direction.x*cos(30),car.direction.y,car.direction.z * cos(30) };
//	GLfloat lightPosition2[] = { car.position.x, car.position.y+2 , car.position.z, 1 };
//	const GLfloat x= 30;
//	/*glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
//	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF,6.0 ) ;
//	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_spotDirection);
//	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_Ka);
//	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_Kd);
//	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_Kspec);*/
//
//	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2);
//	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 8.0);
//	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light1_spotDirection1);
//	glLightfv(GL_LIGHT2, GL_AMBIENT, light1_Ka);
//	glLightfv(GL_LIGHT2, GL_DIFFUSE, light1_Kd);
//	glLightfv(GL_LIGHT2, GL_SPECULAR, light1_Kspec);
//}


void setupLights() {
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	/*if (dir == "left") {
	lightPosition1[0]=playerx;
	lightPosition1[1] = playery+1;
	lightPosition1[2] = playerz-2;
	}*/
	if (forward) {
		GLfloat light1_Ka[] = { 1.0f,1.0f,0.0f,1.0f };
		GLfloat light1_Kd[] = { 1.0f,1.0f,0.0f,1.0f };
		GLfloat light1_Kspec[] = { 1,1,0,0 };
		GLfloat light1_spotDirection[] = { 0,-1,0 };
		GLfloat lightPosition1[] = { car.position.x + 3 * car.direction.x, car.position.y + 100, car.position.z + 3 * car.direction.z, 1 };
		GLfloat light1_spotDirection1[] = { car.direction.x ,car.direction.y,car.direction.z  };
		GLfloat lightPosition2[] = { car.position.x, car.position.y +1.5 , car.position.z, 1 };
		glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 8.0);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light1_spotDirection1);
		glLightfv(GL_LIGHT2, GL_AMBIENT, light1_Ka);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light1_Kd);
		glLightfv(GL_LIGHT2, GL_SPECULAR, light1_Kspec);
	}
	else {
		GLfloat light1_Ka[] = { 0.5f,0.5f,0.5f,1.0f };
		GLfloat light1_Kd[] = { 0.5f,0.5f,0.5f,1.0f };
		GLfloat light1_Kspec[] = { 0.5,0.5,0.5,0 };
		GLfloat light1_spotDirection[] = { 0,-1,0 };
		GLfloat lightPosition1[] = { car.position.x + 3 * car.direction.x, car.position.y + 100, car.position.z + 3 * car.direction.z, 1 };
		GLfloat light1_spotDirection1[] = { car.direction.x,car.direction.y,car.direction.z  };
		GLfloat lightPosition2[] = { car.position.x, car.position.y + 1.5 , car.position.z, 1 };
		GLfloat lightIntensity[] = { 1,1,1 };
		glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2);
		glLightfv(GL_LIGHT2, GL_INTENSITY, lightIntensity);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 8.0);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light1_spotDirection1);
		glLightfv(GL_LIGHT2, GL_AMBIENT, light1_Ka);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light1_Kd);
		glLightfv(GL_LIGHT2, GL_SPECULAR, light1_Kspec);
	}

}
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	//glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	GLfloat light_position1[] = { car.position.x , car.position.y + 10, car.position.z , 1 };
	GLfloat light_spotDirection[] = { 0,-1,0 };
	//glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	//glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 0.1);
	//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_spotDirection);

	//GLfloat ambient1[] = { 1.0f, 0.0f, 0.1, 1.0f };
	//glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);

	//// Define Light source 0 diffuse light
	//GLfloat diffuse1[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);

	//// Define Light source 0 Specular light
	//GLfloat specular1[] = { 1.0f, 0.0f, 0.0f, 0.0f };
	//glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);

	// Finally, define light source 0 position in World Space



}

//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}
void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, 1280 / 960, 0.001, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();

}
//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	//gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	//InitLightSource();

	setupCamera();
	setupLights();
}

//=======================================================================
// Render Ground Function
//=======================================================================
void RenderGround()
{
	if (level1) {

	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(5, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(5, 5);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 5);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	/*glDisable(GL_TEXTURE_2D);*/
	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
	}
	else {
		glDisable(GL_LIGHTING);	// Disable lighting 

		glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

		glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

		glBindTexture(GL_TEXTURE_2D, sandGround);	// Bind the ground texture

		glPushMatrix();
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);	// Set quad normal direction.
		glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
		glVertex3f(-20, 0, -20);
		glTexCoord2f(1, 0);
		glVertex3f(20, 0, -20);
		glTexCoord2f(1, 1);
		glVertex3f(20, 0, 20);
		glTexCoord2f(0, 1);
		glVertex3f(-20, 0, 20);
		glEnd();
		glPopMatrix();

		glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

		/*glDisable(GL_TEXTURE_2D);*/
		glColor3f(1, 1, 1);
	}
}

void setCameraPosition() {
	if (camera3rd) {
		camera.eye.x = car.position.x - 5 * car.direction.x;
		camera.eye.y = 15.0f;
		camera.eye.z = car.position.z - 5 * car.direction.z;
		camera.center.x = car.position.x + 5 * car.direction.x;
		camera.center.y = 5.0f;
		camera.center.z = car.position.z + 5 * car.direction.z;
		camera.up.x = 0;
		camera.up.y = 1;
		camera.up.z = 0;
	}
	if (camera1st) {
		camera.eye.x = car.position.x + 2.1 * car.direction.x;
		camera.eye.y = car.position.y + 3.5;
		camera.eye.z = car.position.z + 2.1 * car.direction.z;

		camera.center.x = car.position.x + 3 * car.direction.x;
		camera.center.y = car.position.y + 3.5;
		camera.center.z = car.position.z + 3 * car.direction.z;
		camera.up.x = 0;
		camera.up.y = 1;
		camera.up.z = 0;
	}
}

void MyTimer(int t) {
	//printf("%f, %f", car.position.x, car.position.z);
	timer -= 1;


	glutPostRedisplay();
	glutTimerFunc(2000, MyTimer, 0);

}
void LoseGame() {
	if (timer == 0) {
		loseGame = true;
		timer = 40;
		score = 0;
		for (int i = 0; i < 7; i++)
		{
			ringChecks[i] = 0;
			played[i] = false;
		}
		if (level1) {

		car.position.x = 16;
		car.position.y = 0;
		car.position.z = 14;
		car.angle = 180;
		car.UpdateDir2();
		}
		else if (level2) {
			car.position.x = -10;
			car.position.y = 0;
			car.position.z = 16;
			car.angle = 90;
			car.UpdateDir2();
		}

	}
	else if (life <= 0)
	{
		loseGame = true;
		timer = 40;
		score = 0;
		life = 3;
		for (int i = 0; i < 7; i++)
		{
			ringChecks[i] = 0;
			played[i] = false;
		}
		car.position.x = 16;
		car.position.y = 0;
		car.position.z = 14;
		car.angle = 180;
		car.UpdateDir2();
	}
}
void WinGame() {
	if (level1 == true && score == 50 && timer > 0) {
		level1 = false;
		level2 = true;
		score = 0;
		timer = 50;
		life = 3;
		level = 2;
		car.position = Vector3f(-10, 0, 16);
		car.angle = 90;
		printf("ana fl win");
		for (int i = 0; i < 7; i++) {
			ringChecks[i] = 0;
			played[i] = false;
		}

	}
	else if (level2 == true && score >= 70 && timer > 0) {
		printf("Score: %d \n",score);
		exit(0);

	}
}
//=======================================================================
// Display Function
//=======================================================================
void myDisplay(void)
{
	glOrtho(-50, 50, -50, 50, -100, 100);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	setupCamera();
	setupLights();
	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);


	setfont(GLUT_BITMAP_HELVETICA_18);

	using namespace std::literals::string_literals;
	std::string str1;

	str1 += "Your Score :"s + std::to_string(score);
	const char* y = str1.data();
	printf("Score: %d\n", score);
	setfont(GLUT_BITMAP_HELVETICA_18);

	using namespace std::literals::string_literals;
	std::string str2;

	str2 += "Level :"s + std::to_string(level);
	const char* x = str2.data();

	setfont(GLUT_BITMAP_HELVETICA_18);

	using namespace std::literals::string_literals;
	std::string str3;

	str3 += "Time :"s + std::to_string(timer);
	const char* z = str3.data();

	setfont(GLUT_BITMAP_HELVETICA_18);

	using namespace std::literals::string_literals;
	std::string str4;

	str4 += std::to_string(life);
	const char* v = str4.data();

	////////////////////////////////////////////////////// Level1  ////////////////////////////////////////
	// Draw Ground



	if (level1 == true) {

		RenderGround();



		glPushMatrix();
		car.DrawCar();
		glPopMatrix();

		glPushMatrix();
		Cone1.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone2.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone3.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone4.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone5.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone6.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone7.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone8.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone9.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone10.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone11.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone12.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone13.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone14.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone15.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone16.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone17.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone18.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone19.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone20.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone21.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone22.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone25.DrawCone();
		glPopMatrix();

		glPushMatrix();
		Cone26.DrawCone();
		glPopMatrix();

		glPushMatrix();
		ring20.DrawRing();
		glPopMatrix();

		glPushMatrix();
		ring.DrawRing();
		glPopMatrix();

		glPushMatrix();
		ring2.angle = -50;
		ring2.DrawRing();
		glPopMatrix();

		glPushMatrix();
		ring3.angle = -90;
		ring3.DrawRing();
		glPopMatrix();

		glPushMatrix();
		ring4.angle = -140;
		ring4.DrawRing();
		glPopMatrix();

		glPushMatrix();
		ring5.DrawRing();
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 1, 1);
		drawLabel();
		glPopMatrix();
		

		glPushMatrix();
		glColor3f(1, 1, 1);
		drawstring(-24, 15, 5, x);
		glColor3f(0.7, 0.7, 0.7);

		glColor3f(1, 1, 1);
		drawstring(-24, 12, 5, y);
		glColor3f(0.7, 0.7, 0.7);

		glColor3f(1, 1, 1);
		drawstring(-24, 9, 5, z);
		glColor3f(0.7, 0.7, 0.7);

		glColor3f(1, 1, 1);
		drawstring(-24, 15, -3, v);
		glColor3f(0.7, 0.7, 0.7);
		glPopMatrix();
	}
	/////////////////////////////////////////level1/////////////////////////////





	////////////////////////////level2/////////////////////////////////////////////////

	else if (level2 == true && level1 == false) {

		// Draw Ground
		RenderGround();

		// Draw Tree Model
		glPushMatrix();
		glTranslatef(0, 0, 0);
		glScalef(0.7, 0.7, 0.7);
		model_tree.Draw();
		glPopMatrix();

		// Draw house Model



		glPushMatrix();

		car.DrawCar();
		glPopMatrix();

		glPushMatrix();
		cone1Level2.DrawCone();
		glPopMatrix();

		glPushMatrix();
		cone2Level2.DrawCone();
		glPopMatrix();

		glPushMatrix();
		cone3Level2.DrawCone();
		glPopMatrix();

		glPushMatrix();
		cone4Level2.DrawCone();
		glPopMatrix();

		glPushMatrix();
		cone5Level2.DrawCone();
		glPopMatrix();

		glPushMatrix();
		cone6Level2.DrawCone();
		glPopMatrix();


		glPushMatrix();
		cone7Level2.DrawCone();
		glPopMatrix();


		glPushMatrix();
		cone8Level2.DrawCone();
		glPopMatrix();


		glPushMatrix();
		cone9Level2.DrawCone();
		glPopMatrix();


		glPushMatrix();
		cone10Level2.DrawCone();
		glPopMatrix();




		glPushMatrix();
		cone11Level2.DrawCone();
		glPopMatrix();


		glPushMatrix();
		cone12Level2.DrawCone();
		glPopMatrix();


		glPushMatrix();
		cone13Level2.DrawCone();
		glPopMatrix();


		glPushMatrix();
		cone14Level2.DrawCone();
		glPopMatrix();


		glPushMatrix();
		cone15Level2.DrawCone();
		glPopMatrix();


		glPushMatrix();
		cone16Level2.DrawCone();
		glPopMatrix();

		glPushMatrix();
		cone17Level2.DrawCone();
		glPopMatrix();


		glPushMatrix();
		cone18Level2.DrawCone();
		glPopMatrix();


		glPushMatrix();
		cone19Level2.DrawCone();
		glPopMatrix();


		glPushMatrix();
		cone20Level2.DrawCone();
		glPopMatrix();

		glPushMatrix();
		cone21Level2.DrawCone();
		glPopMatrix();


		glPushMatrix();
		cone22Level2.DrawCone();
		glPopMatrix();

		glPushMatrix();
		cone23Level2.DrawCone();
		glPopMatrix();


		glPushMatrix();
		cone24Level2.DrawCone();
		glPopMatrix();


		glPushMatrix();
		cone25Level2.DrawCone();
		glPopMatrix();


		glPushMatrix();
		cone26Level2.DrawCone();
		glPopMatrix();


		glPushMatrix();
		cone27Level2.DrawCone();
		glPopMatrix();

		glPushMatrix();
		cone28Level2.DrawCone();
		glPopMatrix();


		glPushMatrix();
		cone29Level2.DrawCone();
		glPopMatrix();

		glPushMatrix();
		cone30Level2.DrawCone();
		glPopMatrix();

		glPushMatrix();
		cone31Level2.DrawCone();
		glPopMatrix();

		glPushMatrix();
		cone32Level2.DrawCone();
		glPopMatrix();

		glPushMatrix();
		cone33Level2.DrawCone();
		glPopMatrix();

		glPushMatrix();
		cone34Level2.DrawCone();
		glPopMatrix();

		glPushMatrix();
		cone35Level2.DrawCone();
		glPopMatrix();

		glPushMatrix();
		cone36Level2.DrawCone();
		glPopMatrix();

		glPushMatrix();
		cone37Level2.DrawCone();
		glPopMatrix();



		glPushMatrix();
		ring1Level2.angle = 90;
		ring1Level2.DrawRing();
		glPopMatrix();

		glPushMatrix();
		ring2Level2.angle = 90;
		ring2Level2.DrawRing();
		glPopMatrix();


		glPushMatrix();
		ring3Level2.angle = 87;
		ring3Level2.DrawRing();
		glPopMatrix();

		glPushMatrix();
		ring4Level2.angle = 125;
		ring4Level2.DrawRing();
		glPopMatrix();

		glPushMatrix();
		ring5Level2.angle = 180;
		ring5Level2.DrawRing();
		glPopMatrix();

		glPushMatrix();
		ring6Level2.angle = 240;
		ring6Level2.DrawRing();
		glPopMatrix();



		glPushMatrix();
		ring7Level2.angle = 90;
		ring7Level2.DrawRing();
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 1, 1);
		drawLabelLevel2();
		/*0, 18, -25*/

		glColor3f(1, 1, 1);
		drawstring(-5, 20, -23, x);
		glColor3f(0.7, 0.7, 0.7);

		glColor3f(1, 1, 1);
		drawstring(-5, 18, -23, y);
		glColor3f(0.7, 0.7, 0.7);

		glColor3f(1, 1, 1);
		drawstring(-5, 16, -23, z);
		glColor3f(0.7, 0.7, 0.7);

		glColor3f(1, 1, 1);
		drawstring(4, 20, -23, v);
		glColor3f(0.7, 0.7, 0.7);
		glPopMatrix();

	}

	//////////////////////////level2//////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////

	int sum = 0;
	for (int i = 0; i < 7; i++) {
		sum += ringChecks[i];
	}
	score = sum;
	for (int i = 0;i < 7;i++) {
		if (ringChecks[i] == 10 && !played[i] ) {
		
			PlaySound(TEXT("mixkit-space-coin-win-notification-271.wav"), NULL, SND_ASYNC);
			played[i] = true;
			break;
		}
	}





	/////////////////////////////////////////////////////////////////////


	//sky box
	glPushMatrix();

	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 100, 100, 100);
	gluDeleteQuadric(qobj);


	glPopMatrix();

	LoseGame();
	WinGame();



	glutSwapBuffers();
}

//=======================================================================
// Keyboard Function
//=======================================================================
void myKeyboard(unsigned char button, int x, int y)
{
	if (collided) {
		PlaySound(TEXT("CollisionSound"), NULL, SND_ASYNC);
		collided = false;
	}
	float d = 0.2;

	switch (button)
	{
	case 'd':
		keystates['d'] = true;
		car.TireDirection = "Right";
		car.theta = -5;
		car.Move(1);
		break;

	case 'w':
		keystates['w'] = true;
		car.UpdateDir();
		car.Move(1);

		break;

	case 's':
		keystates['s'] = true;
		car.UpdateDir();
		car.Move(1);
		break;


	case 'a':
		keystates['a'] = true;
		car.TireDirection = "Left";
		car.theta = 5;
		car.Move(1);
		break;

	case 'i':
		camera.moveY(d);
		break;
	case 'k':
		camera.moveY(-d);
		break;
	case 'j':
		camera.moveX(d);
		break;
	case 'l':
		camera.moveX(-d);
		break;
	case 'u':
		camera.moveZ(d);
		break;
	case 'o':
		camera.moveZ(-d);
		break;
	case '0':
		camera.backtoDefault();
		break;
	case '1':
		camera.lookAtTop();

		break;
	case '2':
		camera.lookAtSide();
		break;
	case '3':
		camera.lookAtFront();
		break;
	case '4':
		camera1st = true;
		camera3rd = false;
		setCameraPosition();
		break;
	case '5':
		camera3rd = true;
		camera1st = false;
		setCameraPosition();
		break;
	case 'h':
		PlaySound(TEXT("Hala peep peep (1).wav"), NULL, SND_ASYNC);
		break;
	case 'z':
		if (light) {
			light = false;
			glDisable(GL_LIGHT2);
		}
		else {
			light = true;
			glEnable(GL_LIGHT2);
		}
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}
void myKeyUp(unsigned char button, int x, int y)
{
	float d = 0.1;

	switch (button)
	{
	case 'd':
		keystates['d'] = false;

		car.theta = 0;
		break;

	case 'w':
		keystates['w'] = false;
		break;

	case 's':
		keystates['s'] = false;
		break;


	case 'a':
		keystates['a'] = false;
		car.theta = 0;
		break;


	default:
		break;
	}

	glutPostRedisplay();
}
void Special(int key, int x, int y) {
	float a = 2.0;

	switch (key) {
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}

	glutPostRedisplay();
}
//=======================================================================
// Motion Function
//=======================================================================
void myMotion(int x, int y)
{
	y = HEIGHT - y;

	if (cameraZoom - y > 0)
	{
		camera.eye.x += -0.1;
		camera.eye.z += -0.1;
	}
	else
	{
		camera.eye.x += 0.1;
		camera.eye.z += 0.1;
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();	//Re-draw scene 
}

//=======================================================================
// Mouse Function
//=======================================================================
void myMouse(int button, int state, int x, int y)
{
	y = HEIGHT - y;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
	}
}

//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	// Loading Model files
	model_house.Load("Models/house/house.3DS");
	model_tree.Load("Models/tree/Tree1.3ds");

	// Loading texture files
	tex_ground.Load("Textures/Road.bmp");
	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
	loadBMP(&tex2, "Textures/coneText.bmp", true);
	loadBMP(&tex3, "Textures/Ring.bmp", true);
	tex_hazoum.Load("Textures/hazoum.bmp");
	loadBMP(&texTire, "Textures/Tire.bmp", true);
	loadBMP(&carTexture, "Textures/carTexture.bmp", true);
	loadBMP(&glassTexture, "Textures/rainTexture.bmp", true);
	loadBMP(&sandGround, "Textures/desert.bmp", true);

}

//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutTimerFunc(0, MyTimer, 0);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(100, 0);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);

	glutKeyboardFunc(myKeyboard);
	glutKeyboardUpFunc(myKeyUp);
	glutSpecialFunc(Special);

	glutMotionFunc(myMotion);
	glutMouseFunc(myMouse);

	glutReshapeFunc(myReshape);


	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}