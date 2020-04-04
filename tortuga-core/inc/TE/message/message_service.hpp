#ifndef TA_MSG_MANAGER_HPP
#define TA_MSG_MANAGER_HPP

#include <SFML/System.hpp>
#include <functional>
#include <map>
#include <vector>
#include "message.hpp"
#include "subscription.hpp"
#include "../core/IUpdatable.hpp"
#include "../services/configuration.hpp"
#include "../services/service.hpp"

using namespace std;

namespace ta {

using namespace utils;

/**
 * @brief Internal subscription
 * @note
 * @retval None
 */
struct _sub {
    unsigned int id;
    std::function<void(message)> _func;

    _sub(unsigned int id, std::function<void(message)> func)
            : id(id), _func(func) {}
};


struct MessageServiceConf : public IServiceConfiguration {
};

/**
 * @brief
 * @note
 * @retval None
 */
class MessageService : public ISingletonService<MessageService, MessageServiceConf> {
    friend class ISingletonService<MessageService, MessageServiceConf>;

    friend class Subscription;

    typedef vector<message> messages_t;
    typedef map<unsigned int, vector<_sub>> subscriptions_t;

    messages_t messages;
    subscriptions_t suscribers;

public:
    MessageService() {}

    MessageService(const MessageService&) = delete;

    MessageService& operator=(const MessageService&) = delete;

    ~MessageService() {}

    /**
     * @brief Subscribe an instance of observer for a given message type
     * @note A subscription should not outlive the callback existence !!
     * @param  obj:
     */
    Subscription subscribe(messageType_t msgType, std::function<void(message)> callback);

    /**
     * @brief
     * @note A subscription should not outlive the callback existence !!
     * @retval
     */
    template<typename T>
    Subscription subscribe(messageType_t msgType, void (T::*method)(message), T* instance) {
        return this->subscribe(msgType, [instance, method](message msg) { (instance->*method)(msg); });
    }

    /**
     * @brief
     * @note
     * @param  &&Subscription:
     * @retval None
     */
    void unsubscribe(Subscription&& Subscription);

    /**
     * @brief Save a message in the event manager in order to be processed during
     * next update call
     * @note
     * @param  msg: Message to dispatch to observers
     */
    void sendMessage(message msg);

protected:
    void vInit(MessageServiceConf initStructArg) override {};

    void vDestroy() override {};

public:
    /**
     * @brief Forward all the messages to the observers
     */
    void vUpdate(const Time& time) override;

private:
    void unsubscribe(unsigned int sub_id);

};

}  // namespace ta

#endif  // TA_MSG_MANAGER_HPP
