#ifndef FOOBAR_RESOURCE_SERVICE_HPP
#define FOOBAR_RESOURCE_SERVICE_HPP

#include <SFML/System.hpp>
#include <future>
#include <map>
#include <tuple>

#include "resource_info.hpp"

namespace ta {

using namespace std;

class ResourceService {
private:
    map<const char*, raw_resource_handler> loaded_resources;

public:
    /**
     * @brief Load asynchronously a resource from the bundle file
     * @note Rely on the EventService to informs when the resource is loaded
     * @param  info: Resource to load, should be listed as static field in the
     * ResourceManifest type
     */
    future<raw_resource_handler> deferredLoad(const resource_info& info);

    /**
     * @brief Load synchronously a resource from the bundle file
     * @note If the resource to load is heavy calling this method will result in
     * an unresponsive application
     * @param  info: Resource to load, should be listed as static field in the
     * ResourceManifest type
     * @param  out_ptr: ref to the load resource
     * @param  out_size: size of the resource in memory
     */
    void immediateLoad(const resource_info& info, const char** out_ptr,
                       long* out_size);

    /**
     * @brief Get the location and size of a loaded resource
     * @note Always load a resource before using this function.
     * Trying to get a resource not already loaded could lead to undefined
     * behavior
     * @param  info: Resource to load, should be listed as static field in
     * the ResourceManifest type
     * @param  out_ptr: ref to the load resource
     * @param  out_size: size of the resource in memory
     */
    void get(const resource_info& info, const char** out_ptr, long* out_size);

private:
    /**
     * @brief
     * @note
     * @param  info:
     * @retval
     */
    bool isLoaded(const resource_info& info);

    /**
     * @brief
     * @note
     * @param  &info:
     * @param  **out_ptr:
     * @param  *out_size:
     * @retval None
     */
    void load(const resource_info& info, const char** out_ptr, long* out_size);

    /**
     * @brief
     * @note
     * @param  &info:
     * @param  promise:
     * @retval None
     */
    void asyncLoad(const resource_info& info,
                   promise<raw_resource_handler> promise);
};

}

#endif  // FOOBAR_RESOURCE_SERVICE_HPP