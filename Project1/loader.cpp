#include "loader.h"
#include <iostream>
#include <fstream>

using namespace std;
#define MIN2(a,b) (((a) < (b))?(a):(b))
#define MAX2(a,b) (((a) > (b))?(a):(b))

// str to int
inline int StrToInt(const string &str) {
	int i;
	if (sscanf_s(str.c_str(), "%i", &i) == 1) return i;
	else return 0;
}

// split string
inline vector<string> split_string(const string& str, const string& split_str) {
	vector<string> stlv_string;
	string part_string("");
	string::size_type i;
	i = 0;
	while (i < str.size()) {
		if (split_str.find(str[i]) != string::npos) {
			stlv_string.push_back(part_string);
			part_string = "";
			while (split_str.find(str[i]) != string::npos) {
				++i;
			}
		}
		else {
			part_string += str[i];
			++i;
		}
	}
	if (!part_string.empty())
		stlv_string.push_back(part_string);
	return stlv_string;
}

// load file
Mesh* ObjLoader::load(const char* file) {
	Mesh *m = new Mesh;
	m->dot_vertex.clear();
	m->face_index_vertex.clear();
	ifstream infile(file);
	if (infile.fail()) {
		cout << "Error opening file " << file;
		return NULL;
	}
	char current_line[1024];
	while (!infile.eof()) {
		infile.getline(current_line, 1024);
		switch (current_line[0]) {
		case'v':
			float x, y, z;
			switch (current_line[1]) {
			case 'n':
				sscanf_s(current_line, "vn %f %f %f", &x, &y, &z);
				m->dot_normalPerFace.push_back(Vec3f(x, y, z));
				m->dot_normalPerVertex.push_back(Vec3f(x, y, z));
				break;
			case 't':
				sscanf_s(current_line, "vt %f %f", &x, &y);
				m->dot_texture.push_back(Vec2f(x, y));
				break;
			default:
				sscanf_s(current_line, "v %f %f %f", &x, &y, &z);
				m->dot_vertex.push_back(Vec3f(x, y, z));
				break;
			}
			break;
		case 'f': {
			vector<string> faces = split_string(current_line, " \t.\r\n");
			int vnt[3][3] = { { -1, -1, -1 },{ -1, -1, -1 },{ -1, -1, -1 } };
			string::size_type begin, end;
			for (int i = 0; i < 2; i++) {
				begin = 0;
				int j = 0;
				do {
					end = faces[i + 1].find_first_of("/", begin);
					if (begin < end) {
						vnt[i][j] = StrToInt(faces[i + 1].substr(begin, end - begin)) - 1;
					}
					else {
						vnt[i][j] = -1;
					}
					begin = end + 1;
					j++;
				} while (end != string::npos);
			}
			for (unsigned int i = 3; i < faces.size(); i++) {
				begin = 0;
				int j = 0;
				do {
					end = faces[i].find_first_of("/", begin);
					if (begin < end) {
						vnt[2][j] = StrToInt(faces[i].substr(begin, end - begin)) - 1;
					}
					else {
						vnt[2][j] = -1;
					}
					begin = end + 1;
					j++;
				} while (end != string::npos);
				for (int j = 0; j < 3; j++) {
					m->face_index_vertex.push_back(vnt[j][0]);
					if (vnt[j][1] != -1) m->face_index_texture.push_back(vnt[j][1]);
					if (vnt[j][2] != -1) m->face_index_normalPerFace.push_back(vnt[j][2]);
					if (vnt[j][2] != -1) m->face_index_normalPerVertex.push_back(vnt[j][2]);
				}
				memcpy(&vnt[1], &vnt[2], sizeof(int) * 3);
			}
		}
				  break;
		default:
			break;
		}
	}

	return m;
}

void Mesh::calculateAABB() {
	vector<Vec3<float>>& v = this->dot_vertex;
	if (v.empty()) return;
	this->localBoundingMaxPoint = this->localBoundingMinPoint = v[0];
	for (unsigned int i = 1; i < v.size(); i++) {
		this->localBoundingMinPoint.x = MIN2(this->localBoundingMinPoint.x, v[i].x);
		this->localBoundingMinPoint.y = MIN2(this->localBoundingMinPoint.y, v[i].y);
		this->localBoundingMinPoint.z = MIN2(this->localBoundingMinPoint.z, v[i].z);
		this->localBoundingMaxPoint.x = MAX2(this->localBoundingMaxPoint.x, v[i].x);
		this->localBoundingMaxPoint.y = MAX2(this->localBoundingMaxPoint.y, v[i].y);
		this->localBoundingMaxPoint.z = MAX2(this->localBoundingMaxPoint.z, v[i].z);
	}
}