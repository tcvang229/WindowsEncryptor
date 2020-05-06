#include "FileEnDe.h"
#include <iostream>
#include <string>
#include <fstream>

void ifFileExsist(char *fileName)
{
	std::ofstream file;

	file.open(fileName);

	if (!file)
	{
		std::cout << "Error in creating file.";
	}

	std::cout << "file successfully created: ";
	file.close();
}

void fileEncryption(char *fileName)
{
	std::string fileReader;
	std::ifstream inFile;
	std::ofstream outFile;

	int space = 0;

	inFile.open(fileName);
	outFile.open("fileEncryptor.txt");

	if (inFile.fail())
	{
		std::cerr << "Error: openFile fail.";
		std::exit(1);
	}


	while (!inFile.eof())
	{

		inFile >> fileReader;

		for (int i = 0; i < fileReader.length(); i++)
		{
			fileReader[i] = fileReader[i] + 4;
		}

		
		if (space == 1)
		{
			outFile << " " << fileReader;
		}
		else
		{
			outFile << fileReader;
			space = 1;
		}

	}
	inFile.close();
	outFile.close();
}

void fileDecryption()
{
	std::string fileReader;
	std::ifstream inFile;
	std::ofstream outFile;

	int space = 0;

	inFile.open("fileEncryptor.txt");
	outFile.open("fileDecryptor.txt");

	if (inFile.fail())
	{
		std::cerr << "Error: openFile fail.";
		std::exit(1);
	}


	while (!inFile.eof())
	{
		inFile >> fileReader;

		for (int i = 0; i < fileReader.length(); i++)
		{
			fileReader[i] = fileReader[i] - 4;
		}

		if (space == 1)
		{
			outFile << " " << fileReader;
		}
		else
		{
			outFile << fileReader;
			space = 1;
		}
	}
	inFile.close();
	outFile.close();
}