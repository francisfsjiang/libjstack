#include "abathur/channel.hpp"

#include "abathur/event.hpp"
#include "abathur/event_processor.hpp"
#include "abathur/log.hpp"

namespace abathur {

    thread_local std::shared_ptr<Channel> current_channel = nullptr;

    Channel::Channel(EventProcessor* processor) {
        LOG_TRACE << "Channel constructing, " << this;
        processor_ = processor;

        // Channel initial process
        routine_ = new Corountine::push_type(
                [&](Corountine::pull_type& routine_in) {
                    current_channel->routine_in_ = &routine_in;
                    processor_->process_loop();
                }
        );
    }

    Channel::~Channel() {
        LOG_TRACE << "Channel deconstructing, " << this;
        delete processor_;
    }

    void Channel::process(const abathur::Event &event) {
        LOG_TRACE << "In to channel.";
        current_channel = shared_from_this();
        (*routine_)(event);
        current_channel = nullptr;
        LOG_TRACE << "Out from channel.";
    }

    Corountine::pull_type* Channel::get_routine_in() {
        return routine_in_;
    }

}
