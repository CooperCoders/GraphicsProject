
#include <iostream>
#include <string>
#include <assert.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <time.h>
#include <list>


#include "shader.h"
#include "control.h"
#include "vertex.h"
#include "control.h"
#include "pipeline.h"

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 640
#define FRAME_TIME 50
#define NUM_PARTICLES 30000

GLuint VBO;
GLuint IBO;
Control mainControl;
Vertex Vertices[NUM_PARTICLES * 2 + 100];
int count = 0;



static void RenderSceneCB()
{
	count = 1;
	mainControl.newTime = glutGet(GLUT_ELAPSED_TIME);
	mainControl.deltaTime = mainControl.newTime - mainControl.currentTime;
	mainControl.fpsTime += mainControl.deltaTime;
	mainControl.frames += 1;
	mainControl.currentTime = mainControl.newTime;
	while (mainControl.deltaTime > 0)
	{
		int dt = !(FRAME_TIME < mainControl.deltaTime) ? mainControl.deltaTime : FRAME_TIME;
		
		mainControl.deltaTime -= dt;

	}



	glClear(GL_COLOR_BUFFER_BIT);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_DYNAMIC_DRAW);



	Pipeline p;
	p.Rotate(0.0f, 0, 0.0f);
	p.WorldPos(0.0f, 0.0f, mainControl.zoom);
	p.SetPerspectiveProj(45, mainControl.windowWidth, mainControl.windowHeight, .01f, 100.0f);
	mainControl.transform = *(p.GetTrans());




	glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, (const GLfloat*)p.GetTrans());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);

	glDrawArrays(GL_POINTS, 0, count);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glutSwapBuffers();

	if (mainControl.fpsTime > 1000)
	{
		std::cout << "Frames per Second: " << mainControl.frames / (mainControl.fpsTime / 1000.0f) << "\t\tParticles: " << count << std::endl;
		mainControl.frames = 0;
		mainControl.fpsTime = 0;
	}
}


static void SpecialKeyboardCB(int Key, int x, int y)
{
	mainControl.mouseX = x;
	mainControl.mouseY = y;
}


static void KeyboardCB(unsigned char Key, int x, int y)
{
	switch (Key) {
	case 'q':
		exit(0);
	}
	mainControl.mouseX = x;
	mainControl.mouseY = y;
	mainControl.keys[Key] = true;
}

void ReleaseKeyCB(unsigned char key, int x, int y)
{
	mainControl.keys[key] = false;
}

static void PassiveMouseCB(int x, int y)
{
	mainControl.mouseX = x;
	mainControl.mouseY = y;
}

void ChangeSizeCB(int w, int h)
{
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;
	mainControl.windowWidth = w;
	mainControl.windowHeight = h;
	glViewport(0, 0, w, h);
}

static void ActiveMouseCB(int button, int state, int x, int y)
{
	mainControl.mouseX = x;
	mainControl.mouseY = y;
}

static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
	glutIdleFunc(RenderSceneCB);
	glutSpecialFunc(SpecialKeyboardCB);
	glutPassiveMotionFunc(PassiveMouseCB);
	glutKeyboardFunc(KeyboardCB);
	glutMouseFunc(ActiveMouseCB);
	glutReshapeFunc(ChangeSizeCB);
	glutKeyboardUpFunc(ReleaseKeyCB);
	glutMotionFunc(PassiveMouseCB);
}

static void CreateVertexBuffer()
{
	Vertices[0] = Vertex(Vector3f(0.f, .0f, 0.0f), Vector4f(1, 0, 0, 1));

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_DYNAMIC_DRAW);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Graphics Project");

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(5.0);
	InitializeGlutCallbacks();

	srand(time(NULL));
	mainControl.zoom = 2;


	mainControl.currentTime = glutGet(GLUT_ELAPSED_TIME);


	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		return 1;
	}

	printf("GL version: %s\n", glGetString(GL_VERSION));

	glClearColor(0.f, 0.f, 0.f, 0.0f);

	CreateVertexBuffer();

	CompileShaders();

	glutMainLoop();

	return 0;
}