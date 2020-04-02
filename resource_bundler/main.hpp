#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <cstring>
#include <string>
#include <dirent.h>

using namespace std;

struct resource_info {
  string name;
  string filepath;
  string extension;
  long size;  // as bytes
  long head;
};

struct resource_info_list {
  resource_info info;
  resource_info_list* next = nullptr;
};

string getExtension(const string s);

string getName(string root, string filepath);

void writeManifestCppFile(resource_info_list* resourceInfoList);

void writeManifestHppFile(resource_info_list* resourceInfoList);

bool isFolder(const char* folder);

resource_info_list* getFolderContent(const char* root, const char* folder);