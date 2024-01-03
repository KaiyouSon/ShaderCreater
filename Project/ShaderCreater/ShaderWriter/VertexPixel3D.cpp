#include "VertexPixel3D.h"
#include <fstream>
#include <sstream>

std::string VertexPixel3D::folderPath = "ShaderCreater/Template/VP3D";

std::string VertexPixel3D::ReadFileContent(const std::ifstream& file)
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

void VertexPixel3D::WriteHeader(std::ofstream& file)
{
	// HLSLファイルを書き込みモードで開きます
	std::string fullPath = folderPath + "/" + "VP3D.hlsli";
	std::ifstream templateFile(fullPath);

	// ファイルの内容を読み込む
	std::string fileContent = ReadFileContent(templateFile);

	// ファイルを閉じる
	templateFile.close();

	file << fileContent << std::endl;
}

void VertexPixel3D::WriteVertex(std::ofstream& file, const std::string headerName)
{
	// HLSLファイルを書き込みモードで開きます
	std::string fullPath = folderPath + "/" + "VP3DVS.hlsl";
	std::ifstream templateFile(fullPath);

	// ファイルの内容を読み込む
	std::string fileContent = ReadFileContent(templateFile);

	// ファイルを閉じる
	templateFile.close();

	file << "#include \"" + headerName + "\"" << std::endl;
	file << fileContent << std::endl;
}

void VertexPixel3D::WritePixel(std::ofstream& file, const std::string headerName)
{
	// HLSLファイルを書き込みモードで開きます
	std::string fullPath = folderPath + "/" + "VP3DPS.hlsl";
	std::ifstream templateFile(fullPath);

	// ファイルの内容を読み込む
	std::string fileContent = ReadFileContent(templateFile);

	// ファイルを閉じる
	templateFile.close();

	file << "#include \"" + headerName + "\"" << std::endl;
	file << fileContent << std::endl;
}
