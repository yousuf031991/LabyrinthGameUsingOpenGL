#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include "imathvec.h"

//Not a good way to deal with a namespace, but quite convenient
using namespace Imath;
using namespace std;


// Feel free to specify the template with other types
typedef Vec3<float> Vec3f;
typedef Vec2<float> Vec2f;

struct Mesh {
	// vertex
	vector<Vec3f> dot_vertex;
	vector<Vec3f> dot_normalPerFace;
	vector<Vec3f> dot_normalPerFaceVis;
	vector<Vec3f> dot_normalPerVertex;
	vector<Vec3f> dot_normalPerVertexWeighted;
	vector<Vec2f> dot_texture;
	// faces
	vector<int> face_index_vertex;
	vector<int> face_index_normalPerFace;
	vector<int> face_index_normalPerVertex;
	vector<int> face_index_normalPerVertexWeighted;
	vector<int> face_index_texture;
	vector<float> area_per_face;

	Vec3f localBoundingMinPoint;
	Vec3f localBoundingMaxPoint;	
	public:
		void calculateAABB();
};
#endif