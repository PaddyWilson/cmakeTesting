#include "Downloader.h"

#include <iostream>
#include <thread>

// #include <Windows.h>
// #pragma comment(lib, "urlmon.lib")

using namespace std;

int Downloader::Download(std::string URL, std::string saveName)
{
	std::wstring temp_url = std::wstring(URL.begin(), URL.end());
	std::wstring temp_saveName = std::wstring(saveName.begin(), saveName.end());

	// URL of the file to download
	const wchar_t* sURL = temp_url.c_str();// URL.c_str();//  L"https://cards.scryfall.io/png/front/9/4/94eea6e3-20bc-4dab-90ba-3113c120fb90.png?1670031714";
	// Name of the Destination file 
	const wchar_t* dFile = temp_saveName.c_str(); // L"image.png";

	//this only works on windows
	if (S_OK == URLDownloadToFile(NULL, sURL, dFile, 0, NULL))
	{
		cout << "The file is saved to " << saveName << endl;
		return 0;
	}
	else
	{
		cout << "Unable to Download the file." << endl;
		return -1;
	}
}

int Downloader::DownloadList(std::vector<std::string> URL, std::vector<std::string> saveName)
{
	if (URL.size() != saveName.size())
		return -1;

	for (size_t i = 0; i < URL.size(); i++)
		Download(URL[i], saveName[i]);

	return 0;
}

void Downloader::DownloadAsync(std::string URL, std::string saveName)
{
	thread thread(Download, URL, saveName);
}

void Downloader::DownloadListAsync(std::vector<std::string> URL, std::vector<std::string> saveName)
{
	//has to have matching sizes
	if (URL.size() != saveName.size())
		return;

	thread thread(DownloadList, URL, saveName);
}
