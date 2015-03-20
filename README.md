# Demoniac

[![Build Status](https://travis-ci.org/neveralso/Demoniac.svg?branch=master)](https://travis-ci.org/neveralso/Demoniac)[![Join the chat at https://gitter.im/neveralso/Demoniac](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/neveralso/Demoniac?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

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

#STILL IN DEVELOPING →_→
