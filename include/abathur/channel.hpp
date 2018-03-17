#ifndef _ABATHUR_CHANNEL_HPP_
#define _ABATHUR_CHANNEL_HPP_

#include <memory>
#include <map>

#include <boost/coroutine2/all.hpp>

namespace abathur {

    class Event;

    class EventProcessor;

    typedef boost::coroutines2::coroutine<Event> Corountine;

    class Channel {
    private:
        Corountine::push_type* routine_ = nullptr;
        Corountine::pull_type* routine_in_ = nullptr;
        std::shared_ptr<EventProcessor> processor_ = nullptr;

        std::map<int, int> fd_flags_;

    public:

        Channel(std::shared_ptr<EventProcessor>);
        Corountine::pull_type* get_routine_in();
        void Process(const Event&);
    };

    extern thread_local Channel* current_channel;

}

#endif //_ABATHUR_CHANNEL_HPP_
