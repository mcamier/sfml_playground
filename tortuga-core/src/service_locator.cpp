#include "../inc/TE/service_locator.hpp"

#include "../inc/TE/message/message_service.hpp"
#include "../inc/TE/resource/resource_service.hpp"
#include "../inc/TE/screen/screen_service.hpp"

namespace ta {
ResourceService* ServiceLocator::resourceService = nullptr;
MessageService* ServiceLocator::messageService = nullptr;
ScreenService* ServiceLocator::screenService = nullptr;

}  // namespace ta