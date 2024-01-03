#pragma once
#include <string>

class VertexPixel2D
{
public:
	static std::string folderPath;

private:
	static std::string ReadFileContent(const std::ifstream& file);

public:
	static void WriteHeader(std::ofstream& file);
	static void WriteVertex(std::ofstream& file, const std::string headerName);
	static void WritePixel(std::ofstream& file, const std::string headerName);

}typedef VP2D;