#ifndef _ABATHUR_EVENT_PROCESSOR_HPP_
#define _ABATHUR_EVENT_PROCESSOR_HPP_


namespace abathur {

    class Event;

    class EventProcessor: public std::enable_shared_from_this<EventProcessor> {
    private:

    public:
        EventProcessor() = default;

        virtual ~EventProcessor() = default;

        virtual void ProcessEvent(const Event&) = 0;
    };
}

#endif //_ABATHUR_EVENT_PROCESS_HPP_
