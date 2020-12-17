#include <iostream>
#include <gl\glut.h>
#include <vector>
#include <math.h>

#define ONE 1000
#define TWO 1001
#define THREE 1002


using namespace std;

struct Vertex
{
	int x;
	int y;
};

std::vector<Vertex> vrtxs;


void setPixel(int x, int y)
{
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

void DDA(int x1, int y1, int x2, int y2) {
	float dx = x2 - x1;
	float dy = y2 - y1;

	int steps;

	if(abs(dx) > abs(dy)){
		steps = abs(dx);
	}
	else {
		steps = abs(dy);
	}
		
	float xi = dx / steps;
	float yi = dy / steps;

	int x = x1;
	int y = y1;


	for(int i = 0; i < steps;i++) {
		setPixel(x, y);
		x += xi;
		y += yi;
	}

}

int CrossProduct(pair<Vertex,Vertex> e1, pair<Vertex,Vertex> e2) 
{
	Vertex A,B;
	A.x = e1.second.x - e1.first.x;
	A.y = e1.second.y - e1.first.y;

	B.x = e2.second.x - e2.first.x;
	B.y = e2.second.y - e2.first.y;

	
	return A.x * B.y - A.y * B.x;

}

pair<bool,Vertex> IntersectionOf2Lines(pair<Vertex,Vertex> E1, pair<Vertex, Vertex> E2)
{

	Vertex P1 = E1.first;
	Vertex P2 = E1.second;

	Vertex Q1 = E2.first;
	Vertex Q2 = E2.second;

	int dy1 = P2.y - P1.y;
	int dx1 = P1.x - P2.x;
	int p = dy1 * (P1.x) + dx1 * (P1.y);

	int dy2 = Q2.y - Q1.y;
	int dx2 = Q1.x - Q2.x;
	int q = dy2 * (Q1.x) + dx2 * (Q1.y);

	int determinant = dy1 * dx2 - dy2 * dx1;

	Vertex intrsct;

	if (determinant == 0)
	{
		intrsct.x = -1;
		intrsct.y = -1;
		
		return make_pair(false,intrsct);

	}
	else
	{
		double x = (dx2 * p - dx1 * q) / determinant;
		double y = (dy1 * q - dy2 * p) / determinant;
		intrsct.x = x;
		intrsct.y = y;



		int distA = sqrt(pow((Q1.x - intrsct.x), 2) + pow(Q1.y - intrsct.y, 2)) + sqrt(pow((Q2.x - intrsct.x), 2) + pow(Q2.y - intrsct.y, 2));
		int distB = sqrt(pow(Q1.x - Q2.x, 2) + pow(Q1.y - Q2.y, 2));

		// if distA == distB : the point is on Line segment Q1-Q2
		if (distA == distB)
		{
			return make_pair(true, intrsct);

		}
		else {
			return make_pair(false, intrsct);
		}

	}

}


bool ConcaveEdgePair(pair<Vertex, Vertex> e1, pair<Vertex, Vertex> e2) {

	if (CrossProduct(e1, e2) >= 0) 
	{
		return false;
	}
	else 
	{
		return true;
	}
}

void DrawPolygon(vector<Vertex> vrxs) 
{	
		
	Vertex First;
	Vertex Second;

	int size = vrxs.size();
	for (int i = 0; i < size - 1 ; i++)
	{
		DDA(vrxs[i].x,vrxs[i].y,vrxs[i+1].x,vrxs[i+1].y);
	}
	
	DDA(vrxs[size - 1].x, vrxs[size - 1].y, vrxs[0].x, vrxs[0].y);

}

// This Function Finds Intersection of the target edge with other edges (except adjacent ones)
// After Finding The Intersection : It is what we want if the intersectio is on the 
// line, otherwise it's outside the polygon
// Then: Creates two vector<Vertex> sets which are polygons
// We run the main function recursively on the result of this function
pair<vector<Vertex>, vector<Vertex>> FindIntersection(int index,vector<Vertex> vrtxs)
{

	int size = vrtxs.size();
	bool done = false;

	pair<Vertex, Vertex> edge;

	pair<Vertex, Vertex> myEdge;

	if (index == size - 1) {
		myEdge = make_pair(vrtxs[index], vrtxs[0]);
	}
	else {
		myEdge = make_pair(vrtxs[index], vrtxs[index + 1]);
	}

	vector<pair<Vertex,Vertex>> edgesToIntersect;
	
	int ignore[3];
	if (index == size - 1) {
		ignore[0] = index - 1;
		ignore[1] = index;
		ignore[2] = 0;
	}
	else if (index == 0) {
		ignore[0] = size - 1;
		ignore[1] = index;
		ignore[2] = index + 1;
	}
	else {
		ignore[0] = index - 1;
		ignore[1] = index;
		ignore[2] = index + 1;
	}

	pair<Vertex, Vertex> temp;
	pair<bool, Vertex> result;


	vector<Vertex> polygon_1;
	vector<Vertex> polygon_2;

	pair<vector<Vertex>, vector<Vertex>> splited;


	int i = 0;
	while (!done) 
	{
		if(i != ignore[0] && i != ignore[1] && i != ignore[2])
		{
			if (i == size - 1) {
				temp = make_pair(vrtxs[i],vrtxs[0]);
			}
			else {
				temp = make_pair(vrtxs[i], vrtxs[i+1]);
			}

			cout << temp.first.x << " " << temp.first.y << endl;
			cout << temp.second.x << " " << temp.second.y << endl;
			result = IntersectionOf2Lines(myEdge, temp);

			cout << result.first << endl;

			if (result.first) {

				if (index < i) {
					polygon_1.push_back(result.second);
					for (int k = i + 1; k < size; k++)
					{
						polygon_1.push_back(vrtxs[k]);
					}

					for (int k = 0; k < index + 1; k++)
					{
						polygon_1.push_back(vrtxs[k]);
					}

					polygon_2.push_back(result.second);
					for (int k = index + 1; k < i + 1; k++)
					{
						polygon_2.push_back(vrtxs[k]);
					}

					splited = make_pair(polygon_1, polygon_2);

					return splited;
				}
				else {
					polygon_1.push_back(result.second);
					for (int k = index + 1; k < size; k++)
					{
						polygon_1.push_back(vrtxs[k]);
					}

					for (int k = 0; k < i + 1; k++)
					{
						polygon_1.push_back(vrtxs[k]);
					}


					int next = index + 1;
					if (next == size) { next = 0; }

					polygon_2.push_back(result.second);
					for (int k = i + 1; k < index+1; k++)
					{
						polygon_2.push_back(vrtxs[k]);
					}

					splited = make_pair(polygon_1, polygon_2);

					return splited;
				}



				break;

			}
		}

		i++;
	}


}



void SplitPolygon(vector<Vertex> vrtxs) {

	// Assuming They Are Given In A Counterclockwise Order
	int size = (int)vrtxs.size();

	Vertex first;
	Vertex second;
	Vertex third;
	Vertex fourth;

	vector<pair<Vertex,Vertex>> polygon;
	vector<vector<Vertex>> polygons;

	bool concave = false;
	bool done = false;

	pair<Vertex, Vertex> edge_1;
	pair<Vertex, Vertex> edge_2;

	int num = 0;

	int i = 0;
	while (!done)
	{


		if (i == size - 2) {
			first = vrtxs[i];
			second = vrtxs[i + 1];
			edge_1 = make_pair(first, second);
			polygon.push_back(edge_1);

			third = vrtxs[i + 1];
			fourth = vrtxs[0];

			edge_2 = make_pair(first, second);

			
		}
		else if (i == size - 1) 
		{
			first = vrtxs[i];
			second = vrtxs[0];
			edge_1 = make_pair(first, second);
			polygon.push_back(edge_1);

			third = vrtxs[0];
			fourth = vrtxs[1];

			edge_2 = make_pair(third, fourth);

			done = true;
		}
		else {
			first = vrtxs[i];
			second = vrtxs[i + 1];
			edge_1 = make_pair(first, second);
			polygon.push_back(edge_1);

			third = vrtxs[i + 1];
			fourth = vrtxs[i + 2];

			edge_2 = make_pair(third,fourth);
		}


		if (ConcaveEdgePair(edge_1, edge_2)) 
		{


			concave = true;


			pair<vector<Vertex>,vector<Vertex>> pols = FindIntersection(i,vrtxs);

			// RECURSIVE :

			SplitPolygon(pols.first);

			SplitPolygon(pols.second);

			break;

		}

		i++;

		num++;
			
	}

	if (!concave) {
		DrawPolygon(vrtxs);
	}


}

void PolygonOne() {
	int xs[] = { 100,100,200,100,400,400 };
	int ys[] = { 400,300,200,100,100,400 };
	int length = 6;

	vector<Vertex> vrtxs;
	Vertex v;

	for (int i = 0; i < length; i++)
	{
		v.x = xs[i];
		v.y = ys[i];
		vrtxs.push_back(v);
	}

	SplitPolygon(vrtxs);
}

void PolygonTwo() {
	int xs[] = {200,300,400,500,600,700,800,900,900,200};
	int ys[] = {200,200,300,200,200,300,200,200,500,500};
	int length = 10;

	vector<Vertex> vrtxs;
	Vertex v;

	for (int i = 0; i < length; i++)
	{
		v.x = xs[i];
		v.y = ys[i];
		vrtxs.push_back(v);
	}

	SplitPolygon(vrtxs);
}

void PolygonThree() {
	int xs[] = { 200,300,400,500,600,700,800,900,900,500,400,300,200 };
	int ys[] = { 200,200,300,200,200,300,200,200,500,500,400,500,500 };
	int length = 13;

	vector<Vertex> vrtxs;
	Vertex v;

	for (int i = 0; i < length; i++)
	{
		v.x = xs[i];
		v.y = ys[i];
		vrtxs.push_back(v);
	}

	SplitPolygon(vrtxs);

}

void init()
{

	glNewList(ONE, GL_COMPILE);
	PolygonOne();
	glEndList();
	
	glNewList(TWO, GL_COMPILE);
	PolygonTwo();
	glEndList();

	glNewList(THREE, GL_COMPILE);
	PolygonThree();
	glEndList();

}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(-50,500,0);
	glCallList(ONE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(350, 400, 0);
	glCallList(TWO);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(100, 50, 0);
	glCallList(THREE);
	glPopMatrix();

	glFlush();
}


void reshape(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspestRatio = (float)width / height;
	if (width > height)
	{
		gluOrtho2D(0, 1000 * aspestRatio, 0, 1000);
	}
	else
	{
		gluOrtho2D(0, 1000, 0, 1000 / aspestRatio);
	}

	glViewport(0, 0, width, height);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);

	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Splitter");

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 1000, 0, 1000);

	init();

	glutDisplayFunc(render);
	glutReshapeFunc(reshape);


	glutMainLoop();
}