#include "abathur/channel.hpp"

#include "abathur/event.hpp"
#include "abathur/event_processor.hpp"

namespace abathur {

    thread_local Channel* current_channel = nullptr;

    Channel::Channel(std::shared_ptr<EventProcessor> processor) {
        processor_ = std::move(processor);

        // Channel initial process
        routine_ = new Corountine::push_type(
                [&](Corountine::pull_type& routine_in) {
                    if (!routine_in) return;

                    routine_in_ = &routine_in;
                    while (true) {
                        auto ev = routine_in.get();
                        processor_->ProcessEvent(ev);
                        routine_in();
                    }
                }
        );
    }

    void Channel::Process(const abathur::Event& event) {
        current_channel = this;
        (*routine_)(event);
        current_channel = nullptr;
    }

    Corountine::pull_type* Channel::get_routine_in() {
        return routine_in_;
    }

}
