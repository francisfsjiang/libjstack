#ifndef _ABATHUR_CHANNEL_HPP_
#define _ABATHUR_CHANNEL_HPP_

#include <memory>
#include <map>

#include <boost/coroutine2/all.hpp>

namespace abathur {

    class Event;

    class EventProcessor;

    typedef boost::coroutines2::coroutine<Event> Corountine;

    class Channel: public std::enable_shared_from_this<Channel>{
    private:
        Corountine::push_type* routine_ = nullptr;
        Corountine::pull_type* routine_in_ = nullptr;
        EventProcessor* processor_ = nullptr;

        std::map<int, int> fd_flags_;

    public:
        Channel(EventProcessor*);
        ~Channel();
        Corountine::pull_type* get_routine_in();
        void Process(const Event&);
    };

    extern thread_local std::shared_ptr<Channel> current_channel;

}

#endif //_ABATHUR_CHANNEL_HPP_
