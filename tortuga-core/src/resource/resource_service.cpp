#include "../../inc/TE/resource/resource_service.hpp"

#include "../../inc/TE/resource/resource_info.hpp"
#include "../../inc/TE/core/core.hpp"
#include "../../inc/TE/logger.hpp"
#include "../../inc/TE/logger.hpp"
#include "../../inc/TE/log_utils.hpp"

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <future>
#include <iostream>
#include <map>
#include <thread>
#include <utility>

#include <SFML/System.hpp>

namespace ta {

using namespace utils;

void ResourceService::vUpdate(const Time& time) {
    for (auto it = inProgress.begin(); it != inProgress.end();) {
        future<raw_resource_handler>& f = (*it).second;

        if (f.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            REP_DEBUG("deferred loading of resource #" << (*it).first << " is done", LogChannelFlag::DEFAULT)
            // TODO consider sending an Event
            inProgress.erase(it++);
        } else {
            it++;
        }
    }
}

void ResourceService::deferredLoad(const resource_info& info) {
    // start a thread & load the resources in the thread
    REP_DEBUG("deferred loading of resource #" << info.id, LogChannelFlag::DEFAULT)
    promise<raw_resource_handler> pr;
    auto fu = pr.get_future();

    auto it = loaded_resources.find(info.id);
    if (it == loaded_resources.end()) {
        std::thread t(&ResourceService::asyncLoad, this, info, std::move(pr));
        inProgress.insert(std::make_pair(info.id, std::move(fu)));
        t.detach();
    } else {
        // the resource is already loaded the promise value can me set directly
        const void* ptr;
        long size;
        getResource(info, &ptr, &size);
        raw_resource_handler hdl(ptr, size);
        pr.set_value(hdl);
    }
}

void ResourceService::immediateLoad(const resource_info& info, const void** out_ptr, long* out_size) {
    getResource(info, out_ptr, out_size);
    if (*out_ptr == nullptr || *out_size == 0) {
        std::cout << "immediate load of resource " << info.name << std::endl;
        load(info, out_ptr, out_size);
    }
}

void ResourceService::getResource(const resource_info& info, const void** out_ptr, long* out_size) {
    auto it = loaded_resources.find(info.id);
    if (it != loaded_resources.end()) {
        raw_resource_handler& hdl = it->second;
        *out_ptr = hdl.ptr;
        *out_size = hdl.size;
        return;
    }

    *out_ptr = nullptr;
    *out_size = 0;
}

void ResourceService::load(const resource_info& info, const void** out_ptr, long* out_size) {
    char* ptr = (char*) std::malloc(sizeof(char) * info.size);

    string filepath = GetWorkingDir() + string("bundle.bin");
    std::ifstream bundle_file(filepath.c_str(), std::ios::binary | std::ios::in);
    if (!bundle_file) {
        REP_FATAL("fail to open the resource bundle file", LogChannelFlag::DEFAULT)
    }
    bundle_file.seekg(info.head, ios_base::beg);
    bundle_file.read(ptr, info.size);
    bundle_file.close();

    loaded_resources.insert(std::make_pair(info.id, raw_resource_handler(ptr, info.size)));

    *out_ptr = ptr;
    *out_size = info.size;
}

void ResourceService::asyncLoad(const resource_info& info, promise<raw_resource_handler> promise) {
    char* ptr = (char*) std::malloc(sizeof(char) * info.size);

    string filepath = GetWorkingDir() + string("bundle.bin");
    std::ifstream bundle_file(filepath.c_str(), std::ios::binary | std::ios::in);
    if (!bundle_file) {
        REP_FATAL("fail to open the resource bundle file", LogChannelFlag::DEFAULT)
    }
    bundle_file.seekg(info.head, ios_base::beg);
    bundle_file.read(ptr, info.size);
    bundle_file.close();

    // set value in the promise
    raw_resource_handler hdl(ptr, info.size);
    promise.set_value(hdl);

    // set value in the map of loaded resources
    loaded_resources.insert(std::make_pair(info.id, hdl));
}

void ResourceService::vDestroy() {
    for (auto& entry : loaded_resources) {
        const void* ptr = entry.second.ptr;
        std::free(const_cast<void*>(ptr));
    }

    for (auto& entry : inProgress) {
        // TODO
    }
}

}