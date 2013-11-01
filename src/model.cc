#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "model.h"

using namespace std;

Model::Model(std::string const &path)
{
	loadModel(path);

	for (WavefrontObject &wo : d_objects)
	{
		// Create a VAO
		glGenVertexArrays(1, &wo.vao);
		glBindVertexArray(wo.vao);

		// Create a VBO
		glGenBuffers(1, &wo.vbo); // Generate 1 buffer
		glBindBuffer(GL_ARRAY_BUFFER, wo.vbo);

		// Copy vertex data into VBO
		glBufferData(GL_ARRAY_BUFFER, wo.vboArray.size() * sizeof(float), wo.vboArray.data(), GL_STATIC_DRAW);
	}
}

Model::~Model()
{
	for (WavefrontObject &wo : d_objects)
	{
		glDeleteBuffers(1, &wo.vbo);
		glDeleteVertexArrays(1, &wo.vao);
	}
}

void Model::initAttributes(ShaderProgram &shaderProgram)
{
	for (WavefrontObject &wo : d_objects)
	{
		glBindVertexArray(wo.vao);
		glBindBuffer(GL_ARRAY_BUFFER, wo.vbo);

		// Link array buffer to "position" attribute
		GLint posAttrib = shaderProgram.attribute("position");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

		GLint normAttrib = shaderProgram.attribute("normal");
		glEnableVertexAttribArray(normAttrib);
		glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));

		// Link array buffer to "texcoord" attribute
		GLint texAttrib = shaderProgram.attribute("texcoord");
		glEnableVertexAttribArray(texAttrib);
		glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	}
}

void Model::draw() const
{
	for (WavefrontObject const &wo : d_objects)
	{
		glBindVertexArray(wo.vao);
		//cout << "drawing " << wo.name << " with " << (wo.vboArray.size() / 8) << "vertices.\n";
		glDrawArrays(GL_TRIANGLES, 0, wo.vboArray.size() / 8);
	}
}

void Model::insertVertices(vector<size_t> indices, int *vertIdx, int *texIdx, int *normIdx)
{
	vector<float> &arr = d_objects.back().vboArray;

	glm::vec3 vert[3], norm[3];
	glm::vec2 tex[3];
	int j = 0;

	for (size_t i : indices)
	{
		vert[j] = d_objects.back().verts[vertIdx[i] - 1];

		if (texIdx[i] > 0)
			tex[j] = d_objects.back().texcoords[texIdx[i] - 1];
		else if (texIdx[i] < 0)
			tex[j] = *(d_objects.back().texcoords.end() + texIdx[i]);
		else
			tex[j] = glm::vec2(0.0f);

		if (normIdx[i] > 0)
			norm[j] = d_objects.back().norms[normIdx[i] - 1];
		else if (normIdx[i] < 0)
			norm[j] = *(d_objects.back().norms.end() + normIdx[i]);
		else
			norm[j] = glm::vec3(0.0f);

		arr.insert(arr.end(), {vert[j].x, vert[j].y, vert[j].z});
		arr.insert(arr.end(), {norm[j].x, norm[j].y, norm[j].z});
		arr.insert(arr.end(), {tex[j].x, tex[j].y});

		++j;
	}
}

void Model::loadModel(string const &path)
{
	ifstream modelFile(path);
	if (not modelFile)
		throw string("failed to load model '" + path + "' from file.");

	bool smoothing; // TODO
	bool firstObject = true;
	d_objects.push_back(WavefrontObject());

	while (modelFile)
	{
		string currentLine, type;
		
		getline(modelFile, currentLine);
		stringstream lineStream(currentLine);
		lineStream >> type;

		// comment
		if (type == "#")
			continue;

		// object name
		else if (type == "o")
		{
			string name;
			lineStream >> name;

			if (not firstObject)
				d_objects.push_back(WavefrontObject());

			firstObject = false;

			d_objects.back().name = name;
		}

		// smoothing group
		else if (type == "s")
		{
			// Sets the smoothing group number
			// to disable: 0 or 'off'
			// to enable: any other positive number
			size_t smoothNum = 0;
			lineStream >> smoothNum;

			if (smoothNum > 0)
				smoothing = true;
		}

		// vertex specification
		else if (type == "v")
		{
			// v x y z
			float x, y, z;
			lineStream >> x >> y >> z;

			d_objects.back().verts.push_back(glm::vec3(x, y, z));
		}

		// vertex normal specification
		else if (type == "vn")
		{
			// vn i j k
			float i, j, k;
			lineStream >> i >> j >> k;

			d_objects.back().norms.push_back(glm::vec3(i, j, k));
		}

		// texture coordinate specification
		else if (type == "vt")
		{
			// vt u v(0) w(0)
			float u, v = 0;
			lineStream >> u >> v;

			d_objects.back().texcoords.push_back(glm::vec2(u, 1.0f-v));
		}

		// face specification
		else if (type == "f")
		{
			// f v1(/[vt1]/vn1) v2(/[vt2]/vn2) v3(/[vt3]/vn3) v4(/[vt4]/vn4)  ...
			// minimum of 3 vertices, no maximum
			// indices start from 1, can be negative to count relatively upwards
			// in the file (-1 is the last one before this line)

			size_t vertNum = 0;
			int vertIdx[4], texIdx[4], normIdx[4];
			while (lineStream)
			{
				string vertStr;
				lineStream >> vertStr;

				if (vertStr.size() == 0)
					continue;

				if (vertStr.find("//") != string::npos) // v and vn are given
				{
					sscanf(vertStr.c_str(), "%d//%d", &vertIdx[vertNum], &normIdx[vertNum]);
					texIdx[vertNum] = 0;
				}
				else if (vertStr.find("/") != string::npos) // v, vt and vn are given
				{
					sscanf(vertStr.c_str(), "%d/%d/%d", &vertIdx[vertNum], &texIdx[vertNum], &normIdx[vertNum]);
				}
				else // only v is given
				{
					sscanf(vertStr.c_str(), "%d", &vertIdx[vertNum]);
					texIdx[vertNum] = 0;
					normIdx[vertNum] = 0;
				}

				++vertNum;
				if (vertNum == 4)
					break;
			}

			if (vertNum < 3)
				throw string(path + ": face statement with less than three vertices.");

			// triangle
			insertVertices({0, 1, 2}, vertIdx, texIdx, normIdx);

			if (vertNum == 4) // square, extra triangle
				insertVertices({2, 3, 0}, vertIdx, texIdx, normIdx);
		}

		else if (type.length() > 0)
		{
			throw string(path + ": unsupported command '" + type + "' found.");
		}
	}
}