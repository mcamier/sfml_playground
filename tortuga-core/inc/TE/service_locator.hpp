#ifndef TA_SERVICE_LOCATOR_HPP
#define TA_SERVICE_LOCATOR_HPP

#include "message/message_service.hpp"
#include "resource/resource_service.hpp"
#include "screen/screen_service.hpp"

namespace ta {

class ServiceLocator {
 public:
  static ResourceService* resourceService;
  static MessageService* messageService;
  static ScreenService* screenService;
};

}  // namespace ta

#endif  // TA_SERVICE_LOCATOR_HPP