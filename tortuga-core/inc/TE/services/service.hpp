#ifndef TA_SERVICE_INIT_HPP
#define TA_SERVICE_INIT_HPP

#include <type_traits>
#include <utility>
#include <cstdint>
#include <string>
#include <map>
#include <SFML/System/Time.hpp>

#include "../core/core.hpp"
#include "../hash.hpp"
#include "configuration.hpp"

namespace ta::utils {

using std::string;
using std::map;


// Enumerate the different status a manager could have
enum ServiceState {
    UNINITIALIZED = 0x01,
    INITIALIZED = 0x02,
    DESTROYED = 0x04
};

//
// Must be used inside a class extending the interface IServiceConfiguration
//
#define CONF_PROPERTY(TYPE, NAME) \
protected: \
    unsigned int hash##NAME = makeHash(#NAME); \
    string _##NAME() { \
        auto prop = properties.find(this->hash##NAME); \
        if (prop == properties.end()) return ""; \
        return prop->second; \
    } \
public: \
    TYPE get_##NAME() { \
        return getCastedProperty<TYPE>(this->_##NAME()); \
    }

template<typename T>
class ISingleton {
protected:
    // Internal getter of the reference of the static instance pointer
    // Return a reference to the static instance pointer
    static T *&_instance() {
        static T *instance = nullptr;
        return instance;
    }

    // Internal getter of the reference of the static state
    // Return a reference to the static state
    static ServiceState &_state() {
        static ServiceState state = ServiceState::UNINITIALIZED;
        return state;
    }

public:
    // Getter to specific system reference
    //
    // WARNING: if DEBUG_ASSERTION_ENABLED is defined this call will raise a breakpoint if the internal
    // instance pointer points to nullptr or the system state is not INITIALIZED.
    //
    // Return a reference to the specific system instance
    static T &get() {
        ASSERT(_instance() != nullptr);
        ASSERT_FLAG(_state(), ServiceState::INITIALIZED);
        return *_instance();
    }
};


template<typename T, typename INIT_T>
class IService {

protected:
    virtual void vInit(INIT_T initStructArg) = 0;

    virtual void vDestroy() = 0;

public:
    virtual void vUpdate(const sf::Time& time) = 0;
};


// SingletonManager classes meant to be used as global services providers, they are singletons and requires
// to be initialized within the Application's initialization and destroyed within Application's
// destruction.
// They could must accessed through the entire application
//
// A class extending Singleton should removed its copy constructor and its assigment operator
// Furthermore, its constructor should be private or private as a semantic requirement
template<typename T, typename INIT_T>
class ISingletonService :
        public ISingleton<T>,
        public virtual IService<T, INIT_T> {
public:
    static void initialize(INIT_T initStructArg = {}) {
        static_assert(std::is_base_of<ISingletonService, T>::value, "Type T must be derivated from Manager");

        if ((ISingleton<T>::_state() & ServiceState::UNINITIALIZED) == ServiceState::UNINITIALIZED) {
            ASSERT(Singleton<T>::_instance() == nullptr);

            ISingleton<T>::_instance() = new T();
            ((ISingletonService *) ISingleton<T>::_instance())->vInit(std::forward<INIT_T>(initStructArg));
            ISingleton<T>::_state() = ServiceState::INITIALIZED;
        }
    }

    static void destroy() {
        ASSERT_FLAG(Singleton<T>::_state(), INITIALIZED);

        ((ISingletonService *) ISingleton<T>::_instance())->vDestroy();
        delete ISingleton<T>::_instance();
        ISingleton<T>::_instance() = nullptr;
        ISingleton<T>::_state() = ServiceState::DESTROYED;
    }
};

} // namespace utils

#endif //TA_SERVICE_INIT_HPP
