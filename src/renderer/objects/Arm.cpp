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
		if (i < vertexPositionCount && index != i) std::cout << "Index mismatch: " << i << " " << index << std::endl;
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
		i3 = GetRemainingIndex(data, vertexPositions, t1, i1, i2);
		i4 = GetRemainingIndex(data, vertexPositions, t2, i1, i2);
		data.edges.push_back({ i1, i2, i3, i4 });
	}
	filestream.close();

	return data;
}

unsigned int Arm::GetRemainingIndex(VerticesData& data, std::vector<glm::vec3> vertexPositions, unsigned int triangleIndex,
	unsigned int v1, unsigned int v2) const
{
	auto triangle = data.triangles[triangleIndex];
	auto vertices = data.vertices;
	auto pos1 = vertexPositions[v1];
	auto pos2 = vertexPositions[v2];
	auto tPos1 = vertices[triangle[0]].position;
	auto tPos2 = vertices[triangle[1]].position;
	if (tPos1 != pos1 && tPos1 != pos2)
	{
		return triangle[0];
	}
	else if (tPos2 != pos1 && tPos2 != pos2)
	{
		return triangle[1];
	}
	else return triangle[2];
}
