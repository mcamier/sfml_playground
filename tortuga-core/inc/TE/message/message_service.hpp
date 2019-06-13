#ifndef TA_MSG_MANAGER_HPP
#define TA_MSG_MANAGER_HPP

#include <SFML/System.hpp>
#include <functional>
#include <map>
#include <vector>
#include "message.hpp"
#include "subscription.hpp"

using namespace std;

namespace ta {

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

/**
 * @brief
 * @note
 * @retval None
 */
class MessageService {
  friend class Subscription;

  typedef vector<message> messages_t;
  typedef map<unsigned int, vector<_sub>> subscriptions_t;

  messages_t messages;
  subscriptions_t suscribers;

 public:
  MessageService() {}
  MessageService(MessageService &&other) = default;
  MessageService &operator=(MessageService &&other) = default;
  ~MessageService() {}

  /**
   * @brief Subscribe an instance of observer for a given message type
   * @note A subscription should not outlive the callback existence !!
   * @param  obj:
   */
  Subscription subscribe(messageType_t msgType,
                         std::function<void(message)> callback);

  /**
   * @brief
   * @note A subscription should not outlive the callback existence !!
   * @retval
   */
  template <typename T>
  Subscription subscribe(messageType_t msgType, void (T::*method)(message),
                         T *instance) {
    return this->subscribe(
        msgType, [instance, method](message msg) { (instance->*method)(msg); });
  }

  /**
   * @brief
   * @note
   * @param  &&Subscription:
   * @retval None
   */
  void unsubscribe(Subscription &&Subscription);

  /**
   * @brief Save a message in the event manager in order to be processed during
   * next update call
   * @note
   * @param  msg: Message to dispatch to observers
   */
  void sendMessage(message msg);

  /**
   * @brief Forward all the messages to the observers
   */
  void update();

 private:
  void unsubscribe(unsigned int sub_id);

  // no move copy or assignement
  MessageService(const MessageService &) = delete;
  MessageService &operator=(const MessageService &) = delete;
};

}  // namespace ta

#endif  // TA_MSG_MANAGER_HPP
