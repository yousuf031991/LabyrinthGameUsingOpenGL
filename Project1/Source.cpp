#include <iostream>
#include <GL/glut.h>
#include <stdio.h>
#include "mesh.h"
#include "loader.h"
#include "oo_unit.h"

#define MIN2(a,b) (((a) < (b))?(a):(b))
#define MAX2(a,b) (((a) > (b))?(a):(b))

using namespace Imath;
using namespace std;

GLuint boxCarBB, boxCarBB1, boxCarBB2, carBB2List, carBB3List;
// menu
const int SMOOTH = 0;
const int FLAT = 1;
const int V_OVERVIEW = 2;
const int V_FPS = 3;
const int V_TOP = 100;
// menu - display list
const int DLIST_ON = 4;
const int DLIST_OFF = 5;
// submenu Car speed
const int SLOW = 6;
const int MEDIUM = 7;
const int FAST = 8;
// submenu nav
const int N_LIGHT = 9;
const int N_FPS = 10;
// submenu materials
const int M_DIFFUSE = 11;
const int M_SPECULAR = 12;
const int M_DESIGN = 13;
//submenu crease angles
const int C_15 = 14;
const int C_25 = 15;
const int C_35 = 16;
//submenu Normal Vis
const int N_V_ON = 17;
const int N_V_OFF = 18;
//submenu NormalS
const int N_PER_FACE = 19;
const int N_NON_WEIGHTED = 20;
const int N_WEIGHTED = 21;
//submenu texturing
const int T_ON = 22;
const int T_OFF = 23;

//displa List
const int D_LIST_ON = 41;
const int D_LIST_OFF = 42;

//submenu plane
const int P_FLAT = 26;
const int P_MULTI = 27;
const int P_MARBLE = 28;

const float PI = 3.14159;

//light submenu
const int L_ON = 29;
const int L_OFF = 30;
//collision
const int C_ON = 111;
const int C_OFF = 112;
// models
const char* modelfile[] = {
	"..\\data\\porsche.obj",
	"..\\data\\45.obj",
	"..\\data\\f-16.obj",
	"..\\data\\al.obj",
	"..\\data\\dolphins.obj",	
	"..\\data\\rose+vase.obj"	
};

//display list
GLuint listName;
char xst[15], yst[15], zst[15];
char lxst[15], lyst[15], lzst[15];
char cxst[15], cyst[15], czst[15];
char clxst[15], clyst[15], clzst[15];
char camAnglest[25];
// variable to change view
int viewType = 0;
// variable to control display list setting
bool dispListOn = false;

int height = 700;
int width = 600;
int initStru = 78;
// car controls
bool timerStart = false;
int timeForTimer = 1;
float speed = 6.0;
float carPosX = 520.0, carPosZ = 100.0, carPosY = 10.0;
float carLx = 0.0f, carLy = 0.0f, carLz = 1.0f;
float carAngle = 0.0;
int blinkCount = 0;

int dist = 700;
float angleObj1 = 2.0;
float angleObj2 = 2.0;
// light
float angleSun = 0.0;
GLfloat light_position[] = { 0.0, 100.0, 0.0, 1.0 };
bool lightOn = true;
bool navLight = false;

bool collisionOn = true;
bool collided = false;
// normals
int normalType = 1;
int normalOn = 0;

// material
int materialType = 0;

// texture
int textureOn = 1;

//noise
int noiseType = 0;

float camAngle = 0.0;
float x = 600.0, y = 300.0, z = -100.0;
float lx = 600.0, ly = 1.0, lz = 600.0;
float ratio = 1.0;

float bulletSpeed = 2.5;

Mesh* mesh2;
Mesh* mesh3;
Mesh* mesh4;
Mesh* mesh5;
Mesh* mesh6;
Mesh* mesh7;
Mesh * mesh1;

Unit * carBB = new Unit();
Unit * carRevolve1BB = new Unit();
Unit * carRevolve2BB = new Unit();
Unit * carBB2 = new Unit();
Unit * carBB3 = new Unit();

GLuint displayPlaneMarble[3][2][2];
GLuint displayPlaneMulti[3][2][2];
GLuint displayCar, display45;
GLuint displayPlane[3][2][2];
GLuint displayCylinder[3][2][2];
GLuint displayCube1[3][2][2];
GLuint displayCube2[3][2][2];

GLuint displayDome[3][2][2];

int labrynth[][6] = {
	{ 790, 0, 50, 10, 50, 800 },
	{ 100, 0, 50, 10, 50, 800 },
	{ 100, 0, 840, 400, 50, 10 },
	{ 600, 0, 840, 200, 50, 10 },
	{ 600, 0, 650, 10, 50, 200 },
	{ 690, 0, 550, 10, 50, 200 },
	{ 400, 0, 540, 300, 50, 10 },
	//{ 500, 0, 840, 100, 50, 10 },
	{ 500, 0, 550, 10, 50, 200 },
	{ 400, 0, 740, 100, 50, 10 },
	{ 400, 0, 650, 10, 50, 100 },
	{ 200, 0, 740, 100, 50, 10 },
	{ 300, 0, 450, 10, 50, 300 },
	{ 100, 0, 640, 200, 50, 10 },
	{ 200, 0, 450, 100, 50, 10 },
	{ 190, 0, 450, 10, 50, 100 },
	{ 400, 0, 350, 10, 50, 200 },
	{ 300, 0, 350, 400, 50, 10 },
	{ 100, 0, 350, 100, 50, 10 },
	{ 190, 0, 150, 10, 50, 200 },
	{ 190, 0, 150, 100, 50, 10 },
	{ 290, 0, 150, 10, 50, 100 },
	{ 690, 0, 150, 10, 50, 200 },
	{ 500, 0, 150, 200, 50, 10 },
	{ 500, 0, 50, 10, 50, 100 },
	{ 500, 0, 50, 300, 50, 10 },
	{ 100, 0, 50, 300, 50, 10 },
	{ 400, 0, 50, 10, 50, 200 },
	{ 400, 0, 250, 200, 50, 10 },
};

const int labrynthLen = 28;
GLuint newMesh[labrynthLen];
/* ------------------------------------------- BEGIN::TEXTURES -------------------------------------- */
int permutation[] = { 151,160,137,91,90,15,
131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};

// noise class
class ImprovedNoise {

private:
	int p[512];

public:

	ImprovedNoise() {
		for (int i = 0; i < 256; i++)
			p[256 + i] = p[i] = permutation[i];
	}

public:

	double perlinMarble(float x, float y) {
		double total = 0;
		double scale = 0.12;
		double p = 3.0; //0.1; //persistence 
		double n = 6.0; // number of octaves
		double frequency, amplitude;
		for (int i = 0; i<n; i++) {
			frequency = pow(2, (double)i);
			amplitude = pow(p, (double)-i) * 2;
			total = total + noise(scale*frequency* x, scale*frequency* y, 11.5) * amplitude;
		}
		return sin(2 * (x*scale) + total);
	}

	double perlinMultiscale(float x, float y) {
		double total = 0;
		double scale = 0.2;
		double p = 3.0; //0.1; //persistence 
		double n = 6.0; // number of octaves
		double frequency, amplitude;
		for (int i = 0; i<n; i++) {
			frequency = pow(2, (double)i);
			amplitude = pow(p, (double)-i) * 2;
			total = total + noise(scale*frequency* x, scale*frequency* y, 11.5) * amplitude;
		}
		return total;
	}

	double noise(double x, double y, double z) {
		// find unit cube that contains point
		int X = (int)floor(x) & 255;
		int	Y = (int)floor(y) & 255;
		int Z = (int)floor(z) & 255;
		// find relative x,y,z of point in cube
		x -= floor(x);
		y -= floor(y);
		z -= floor(z);
		//compute fade curves for each x,y,z
		double u = fade(x);
		double v = fade(y);
		double w = fade(z);
		// hash coordinates of the 8 cube corners
		int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z;
		int B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;
		// add blended results from 8 corners of cube
		return lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z),
			grad(p[BA], x - 1, y, z)),
			lerp(u, grad(p[AB], x, y - 1, z),
				grad(p[BB], x - 1, y - 1, z))),
			lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1),
				grad(p[BA + 1], x - 1, y, z - 1)),
				lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
					grad(p[BB + 1], x - 1, y - 1, z - 1))));
	}

	static double fade(double t) {
		return t * t * t * (t * (t * 6 - 15) + 10);
	}

	static double lerp(double t, double a, double b) {
		return a + t * (b - a);
	}

	// convert 4 bits of hash code into 12 gradient directions.
	static double grad(int hash, double x, double y, double z) {
		int h = hash & 15;
		double u = h<8 ? x : y, v = h<4 ? y : h == 12 || h == 14 ? x : z;
		return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
	}

};
/* ------------------------------------------- END::NOISE -------------------------------------- */
/* ------------------------------------------- BEGIN::TEXTURES -------------------------------------- */
#include <windows.h>
#include <wingdi.h>

// textures with BITMAPS
GLuint textureArray[8];

// Load a DIB/BMP file from disk.
GLubyte *LoadDIBitmap(const char *filename, BITMAPINFO **info) {
	FILE *fp;      // open file pointer
	GLubyte * bits; // bitmap pixel bits
	int bitsize;   // Size of bitmap
	int infosize;  // Size of header information
	BITMAPFILEHEADER header; // File header
							 // try opening the file; use "rb" mode to read this *binary* file.
	if ((fp = fopen(filename, "rb")) == NULL) {
		cout << "Returning null";
		return (NULL);
	}
	// read the file header and any following bitmap information.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		// Couldn't read the file header - return NULL.
		fclose(fp);
		return (NULL);
	}
	// Check for BM reversed.
	if (header.bfType != 'MB') {
		// not a bitmap file - return NULL.
		fclose(fp);
		return (NULL);
	}
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		// couldn't allocate memory for bitmap info - return NULL.
		fclose(fp);
		return (NULL);
	}
	if (fread(*info, 1, infosize, fp) < infosize) {
		// Couldn't read the bitmap header - return NULL.
		free(*info);
		fclose(fp);
		return (NULL);
	}
	// Now that we have all the header info read in, allocate memory for the bitmap and read *it* in.
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8 * abs((*info)->bmiHeader.biHeight);
	if ((bits = (GLubyte *)malloc(bitsize)) == NULL) {
		// Couldn't allocate memory - return NULL!
		free(*info);
		fclose(fp);
		return (NULL);
	}
	if (fread(bits, 1, bitsize, fp) < bitsize) {
		// couldn't read bitmap - free memory and return NULL!
		free(*info);
		free(bits);
		fclose(fp);
		return (NULL);
	}
	// OK, everything went fine - return the allocated bitmap.
	fclose(fp);
	return (bits);
}

float scaleIt(float x) {
	return (x + 1) / 2;
}

Vec3f topSky(float a) {
	Vec3f black = Vec3f(0, 0, 0);
	Vec3f color = Vec3f(0.8, 0.34, 0.3);
	return ((1 - a) * black + a * color);
}

float noiseParameter(float u, float v) {
	float temp = 0;
	ImprovedNoise n1;
	for (int i = 1; i <= 7; i++) {
		temp += pow(1.5, (double)-i) * n1.noise(pow(2, (double)i) * u, pow(2, (double)i) * v, 11.5);
	}
	return temp;
}

void codedTexture(UINT textureArray[], int n)
{
	const int TexHeight = 500;
	const int TexWidth = 500;
	// create texture in memory
	GLubyte textureImage[TexHeight][TexWidth][4];
	ImprovedNoise no1;
	for (int i = 0; i < TexHeight; i++)
		for (int j = 0; j < TexWidth; j++)
		{
			Vec3f pix = topSky(scaleIt(noiseParameter((float)i / TexHeight, (float)j / TexWidth)));
			textureImage[i][j][0] = pix[0] * 255; 
			textureImage[i][j][1] = pix[1] * 255; 
			textureImage[i][j][2] = pix[2] * 255; 
			textureImage[i][j][3] = 100;
		}
	// setup texture
	glGenTextures(1, &textureArray[n]);
	glBindTexture(GL_TEXTURE_2D, textureArray[n]);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 									
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TexWidth, TexHeight, GL_BGRA_EXT, GL_UNSIGNED_BYTE, textureImage);
}

// bmpTexture
void bmpTexture(UINT textureArray[], LPSTR file, int n) {
	BITMAPINFO *bitmapInfo; // Bitmap information
	GLubyte    *bitmapBits; // Bitmap data
	if (!file) {
		cout << "texture file not found!" << endl;
		return;
	}
	bitmapBits = LoadDIBitmap(file, &bitmapInfo);
	glGenTextures(1, &textureArray[n]);
	glBindTexture(GL_TEXTURE_2D, textureArray[n]);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // must set to 1 for compact data
										   // glTexImage2D Whith size and minification
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bitmapInfo->bmiHeader.biWidth, bitmapInfo->bmiHeader.biHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bitmapBits);
}

/* ------------------------------------------- END::TEXTURES ----------------------------------------- */

/* ------------------------------------------- END::BULLET ----------------------------------------- */
class Bullet {
	public:
		float initX;
		float initZ;
		float initY;
		float nextX;
		float nextZ;
		bool active;
		Bullet(float x1, float z1, float y1, float x2, float z2);
};

Bullet::Bullet(float x1, float z1, float y1, float x2, float z2) {
	initX = x1;
	initZ = z1; 
	initY = y1;
	nextX = x2;
	nextZ = z2;
	active = true;
}

vector<Bullet> arrBul;

void bulletShoot() {
	for (int i = 0; i < arrBul.size(); i++) {
		if (arrBul[i].active) {
			arrBul[i].initX = arrBul[i].initX + bulletSpeed* arrBul[i].nextX;
			arrBul[i].initZ = arrBul[i].initZ + bulletSpeed* arrBul[i].nextZ;			
			if (arrBul[i].initX > 1500 || arrBul[i].initX < -1500 || arrBul[i].initZ > 1500 || arrBul[i].initZ < -1500) {				
					arrBul[i].active = false;				
			}
		}
	}
}

void bulletDisplay() {
	int delNum = -1;
	for (int i = 0; i < arrBul.size(); i++) {
		if (arrBul[i].active) {
			glPushMatrix();
			glTranslatef(arrBul[i].initX, arrBul[i].initY, arrBul[i].initZ);			
			//glutSolidSphere(5.0, 10.0, 10.0);
			glRotated(carAngle * 180 / PI, 0, 1, 0);			
			glCallList(display45);
			glPopMatrix();
		}
		else {
			delNum = i;
		}
	}
	if(delNum >= 0)
		arrBul.erase(arrBul.begin() + delNum);
}

/* ------------------------------------------- END::BULLET ----------------------------------------- */

// scene parameters
Vec3f bbxMin, bbxMax, bbxCenter;

// normal per face
void calculateNormalPerFace(Mesh* m) {
	Vec3f v1, v2, v3, v4, v5, v6;
	float area;
	for (int i = 0; i < m->face_index_vertex.size(); i += 3) {
		v1 = m->dot_vertex[m->face_index_vertex[i]];
		v2 = m->dot_vertex[m->face_index_vertex[i + 1]];
		v3 = m->dot_vertex[m->face_index_vertex[i + 2]];
		v6 = (v1 + v2 + v3) / 3;
		v4 = (v2 - v1);
		v5 = (v3 - v1);
		area = v4.cross(v5).length() / 2;
		m->area_per_face.push_back(area);
		v4 = v4.cross(v5);		
		v4 = v4.normalize();
		m->dot_normalPerFace.push_back(v4);
		m->dot_normalPerFaceVis.push_back(v6);
		int pos = m->dot_normalPerFace.size() - 1;
		// same normal for all vertex in this face
		m->face_index_normalPerFace.push_back(pos);
		m->face_index_normalPerFace.push_back(pos);
		m->face_index_normalPerFace.push_back(pos);
	}
}

// calculate normal per vertex and weighted
void calculateNormalPerVertex(Mesh* m) {
	m->dot_normalPerVertex.clear();
	m->face_index_normalPerVertex.clear();
	Vec3<float> suma; suma.x = 0; suma.y = 0; suma.z = 0;
	//initialize
	for (unsigned int val = 0; val < m->dot_vertex.size(); val++) {
		m->dot_normalPerVertex.push_back(suma);
		m->dot_normalPerVertexWeighted.push_back(suma);
	}
	// calculate sum for vertex
	for (long pos = 0; pos < m->face_index_vertex.size(); pos++) {
		m->dot_normalPerVertex[m->face_index_vertex[pos]] +=
			m->dot_normalPerFace[m->face_index_normalPerFace[pos]];
		m->dot_normalPerVertexWeighted[m->face_index_vertex[pos]] +=
			m->dot_normalPerFace[m->face_index_normalPerFace[pos]] * m->area_per_face[m->face_index_normalPerFace[pos]];
	}
	// normalize for vertex 
	for (unsigned int val = 0; val < m->dot_normalPerVertex.size(); val++) {
		m->dot_normalPerVertex[val] = m->dot_normalPerVertex[val].normalize();
		m->dot_normalPerVertexWeighted[val] = m->dot_normalPerVertexWeighted[val].normalize();
	}
	//normalVertexIndex is the same that vertexIndex
	for (unsigned int pos = 0; pos < m->face_index_vertex.size(); pos++) {
		m->face_index_normalPerVertex.push_back(m->face_index_vertex[pos]);
		m->face_index_normalPerVertexWeighted.push_back(m->face_index_vertex[pos]);
	}
}

void drawLabrynth() {
	for (int i = 0; i < labrynthLen; i++) {
		int xlap = 0;
		int zlap = 0;
		GLuint mesh = 0;
		if (labrynth[i][3] == 10) {
			xlap = 10;
			zlap = 100;
			mesh = displayCube2[normalType][normalOn][textureOn];
		}
		else {
			xlap = 100;
			zlap = 10;
			mesh = displayCube1[normalType][normalOn][textureOn];
		}
		for (int x = 0; x < labrynth[i][3]; x += xlap)
			for (int z = 0; z < labrynth[i][5]; z += zlap) {
				glPushMatrix();
				glTranslatef(labrynth[i][0] + x, labrynth[i][1], labrynth[i][2] + z);
				glCallList(mesh);
				glPopMatrix();
			}
	}
}

// creating a triangulated plane
Mesh* createPlane(int arena_width, int arena_depth, int arena_cell, int noiseType) {
	Mesh *me = new Mesh;
	int n = arena_width / arena_cell;
	int m = arena_depth / arena_cell;
	int something = 80;
	ImprovedNoise n2;
	// vertices
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if(noiseType == 0)
				me->dot_vertex.push_back(Vec3<GLfloat>(i*arena_cell, 0.0, j*arena_cell));
			else if(noiseType == 1)
				me->dot_vertex.push_back(Vec3<GLfloat>(i*arena_cell, something*cos((float)i / 6.0) * n2.perlinMarble(i, j), j*arena_cell));
			else
				me->dot_vertex.push_back(Vec3<GLfloat>(i*arena_cell, something * n2.perlinMultiscale(i, j), j*arena_cell));
		}
	}
	//texture
	me->dot_texture.push_back(Vec2<GLfloat>(0.0, 0.0));
	me->dot_texture.push_back(Vec2<GLfloat>(0.0, 1.0));
	me->dot_texture.push_back(Vec2<GLfloat>(1.0, 0.0));
	me->dot_texture.push_back(Vec2<GLfloat>(1.0, 1.0));
	// faces
	for (int i = 0; i < (n*m) - m; i++) {
		if ((i + 1) % n == 0) continue;
		me->face_index_vertex.push_back(i); me->face_index_vertex.push_back(i + 1);
		me->face_index_vertex.push_back(i + n);
		me->face_index_vertex.push_back(i + 1); me->face_index_vertex.push_back(i + n + 1);
		me->face_index_vertex.push_back(i + n);
		// index for texture
		/*for (int t = 0; t < 6; t++) {*/
			me->face_index_texture.push_back(3);//0
			me->face_index_texture.push_back(2);//2
			me->face_index_texture.push_back(1);//1
			me->face_index_texture.push_back(2);//0
			me->face_index_texture.push_back(0);//3
			me->face_index_texture.push_back(1);//2
		/*}*/
	}
	return me;
}

Mesh* createCylinder(int radius, int height) {
	Mesh* mesh = new Mesh;
	int index = 0;

	for (int i = 0; i < 360; i += 18) {
		float angleone = ((float)i)*M_PI / 180;
		float angletwo = ((float)(i + 18))*M_PI / 180;

		mesh->dot_vertex.push_back(Vec3<GLfloat>(radius*cos(angleone), height, radius*sin(angleone)));
		mesh->dot_vertex.push_back(Vec3<GLfloat>(radius*cos(angleone), 0, radius*sin(angleone)));
		mesh->dot_vertex.push_back(Vec3<GLfloat>(radius*cos(angletwo), 0, radius*sin(angletwo)));
		mesh->dot_vertex.push_back(Vec3<GLfloat>(radius*cos(angletwo), height, radius*sin(angletwo)));

		int j = 4 * index;
		mesh->face_index_vertex.push_back(j);
		mesh->face_index_vertex.push_back(j + 2);
		mesh->face_index_vertex.push_back(j + 1);
		mesh->face_index_vertex.push_back(j);
		mesh->face_index_vertex.push_back(j + 3);
		mesh->face_index_vertex.push_back(j + 2);
		index += 1;


		mesh->dot_texture.push_back(Vec2<GLfloat>(0.0, 1.0));
		mesh->dot_texture.push_back(Vec2<GLfloat>(1.0, 1.0));
		mesh->dot_texture.push_back(Vec2<GLfloat>(1.0, 0.0));
		mesh->dot_texture.push_back(Vec2<GLfloat>(0.0, 0.0));
		for (int t = 0; t<6; t++) {
			mesh->face_index_texture.push_back(0);//0
			mesh->face_index_texture.push_back(2);//1
			mesh->face_index_texture.push_back(1);//2
			mesh->face_index_texture.push_back(0);//0
			mesh->face_index_texture.push_back(3);//2
			mesh->face_index_texture.push_back(2);//3
		}
	}
	return mesh;
}

Mesh* createCube(int BOX_WIDTH, int BOX_HEIGHT, int BOX_DEPTH) {
	Mesh *mesh = new Mesh;
	// Vertexes

	mesh->dot_vertex.push_back(Vec3<GLfloat>(0.0, BOX_HEIGHT, BOX_DEPTH));
	mesh->dot_vertex.push_back(Vec3<GLfloat>(BOX_WIDTH, BOX_HEIGHT, BOX_DEPTH));
	mesh->dot_vertex.push_back(Vec3<GLfloat>(BOX_WIDTH, 0.0, BOX_DEPTH));
	mesh->dot_vertex.push_back(Vec3<GLfloat>(0.0, 0.0, BOX_DEPTH));

	mesh->dot_vertex.push_back(Vec3<GLfloat>(0.0, BOX_HEIGHT, 0.0));
	mesh->dot_vertex.push_back(Vec3<GLfloat>(BOX_WIDTH, BOX_HEIGHT, 0.0));
	mesh->dot_vertex.push_back(Vec3<GLfloat>(BOX_WIDTH, 0.0, 0.0));
	mesh->dot_vertex.push_back(Vec3<GLfloat>(0.0, 0.0, 0.0));

	// face 1
	mesh->face_index_vertex.push_back(0);//0
	mesh->face_index_vertex.push_back(2);//1
	mesh->face_index_vertex.push_back(1);//2
	mesh->face_index_vertex.push_back(0);//0
	mesh->face_index_vertex.push_back(3);//2
	mesh->face_index_vertex.push_back(2);//3
										 // face 2
	mesh->face_index_vertex.push_back(0);//0
	mesh->face_index_vertex.push_back(5);//1
	mesh->face_index_vertex.push_back(4);//5
	mesh->face_index_vertex.push_back(0);//0
	mesh->face_index_vertex.push_back(1);//5
	mesh->face_index_vertex.push_back(5);//4
										 // face 3
	mesh->face_index_vertex.push_back(1);//1
	mesh->face_index_vertex.push_back(6);//2
	mesh->face_index_vertex.push_back(5);//6
	mesh->face_index_vertex.push_back(1);//1
	mesh->face_index_vertex.push_back(2);//6
	mesh->face_index_vertex.push_back(6);//5
										 // face 4
	mesh->face_index_vertex.push_back(2);//2
	mesh->face_index_vertex.push_back(7);//3
	mesh->face_index_vertex.push_back(6);//7
	mesh->face_index_vertex.push_back(2);//2
	mesh->face_index_vertex.push_back(3);//7
	mesh->face_index_vertex.push_back(7);//6
										 // face 5
	mesh->face_index_vertex.push_back(4);//0
	mesh->face_index_vertex.push_back(3);//3
	mesh->face_index_vertex.push_back(0);//7
	mesh->face_index_vertex.push_back(4);//0
	mesh->face_index_vertex.push_back(7);//7
	mesh->face_index_vertex.push_back(3);//4
										 // face 6
	mesh->face_index_vertex.push_back(5);//4 
	mesh->face_index_vertex.push_back(7);//5
	mesh->face_index_vertex.push_back(4);//6
	mesh->face_index_vertex.push_back(5);//4
	mesh->face_index_vertex.push_back(6);//6
	mesh->face_index_vertex.push_back(7);//7

										 // texture
	mesh->dot_texture.push_back(Vec2<GLfloat>(0.0, 1.0));
	mesh->dot_texture.push_back(Vec2<GLfloat>(1.0, 1.0));
	mesh->dot_texture.push_back(Vec2<GLfloat>(1.0, 0.0));
	mesh->dot_texture.push_back(Vec2<GLfloat>(0.0, 0.0));
	for (int t = 0; t < 6; t++) {
		mesh->face_index_texture.push_back(0);//0
		mesh->face_index_texture.push_back(2);//1
		mesh->face_index_texture.push_back(1);//2
		mesh->face_index_texture.push_back(0);//0
		mesh->face_index_texture.push_back(3);//2
		mesh->face_index_texture.push_back(2);//3
	}

	return mesh;
}

Mesh* createDome(bool b) {
	int radius = 550;
	//int newradius = 250;
	int height = 0;
	int newheight = 150;
	int index = 0;
	int radiusindex = 40;

	Mesh* mesh = new Mesh;
	for (int t = 0; t < 5; t++) {
		int i;
		if (t % 2 == 0)
			i = 0;
		else
			i = 9;
		int newradius = radius - radiusindex;
		if (t == 4)
			newheight -= 100;
		//cout << t << " " << radius << " " << newradius << " " << height << " " << newheight << endl;
		for (; i < 360; i += 18) {

			float angleone = ((float)i)*M_PI / 180;
			float angletwo = ((float)(i + 9))*M_PI / 180;
			float anglethree = ((float)(i + 18))*M_PI / 180;
			float anglefour = ((float)(i + 27))*M_PI / 180;

			if (b) {
				glPushMatrix();
				glBegin(GL_LINE_STRIP);
				glVertex3f(radius*cos(angleone), height, radius*sin(angleone));
				glVertex3f(newradius*cos(angletwo), newheight, newradius*sin(angletwo));
				glVertex3f(radius*cos(anglethree), height, radius*sin(anglethree));
				glEnd();
				glPopMatrix();
			}

			else {

				mesh->dot_vertex.push_back(Vec3<GLfloat>(radius*cos(angleone), height, radius*sin(angleone)));
				mesh->dot_vertex.push_back(Vec3<GLfloat>(newradius*cos(angletwo), newheight, newradius*sin(angletwo)));
				mesh->dot_vertex.push_back(Vec3<GLfloat>(radius*cos(anglethree), height, radius*sin(anglethree)));

				mesh->dot_vertex.push_back(Vec3<GLfloat>(newradius*cos(angletwo), newheight, newradius*sin(angletwo)));
				mesh->dot_vertex.push_back(Vec3<GLfloat>(radius*cos(anglethree), height, radius*sin(anglethree)));
				mesh->dot_vertex.push_back(Vec3<GLfloat>(newradius*cos(anglefour), newheight, newradius*sin(anglefour)));

				int j = index * 6;
				mesh->face_index_vertex.push_back(j);
				mesh->face_index_vertex.push_back(j + 2);
				mesh->face_index_vertex.push_back(j + 1);
				mesh->face_index_vertex.push_back(j + 3);
				mesh->face_index_vertex.push_back(j + 4);
				mesh->face_index_vertex.push_back(j + 5);

				mesh->dot_texture.push_back(Vec2<GLfloat>(0.0, 1.0));
				mesh->dot_texture.push_back(Vec2<GLfloat>(1.0, 1.0));
				mesh->dot_texture.push_back(Vec2<GLfloat>(1.0, 0.0));
				mesh->dot_texture.push_back(Vec2<GLfloat>(0.0, 0.0));
				for (int t = 0; t<6; t++) {
					mesh->face_index_texture.push_back(0);//0
					mesh->face_index_texture.push_back(2);//1
					mesh->face_index_texture.push_back(1);//2
					mesh->face_index_texture.push_back(0);//0
					mesh->face_index_texture.push_back(3);//2
					mesh->face_index_texture.push_back(2);//3
				}

			}
			index += 1;
		}
		//index = 0;
		radius = newradius;
		radiusindex += 35;
		height += 150;
		newheight += 150;
	}
	if (!b)
		return mesh;
}

// draw
GLuint meshToDisplayList(Mesh* m, int id, int normalType, int normalOn) {
	GLuint listID = glGenLists(id);
	m->calculateAABB();
	glNewList(listID, GL_COMPILE);
	if (id != 10000) {
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, textureArray[id - 1]);
	}
	glBegin(GL_TRIANGLES);
	for (unsigned int i = 0; i < m->face_index_vertex.size(); i++) {
		
		// PER FACE NORMALS
		if (normalType == 0) {
			if ((!m->dot_normalPerFace.empty() && !m->face_index_normalPerFace.empty())) {
				glNormal3fv(&m->dot_normalPerFace[m->face_index_normalPerFace[i]].x);
				
			}
		}
		else if (normalType == 1) {
			if ((!m->dot_normalPerVertex.empty() && !m->face_index_normalPerVertex.empty())) {
				glNormal3fv(&m->dot_normalPerVertex[m->face_index_normalPerVertex[i]].x);				
			}
		}
		else {
			if ((!m->dot_normalPerVertexWeighted.empty() && !m->face_index_normalPerVertexWeighted.empty())) {
				glNormal3fv(&m->dot_normalPerVertexWeighted[m->face_index_normalPerVertexWeighted[i]].x);
			}
		}
		// TEXTURES
		if (!m->dot_texture.empty() && !m->face_index_texture.empty()) {
			glTexCoord2fv(&m->dot_texture[m->face_index_texture[i]].x);
		}
		// COLOR
		Vec3f offset = (m->dot_vertex[m->face_index_vertex[i]]);
		// VERTEX
		//glColor3f(fabs(sin(offset.x)), fabs(cos(offset.y)), fabs(offset.z));
		glVertex3fv(&m->dot_vertex[m->face_index_vertex[i]].x);
	}	
	glEnd();
	if (normalOn) {		
		vector<Vec3f> curNormals, tNormal;
		if (normalType == 0)
			curNormals = m->dot_normalPerFace;
		else if (normalType == 1)
			curNormals = m->dot_normalPerVertex;
		else 
			curNormals = m->dot_normalPerVertexWeighted;
		glColor3f(1, 0, 0);
		glLineWidth(5.0);
		for (unsigned int i = 0; i < curNormals.size(); i++) {
			glBegin(GL_LINES);			
			Vec3f v3 = curNormals[i];
			if (normalType == 0) {				
				V3f vVis1 = m->dot_normalPerFaceVis[i];
				V3f vVis2 = vVis1 + curNormals[i] * 100;
				glVertex3fv(&vVis1.x);
				glVertex3fv(&vVis2.x);
				glEnd();
				continue;
			}
			/*cout << v3 << "\n";*/
			v3 *= 100;
			/*cout << v3 << "\n";*/
			glVertex3fv(&curNormals[i].x);
			glVertex3fv(&v3.x);
			//glVertex3fv(&m->dot_normalPerVertex[i].x);
			glEnd();
		}		
	}
	if (id != 10000) {
		glDisable(GL_TEXTURE_2D);
	}
	glEndList();
	return listID;
}

void collideTrue() {
	collided = true;
	glLoadIdentity();
	carPosX = 520.0, carPosZ = 100.0, carPosY = 10.0;
	carLx = 0.0f, carLy = 0.0f, carLz = 1.0f;
	gluLookAt(carPosX, carPosY, carPosZ,
		carPosX + carLx, carPosY + carLy, carPosZ + carLz,
		0.0f, 1.0f, 0.0f);
	timeForTimer = 0;
}

void renderBitmapString(float x, float y, float z, char *string) {
	char *c;
	glRasterPos3f(x, y, z);   // fonts position
	for (c = string; *c != '\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
}

void renderBitmapString2(float x, float y, float z, char *string) {
	char *c;
	glRasterPos3f(x, y, z);   // fonts position
	for (c = string; *c != '\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
}

void blinkText() {	
	if (blinkCount % 2 == 0)
		glColor3f(1, 0, 0);
	else
		glColor3f(0, 1, 0);
	blinkCount++;
	renderBitmapString2(200.0, 20.0, 0.0, "FINISH!");	
}

bool global_matrix[900][900];

void createMatrix() {
	for (int x = 0; x < 900; x++)
		for (int z = 0; z < 900; z++)
			global_matrix[x][z] = true;

	for (int i = 0; i < labrynthLen; i++) {
		for (int x = 0; x < labrynth[i][3]; x++)
			for (int z = 0; z < labrynth[i][5]; z++)
			{
				global_matrix[labrynth[i][0] + x][labrynth[i][2] + z] = false;
				if (labrynth[i][0] + x + 5 <= 900)
				{
					global_matrix[labrynth[i][0] + x + 5][labrynth[i][2] + z] = false;
					if (labrynth[i][2] + z + 5 <= 900)
					{
						global_matrix[labrynth[i][0] + x + 5][labrynth[i][2] + z + 5] = false;
					}
				}			

				if (labrynth[i][0] + x - 5 >= 0)
				{
					global_matrix[labrynth[i][0] + x - 5][labrynth[i][2] + z] = false;
					if (labrynth[i][2] + z - 5 >= 0)
					{
						global_matrix[labrynth[i][0] + x - 5][labrynth[i][2] + z - 5] = false;
					}
				}			

				if (labrynth[i][2] + z + 5 <= 900)
				{
					global_matrix[labrynth[i][0] + x][labrynth[i][2] + z + 5] = false;
					if (labrynth[i][0] + x + 5 <= 900)
					{
						global_matrix[labrynth[i][0] + x + 5][labrynth[i][2] + z + 5] = false;
					}
				}				
				if (labrynth[i][2] + z - 5 >= 0)
				{
					global_matrix[labrynth[i][0] + x][labrynth[i][2] + z - 5] = false;
					if (labrynth[i][0] + x - 5 >= 0)
					{
						global_matrix[labrynth[i][0] + x - 5][labrynth[i][2] + z - 5] = false;
					}
				}				

			}
	}
}



void display() {	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();	
	glViewport(0, 0, width, height * 6 / 7); // the first viewport for the actual game
	gluPerspective(90.0, ratio, 1.0, 2000);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();	
	glLoadIdentity();

	if (materialType == 0)
	{
		GLfloat obj_diffuse[] = { 0.9, 0.9, 0.9, 1.0 };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, obj_diffuse);
		GLfloat obj_emission[] = { 0.1, 0.1, 0.1, 1.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, obj_emission);
		GLfloat obj_specular[] = { 0.0, 0.0, 0.0, 1.0 };
		glMaterialfv(GL_FRONT, GL_SPECULAR, obj_specular);
		GLfloat obj_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
		glMaterialfv(GL_FRONT, GL_AMBIENT, obj_ambient);
	}
	else if (materialType == 1)
	{
		GLfloat obj_specular[] = { 0.9, 0.9, 0.9, 1.0 };
		glMaterialfv(GL_FRONT, GL_SPECULAR, obj_specular);
		GLfloat obj_diffuse[] = { 0.9, 0.9, 0.9, 1.0 };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, obj_diffuse);
		GLfloat obj_emission[] = { 0.1, 0.1, 0.1, 0.1 };
		glMaterialfv(GL_FRONT, GL_EMISSION, obj_emission);
		GLfloat obj_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
		glMaterialfv(GL_FRONT, GL_AMBIENT, obj_ambient);
	}
	else
	{
		GLfloat obj_specular[] = { 0.1, 0.1, 0.1, 0.1 };
		glMaterialfv(GL_FRONT, GL_SPECULAR, obj_specular);
		GLfloat obj_diffuse[] = { 0.9, 0.9, 0.9, 1.0 };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, obj_diffuse);
		GLfloat obj_emission[] = { 0.1, 0.1, 0.1, 0.1 };
		glMaterialfv(GL_FRONT, GL_EMISSION, obj_emission);
		GLfloat obj_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
		glMaterialfv(GL_FRONT, GL_AMBIENT, obj_ambient);
	}
	
	if (viewType == 1) {
		if (collisionOn == true) {
			carBB->mapping();
			boxCarBB = carBB->boxToDisplayList(80);
			glCallList(boxCarBB);
		}
		gluLookAt(carPosX, carPosY, carPosZ,
			carPosX + carLx, carPosY + carLy, carPosZ + carLz,
			0.0f, 1.0f, 0.0f);
		bulletDisplay();
		bulletShoot();			
	}
	else if(viewType == 0){		
		// draw car	
		gluLookAt(x, y, z,
			lx, ly, lz,
			0.0f, 1.0f, 0.0f);
		glPushMatrix();		
		glTranslatef(carPosX, carPosY, carPosZ);
		glScalef(0.5, 0.5, 0.5);				
		glCallList(displayCar);
		glPopMatrix();
	}
	else if (viewType == 2){	
		
		gluLookAt(550, 600, 550,
			550, 0, 550,
			0.0f, 0.0f, 1.0f);
		glPushMatrix();
		glTranslatef(carPosX, carPosY, carPosZ);
		glScalef(0.5, 0.5, 0.5);
		glCallList(displayCar);
		glPopMatrix();
	}

	// draw plane
	if (noiseType == 0)
		glCallList(displayPlane[normalType][normalOn][textureOn]);			
	else if(noiseType == 1)
		glCallList(displayPlaneMarble[normalType][normalOn][textureOn]);
	else
		glCallList(displayPlaneMulti[normalType][normalOn][textureOn]);
	
	//dome
	glPushMatrix();
	glTranslatef(515.0, 0.0, 515.0);
	glCallList(displayDome[normalType][normalOn][textureOn]);
	glPopMatrix();

	// cylinders
	//cylinder 1 with double orbit
	glPushMatrix();
	glTranslatef(550.0, 0.0, 520.0);
	if (collisionOn == true) {
		carRevolve1BB->position.x = 550.0;
		carRevolve1BB->position.y = 0.0;
		carRevolve1BB->position.z = 520.0;
		carRevolve1BB->mapping();
		boxCarBB1 = carRevolve1BB->boxToDisplayList(81);
		glCallList(boxCarBB1);
	}
	glCallList(displayCylinder[normalType][normalOn][textureOn]);
	glPushMatrix();
	glTranslatef(0.0, 150.0, 0.0);
	glPushMatrix();	
	glRotatef(angleObj1, 0.0, 1.0, 0.0);
	glTranslatef(100.0, 0.0, 0.0);
	glutSolidSphere(10.0, 10.0, 10.0);
	glPushMatrix();
	glRotatef(angleObj1, 0.0, 1.0, 0.0);
	glTranslatef(50.0, 0.0, 0.0);
	glScalef(0.2, 0.2, 0.2);
	if (collisionOn) {
		carBB3->mapping();
		carBB3List = carBB3->boxToDisplayList(89);
		glCallList(carBB3List);
	}
	glCallList(displayCar);	
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	//cylinder 2 with static orbit
	glTranslatef(-250.0, 0.0, 50.0);
	if (collisionOn) {
		carRevolve2BB->position.x = 200.0;
		carRevolve2BB->position.y = 0.0;
		carRevolve2BB->position.z = 570.0;
		carRevolve2BB->mapping();
		boxCarBB2 = carRevolve2BB->boxToDisplayList(83);
		glCallList(boxCarBB2);
	}
	glCallList(displayCylinder[normalType][normalOn][textureOn]);

	glPushMatrix();	
	glTranslatef(0.0, 150.0, 0.0);
	glPushMatrix();
	glutSolidSphere(15.0, 15.0, 15.0);

	glRotatef(angleObj1, 0.0, 1.0, 0.0);
	glTranslatef(100.0, 0.0, 0.0);
	glRotatef(-angleObj1, 0.0, 1.0, 0.0);
	glScalef(0.4, 0.4, 0.4);
	if (collisionOn == true) {
		carBB2->mapping();
		carBB2List = carBB2->boxToDisplayList(84);
		glCallList(carBB2List);
	}
	glCallList(displayCar);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();		

	// labrynth
	glPushMatrix();
	//glTranslatef(-500, 0, -500);
	glTranslatef(60, 0, 60);
	drawLabrynth();
	glPopMatrix();
	renderBitmapString2(625, 25, 900, "FINISH");
	renderBitmapString2(525, 25, 200, "START"); 
	// light
	glPushMatrix();
	glTranslatef(450.0, 300.0, 450.0);
	glRotatef(angleSun, 0.0, 1.0, 0.0);
	glTranslatef(450.0, 0.0, 0.0);
	GLfloat mat_emission2[] = { 1.0, 1.0, 1.0, 0.0 };
	//glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission2);
	//glutSolidSphere(30.0, 20.0, 20.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glPopMatrix();
	if (lightOn) {
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
	}
	else {
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
	}
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glViewport(0, 6 * height / 7, width, height / 7);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// top control viewport
	gluOrtho2D(0, width, 0, 100);
	//glColor3f(1.0, 0.0, 0.0);		
	GLfloat cr_specular1[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, cr_specular1);
	GLfloat cr_diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cr_diffuse1);
	GLfloat mat_emission1[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission1);
	GLfloat cr_ambient1[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, cr_ambient1);
	// printing the loaction of camera
	sprintf_s(xst, 15, "x: %f", x);	
	renderBitmapString(20.0, 20.0, 0.0, xst);
	sprintf_s(yst, 15, "y: %f", y);
	renderBitmapString(20.0, 30.0, 0.0, yst);
	sprintf_s(zst, 15, "z: %f", z);
	renderBitmapString(20.0, 40.0, 0.0, zst);
	
	sprintf_s(lxst, 15, "lx: %f", lx);
	renderBitmapString(20.0, 50.0, 0.0, lxst);
	sprintf_s(lyst, 15, "ly: %f", ly);
	renderBitmapString(20.0, 60.0, 0.0, lyst);
	sprintf_s(lzst, 15, "lz: %f", lz);
	renderBitmapString(20.0, 70.0, 0.0, lzst);
	renderBitmapString(20.0, 80.0, 0.0, "Overview coordinates");
	// right side
	sprintf_s(cxst, 15, "x: %f", carPosX);
	renderBitmapString(420.0, 20.0, 0.0, cxst);
	sprintf_s(cyst, 15, "y: %f", carPosY);
	renderBitmapString(420.0, 30.0, 0.0, cyst);
	sprintf_s(czst, 15, "z: %f", carPosZ);
	renderBitmapString(420.0, 40.0, 0.0,czst);

	sprintf_s(clxst, 15, "lx: %f", carLx);
	renderBitmapString(420.0, 50.0, 0.0, clxst);
	sprintf_s(clyst, 15, "ly: %f", carLy);
	renderBitmapString(420.0, 60.0, 0.0, clyst);
	sprintf_s(clzst, 15, "lz: %f", carLz);
	renderBitmapString(420.0, 70.0, 0.0, clzst);
	renderBitmapString(420.0, 80.0, 0.0, "Car coordinates");

	if (timerStart) {
		// calculate and display time
		glColor3f(1, 0, 0);	
		int hh = timeForTimer / 3600;
		int temp = timeForTimer - (hh * 3600);
		int mm = temp / 60;
		int ss = temp - (mm * 60);
		int timeInt[3];
		timeInt[0] = hh;
		timeInt[1] = mm;
		timeInt[2] = ss;
		char timeChar[3][20];
		for (int i = 0; i < 3; i++) {
			ostringstream temp;
			temp << timeInt[i];
			string tempStr = temp.str();
			strcpy_s(timeChar[i], tempStr.c_str());
		}
		if(collided)
			renderBitmapString2(200.0, 10.0, 0.0, "Collision! try again!");
		if (collided && timeForTimer > 3)
			collided = false;
		renderBitmapString2(200.0, 30.0, 0.0, "Press space bar to shoot!!");
		renderBitmapString2(200.0, 80.0, 0.0, "Get to the finish line!!");
		renderBitmapString(200.0, 60.0, 0.0, "Timer");
		renderBitmapString(200.0, 50.0, 0.0, timeChar[0]);
		renderBitmapString(210.0, 50.0, 0.0, ":");
		renderBitmapString(220.0, 50.0, 0.0, timeChar[1]);
		renderBitmapString(230.0, 50.0, 0.0, ":");
		renderBitmapString(240.0, 50.0, 0.0, timeChar[2]);
	}
	//winning condition
	if (carPosX >= 600.0 && carPosX <= 650.0) {
		if (carPosZ >= 850.0 && carPosZ <= 900.0) {
			blinkText();
			timerStart = false;
			timeForTimer = 1;
		}
	}
	glutSwapBuffers();			
	angleObj1 += 0.2;
	if (angleObj1 >= 360.0)
		angleObj1 = 0.0;
	angleObj2 += 0.2;
	if (angleObj2 >= 360.0)
		angleObj2 = 0.0;
	if (collisionOn && viewType == 1) {
		carBB->position.x = carPosX;
		carBB->position.y = carPosY;
		carBB->position.z = carPosZ;
		carBB->mapping();		
		carRevolve1BB->mapping();
		if (carBB->intersect(carRevolve1BB) || carBB->intersect(carRevolve2BB)) {
			collideTrue();			
		}		
	}
}

void processSubMenuEvents(int option) {
	switch (option) {
	case SLOW:
		speed = 2.0;
		break;
	case MEDIUM:
		speed = 8.0;
		break;
	case FAST:
		speed = 16.0;
		break;
	case SMOOTH:
		glShadeModel(GL_SMOOTH);
		break;
	case FLAT:
		glShadeModel(GL_FLAT);
		break;
	case V_OVERVIEW:
		viewType = 0;
		break;
	case V_FPS:
		viewType = 1;
		break;
	case V_TOP:
		viewType = 2;
		break;
	case L_ON:
		lightOn = true;
		break;
	case L_OFF:
		lightOn = false;
		break;
	case N_LIGHT:
		navLight = true;
		break;
	case N_FPS:
		navLight = false;
		break;
	case N_PER_FACE:
		normalType = 0;		
		break;
	case N_NON_WEIGHTED:
		normalType = 1;
		break;
	case N_WEIGHTED:
		normalType = 2;
		break;
	case P_FLAT:
		noiseType = 0;
		break;
	case P_MARBLE:
		noiseType = 1;
		break;
	case P_MULTI:
		noiseType = 2;
		break;
	case T_ON:
		textureOn = 1;
		break;
	case T_OFF:
		textureOn = 0;
		break;	
	case N_V_ON:
		normalOn = 1;		
		break;
	case N_V_OFF:
		normalOn = 0;
		break;	
	case M_DIFFUSE:
		materialType = 0;
		break;
	case M_SPECULAR:
		materialType = 1;
		break;
	case M_DESIGN:
		materialType = 2;
		break;
	case C_ON:
		collisionOn = true;
		break;
	case C_OFF:
		collisionOn = false;
		break;
	}
	glutPostRedisplay();
}

void processMenuEvents(int option) {
	switch (option) {	
	}
	glutPostRedisplay();
}

void orientMe(float ang) {
	x = 600 + dist * sin(ang);
	z = 600 + dist * cos(ang + PI);
	glLoadIdentity();
	gluLookAt(x, y, z,
		lx, ly, lz,
		0.0f, 1.0f, 0.0f);
}

void orientCar(float ang) {
	carLx = sin(ang);
	carLz = cos(ang);
	glLoadIdentity();
	gluLookAt(carPosX, carPosY, carPosZ,
		carPosX + carLx, carPosY + carLy, carPosZ + carLz,
		0.0f, 1.0f, 0.0f);
}

void moveMeFlat(int i) {
	dist += i;
	orientMe(camAngle);
}


void moveCarFlat(int i) {	
	float temp1 = carPosX + i*(carLx);
	float temp2 = carPosZ + i*(carLz);
	int t1 = ceil(temp1);
	int t2 = ceil(temp2);
	if (collisionOn == true) {
		if (global_matrix[t1-60][t2-60]) {			
			carPosX = temp1;
			carPosZ = temp2;
			glLoadIdentity();
			gluLookAt(carPosX, carPosY, carPosZ,
				carPosX + carLx, carPosY + carLy, carPosZ + carLz,
				0.0f, 1.0f, 0.0f);
		}
		else {
			collideTrue();
		}
	}
	else {
		carPosX = temp1;
		carPosZ = temp2;
		glLoadIdentity();
		gluLookAt(carPosX, carPosY, carPosZ,
			carPosX + carLx, carPosY + carLy, carPosZ + carLz,
			0.0f, 1.0f, 0.0f);
	}
}

void moveMeUpDown(int i) {
	y += i;
	glLoadIdentity();
	gluLookAt(x, y, z,
		lx, ly, lz,
		0.0f, 1.0f, 0.0f);
}

void moveCarUpDown(int i) {
	carPosY += i;
	glLoadIdentity();
	gluLookAt(carPosX, carPosY, carPosZ,
		carPosX + carLx, carPosY + carLy, carPosZ + carLz,
		0.0f, 1.0f, 0.0f);
}

void lightMove(float i) {
	angleSun += i;	
}

void hitBullet() {
	Bullet *bul = new Bullet(carPosX, carPosZ, carPosY, carLx, carLz);	
	arrBul.push_back(*bul);
	glutPostRedisplay();
}

void inputKey(unsigned char c, int x, int y) {
	switch (c) {
	case 'a':
		if (viewType == 1)
			moveCarUpDown(speed);		
		else if(viewType == 0)
			moveMeFlat(speed);
		break;
	case 's':
		if (viewType == 1)
			moveCarUpDown(-speed);
		else if(viewType == 0)
			moveMeFlat(-speed);
		break;		
	case ' ':
		if (viewType == 1)
			hitBullet();
	}
}

void specialKeys(int key, int x, int y) {
	if (navLight) {
		switch (key) {
		case GLUT_KEY_LEFT:
			lightMove(5.0);
			break;
		case GLUT_KEY_RIGHT:
			lightMove(-5.0);
			break;
		}
		glutPostRedisplay();
		return;
	}

	switch (key) {
	case GLUT_KEY_UP: // up function key 
		if (viewType == 0) {
			moveMeUpDown(5);
		}
		else if(viewType == 1){
			moveCarFlat(speed);
			timerStart = true;
		}
		break;
	case GLUT_KEY_DOWN:
		if (viewType == 0) {
			moveMeUpDown(-5);
		}
		else if(viewType == 1) {
			moveCarFlat(-speed);
			timerStart = true;
		}
		break;
	case GLUT_KEY_LEFT:
		if (viewType == 0) {
			camAngle += 0.05;
			orientMe(camAngle);
		}
		else if(viewType == 1) {
			carAngle += 0.05;
			orientCar(carAngle);
			timerStart = true;
		}
		break;
	case GLUT_KEY_RIGHT:
		if (viewType == 0) {
			camAngle -= 0.05;
			orientMe(camAngle);
		}
		else if (viewType == 1) {
			carAngle -= 0.05;
			orientCar(carAngle);
			timerStart = true;
			break;
		}
	}
	glutPostRedisplay();
}

void createGLUTMenus() {	
	// submenus
	GLint subMenuSpeed = glutCreateMenu(processSubMenuEvents);
	glutAddMenuEntry("Slow", SLOW);
	glutAddMenuEntry("Medium", MEDIUM);
	glutAddMenuEntry("Fast", FAST);	

	GLint subMenuShading = glutCreateMenu(processSubMenuEvents);
	glutAddMenuEntry("Smooth", SMOOTH);
	glutAddMenuEntry("Flat", FLAT);

	GLint subMenuView = glutCreateMenu(processSubMenuEvents);
	glutAddMenuEntry("Overview - 45", V_OVERVIEW);
	glutAddMenuEntry("First Person", V_FPS);
	glutAddMenuEntry("Overview - Top down", V_TOP);

	GLint subMenuNavigation = glutCreateMenu(processSubMenuEvents);
	glutAddMenuEntry("Light Source", N_LIGHT);
	glutAddMenuEntry("Camera", N_FPS);

	GLint subMenuMaterials = glutCreateMenu(processSubMenuEvents);
	glutAddMenuEntry("Diffuse", M_DIFFUSE);
	glutAddMenuEntry("Specular", M_SPECULAR);
	glutAddMenuEntry("Design", M_DESIGN);

	GLint subMenuCrease= glutCreateMenu(processSubMenuEvents);
	glutAddMenuEntry("15", C_15);
	glutAddMenuEntry("25", C_25);
	glutAddMenuEntry("35", C_35);

	GLint subMenuNormalVisualisation = glutCreateMenu(processSubMenuEvents);
	glutAddMenuEntry("ON", N_V_ON);
	glutAddMenuEntry("OFF", N_V_OFF);

	GLint subMenuDList = glutCreateMenu(processSubMenuEvents);
	glutAddMenuEntry("ON", D_LIST_ON);
	glutAddMenuEntry("OFF", D_LIST_OFF);

	GLint subMenuNormals = glutCreateMenu(processSubMenuEvents);
	glutAddMenuEntry("Per Face Normal", N_PER_FACE);
	glutAddMenuEntry("Per Vertex Normals", N_NON_WEIGHTED);
	glutAddMenuEntry("Per Vertex Normals Weighted", N_WEIGHTED);

	GLint subMenuTexturing = glutCreateMenu(processSubMenuEvents);
	glutAddMenuEntry("ON", T_ON);
	glutAddMenuEntry("OFF", T_OFF);	

	GLint subMenuPlane = glutCreateMenu(processSubMenuEvents);
	glutAddMenuEntry("Flat", P_FLAT);
	glutAddMenuEntry("Marble", P_MARBLE);
	glutAddMenuEntry("Multiscale", P_MULTI);

	GLint subMenuLight = glutCreateMenu(processSubMenuEvents);
	glutAddMenuEntry("ON", L_ON);
	glutAddMenuEntry("OFF", L_OFF);

	GLint subMenuCollision = glutCreateMenu(processSubMenuEvents);
	glutAddMenuEntry("ON", C_ON);
	glutAddMenuEntry("OFF", C_OFF);
	
	// menu
	GLint menu = glutCreateMenu(processMenuEvents);	
	glutAddSubMenu("Shading", subMenuShading);	
	glutAddSubMenu("View", subMenuView);
	glutAddSubMenu("Speed of car", subMenuSpeed);
	glutAddSubMenu("Navigation", subMenuNavigation);
	glutAddSubMenu("Materials", subMenuMaterials);
	glutAddSubMenu("Crease Angles", subMenuCrease);
	glutAddSubMenu("Normal Visualisation", subMenuNormalVisualisation);
	glutAddSubMenu("Normals", subMenuNormals);
	glutAddSubMenu("Texturing", subMenuTexturing);	
	glutAddSubMenu("Display List", subMenuDList);
	glutAddSubMenu("Plane", subMenuPlane);
	glutAddSubMenu("Light", subMenuLight);
	glutAddSubMenu("Collision", subMenuCollision);
	// attach the menu to the right button 
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void reshape(int w, int h) {
	width = w;
	height = h;
	if (h == 0) h = 1;
	ratio = 1.0f * w / h;	
}

void displayArray( GLuint (&dp)[3][2][2], Mesh *mesh, int startId) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				dp[i][j][k] = meshToDisplayList(mesh, startId + k, i, j);				
			}
		}
	}	
}

void init() {	
	ratio = (double)width / (double)height;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	mesh1 = createPlane(1200, 1200, 150, 0);		
	mesh2 = createPlane(1200, 1200, 30, 1);
	mesh3 = createPlane(1200, 1200, 30, 2);	
	mesh4 = createCylinder(20, 200);
	mesh5 = createCube(100, 50, 10);
	mesh6 = createCube(10, 50, 100);
	mesh7 = createDome(false);
	Mesh* mesh10 = ObjLoader::load(modelfile[0]);
	Mesh* mesh11 = ObjLoader::load(modelfile[1]);

	calculateNormalPerFace(mesh1);
	calculateNormalPerVertex(mesh1);
	calculateNormalPerFace(mesh2);
	calculateNormalPerVertex(mesh2);

	calculateNormalPerFace(mesh3);
	calculateNormalPerVertex(mesh3);

	calculateNormalPerFace(mesh4);
	calculateNormalPerVertex(mesh4);

	calculateNormalPerFace(mesh5);
	calculateNormalPerVertex(mesh5);
	calculateNormalPerFace(mesh6);
	calculateNormalPerVertex(mesh6);

	calculateNormalPerFace(mesh7);
	calculateNormalPerVertex(mesh7);

	calculateNormalPerFace(mesh10);
	calculateNormalPerVertex(mesh10);	

	calculateNormalPerFace(mesh11);
	calculateNormalPerVertex(mesh11);

	carBB->mesh = mesh10;
	carBB->mesh->calculateAABB();
	carRevolve1BB->mesh = mesh4;
	carRevolve1BB->mesh->calculateAABB();
	carRevolve2BB->mesh = mesh4;
	carRevolve2BB->mesh->calculateAABB();
	carBB2->mesh = mesh10;
	carBB2->mesh->calculateAABB();
	carBB3->mesh = mesh10;
	carBB3->mesh->calculateAABB();

	bmpTexture(textureArray, "../bmp-files/grass.bmp", 1);	

	// cylinder

	bmpTexture(textureArray, "../bmp-files/oldbox.bmp", 3);	
	bmpTexture(textureArray, "../bmp-files/metalplate.bmp", 5);

	codedTexture(textureArray, 7);
	
	displayArray(displayPlaneMarble, mesh2, 1);
	displayArray(displayPlaneMulti, mesh3, 1);
	displayArray(displayPlane, mesh1, 1);
	displayArray(displayCylinder, mesh4, 3);

	displayArray(displayCube1, mesh5, 5);
	displayArray(displayCube2, mesh6, 5);

	displayArray(displayDome, mesh7, 7);

	displayCar = meshToDisplayList(mesh10, 20, 1, 0);
	display45 = meshToDisplayList(mesh11, 22, 1, 0);	
	/*displayArray(displayCar, mesh10, 30);*/
	createMatrix();

	// light
	GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

void timer(int)
{	
	if (timerStart) {
		timeForTimer += 1;
	}	
	glutPostRedisplay();
	glutTimerFunc(1000.0, timer, 0);
}

int main(int argc, char * argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0); //specifies top-left corner of the window in pixels
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Death Match");	
	glutIdleFunc(display);		
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);	
	glutKeyboardFunc(inputKey);
	glutSpecialFunc(specialKeys);	
	glutTimerFunc(1000.0, timer, 0);
	createGLUTMenus();
	init();
	glutMainLoop();	
}