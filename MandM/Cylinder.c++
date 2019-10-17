// Cylinder.c++

#include <iostream>
#include <math.h>

#include "Cylinder.h"

// *************************************************************************
// EXERCISE: Modify the constructor prototype to accept information
//           necessary to address the EXERCISE in Cylinder::defineCylinder.
// *************************************************************************
// This simple Cylinder class creates a cylinder along the x-axis:
// (x1, yb, zb) to (x2, yb, zb) with radius=r
Cylinder::Cylinder(ShaderIF* sIF) : shaderIF(sIF)
{
	kd[0] = 0.25; kd[1] = 1.0; kd[2] = 0.5;
	double x1 = 0.6, x2 = 1.1;
	double yb = -0.35, zb = 1.4;
	double r = 0.05;
	xmin = x1;
	xmax = x2;
	ymin = yb - r;
	ymax = yb + r;
	zmin = zb - r;
	zmax = zb + r;
	defineCylinder(x1, x2, yb, zb, r);
}

Cylinder::~Cylinder()
{
	glDeleteBuffers(2, vbo);
	glDeleteVertexArrays(1, vao);
}

const int N_POINTS_AROUND_SLICE = 18; // number points around a cross-section

void Cylinder::defineCylinder(double x1, double x2, double yb, double zb, double r)
{
	typedef float vec3[3];
	int nPoints = 2 * (N_POINTS_AROUND_SLICE + 1); // "+1" because last point = first
	vec3* coords = new vec3[nPoints];
	vec3* normals = new vec3[nPoints];
	double theta = 0.0;
	double dTheta = 2.0*M_PI/N_POINTS_AROUND_SLICE;
	// ************************************************************************
	// EXERCISE: In the for-loop that follows, define the coordinates and
	//           normals for a GL_TRIANGLE_STRIP that approximates a cylinder
	//           in one of the following ways:
	//           1. Along one of the x-, y-, or z-axes
	//           2. Along an axis parallel to one of the x-, y-, or z-axes
	//           3. In general position and orientation using the cryph utilities.
	// ************************************************************************
	for (int i=0 ; i<=N_POINTS_AROUND_SLICE ; i++)
	{
		// Each time through this loop, create two points and their corresponding
		// (and common) normal vectors

		// Refer to 672's InClass/3DModeling/3DGeometryAndAttributeModeling101.html

		theta += dTheta;
	}

	// ************************************************************************
	// EXERCISE: Create/fill VAOs and VBOs here.
	//           Also use glVertexAttribPointer and glEnableVertexAttribArray
	// ************************************************************************
	std::cout << "Cylinder::defineCylinder: create/fill VBOs. You will see errors until you do so.\n";

	delete [] coords;
	delete [] normals;
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Cylinder::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

bool Cylinder::handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY)
{
	// Cylinder does not look for events. Just hand off back to inherited handleCommand.
	return this->ModelView::handleCommand(anASCIIChar, ldsX, ldsY);
}

void Cylinder::renderCylinder()
{
	glUniform3fv(shaderIF->ppuLoc("kd"), 1, kd);
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 2*(N_POINTS_AROUND_SLICE+1));
}

void Cylinder::render()
{
	typedef float vec3[3];
	GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);
	glUseProgram(shaderIF->getShaderPgmID());

	cryph::Matrix4x4 mc_ec, ec_lds;
	getMatrices(mc_ec, ec_lds);
	float mat[16];
	glUniformMatrix4fv(shaderIF->ppuLoc("mc_ec"), 1, false, mc_ec.extractColMajor(mat));
	glUniformMatrix4fv(shaderIF->ppuLoc("ec_lds"), 1, false, ec_lds.extractColMajor(mat));

	renderCylinder();

	glUseProgram(pgm);
}
