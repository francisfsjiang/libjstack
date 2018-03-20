#ifndef _ABATHUR_POLLER_POLLER_HPP_
#define _ABATHUR_POLLER_POLLER_HPP_

#include <vector>
#include <map>
#include <memory>

namespace abathur {

    class Channel;

    namespace poller {

        static const int MAX_READY_EVENTS_NUM = 500;

        class Poller {
        public:

            Poller() = default;

            virtual ~Poller() = default;

            virtual int poll(int) = 0;

            virtual void handle_events(
                    const int &events_ready_amount,
                    const std::map<int, std::pair<uint, std::shared_ptr<Channel>>> &channel_map
            ) = 0;

            virtual void add_channel(int, uint) = 0;

            virtual void update_channel(int, uint, uint) = 0;

            virtual void delete_channel(int) = 0;

            Poller(const Poller&) = delete;
            const Poller& operator=(const Poller&) = delete;
        };


    }
}


#endif //_ABATHUR_POLLER_HPP_
