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

            virtual int Poll(int) = 0;

            virtual void HandleEvents(
                    const int& events_ready_amount,
                    const std::map<int, std::pair<uint, Channel*>>& channel_map
            ) = 0;

            virtual void AddChannel(int, uint) = 0;

            virtual void UpdateChannel(int, uint, uint) = 0;

            virtual void DeleteChannel(int) = 0;

            Poller(const Poller&) = delete;
            const Poller& operator=(const Poller&) = delete;
        };


    }
}


#endif //_ABATHUR_POLLER_HPP_
