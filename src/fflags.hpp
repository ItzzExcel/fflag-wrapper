/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * ░▒█▀▀▀░▒█▀▀▀░█░░█▀▀▄░█▀▀▀░░░▒█░░▒█░█▀▀▄░█▀▀▄░▄▀▀▄░▄▀▀▄░█▀▀░█▀▀▄
 * ░▒█▀▀░░▒█▀▀░░█░░█▄▄█░█░▀▄░░░▒█▒█▒█░█▄▄▀░█▄▄█░█▄▄█░█▄▄█░█▀▀░█▄▄▀
 * ░▒█░░░░▒█░░░░▀▀░▀░░▀░▀▀▀▀░░░▒▀▄▀▄▀░▀░▀▀░▀░░▀░█░░░░█░░░░▀▀▀░▀░▀▀
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * Written by ItzzExcel for https://github.com under the MIT License.
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * https://github.com/ItzzExcel/fflag-wrapper/
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * Yes, it's that simple.
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 * Public changable values:
 * 	- define: #define AUTOCREATE_JSON_FILE
 * 	- ::ALLOW_BLOXSTRAP = <bool>

 * Public functions:
 * 	- ::Read(<string> fflag_id) => <string> fflag value
 * 	- ::Write(<string> fflag_id, <string> content) => <bool> operation completed
 * 	- ::Delete(<string fflag_id> => <bool> operation completed

 * Internal auxiliar functions:
 * 	- ::GetHomePath(<void>) => <string> user's home folder path
 * 	- ::DirectoryExists(<string> directory_path) => <bool>
 * 	- ::FileExists(<string> file_path) => <bool>
 * 	- ::WriteFile(<string> file_path, <string> content) => <bool> operation completed
 * 	- ::CreateFolder(<string> directory_path) => <bool> operation completed
 * 	- ::GetClientSettings(<void>) => <string returns the path of the Roblox root folder depending if the Bloxstrap bool is set to true/false
*/

#define AUTOCREATE_JSON_FILE

#include <ShlObj.h>
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
#include "include/json.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

namespace fflags
{
	// public:
	bool ALLOW_BLOXSTRAP = false;

	// internal:
	std::string GetHomeFolder()
	{
		char path[MAX_PATH];

		HRESULT result = SHGetFolderPathA(NULL, CSIDL_PROFILE, NULL, 0, path);

		if (result != S_OK)
			return "";

		return std::string(path);
	}

	bool DirectoryExists(std::string file_path)
	{
		DWORD fileAttributes = GetFileAttributesA(file_path.c_str());
		if (fileAttributes == INVALID_FILE_ATTRIBUTES)
			return false;

		return (fileAttributes & FILE_ATTRIBUTE_DIRECTORY);
	}

	bool FileExists(std::string file_path)
	{
		DWORD fileAttributes = GetFileAttributesA(file_path.c_str());
		return (fileAttributes != INVALID_FILE_ATTRIBUTES) && !(fileAttributes & FILE_ATTRIBUTE_DIRECTORY);
	}

	bool WriteFile(std::string file_path, std::string content)
	{
		std::ofstream(file_path) << content;
		return std::ofstream(file_path).good();
	}

	bool CreateFolder(std::string dir_path)
	{
		return CreateDirectoryA(dir_path.c_str(), nullptr) || GetLastError() == ERROR_ALREADY_EXISTS;
	}

	std::string GetClientSettings()
	{
		std::string BloxstrapPath = GetHomeFolder() + "\\AppData\\Local\\Bloxstrap\\Modifications\\ClientSettings";

		if (ALLOW_BLOXSTRAP && DirectoryExists(BloxstrapPath))
			return BloxstrapPath;

		std::string VanillaRobloxPath = GetHomeFolder() + "\\AppData\\Local\\Roblox\\Versions";

		if (!fs::exists(VanillaRobloxPath) || !fs::is_directory(VanillaRobloxPath))
			return "";

		for (const auto &entry : fs::directory_iterator(VanillaRobloxPath))
			if (fs::is_directory(entry.path()) && fs::exists(entry.path() / "RobloxPlayerBeta.exe"))
				return (entry.path() / "ClientSettings").string();

		return "";
	}

	// public:
	std::string Read(std::string fflag_id)
	{
		std::string file_path = GetClientSettings() + "\\ClientAppSettings.json";

#ifdef AUTOCREATE_JSON_FILE
		if (!DirectoryExists(GetClientSettings()) && !CreateFolder(GetClientSettings()))
			return "";

		if (!FileExists(file_path) && !WriteFile(file_path, "{}"))
			return "";
#endif

		try
		{
			std::ifstream input_file(file_path);
			if (!input_file.is_open())
				return "";

			json json_data;
			input_file >> json_data;

			return json_data.contains(fflag_id) ? json_data[fflag_id].get<std::string>() : "";
		}
		catch (const std::exception &)
		{
			return "";
		}
	}

	bool Write(std::string fflag_id, std::string value)
	{
		std::string fflags_path = GetClientSettings() + "\\ClientAppSettings.json";
		json json_data;

#ifdef AUTOCREATE_JSON_FILE
		if (!DirectoryExists(GetClientSettings()) && !CreateFolder(GetClientSettings()))
			return false;

		if (!FileExists(fflags_path) && !WriteFile(fflags_path, "{}"))
			return false;
#endif

		try
		{
			std::ifstream input_file(fflags_path);
			if (!input_file.is_open())
				return false;

			input_file >> json_data;
			input_file.close();

			json_data[fflag_id] = value;

			std::ofstream output_file(fflags_path);
			if (output_file.is_open())
			{
				output_file << std::setw(2) << json_data << std::endl;
				return true;
			}
		}
		catch (const std::exception &)
		{
			return false;
		}

		return false;
	}

	bool Delete(std::string FFlag)
	{
		std::string file_path = GetClientSettings() + "\\ClientAppSettings.json";

#ifdef AUTOCREATE_JSON_FILE
		if (!DirectoryExists(GetClientSettings()) && !CreateFolder(GetClientSettings()))
			return false;

		if (!FileExists(file_path) && !WriteFile(file_path, "{}"))
			return false;
#endif

		try
		{
			std::ifstream input_file(file_path);
			if (!input_file.is_open())
				return false;

			json json_data;
			input_file >> json_data;
			input_file.close();

			if (json_data.contains(FFlag))
			{
				json_data.erase(FFlag);
				std::ofstream ouput_file(file_path);
				if (ouput_file.is_open())
				{
					ouput_file << std::setw(2) << json_data << std::endl;
					return true;
				}
			}
		}
		catch (const std::exception &)
		{
			return false;
		}

		return false;
	}
};