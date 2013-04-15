#include "model.ih"

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

			cout << "o line spotted: name = " << name << endl;
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