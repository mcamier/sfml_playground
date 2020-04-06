#ifndef FOOBAR_RESOURCE_SERVICE_HPP
#define FOOBAR_RESOURCE_SERVICE_HPP

#include <SFML/System.hpp>
#include <future>
#include <map>
#include <tuple>

#include "resource_info.hpp"
#include "../core/IUpdatable.hpp"
#include "../services/configuration.hpp"
#include "../services/service.hpp"

namespace ta {

using namespace std;
using utils::ISingletonService;
using utils::IServiceConfiguration;

struct ResourceServiceConf : public IServiceConfiguration {};

class ResourceService : public ISingletonService<ResourceService, ResourceServiceConf> {
    friend ISingletonService<ResourceService, ResourceServiceConf>;

private:
    map<ResourceId, raw_resource_handler> loaded_resources;
    map<ResourceId, future<raw_resource_handler>> inProgress;

public:
    /**
     * @brief Load asynchronously a resource from the bundle file
     * @note Rely on the EventService to informs when the resource is loaded
     */
    void deferredLoad(const resource_info& info);

    /**
     * @brief Load synchronously a resource from the bundle file
     * @note If the resource to load is heavy calling this method will result in
     * an unresponsive application
     * @param  info: Resource to load, should be listed as static field in the
     * ResourceManifest type
     * @param  out_ptr: ref to the load resource
     * @param  out_size: size of the resource in memory
     */
    void immediateLoad(const resource_info& info);

    /**
     * @brief Get the location and size of a loaded resource
     * @note Always load a resource before using this function.
     * Trying to get a resource not already loaded will rise a fatal error
     * @param  info: Resource to load, should be listed as static field in
     * the ResourceManifest type
     * @param  out_ptr: ref to the load resource
     * @param  out_size: size of the resource in memory
     */
    void getResource(const resource_info& info, void** out_ptr, long* out_size);

private:
    /**
     * @brief Aimed to be called in a separate thread for non-blocking resource loading
     */
    void loadResourceFromBundle(const resource_info& info, promise<raw_resource_handler> promise);

protected:
    void vInit(ResourceServiceConf initStructArg) override {}

    void vDestroy() override;

public:
    void vUpdate(const Time& time) override;
};

}

#endif  // FOOBAR_RESOURCE_SERVICE_HPP