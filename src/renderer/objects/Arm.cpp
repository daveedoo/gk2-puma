#include "Arm.h"
#include <array>
#include <fstream>
#include <sstream>
#include <iostream>

VerticesData Arm::GetVertexData() const
{
	VerticesData data;
	// read data from filename line by line
	std::string filepath = "./res/" + this->filename;
	std::ifstream filestream(filepath);
	std::string line;
	std::vector<glm::vec3> vertexPositions;
	std::getline(filestream, line);
	int vertexPositionCount = std::stoi(line);
	vertexPositions.reserve(vertexPositionCount);
	for (int i = 0; i < vertexPositionCount; i++)
	{
		std::getline(filestream, line);
		std::istringstream iss(line);
		float x, y, z;
		iss >> x >> y >> z;
		vertexPositions.push_back(glm::vec3(x, y, z));
	}
	std::getline(filestream, line);
	data.vertexCount = std::stoi(line);
	data.vertices.reserve(data.vertexCount);
	for (int i = 0; i < data.vertexCount; i++)
	{
		std::getline(filestream, line);
		std::istringstream iss(line);
		int index;
		float x, y, z;
		iss >> index >> x >> y >> z;
		VertexPosNormal vertex = {
			vertexPositions[index],
			glm::vec3(x, y, z)
		};
		data.vertices.push_back(vertex);
	}
	std::getline(filestream, line);
	int triangleCount = std::stoi(line);
	data.triangles.reserve(triangleCount);
	data.triangleCount = triangleCount;
	for (int i = 0; i < triangleCount; i++)
	{
		std::getline(filestream, line);
		std::istringstream iss(line);
		unsigned int i1, i2, i3;
		iss >> i1 >> i2 >> i3;
		data.triangles.push_back({ i1, i2, i3 });
	}
	//TODO load edges
	filestream.close();

	return data;
}
