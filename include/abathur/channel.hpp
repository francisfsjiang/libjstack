#ifndef _ABATHUR_CHANNEL_HPP_
#define _ABATHUR_CHANNEL_HPP_

#include <memory>
#include <map>

#include <boost/coroutine2/all.hpp>

namespace abathur {

    class Event;

    class EventProcessor;

    class Channel {
    private:
        typedef boost::coroutines2::coroutine<Event> Corountine;
        Corountine::push_type* sub_routine_ = nullptr;
        std::shared_ptr<EventProcessor> processor_ = nullptr;

        std::map<int, int> fd_flags_;

    public:

        Channel(std::shared_ptr<EventProcessor>);

        void Process(const Event&);
    };
}

#endif //_ABATHUR_CHANNEL_HPP_
