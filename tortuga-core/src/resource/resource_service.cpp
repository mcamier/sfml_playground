#include "../../inc/TE/resource/resource_service.hpp"

#include <algorithm>
#include <iostream>

void ResourceService::deferredLoad(const resource_info& info) {
  std::cout << "deferred load of resource " << info.name << std::endl;
}

void ResourceService::immediateLoad(const resource_info& info, char& out_bytes,
                                    long& out_size) {
  std::cout << "immediate load of resource " << info.name << std::endl;
}

void ResourceService::get(const resource_info& info, char& out_bytes,
                          long& out_size) {
  std::cout << "get resource " << info.name << std::endl;
}

bool ResourceService::isLoaded(const resource_info& info) {
  /*if (loaded_resources.size() == 0) return false;

  auto it = loaded_resources.find(info);
  if (it == loaded_resources.end()) return false;

  return true;*/
  return true;
}