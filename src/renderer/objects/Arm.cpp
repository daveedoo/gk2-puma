#include "Arm.h"
#include <array>
#include <fstream>
#include <sstream>
#include <iostream>

VerticesData Arm::GetVerticesData() const
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
	std::getline(filestream, line);
	int edgeCount = std::stoi(line);
	data.edges.reserve(edgeCount);
	for (int i = 0; i < edgeCount; i++)
	{
		std::getline(filestream, line);
		std::istringstream iss(line);
		unsigned int i1, i2, i3, i4, t1, t2;
		iss >> i1 >> i2 >> t1 >> t2;
		i3 = GetRemainingIndex(data, t1, i1, i2);
		i4 = GetRemainingIndex(data, t2, i1, i2);
		data.edges.push_back({ i1, i2, i3, i4 });
	}
	filestream.close();

	return data;
}

unsigned int Arm::GetRemainingIndex(VerticesData& data, unsigned int triangleIndex, unsigned int v1, unsigned int v2) const
{
	auto triangle = data.triangles[triangleIndex];
	if (triangle[0] != v1 && triangle[0] != v2)
	{
		return triangle[0];
	}
	else if (triangle[1] != v1 && triangle[1] != v2)
	{
		return triangle[1];
	}
	else return triangle[2];
}
