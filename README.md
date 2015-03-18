# Demoniac

Demoniac is a C++ web framework and asynchronous networking library.
By using non-blocking network I/O,
Demoniac can scale to tens of thousands of open connections.

# Hello, Wrold

```c++
#include <iostream>
#include "Demoniac.h"

class MainHandler(dc::RequestHandler) {
public:
    dc::Response get() {
        return "Hello, GFW";
    }
}


int main() {
    dc::Application app();
    app.listen(8888)
    app.add_handler<MainHandler>("/");
    dc::IOLoop ioloop();
    ioloop.start();
}

```

#STILL IN DEVELOPING →_→