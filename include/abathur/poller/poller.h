#ifndef _ABATHUR_POLLER_POLLER_H_
#define _ABATHUR_POLLER_POLLER_H_

#include <vector>
#include <map>

namespace abathur {

    class EventCallback;

    namespace poller {

        static const int MAX_READY_EVENTS_NUM = 500;

        class Poller {
        public:

            Poller() = default;

            virtual ~Poller() = default;

            virtual int Poll(int time_out) = 0;

            virtual void HandleEvents(const int& events_ready_amount, const std::map<int, EventCallback>& events_map) = 0;

            virtual void AddEventCallback(const int& fd, const EventCallback& e) = 0;

            virtual void UpdateEventCallback(const int& fd, const EventCallback& e) = 0;

            virtual void DeleteEventCallback(const int& fd) = 0;

            Poller(const Poller&) = delete;
            const Poller& operator=(const Poller&) = delete;
        };


    }
}


#endif //_ABATHUR_POLLER_H_
