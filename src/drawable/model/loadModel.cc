#include "model.ih"

void Model::loadModel(string const &modelPath)
{
	ifstream modelFile(modelPath);
	if (not modelFile)
	{
		cerr << "Error loading model from file\n";
		return;
	}

	vector<glm::vec3> verts;
	vector<glm::vec3> norms;
	vector<glm::vec2> texcoords;

	while (modelFile)
	{
		string lineStr;
		getline(modelFile, lineStr);

		if (not modelFile)
			break;

		stringstream lineStream(lineStr);

		float x, y, z;
		float u, v;

		string type;
		lineStream >> type;

		if (not lineStream)
			continue;


		if (type == "v") // vertex
		{
			lineStream >> x >> y >> z;

			if (not lineStream)
				continue;

			verts.push_back(glm::vec3(x, y, z));
		}

		else if (type == "vn") // normal
		{
			lineStream >> x >> y >> z;

			if (not lineStream)
				continue;

			norms.push_back(glm::vec3(x, y, z));
		}

		else if (type == "vt") // tex coord
		{
			// TODO: sometimes there's a third (w) coord, read it
			lineStream >> u >> v;

			if (not lineStream)
				continue;

			texcoords.push_back(glm::vec2(u, v));
		}

		else if (type == "f") // face, assume triangles, assume faces come last
		{
			string v[3];
			lineStream >> v[0] >> v[1] >> v[2];

			if (not lineStream)
				continue;

			size_t vertNum[3], texCoordNum[3], normNum[3];

			for (size_t idx = 0; idx != 3; ++idx)
			{
				// Split string of format "123/456/789" or "123//789"
				// into three size_t's.
				// This is probably the worst way to do this
				// TODO: Replace with some fancy GA/STL way
				vertNum[idx] = stoi(v[idx].substr(0, v[idx].find('/')));

				int len = v[idx].find('/', v[idx].find('/') + 1) - (v[idx].find('/') + 1);

				texCoordNum[idx] = 0;
				if (len != 0)
				{
					texCoordNum[idx] = stoi(v[idx].substr(v[idx].find('/') + 1, len));
				}
				
				normNum[idx] = stoi(v[idx].substr(v[idx].find('/') + 1 + len + 1));

				// insert into vertex vector
				// push verts[vertNum[idx]], norms[normNum[idx]], texcoords[texCoordNum[idx]])

				d_verts.insert(d_verts.end(), {verts[vertNum[idx]-1].x, verts[vertNum[idx]-1].y, verts[vertNum[idx]-1].z});
				d_verts.insert(d_verts.end(), {norms[normNum[idx]-1].x, norms[normNum[idx]-1].y, norms[normNum[idx]-1].z});

				if(texCoordNum[idx] != 0)
					d_verts.insert(d_verts.end(), {texcoords[texCoordNum[idx]-1].x, texcoords[texCoordNum[idx]-1].y});
				else
					d_verts.insert(d_verts.end(), {0.0f, 1.0f});
			}
		}
	}

	d_numVerts = d_verts.size() / 8;

	/*
	for(int i = 0; i <= d_verts.size(); i += 8)
	{
		cout << "(" << d_verts[i]   << ", " << d_verts[i+1] << ", " << d_verts[i+2] << ") ";
		cout << "(" << d_verts[i+3] << ", " << d_verts[i+4] << ", " << d_verts[i+5] << ") ";
		cout << "(" << d_verts[i+6] << ", " << d_verts[i+7] << ")\n";
	}

	cout << "number of verts: " << d_numVerts << ", sizeof d_verts: " << d_verts.size() << "\n";
	*/
}