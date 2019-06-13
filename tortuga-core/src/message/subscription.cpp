#include "../../inc/TE/message/subscription.hpp"

#include <iostream>
#include <mutex>

#include "../../inc/TE/message/message_service.hpp"

namespace ta {

std::mutex Subscription::mutex_last_id = std::mutex();
unsigned int Subscription::last_id = 1;

Subscription::Subscription() {
  id = 0;
  manager = nullptr;
}

Subscription::Subscription(MessageService *msgManager) {
  std::lock_guard<std::mutex> lock(Subscription::mutex_last_id);
  id = last_id;
  manager = msgManager;
  Subscription::last_id++;
}

Subscription::Subscription(Subscription &&other) {
  id = other.id;
  manager = other.manager;

  other.id = 0;
  other.manager = nullptr;
}

Subscription &Subscription::operator=(Subscription &&other) {
  if (this == &other) return *this;

  // unsubscribe the previously held subscription
  // otherwise, the subscription will never be released for the message manager
  if (manager != nullptr && id != 0) {
    manager->unsubscribe(id);
  }

  id = other.id;
  manager = other.manager;
  other.id = 0;
  other.manager = nullptr;

  return *this;
}

Subscription::~Subscription() {
  if (manager != nullptr && id != 0) {
    manager->unsubscribe(this->id);
  }
}

}  // namespace ta