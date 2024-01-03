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

	std::cout << "ファイル名を入力してください" << std::endl;
	std::string filename;
	std::cin >> filename;
	std::cout << std::endl;

	std::cout << "作成する種類を選択してください" << std::endl;
	std::cout << "1.頂点シェーダ" << std::endl;
	std::cout << "2.ジオメトリシェーダ" << std::endl;
	std::cout << "3.ピクセルシェーダ" << std::endl;
	std::cout << "4.コンピュートシェーダ" << std::endl;

	// 一行で入力された文字列を格納する変数
	std::string inputLine;

	// 一行読み込む
	std::cin.ignore(1024, '\n');
	std::getline(std::cin, inputLine);

	// 入力された文字列をストリームに変換
	std::istringstream inputStream(inputLine);

	// 選択したファイルをビット演算で格納
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

	// 拡張子
	const std::string headerExt = ".hlsli";
	const std::string sourceExt = ".hlsl";

	// フォルダーのパス
	fs::path folderPath = "Shader/" + filename;
	fs::create_directory(folderPath);

	// 先にヘッダーファイルを作成

	// HLSLファイルを書き込みモードで開きます
	std::string fullPath = folderPath.string() + "/" + filename + headerExt;
	std::ofstream hlslFile(fullPath);

	// ファイルが正しく開かれたかを確認します
	if (!hlslFile.is_open())
	{
		std::cerr << "HLSLファイルを開くことができませんでした: " << filename << std::endl;
		return 1; // エラーコードを返してプログラムを終了します
	}

	// 書き込み
	VP3D::WriteHeader(hlslFile);

	// HLSLファイルを閉じます
	hlslFile.close();

	// 設定ファイル
	std::string iniPath = folderPath.string() + "/" + filename + ".ini";
	std::ofstream iniFile(iniPath);

	// ビットを元にソースファイルを作成する
	for (uint32_t i = 0; i < MaxEnumCount; i++)
	{
		uint32_t bit2 = (uint32_t)powf(2, i);

		if (bit & bit2)
		{
			// HLSLファイルを書き込みモードで開きます
			std::string filePath = filename + fileTagMap[(ShaderType)(i + 1)] + sourceExt;
			std::string fullPath = folderPath.string() + "/" + filePath;

			std::ofstream hlslFile(fullPath);

			// ファイルが正しく開かれたかを確認します
			if (!hlslFile.is_open())
			{
				std::cerr << "HLSLファイルを開くことができませんでした: " << filename << std::endl;
				return 1; // エラーコードを返してプログラムを終了します
			}

			if (i == (uint32_t)ShaderType::Vertex - 1)
			{
				// 書き込み
				std::string code;
				VP3D::WriteVertex(hlslFile, filename + headerExt);
				hlslFile << code;
			}
			else if (i == (uint32_t)ShaderType::Pixel - 1)
			{
				// 書き込み
				std::string code;
				VP3D::WritePixel(hlslFile, filename + headerExt);
				hlslFile << code;
			}

			// HLSLファイルを閉じます
			hlslFile.close();

			// 種類とパスを書き込む
			iniFile << fileTagMap[(ShaderType)(i + 1)] + " " + filePath << std::endl;
			//std::cout << fileTagMap[(ShaderType)(i + 1)] << std::endl;
		}
	}

	iniFile.close();

	return 0;
};