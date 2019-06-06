#ifndef FOOBAR_RESOURCE_SERVICE_HPP
#define FOOBAR_RESOURCE_SERVICE_HPP

#include <map>

#include "resource_info.hpp"

using namespace std;

class ResourceService {
 private:
  // map<resource_info, raw_resource_handler> loaded_resources;

 public:
  /**
   * @brief Load asynchronously a resource from the bundle file
   * @note Rely on the EventService to informs when the resource is loaded
   * @param  info: Resource to load, should be listed as static field in the
   * ResourceManifest type
   */
  void deferredLoad(const resource_info &info);

  /**
   * @brief Load synchronously a resource from the bundle file
   * @note If the resource to load is heavy calling this method will result in
   * an unresponsive application
   * @param  info: Resource to load, should be listed as static field in the
   * ResourceManifest type
   * @param  out_bytes: ref to the load resource
   * @param  out_size: size of the resource in memory
   */
  void immediateLoad(const resource_info &info, char &out_bytes,
                     long &out_size);

  /**
   * @brief Get the location and size of a loaded resource
   * @note Always load a resource before using this function.
   * Trying to get a resource not already loaded could lead to undefined
   * behavior
   * @param  info: Resource to load, should be listed as static field in
   * the ResourceManifest type
   * @param  out_bytes: ref to the load resource
   * @param  out_size: size of the resource in memory
   */
  void get(const resource_info &info, char &out_bytes, long &out_size);

 private:
  /**
   * @brief
   * @note
   * @param  info:
   * @retval
   */
  bool isLoaded(const resource_info &info);
};

#endif  // FOOBAR_RESOURCE_SERVICE_HPP