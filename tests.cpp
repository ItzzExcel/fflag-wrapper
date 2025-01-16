#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <thread>
#include <chrono>

#include "src/fflags.hpp"

#define print(...) \
	printf("\n");  \
	printf(__VA_ARGS__);

std::string boolToString(bool x) { return x ? "True" : "False"; }

//////////////////////////////////////////////////////

int main(int argc, char const *argv[])
{

	print("Tests running for fflag-wrapper");
	print("\t\"If you write tests, it means you don't believe in yourself\"\n\t-Excel, 2025\n");

	std::string ffGetHomeFolder = fflags::GetHomeFolder();
	if (!ffGetHomeFolder.empty())
	{
		print("GetHomeFolder()\n > %s\n", ffGetHomeFolder.c_str());
	}
	else
	{
		print("GetHomeFolder() returned an empty string.");
	}

	bool ffDirectoryExists = fflags::DirectoryExists(ffGetHomeFolder);
	if (ffDirectoryExists)
	{
		print("DirectoryExists(%s)\n > %s\n", ffGetHomeFolder.c_str(), boolToString(ffDirectoryExists).c_str())
	}
	else
	{
		print("DirectoryExists(%s) returned %s, it should really not.\n", ffGetHomeFolder.c_str(), boolToString(ffDirectoryExists).c_str());
	}

	std::string example_file = ffGetHomeFolder + "\\NTUSER.DAT";
	bool ffFileExists = fflags::FileExists(example_file);
	if (ffFileExists)
	{
		print("FileExists(%s)\n > %s\n", example_file.c_str(), boolToString(ffFileExists).c_str())
	}
	else
	{
		print("FileExists(%s) returned %s, it should really not.\n", example_file.c_str(), boolToString(ffDirectoryExists).c_str());
	}

	std::string example_path = ffGetHomeFolder + "\\AppData\\Local\\Temp\\important_message.txt";
	std::string example_content = "Made by Humans from the Earth";
	bool ffWriteFile = fflags::WriteFile(example_path, example_content);
	if (ffWriteFile)
	{
		print("WriteFile(%s, %s)\n > %s\n", example_path.c_str(), example_content.c_str(), boolToString(ffWriteFile).c_str());
	}
	else
	{
		print("WriteFile(%s, %s) returned %s, it should really not.\n", example_path.c_str(), example_content.c_str(), boolToString(ffWriteFile).c_str());
	}

	std::string example_dir_path = ffGetHomeFolder + "\\AppData\\Local\\Temp\\important_folder";
	bool ffCreateDirectory = fflags::CreateFolder(example_dir_path);
	if (ffCreateDirectory)
	{
		print("CreateFolder(%s)\n > %s\n", example_dir_path.c_str(), boolToString(ffCreateDirectory).c_str())
	}
	else
	{
		print("CreateFolder(%s) returned %s, it should really not.\n", boolToString(ffCreateDirectory).c_str());
	}

	fflags::ALLOW_BLOXSTRAP = false;
	std::string ffGetClientSettings = fflags::GetClientSettings();

	print("GetClientSettings() (ALLOW_BLOXSTRAP = %s)\n > %s\n", boolToString(fflags::ALLOW_BLOXSTRAP).c_str(), ffGetClientSettings.empty() ? "Returned an empty string." : (ffGetClientSettings).c_str());

	fflags::ALLOW_BLOXSTRAP = true;
	ffGetClientSettings = fflags::GetClientSettings();

	print("GetClientSettings() (ALLOW_BLOXSTRAP = %s)\n > %s\n", boolToString(fflags::ALLOW_BLOXSTRAP).c_str(), ffGetClientSettings.empty() ? "Returned an empty string." : (ffGetClientSettings).c_str());

	if (!ffGetClientSettings.empty())
	{
		fflags::ALLOW_BLOXSTRAP = true;

		// Read a value from ClientAppSettings.json
		std::string value = fflags::Read("thomas shelby");
		print("The value of \"thomas shelby\" is %s", value.c_str());

		// Write a value in ClientAppSettings.json
		std::string fps_cap = "999";
		if (fflags::Write("thomas shelby", fps_cap))
		{
			print("\"thomas shelby\" set to %s", fps_cap.c_str());
		}

		// Delete a value from ClientAppSettings.json
		if (fflags::Delete("thomas shelby"))
		{
			print("\"thomas shelby\" deleted from ClientAppSettings.json");
		}
	}

	return 0;
}
