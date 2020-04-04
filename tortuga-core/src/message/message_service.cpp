#include "../../inc/TE/message/message_service.hpp"

#include "../../inc/TE/message/message.hpp"
#include "../../inc/TE/message/subscription.hpp"

#include <algorithm>

namespace ta {

Subscription MessageService::subscribe(messageType_t msgType,
                                       std::function<void(message)> callback) {
    Subscription sub(this);
    _sub internal_sub = _sub(sub.id, callback);

    auto it = suscribers.find(msgType);
    if (it == suscribers.end()) {
        suscribers[msgType] = vector<_sub>();
        suscribers[msgType].push_back(internal_sub);
    } else {
        auto& obs = it->second;
        obs.push_back(internal_sub);
    }

    return std::move(sub);
}

void MessageService::unsubscribe(unsigned int sub_id) {
    for (auto itMap = suscribers.begin(); itMap != suscribers.end(); itMap++) {
        vector<_sub>& vec = itMap->second;

        for (auto itSub = vec.begin(); itSub != vec.end(); itSub++) {
            if (itSub->id == sub_id) {
                vec.erase(itSub);
                return;  // not a clean solution to finish the loop earlier
            }
        }
    }
}

void MessageService::unsubscribe(Subscription&& sub) {
    this->unsubscribe(sub.id);
    sub.id = 0;
    sub.manager = nullptr;
}

void MessageService::sendMessage(message msg) {
    messages.push_back(std::move(msg));
}

void MessageService::vUpdate(const Time& time) {
    // perform a copy of the vector of the last frame messages
    messages_t lastFrameMsg = messages;
    // clear messages in case of new messages sent by currently processed messages
    messages.clear();

    for (auto& msg : lastFrameMsg) {
        auto it = suscribers.find(msg.type);
        if (it != suscribers.end()) {
            auto obs = it->second;

            for (auto& observer : it->second) {
                observer._func(msg);
            }
        }
    }
}

}  // namespace ta