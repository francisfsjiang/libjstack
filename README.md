# Demoniac

[![Build Status](https://travis-ci.org/neveralso/Demoniac.svg?branch=master)](https://travis-ci.org/neveralso/Demoniac)  [![Join the chat at https://gitter.im/neveralso/Demoniac](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/neveralso/Demoniac?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

Demoniac is a C++ web framework and asynchronous networking library.
By using non-blocking network I/O,
Demoniac can scale to tens of thousands of open connections.

# Hello, Wrold

```c++
#include <iostream>
#include "Demoniac.h"

class MainHandler: dc::RequestHandler {
public:
    dc::Response get() {
        return "Hello, GFW";
    }
};

int main() {
    dc::Application app;
    app.listen(8888)
    app.add_handler<MainHandler>("/");
    dc::IOLoop ioloop;
    ioloop.start();
}

```


##First example is avaliable on MacOS X

    git clone https://github.com/neveralso/Demoniac.git
    cd Demoniac
    cmake .
    make
    cd example
    make
    ./echo_server

then

    telnet 127.0.0.1 8000

have fun~~

#STILL IN DEVELOPING →_→
