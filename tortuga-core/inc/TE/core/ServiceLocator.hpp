#ifndef TA_SERVICE_LOCATOR_HPP
#define TA_SERVICE_LOCATOR_HPP


namespace ta {

// forward declarations
class ResourceService;
class MessageService;
class ScreenService;

class ServiceLocator {
public:
    ResourceService* resourceService;
    MessageService* messageService;
    ScreenService* screenService;

    ServiceLocator() :
            resourceService(nullptr),
            messageService(nullptr),
            screenService(nullptr) {}

    ServiceLocator(ResourceService* resourceService, MessageService* messageService, ScreenService* screenService) :
            resourceService(resourceService),
            messageService(messageService),
            screenService(screenService) {}
};

ScreenService* GetScreenService();
MessageService* GetMessageService();
ResourceService* GetResourceService();

}  // namespace ta

#endif  // TA_SERVICE_LOCATOR_HPP