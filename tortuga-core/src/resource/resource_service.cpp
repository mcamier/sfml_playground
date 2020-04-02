#include "../../inc/TE/resource/resource_service.hpp"

#include "../../inc/TE/resource/resource_info.hpp"
#include "../../inc/TE/core/core.hpp"

#include <chrono>
#include <fstream>
#include <future>
#include <iostream>
#include <map>
#include <thread>
#include <utility>

#include <SFML/System.hpp>

namespace ta {

future<raw_resource_handler> ResourceService::deferredLoad(
        const resource_info& info) {
    // start a thread
    // load the resources in the thread
    std::cout << "deferred load of resource " << info.name << std::endl;
    promise<raw_resource_handler> pr;
    auto fu = pr.get_future();

    if (!isLoaded(info)) {
        std::thread t(&ResourceService::asyncLoad, this, info, std::move(pr));
        t.detach();
    } else {
        // the resource is already loaded the promise value can me set directly
        const char* ptr;
        long size;
        getResource(info, &ptr, &size);
        raw_resource_handler hdl(ptr, size);
        pr.set_value(hdl);
    }

    return std::move(fu);
}

void ResourceService::immediateLoad(const resource_info& info,
                                    const char** out_ptr, long* out_size) {
    getResource(info, out_ptr, out_size);
    if (*out_ptr == nullptr || *out_size == 0) {
        std::cout << "immediate load of resource " << info.name << std::endl;
        load(info, out_ptr, out_size);
    }
}

void ResourceService::getResource(const resource_info& info, const char** out_ptr,
                          long* out_size) {
    if (isLoaded(info)) {
        auto it = loaded_resources.find(info.name);
        if (it != loaded_resources.end()) {
            raw_resource_handler& hdl = it->second;
            *out_ptr = hdl.ptr;
            *out_size = hdl.size;
            return;
        }
    }

    *out_ptr = nullptr;
    *out_size = 0;
}

bool ResourceService::isLoaded(const resource_info& info) {
    if (loaded_resources.size() == 0) return false;

    auto it = loaded_resources.find(info.name);
    if (it == loaded_resources.end()) return false;

    return true;
}

void ResourceService::load(const resource_info& info, const char** out_ptr,
                           long* out_size) {
    char* ptr = (char*) malloc(sizeof(char) * info.size);

    string filepath = GetWorkingDir() + string("bundle.bin");
    std::ifstream bundle_file(filepath.c_str(), std::ios::binary | std::ios::in);
    if (!bundle_file) {
        // TODO handle the error
        cout << "fail to open the bundle file" << endl;
    }
    bundle_file.seekg(info.head, ios_base::beg);
    bundle_file.read(ptr, info.size);
    bundle_file.close();

    loaded_resources.insert(
            std::make_pair(info.name, raw_resource_handler(ptr, info.size)));

    *out_ptr = ptr;
    *out_size = info.size;
}

void ResourceService::asyncLoad(const resource_info& info,
                                promise<raw_resource_handler> promise) {
    char* ptr = (char*) malloc(sizeof(char) * info.size);

    std::chrono::duration<int, std::milli> some_wait(3000);
    this_thread::sleep_for(some_wait);

    string filepath = GetWorkingDir() + string("bundle.bin");
    std::ifstream bundle_file(filepath.c_str(), std::ios::binary | std::ios::in);
    if (!bundle_file) {
        // TODO handle the error
        cout << "fail to open the bundle file" << endl;
    }
    bundle_file.seekg(info.head, ios_base::beg);
    bundle_file.read(ptr, info.size);
    bundle_file.close();

    // set value in the promise
    raw_resource_handler hdl(ptr, info.size);
    promise.set_value(hdl);

    // set value in the map of loaded resources
    loaded_resources.insert(std::make_pair(info.name, hdl));
}

void ResourceService::update(const Time & time) {

}

}