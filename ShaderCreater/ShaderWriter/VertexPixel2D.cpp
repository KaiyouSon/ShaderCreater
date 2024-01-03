#include "VertexPixel2D.h"
#include <fstream>
#include <sstream>

std::string VertexPixel2D::folderPath = "Template/VP2D";

std::string VertexPixel2D::ReadFileContent(const std::ifstream& file)
{
	std::string fileContent;
	if (file.is_open() == true)
	{
		// ファイルの内容をすべて読み込む
		std::stringstream buffer;
		buffer << file.rdbuf();
		fileContent = buffer.str();
	}

	return fileContent;
}

void VertexPixel2D::WriteHeader(std::ofstream& file)
{
	// HLSLファイルを書き込みモードで開きます
	std::string fullPath = folderPath + "/" + "VP2D.hlsli";
	std::ifstream templateFile(fullPath);

	// ファイルの内容を読み込む
	std::string fileContent = ReadFileContent(templateFile);

	// ファイルを閉じる
	templateFile.close();

	file << fileContent << std::endl;
}

void VertexPixel2D::WriteVertex(std::ofstream& file, const std::string headerName)
{
	// HLSLファイルを書き込みモードで開きます
	std::string fullPath = folderPath + "/" + "VP2DVS.hlsl";
	std::ifstream templateFile(fullPath);

	// ファイルの内容を読み込む
	std::string fileContent = ReadFileContent(templateFile);

	// ファイルを閉じる
	templateFile.close();

	file << "#include \"" + headerName + "\"" << std::endl;
	file << fileContent << std::endl;
}

void VertexPixel2D::WritePixel(std::ofstream& file, const std::string headerName)
{
	// HLSLファイルを書き込みモードで開きます
	std::string fullPath = folderPath + "/" + "VP2DPS.hlsl";
	std::ifstream templateFile(fullPath);

	// ファイルの内容を読み込む
	std::string fileContent = ReadFileContent(templateFile);

	// ファイルを閉じる
	templateFile.close();

	file << "#include \"" + headerName + "\"" << std::endl;
	file << fileContent << std::endl;
}
