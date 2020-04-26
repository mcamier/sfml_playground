#ifndef TORTUGA_CORE_HPP
#define TORTUGA_CORE_HPP

#include <string>
#include <vector>
#include <stdexcept>

#include <string>
#include <vector>

/**
 * Define few utilities for debugging purpose
 * BREAK(), ASSERT() and ASSERT_FLAG()
 */
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

using std::string;
using std::vector;

namespace ta::core {

    /**
     * List all the files present in a directory
     * This list can be filtered out with the parameter searchPattern (i.e *.png will result in a list containing
     * only the png files present in a given folder)
     *
     * @param directory folder to lookup into
     * @param searchPattern pattern to filter out the files
     * @return list of present files names
     */
    vector<string> GetFileList(const string& directory, const string& searchPattern = "*.*");

    /**
     * Get the current folder path from where the application in executed
     * @return path of the curring working directory
     */
    std::string GetWorkingDir();

}

#endif //TORTUGA_CORE_HPP
