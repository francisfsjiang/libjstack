//
// Created by Neveralso on 15/3/17.
//

#include "Event.h"

using namespace dc;

void Event::set_read_call_back(void *call_back) {
    _read_call_back = call_back;
}

void Event::set_write_call_back(void *call_back) {
    _write_call_back = call_back;
}
