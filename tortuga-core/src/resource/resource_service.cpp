#include "../../inc/TE/resource/resource_service.hpp"

#include "../../inc/TE/resource/resource_info.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <utility>

void ResourceService::deferredLoad(const resource_info& info) {
  // start a thread
  // load the resources in the thread
  std::cout << "deferred load of resource " << info.name << std::endl;
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

  std::ifstream bundle_file("bundle.bin", std::ios::binary | std::ios::in);
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