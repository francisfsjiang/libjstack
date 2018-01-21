#ifndef _ABATHUR_IOLOOP_H_
#define _ABATHUR_IOLOOP_H_

#include <iostream>
#include <vector>
#include <map>

namespace abathur {


class EventCallback;

namespace poller{

    class Poller;

    class KqueuePoller;

    class EpollPoller;

}


class IOLoop {
private:

    //IOLoop *instance_;
    bool quit_;
    abathur::poller::Poller *poller_;
    std::map<int, EventCallback> events_map_;

    IOLoop();

    IOLoop(const IOLoop&) = delete;
    const IOLoop& operator=(const IOLoop&) = delete;

public:

    static IOLoop* Current();

    void Loop();

    void Quit();

    void AddEventCallback(const int& fd, EventCallback e);

    void RemoveEventCallback(const int &fd);

    void Start();

    ~IOLoop();
};

}


#endif //_ABATHUR_IOLOOP_H_
