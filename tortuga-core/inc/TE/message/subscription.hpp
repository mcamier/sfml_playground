
#ifndef TA_SUBSCRIPTION_HPP
#define TA_SUBSCRIPTION_HPP

#include <mutex>

#include "message.hpp"

namespace ta {

// forward declaration
class MessageService;

/**
 * @brief  Handler on event observed message. An instance of this class can be
 * moved but not copied. Because the class destructor is responsible to call the
 * MessageManager's unsubscribe method.
 * @note   RAII object
 */
struct Subscription {
  friend class MessageService;

 public:
  Subscription();
  Subscription(MessageService *msgService);
  Subscription(Subscription &&other);
  Subscription &operator=(Subscription &&other);

  /**
   * @brief Destructor will trigger the unsubscription of the underlying message
   * callback binding.
   * It checks if the object is valid: if an id and an pointer to an instance of
   * messageManager exists
   * @note
   */
  ~Subscription();

 private:
  MessageService *manager;
  unsigned int id;
  static std::mutex mutex_last_id;
  static unsigned int last_id;

  // no copy contructor nor copy assignement
  Subscription(const Subscription &) = delete;
  Subscription &operator=(const Subscription &) = delete;
};
}  // namespace ta

#endif  // TA_SUBSCRIPTION_HPP