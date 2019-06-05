#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

#include <dirent.h>
#include <stdio.h>

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

string getExtension(const string s) {
  size_t i = s.rfind('.', s.length());
  if (i != string::npos) {
    return (s.substr(i + 1, s.length() - i));
  }
  return "";
}

string getName(string root, string filepath) {
  if ('/' != root[(root.length() - 1)]) {
    root = root + "/";
  }

  size_t i = filepath.rfind(root, filepath.length());
  if (i != string::npos) {
    string relative_path =
        filepath.substr(i + root.length(), filepath.length() - i);
    i = relative_path.rfind(".", relative_path.length());
    if (i != string::npos) {
      string name = (relative_path.substr(0, i));
      std::replace(name.begin(), name.end(), '/', '_');
      std::transform(name.begin(), name.end(), name.begin(), ::toupper);
      return name;
    }
  }
  return ("");
}

void writeBundle(resource_info_list resourceInfoList) {}

void writeManifestCppFile(resource_info_list* resourceInfoList) {
  int count = 0;
  ofstream fout("manifest.cpp", ios::trunc | ios::out);
  resource_info_list* next = resourceInfoList;
  fout << "#include \"manifest.hpp\"" << endl;
  fout << endl;
  while (next != nullptr) {
    fout << "const resource_info ResourceManifest::" << next->info.name
         << " = resource_info(\"" << next->info.name << "\", \""
         << next->info.extension << "\", " << next->info.head << ", "
         << next->info.size << ");" << endl;
    next = next->next;
    count++;
  }

  fout << "const int ResourceManifest::_COUNT = " << count << ";" << endl;
  fout << "const resource_info ResourceManifest::_ALL[" << count << "] = {"
       << endl;
  next = resourceInfoList;
  while (next != nullptr) {
    fout << "\tResourceManifest::" << next->info.name;
    if (next->next != nullptr) {
      fout << "," << endl;
    } else {
      fout << endl;
    }
    next = next->next;
  }
  fout << "};" << endl;

  fout.close();
}

void writeManifestHppFile(resource_info_list* resourceInfoList) {
  ofstream fout("manifest.hpp", ios::trunc | ios::out);
  resource_info_list* next = resourceInfoList;

  fout << "struct resource_info {" << endl;
  fout << "\tconst char* name;" << endl;
  fout << "\tconst char* extension;" << endl;
  fout << "\tconst long size;" << endl;
  fout << "\tconst long head;" << endl;
  fout << endl;
  fout << "\tconstexpr resource_info(const char* name, const char* extension, "
          "const long head, const long size) : name(name), "
          "extension(extension), size(size), head(head) {}"
       << endl;
  fout << "};" << endl << endl;

  fout << "class ResourceManifest {" << endl;
  fout << "public:" << endl;
  while (next != nullptr) {
    fout << "\tstatic const resource_info " << next->info.name << ";" << endl;
    next = next->next;
  }

  fout << endl;
  fout << "\tstatic const int _COUNT;" << endl;
  fout << "\tstatic const resource_info _ALL[];" << endl;
  fout << "};";
  fout.close();
}

bool isFolder(const char* folder) {
  bool isFolder = false;
  DIR* rep = opendir(folder);

  if (rep != NULL) {
    isFolder = true;
    closedir(rep);
  }
  return isFolder;
}

resource_info_list* getFolderContent(const char* root, const char* folder) {
  DIR* rep = opendir(folder);

  resource_info_list* head = nullptr;
  resource_info_list* tail = nullptr;

  if (rep != NULL) {
    struct dirent* ent;
    while ((ent = readdir(rep)) != NULL) {
      if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
        std::stringstream stringstream1;
        stringstream1 << folder;
        if ('/' != folder[(strlen(folder) - 1)]) {
          stringstream1 << "/";
        }
        stringstream1 << ent->d_name;
        std::string s = stringstream1.str();

        const char* subFolder = s.c_str();
        if (isFolder(subFolder)) {
          resource_info_list* ptr = getFolderContent(root, subFolder);
          if (nullptr == tail) {
            tail = ptr;
            head = tail;
          } else {
            tail->next = ptr;
            tail = tail->next;
          }

        } else {
          resource_info_list* ptr = new resource_info_list();
          ptr->info.name = getName(string(root), string(s));
          ptr->info.filepath = s;
          ptr->info.extension = getExtension(s);
          ptr->info.size = 1;
          ptr->info.head = 1;

          if (nullptr == tail) {
            tail = ptr;
            head = tail;
          } else {
            tail->next = ptr;
            tail = tail->next;
          }
        }
      }
    }

    closedir(rep);
  }

  return head;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    return -1;
  }
  char* asset_folder = argv[1];
  cout << "Resource bundler scan folder: " << asset_folder << endl;

  resource_info_list* list = getFolderContent(asset_folder, asset_folder);
  // writeBundle(*list);

  // create file bundle
  string bundle_filename = "bundle.bin";
  ofstream bundle_file;
  bundle_file.open(bundle_filename.c_str(), std::ios::binary | std::ios::out);

  resource_info_list* next = list;
  while (next != nullptr) {
    resource_info& info = next->info;
    ifstream res(info.filepath, std::ios::binary | std::ios::in);

    // read all file content and put it into the bundle

    res.close();
    next = next->next;
  }

  // close bundle file
  bundle_file.close();

  writeManifestHppFile(list);
  writeManifestCppFile(list);
}