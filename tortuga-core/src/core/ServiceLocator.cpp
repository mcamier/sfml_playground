#include "../../inc/TE/core/ServiceLocator.hpp"

#include "../../inc/TE/message/message_service.hpp"
#include "../../inc/TE/resource/resource_service.hpp"
#include "../../inc/TE/screen/ScreenService.hpp"

namespace ta {

ServiceLocator* locator = new ServiceLocator(new ResourceService(), new MessageService(), new ScreenService());

ScreenService* GetScreenService() {
    return locator->screenService;
}

MessageService* GetMessageService() {
    return locator->messageService;
}

ResourceService* GetResourceService() {
    return locator->resourceService;
}

}  // namespace ta