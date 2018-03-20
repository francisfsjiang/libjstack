#include "abathur/event_processor.hpp"

#include "abathur/channel.hpp"
#include "abathur/event.hpp"
#include "abathur/log.hpp"

namespace abathur {

    void EventProcessor::process_loop() {
        LOG_TRACE << "Start process loop";
        auto routine_in = current_channel->get_routine_in();
//        (*routine_in)();
        while (true) {
            LOG_TRACE << "Executing process.";
            auto event = routine_in->get();

            int ret = this->process_event(event);
            if (ret == 0) {
                break;
            }

            (*routine_in)();
        }
    }

}