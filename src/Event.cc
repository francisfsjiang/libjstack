//
// Created by Neveralso on 15/3/17.
//

#include "Event.h"

namespace dc {

void Event::set_read_call_back(void *call_back) {
    read_call_back_ = call_back;
}

void Event::set_write_call_back(void *call_back) {
    write_call_back_ = call_back;
}

}