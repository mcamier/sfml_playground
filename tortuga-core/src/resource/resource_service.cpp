#include "../../inc/TE/resource/resource_service.hpp"

#include "../../inc/TE/resource/resource_info.hpp"
#include "../../inc/TE/core/core.hpp"
#include "../../inc/TE/logger.hpp"

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
            /*message msg;
            msg.type = MSG_RESOURCE_LOADED;
            msg.v0.type = variant::type_t::UINT_T;
            msg.v0.uintValue = (*it).first;
            MessageService::get().sendMessage(msg);*/
            inProgress.erase(it++);
        } else {
            it++;
        }
    }
}

void ResourceService::vDestroy() {
    for (auto& entry : inProgress) {
        auto& future = entry.second;
        future.wait();
    }

    for (auto& entry : loaded_resources) {
        const void* ptr = entry.second.ptr;
        std::free(const_cast<void*>(ptr));
    }
}

void ResourceService::deferredLoad(const resource_info& info) {
    auto itLoaded = loaded_resources.find(info.id);
    auto itInProgress = inProgress.find(info.id);

    // only start deferred loading if the resource is neither loaded or currently loading asynchronously
    if (itLoaded == loaded_resources.end() && itInProgress == inProgress.end()) {
        // start a thread & load the resources in the thread
        REP_DEBUG("deferred loading of resource #" << info.id, LogChannelFlag::DEFAULT)
        promise<raw_resource_handler> pr;
        auto fu = pr.get_future();
        std::thread t(&ResourceService::loadResourceFromBundle, this, info, std::move(pr));
        inProgress.insert(std::make_pair(info.id, std::move(fu)));
        t.detach();
    } else {
        REP_DEBUG("request for deferred loading of resource #" << info.id << " ignored", LogChannelFlag::DEFAULT)
    }
}

void ResourceService::immediateLoad(const resource_info& info) {
    auto itLoaded = loaded_resources.find(info.id);
    auto itInProgress = inProgress.find(info.id);
    // resource not loaded already neither being loaded
    if (itLoaded == loaded_resources.end() && itInProgress == inProgress.end()) {
        promise<raw_resource_handler> pr;
        auto fu = pr.get_future();
        this->loadResourceFromBundle(info, std::move(pr));
        fu.wait();
        REP_DEBUG("immediate loading of resource #" << info.id << " is done", LogChannelFlag::DEFAULT)
    } else {
        // if resource is being loaded
        if (itInProgress != inProgress.end()) {
            // the resouce is currently being loaded, wait for it
            auto& future = itInProgress->second;
            REP_DEBUG("the resource #" << info.id << " was already loading, wait for it be loaded...", LogChannelFlag::DEFAULT)
            future.wait();
        } else {
            REP_DEBUG("resource #" << info.id << " is already loaded", LogChannelFlag::DEFAULT)
        }
    }
}

void ResourceService::getResource(const resource_info& info, void** out_ptr, long* out_size) {
    auto it = loaded_resources.find(info.id);
    if (it == loaded_resources.end()) {
        REP_FATAL("cannot get a resource which is not already loaded", LogChannelFlag::DEFAULT)
    }

    raw_resource_handler& hdl = it->second;
    *out_ptr = const_cast<void*>(hdl.ptr);
    *out_size = hdl.size;
}

void ResourceService::loadResourceFromBundle(const resource_info& info, promise<raw_resource_handler> promise) {
    char* ptr = (char*) std::malloc(info.size);

    // little delay for debugging/ testing purpose
    /*std::chrono::duration<int, std::milli> some_wait(2000);
    this_thread::sleep_for(some_wait);*/

    string filepath = GetWorkingDir() + string("bundle.bin");
    std::ifstream bundle_file(filepath.c_str(), std::ifstream::binary);
    if (!bundle_file) {
        REP_FATAL("fail to open the resource bundle file", LogChannelFlag::DEFAULT)
    }
    bundle_file.seekg(info.head-1, ios::beg);
    bundle_file.read(ptr, info.size);
    bundle_file.close();

    // set value in the promise
    raw_resource_handler hdl(ptr, info.size);
    promise.set_value(hdl);

    // set value in the map of loaded resources
    loaded_resources.insert(std::make_pair(info.id, hdl));
}

}