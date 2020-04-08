#ifndef TORTUGA_CORE_HPP
#define TORTUGA_CORE_HPP

#include <string>
#include <vector>
#include <stdexcept>

#include <string>
#include <vector>

#ifdef _DEBUG

#include <stdio.h>
#include <string>

#ifdef _WIN32
//#include <intrin.h>
#define BREAK() __debugbreak()
#else
#define BREAK() __builtin_trap()
#endif

#define ASSERT_SUB_STRING " evaluated to false"
#define ASSERT(expr) \
        if(expr) {} \
        else \
        { \
            throw std::runtime_error(#expr ASSERT_SUB_STRING); \
        }
#define ASSERT_FLAG(expr_flag, has_to_flag) \
        if( (expr_flag & has_to_flag) == has_to_flag) {} \
        else { \
            throw std::runtime_error(#expr_flag ASSERT_SUB_STRING); \
        }
#else
#define ASSERT(expr)
#define ASSERT_FLAG(expr_flag, has_to_flag)
#define BREAK()
#endif


#ifdef RUNNING_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>

// TODO windows version

#elif defined RUNNING_LINUX

#include <unistd.h>
#include <dirent.h>

namespace ta {

using namespace std;

inline std::string GetWorkingDir() {
    char cwd[2048];
    if (!getcwd(cwd, sizeof(cwd))) {
        return "";
    }
    return string(cwd) + string("/");
}

inline vector<string> GetFileList(
        const string& directory,
        const string& searchPattern = "*.*") {

    vector<string> files;
    DIR* dpdf;
    dpdf = opendir(directory.c_str());
    if (!dpdf) {
        return files;
    }
    if (searchPattern.empty()) {
        return files;
    }
    string sp = searchPattern;
    if (sp[0] == '*') {
        sp.erase(sp.begin());
    }
    if (sp[sp.length()] - 1 == '*') {
        sp.pop_back();
    }
    struct dirent* epdf;
    while (epdf = readdir(dpdf)) {
        string name = epdf->d_name;
        if (searchPattern != "*.*") {
            if (name.length() < sp.length()) {
                continue;
            }
            if (sp[0] == '.') {
                if (name.compare(name.length() - sp.length(), sp.length(), sp) != 0) {
                    continue;
                }
            } else if (name.find(sp) == string::npos) {
                continue;
            }
        }
        files.emplace_back(name);
    }
    closedir(dpdf);
    return files;
}

}

#endif

#endif //TORTUGA_CORE_HPP
