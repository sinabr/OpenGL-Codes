
#include <iostream>
//#include <gl/glew.h>
#include <gl/glut.h>


// If Installed with Package Manager : ( I Used This )

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// IF WAS ADDED TO PATH :

//#include "glm.hpp"
//#include "gtc\type_ptr.hpp"

using namespace std;


void rotate_one(int point[3],int vertex[3], float theta) {
	float t_translation[16] = {
	1,		0,		0,		-point[0],
	0,		1,		0,		-point[1],
	0,		0,		1,		-point[2],
	0,		0,		0,				1
	};

	float t_rotate[16] = {
	cos(theta),		0,		sin(theta), 0,
	0,				1,		0,			0,
	-sin(theta),	0,		cos(theta),	0,
	0,				0,		0,			1
	};
}

void camera_config(float aspect, int w, int h, float fovy, float near_, float far_, float eye[3], float lookat[3], float up[3] )
{
	// width: 800, height: 600
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(fovy/2.0, aspect, near_, far_);

	gluLookAt(
		eye[0], eye[1], eye[2],  
		lookat[0], lookat[1], lookat[2],  
		up[0], up[1], up[2]); 

}


void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	float s = 45. / 180 * glm::pi<float>();
	float a = asin(2 / sqrt(13));
	float alpha = 30. / 180 * glm::pi<float>();

	glm::vec3 v_1 = glm::vec3(1, 2, 3);

	// INITIAL POINTS
	glm::vec4 p1(0, 0, 1, 1);
	glm::vec4 p2(1, 0, 0, 1);
	glm::vec4 p3(0, 1, 0, 1);
	glm::vec4 p4(-1, 0, 0, 1);
	glm::vec4 p5(0, 0, 0, 1);

	// 1.1 - Rotation Around <2,2,2>
	// we translate it to the origin, rotate it and translate it back

	glm::mat4 w_t = glm::translate( glm::mat4(1.0), glm::vec3(2, 2, 2) );
	glm::mat4 w_r = glm::rotate( w_t , s , glm::vec3(0, 0, 1) );
	glm::mat4 w_t2 = glm::translate(w_r, glm::vec3(-2, -2, -2));

	auto p1_ = w_t2 * p1;
	auto p2_ = w_t2 * p2;
	auto p3_ = w_t2 * p3;
	auto p4_ = w_t2 * p4;
	auto p5_ = w_t2 * p5;

	cout << "1.1 - Results: " << endl;
	cout << "P1: " << "x: " << p1_.x << " y: " << p1_.y << " z: " << p1_.z << endl;
	cout << "P2: " << "x: " << p2_.x << " y: " << p2_.y << " z: " << p2_.z << endl;
	cout << "P3: " << "x: " << p3_.x << " y: " << p3_.y << " z: " << p3_.z << endl;
	cout << "P4: " << "x: " << p4_.x << " y: " << p4_.y << " z: " << p4_.z << endl;
	cout << "P5: " << "x: " << p5_.x << " y: " << p5_.y << " z: " << p5_.z << endl;


	// 1.2 - Scaling Along <1,2,3>
	// we put it on one of the axis and then scale it, at last we rotate it back

	glm::mat4 c_r_z = glm::rotate(glm::mat4(1.0), glm::radians(-30.0f), glm::vec3(0, 0, 1));
	glm::mat4 c_r_x = glm::rotate(c_r_z, -a, glm::vec3(1, 0, 0));

	glm::mat4 c_s = glm::scale(c_r_x, glm::vec3(1, 2, 3));

	glm::mat4 c_r_x_ = glm::rotate(c_s, a, glm::vec3(1, 0, 0));
	glm::mat4 c_r_z_ = glm::rotate(c_r_x_, alpha, glm::vec3(0, 0, 1));

	p1_ = c_r_z_ * p1_;
	p2_ = c_r_z_ * p2_;
	p3_ = c_r_z_ * p3_;
	p4_ = c_r_z_ * p4_;
	p5_ = c_r_z_ * p5_;

	cout << "1.2 - Results: " << endl;
	cout << "P1: " << "x: " << p1_.x << " y: " << p1_.y << " z: " << p1_.z << " w: " << p1_.w << endl;
	cout << "P2: " << "x: " << p2_.x << " y: " << p2_.y << " z: " << p2_.z << " w: " << p2_.w << endl;
	cout << "P3: " << "x: " << p3_.x << " y: " << p3_.y << " z: " << p3_.z << " w: " << p3_.w << endl;
	cout << "P4: " << "x: " << p4_.x << " y: " << p4_.y << " z: " << p4_.z << " w: " << p4_.w << endl;
	cout << "P5: " << "x: " << p5_.x << " y: " << p5_.y << " z: " << p5_.z << " w: " << p5_.w << endl;

	// 1.3 - Camera Transformation and Projection
	// P_ = A x T_inv_cam x T_obj x P

	float near_ = 0.1;
	float far_ = 1000.0;
	float aspect = 2.0;
	float fov = 60.0/2.0;
	fov = fov / 180 * glm::pi<float>();

	float f = cos(fov) / sin(fov);
	float a_ = (far_ + near_) / (near_ - far_);
	float b_ = (2.0 * far_ * near_) / (near_ - far_);

	// This Matrix Doesn't work because [4][4] must be 1 !!!!
	//float A_array[16] =
	//{
	//	f / aspect,	0,	0,	0,
	//		   0,	f,	0,	0,
	//		   0,	0, a_, b_,
	//		   0,	0, -1,	0
	//};

	float A_array[16] =
	{
		f/aspect,	0,	0,	0,
			   0,	f,	0,	0,
			   0,	0, a_, b_,
			   0,	0, 0,	1
	};



	// P_ref : 0,0,0 - C_eye : 5,5,-5
	float d[3] = {-5.0,-5.0,5.0};

	float norm_d = sqrt(d[0]*d[0] + d[1]*d[1] + d[2]*d[2]);

	

	float a_z[3] = {d[0]/norm_d,d[1]/norm_d,d[2]/norm_d};


	// Up vector - Normalized
	float v_[3] = { 0.0, 1.0, 0.0 };

	// a_x = v x a_z
	float a_x[3] = 
	{
		v_[1] * a_z[2] - v_[2] * a_z[1],
		v_[2] * a_z[0] - v_[0] * a_z[2],
		v_[0] * a_z[1] - v_[1] * a_z[0]
	};

	float a_y[3] =
	{
		a_z[1] * a_x[2] - a_z[2] * a_x[1],
		a_z[2] * a_x[0] - a_z[0] * a_x[2],
		a_z[0] * a_x[1] - a_z[1] * a_x[0]
	};


	


	float c[3] = {5.0,5.0,-5.0};

	// - R_a_transpose x C_eye
	float rc[3] =
	{
		-1 * (c[0] * a_x[0] + c[1] * a_x[1] + c[2] * a_x[2]),
		-1 * (c[0] * a_y[0] + c[1] * a_y[1] + c[2] * a_y[2]),
		-1 * (c[0] * a_z[0] + c[1] * a_z[1] + c[2] * a_z[2])
	};

	cout << "ay :  " << "x : " << rc[0] << " y: " << rc[1] << " z: " << rc[2] << endl;

	float T_inv_cam_[16] =
	{
		a_x[0],	a_x[1],	a_x[2],	rc[0],
		a_y[0],	a_y[1],	a_y[2],	rc[1],
		a_z[0],	a_z[1],	a_z[2],	rc[2],
			 0,		 0,		0,		1
	};

	// in this case Object coordinates are aligned with world coordinates
	float T_obj_[16] =
	{
		1,	0,	0,	0,
		0,	1,	0,	0,
		0,	0,	1,	0,
		0,	0,  0,	1
	};

	glm::mat4 A = glm::transpose(glm::make_mat4(A_array));
	glm::mat4 T_inv_cam = glm::transpose(glm::make_mat4(T_inv_cam_));
	glm::mat4 T_obj = glm::transpose(glm::make_mat4(T_obj_));

	p1_ = A * T_inv_cam * T_obj * p1_;
	p2_ = A * T_inv_cam * T_obj * p2_;
	p3_ = A * T_inv_cam * T_obj * p3_;
	p4_ = A * T_inv_cam * T_obj * p4_;
	p5_ = A * T_inv_cam * T_obj * p5_;

	cout << "1.3 - Results: " << endl;
	cout << "P1: " << "x: " << p1_.x << " y: " << p1_.y << " z: " << p1_.z << " w: " << p1_.w << endl;
	cout << "P2: " << "x: " << p2_.x << " y: " << p2_.y << " z: " << p2_.z << " w: " << p2_.w << endl;
	cout << "P3: " << "x: " << p3_.x << " y: " << p3_.y << " z: " << p3_.z << " w: " << p3_.w << endl;
	cout << "P4: " << "x: " << p4_.x << " y: " << p4_.y << " z: " << p4_.z << " w: " << p4_.w << endl;
	cout << "P5: " << "x: " << p5_.x << " y: " << p5_.y << " z: " << p5_.z << " w: " << p5_.w << endl;

	// 1.4 - Viewport Transformation
	// Vp Matrix

	float vr = 800.0;
	float vl = 0.0;
	float vt = 600.0;
	float vb = 0.0;

	float Vp_[16] =
	{
		(vr - vl)/2.0,   	       0,		  0,	(vr + vl)/2.0,
				    0, (vt - vb)/2.0,	      0,	(vt + vb)/2.0,
				    0,             0,		0.5,		0.5,
				    0,	    	   0,		  0,		      1
	};

	glm::mat4 Vp = glm::transpose(glm::make_mat4(Vp_));

	p1_ = Vp * p1_;
	p2_ = Vp * p2_;
	p3_ = Vp * p3_;
	p4_ = Vp * p4_;
	p5_ = Vp * p5_;
	
	cout << "1.4 - Results: " << endl;
	cout << "P1: " << "x: " << p1_.x << " y: " << p1_.y << " z: " << p1_.z << " w: " << p1_.w << endl;
	cout << "P2: " << "x: " << p2_.x << " y: " << p2_.y << " z: " << p2_.z << " w: " << p2_.w << endl;
	cout << "P3: " << "x: " << p3_.x << " y: " << p3_.y << " z: " << p3_.z << " w: " << p3_.w << endl;
	cout << "P4: " << "x: " << p4_.x << " y: " << p4_.y << " z: " << p4_.z << " w: " << p4_.w << endl;
	cout << "P5: " << "x: " << p5_.x << " y: " << p5_.y << " z: " << p5_.z << " w: " << p5_.w << endl;

	//Simpler Way:

	/*
	*
	1.3 is Done this way in OpenGL:
	To transform camera
	*
	*/

	//gluPerspective(fovy / 2.0, aspect, near_, far_);

	//gluLookAt(
	//	eye[0], eye[1], eye[2],
	//	lookat[0], lookat[1], lookat[2],
	//	up[0], up[1], up[2]);

	/*
	*
	1.4 is done this way in OpenGL:
	To Viewport transformation
	*
	*/

	// Considering : Y_b = 0 and X_l = 0

	// float width = 800;
	// float height = 600;
	// glViewport(0,width,0,height);


}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Transformation-3D");

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 800, 0.0, 600);

	glutDisplayFunc(render);
	glutMainLoop();
}