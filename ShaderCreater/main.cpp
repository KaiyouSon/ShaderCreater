#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <map>
#include <filesystem>
#include "ShaderWriter.h"

namespace fs = std::filesystem;

enum class ShaderType
{
	Vertex = 1,
	Geometry,
	Pixel,
	Compute,
};

const uint32_t MaxEnumCount = 4;

int main()
{
	std::map<ShaderType, std::string> fileTagMap =
	{
		{ ShaderType::Vertex,	"VS" },
		{ ShaderType::Geometry, "GS" },
		{ ShaderType::Pixel,	"PS" },
		{ ShaderType::Compute,	"CS" },
	};

	std::cout << "�t�@�C��������͂��Ă�������" << std::endl;
	std::string filename;
	std::cin >> filename;
	std::cout << std::endl;

	std::cout << "�쐬�����ނ�I�����Ă�������" << std::endl;
	std::cout << "1.���_�V�F�[�_" << std::endl;
	std::cout << "2.�W�I���g���V�F�[�_" << std::endl;
	std::cout << "3.�s�N�Z���V�F�[�_" << std::endl;
	std::cout << "4.�R���s���[�g�V�F�[�_" << std::endl;

	// ��s�œ��͂��ꂽ��������i�[����ϐ�
	std::string inputLine;

	// ��s�ǂݍ���
	std::cin.ignore(1024, '\n');
	std::getline(std::cin, inputLine);

	// ���͂��ꂽ��������X�g���[���ɕϊ�
	std::istringstream inputStream(inputLine);

	// �I�������t�@�C�����r�b�g���Z�Ŋi�[
	uint32_t number;
	uint32_t bit = 0;
	while (inputStream >> number)
	{
		if (number >= MaxEnumCount)
		{
			continue;
		}

		bit |= (uint32_t)powf(2, number - 1);
	}
	//std::cout << bit << std::endl;

	// �g���q
	const std::string headerExt = ".hlsli";
	const std::string sourceExt = ".hlsl";

	// �t�H���_�[�̃p�X
	fs::path folderPath = "Shader/" + filename;
	fs::create_directory(folderPath);

	// ��Ƀw�b�_�[�t�@�C�����쐬

	// HLSL�t�@�C�����������݃��[�h�ŊJ���܂�
	std::string fullPath = folderPath.string() + "/" + filename + headerExt;
	std::ofstream hlslFile(fullPath);

	// �t�@�C�����������J���ꂽ�����m�F���܂�
	if (!hlslFile.is_open())
	{
		std::cerr << "HLSL�t�@�C�����J�����Ƃ��ł��܂���ł���: " << filename << std::endl;
		return 1; // �G���[�R�[�h��Ԃ��ăv���O�������I�����܂�
	}

	// ��������
	VP3D::WriteHeader(hlslFile);

	// HLSL�t�@�C������܂�
	hlslFile.close();

	// �ݒ�t�@�C��
	std::string iniPath = folderPath.string() + "/" + filename + ".ini";
	std::ofstream iniFile(iniPath);

	// �r�b�g�����Ƀ\�[�X�t�@�C�����쐬����
	for (uint32_t i = 0; i < MaxEnumCount; i++)
	{
		uint32_t bit2 = (uint32_t)powf(2, i);

		if (bit & bit2)
		{
			// HLSL�t�@�C�����������݃��[�h�ŊJ���܂�
			std::string filePath = filename + fileTagMap[(ShaderType)(i + 1)] + sourceExt;
			std::string fullPath = folderPath.string() + "/" + filePath;

			std::ofstream hlslFile(fullPath);

			// �t�@�C�����������J���ꂽ�����m�F���܂�
			if (!hlslFile.is_open())
			{
				std::cerr << "HLSL�t�@�C�����J�����Ƃ��ł��܂���ł���: " << filename << std::endl;
				return 1; // �G���[�R�[�h��Ԃ��ăv���O�������I�����܂�
			}

			if (i == (uint32_t)ShaderType::Vertex - 1)
			{
				// ��������
				std::string code;
				VP3D::WriteVertex(hlslFile, filename + headerExt);
				hlslFile << code;
			}
			else if (i == (uint32_t)ShaderType::Pixel - 1)
			{
				// ��������
				std::string code;
				VP3D::WritePixel(hlslFile, filename + headerExt);
				hlslFile << code;
			}

			// HLSL�t�@�C������܂�
			hlslFile.close();

			// ��ނƃp�X����������
			iniFile << fileTagMap[(ShaderType)(i + 1)] + " " + filePath << std::endl;
			//std::cout << fileTagMap[(ShaderType)(i + 1)] << std::endl;
		}
	}

	iniFile.close();

	return 0;
};