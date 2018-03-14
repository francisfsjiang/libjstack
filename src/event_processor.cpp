#include "abathur/event_processor.hpp"

namespace abathur {

    std::shared_ptr<EventProcessor> EventProcessor::GetSelf() {
        return shared_from_this();
    }
}