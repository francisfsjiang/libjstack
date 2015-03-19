//
// Created by Neveralso on 15/3/17.
//

#ifndef _DEMONIAC_EVENT_H_
#define _DEMONIAC_EVENT_H_

#include <functional>

namespace dc {

class Event {
private:
    int fd_;
    std::function<void(int, int)> read_call_back_;
    std::function<void(int, int)> write_call_back_;
public:
    Event(int fd);

    ~Event();

    int GetFD() const;

    void set_read_call_back(std::function<void(int, int)> call_back);

    void set_write_call_back(std::function<void(int, int)> call_back);

    void exec_read_call_back(int fd, int data);

    void exec_write_call_back(int fd, int data);
};

}

#endif //_DEMONIAC_EVENT_H_
