#ifndef FOOBAR_RESOURCE_INFO_HPP
#define FOOBAR_RESOURCE_INFO_HPP

namespace ta {

typedef unsigned int ResourceId;



struct resource_info {
    const ResourceId id;
    const char* name;
    const char* extension;
    const long size;
    const long head;

    constexpr resource_info(ResourceId id, const char* name, const char* extension,
                            const long head, const long size)
            : id(id), name(name), extension(extension), size(size), head(head) {}
};

struct raw_resource_handler {
    const void* ptr;
    const long size;

    // Empty constructor for usage with standard containers like map, vector, etc
    raw_resource_handler() : ptr(nullptr), size(0) {}

    /*raw_resource_handler& operator=(const raw_resource_handler& r) {
        raw_resource_handler handler;
        return handler;
    }*/

    raw_resource_handler(const void* ptr, const long size)
            : ptr(ptr), size(size) {}
};
}

#endif