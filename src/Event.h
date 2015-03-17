//
// Created by Neveralso on 15/3/17.
//

#ifndef _DEMONIAC_EVENT_H_
#define _DEMONIAC_EVENT_H_

namespace dc {

class Event {
private:
    int fd_;
    void *read_call_back_;
    void *write_call_back_;
public:
    Event(int fd);

    int GetFD() const;

    void set_read_call_back(void *call_back);

    void set_write_call_back(void *call_back);
};

}

#endif //_DEMONIAC_EVENT_H_
