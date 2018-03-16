#include "abathur/channel.hpp"

#include "abathur/event.hpp"
#include "abathur/event_processor.hpp"

namespace abathur {

    Channel::Channel(std::shared_ptr<EventProcessor> processor) {
        processor_ = std::move(processor);
        sub_routine_ = new Corountine::push_type(
                [&](Corountine::pull_type& in) {
                    while (true) {
                        if (!in) return;

                        auto ev = in.get();
                        processor_->ProcessEvent(ev);
                        in();

                    }
                }
        );
    }

    void Channel::Process(const abathur::Event& event) {
        (*sub_routine_)(event);
    }

}
