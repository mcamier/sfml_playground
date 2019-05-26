#include <iostream>
#include <iostream>
#include <fstream>
#include <list>
#include <string>

using namespace std;

struct resource_info {
  const char* name;
  const char* extension;
  long size; // as bytes
  long head;
};

struct resource_info_list {
  resource_info info;
  resource_info_list* next = nullptr;
};

string getExtension(string filepath) {
    return "wav";
}


string getName(string filepath) {
    return "sound_hit";
}

int main()
{
    long bundle_size_limit = 500000000; // 500MB
    string bundle_filename = "bundle";

    // resource to merge into
    list<string> resources;
    resources.push_back("sound/hit.wav");
    resources.push_back("sound/boom.wav");
    resources.push_back("font/pixel.ttf");

    resource_info_list bundle_info;

    ofstream bundle_file;
    bundle_file.open(bundle_filename.c_str(), std::ios::binary);

    for(auto itr = resources.begin(); itr != resources.end(); ++itr) {
        string filepath = (*itr);

        ifstream file;

        resource_info info;
        info.extension = getExtension(filepath).c_str();
        info.name = getName(filepath).c_str();

        bundle_info.info = info;
    }

    bundle_file.close();
}


