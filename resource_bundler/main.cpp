#include "main.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return -1;
    }
    char* asset_folder = argv[1];
    cout << "Resource bundler scan folder: " << asset_folder << endl;

    resource_info_list* list = getFolderContent(asset_folder, asset_folder);

    // create file bundle
    string bundle_filename = "bundle.bin";
    ofstream bundle_file;
    bundle_file.open(bundle_filename.c_str(), std::ios::binary | std::ios::out);
    long pos = -1;

    resource_info_list* next = list;
    while (next != nullptr) {
        resource_info& info = next->info;
        info.head = pos + 1;
        ifstream res(info.filepath, std::ios::binary | std::ios::in);

        char buffer[256];
        int buffer_size = 256;

        // read the length of the file
        res.seekg(0, ios_base::end);
        long size = res.tellg();
        cout << "size: " << size << " for file: " << info.name << endl;

        // reset the cursor to the beginning of the file before copying it into the
        // bundle
        res.seekg(0, ios_base::beg);
        long current_pos = res.tellg();
        while (!res.eof()) {
            // when the last portion of the file under copy is smaller then the buffer
            // size we avoid copying extra bytes
            if ((size - current_pos) < buffer_size) {
                int delta = +(size - current_pos);
                res.read(buffer, delta);
                bundle_file.write(buffer, delta);
            } else {
                res.read(buffer, buffer_size);
                bundle_file.write(buffer, buffer_size);
            }
        }
        pos = bundle_file.tellp();
        info.size = size;

        // close this resource file and move on the next one
        res.close();
        next = next->next;
    }

    // close bundle file
    bundle_file.close();

    // write the c++ sources for used by the project
    writeManifestHppFile(list);
    writeManifestCppFile(list);
}

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

void writeManifestCppFile(resource_info_list* resourceInfoList) {
    int count = 0;
    ofstream fout("manifest.cpp", ios::trunc | ios::out);
    resource_info_list* next = resourceInfoList;
    fout << "#include \"manifest.hpp\"" << endl << endl;
    fout << "namespace ta {" << endl;
    fout << endl;
    while (next != nullptr) {
        fout << "const resource_info ResourceManifest::" << next->info.name
             << " = resource_info(" << count << ", \"" << next->info.name << "\", \""
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
    fout << "}" << endl;

    fout.close();
}

void writeManifestHppFile(resource_info_list* resourceInfoList) {
    ofstream fout("manifest.hpp", ios::trunc | ios::out);
    resource_info_list* next = resourceInfoList;

    fout << "#ifndef MANIFEST_HPP" << endl;
    fout << "#define MANIFEST_HPP" << endl << endl;
    fout << "#include \"TE/resource/resource_info.hpp\"" << endl << endl;
    fout << "namespace ta {" << endl << endl;

    fout << "class ResourceManifest {" << endl;
    fout << "public:" << endl;
    while (next != nullptr) {
        fout << "\tstatic const resource_info " << next->info.name << ";" << endl;
        next = next->next;
    }

    fout << endl;
    fout << "\tstatic const int _COUNT;" << endl;
    fout << "\tstatic const resource_info _ALL[];" << endl;
    fout << "};" << endl;
    fout << "}" << endl;
    fout << "#endif";
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