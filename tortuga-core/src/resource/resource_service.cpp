#include "../../inc/TE/resource/resource_service.hpp"

#include "../../inc/TE/resource/resource_info.hpp"

#include <chrono>
#include <fstream>
#include <future>
#include <iostream>
#include <map>
#include <thread>
#include <utility>

#include <SFML/System.hpp>

future<raw_res_hdl> ResourceService::deferredLoad(const resource_info& info) {
  // start a thread
  // load the resources in the thread
  std::cout << "deferred load of resource " << info.name << std::endl;
  promise<raw_res_hdl> pr;
  auto fu = pr.get_future();

  if (!isLoaded(info)) {
    std::thread t(&ResourceService::asyncLoad, this, info, std::move(pr));
    t.detach();
  } else {
    // the resource is already loaded the promise value can me set directly
    const char* ptr;
    long size;
    get(info, &ptr, &size);
    raw_res_hdl hdl;
    hdl.size = size;
    hdl.ptr = ptr;
    pr.set_value(hdl);
  }

  return std::move(fu);
}

void ResourceService::immediateLoad(const resource_info& info,
                                    const char** out_ptr, long* out_size) {
  get(info, out_ptr, out_size);
  if (*out_ptr == nullptr || *out_size == 0) {
    std::cout << "immediate load of resource " << info.name << std::endl;
    load(info, out_ptr, out_size);
  }
}

void ResourceService::get(const resource_info& info, const char** out_ptr,
                          long* out_size) {
  if (isLoaded(info)) {
    std::cout << "resource present" << std::endl;

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
  char* ptr = (char*)malloc(sizeof(char) * info.size);

  std::ifstream bundle_file(
      "/Users/doudou/Workspaces/sfml_playground/build/ong/bundle.bin",
      std::ios::binary | std::ios::in);
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
                                promise<raw_res_hdl> promise) {
  char* ptr = (char*)malloc(sizeof(char) * info.size);

  cout << "async load" << endl;
  std::chrono::duration<int, std::milli> some_wait(3000);
  this_thread::sleep_for(some_wait);

  std::ifstream bundle_file(
      "/Users/doudou/Workspaces/sfml_playground/build/ong/bundle.bin",
      std::ios::binary | std::ios::in);
  if (!bundle_file) {
    // TODO handle the error
    cout << "fail to open the bundle file" << endl;
  }
  bundle_file.seekg(info.head, ios_base::beg);
  bundle_file.read(ptr, info.size);
  bundle_file.close();

  // set value in the promise
  raw_res_hdl hdl;
  hdl.size = info.size;
  hdl.ptr = ptr;
  promise.set_value(hdl);

  // set value in the map of loaded resources
  // TODO
}