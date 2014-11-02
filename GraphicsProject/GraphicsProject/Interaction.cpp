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
#include "Interaction.h"

//position of the vector
glm::vec position = glm::vec3(0, 0, 5);
//horizontal angle: toward -Z
float horizontalAngle = 3.14f;
//vertical angle : 0; look at the horizon
float verticalAngle = 0.0f;
//inifital field of view, basically level of zoom
float initialFoV = 45.0f;

float speed = 3.0f; //3 units per second
float mouseSpeed = 0.005f;

//reading the mouse position
int xpos, ypos;
glfwGetMousePos(&xpos, &ypos);

//reset mouse position for each from so 
//that mouse doesn't go outside window
glfwSetMousePos(640 / 2, 640 / 2);

//computing viewing angles:

//compute new orientation
horizontalAngle += mouseSpeed * deltaTime * float(640 / 2 - xpos); //the bigger this value the more we want to turn
verticalAngle += mouseSpeed * deltaTimee * float(640 / 2 - ypos);

//Direction : Spherical coordinates to Cartesian coordinates conversion
glm::vec3 direction(
	cos(verticalAngle) * sin(horizontalAngle),
	sin(verticalAngle),
	cos(verticalAngle) * cos(horizontalAngle)
);

//right vector
glm::vec3 right = glm::vec3(
	sin(horizontalAngle - 3.14f / 2.0f),
	0,
	cos(horizontalAngle - 3.14f / 2.0f)
);

//Up vector : perpendicular to both direction and right
glm::vec3 up = glm::cross(right, direction);

//Posiion

//Move forward
if (glfwGet)








/*void keyboard(unsigned char key, int x, int y) {
	switch (key){
	case 'r':
		r = 1.0; g = 0.0; b = 0.0;
		break;
	case 'g':
		r = 0.0; g = 1.0; b = 0.0;
		break;
	}
	glutPostRedisplay();
}*/