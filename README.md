# Abathur

[![Build Status](https://travis-ci.org/neveralso/Abathur.svg?branch=master)](https://travis-ci.org/neveralso/Abathur)  [![GPLV2](https://img.shields.io/badge/License-GPLV2-brightgreen.svg)](http://www.gnu.org/licenses/gpl-2.0.html)  [![Join the chat at https://gitter.im/AbathurFreamwork](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/Abathur?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

Abathur is a C++ web framework and asynchronous networking library.
By using non-blocking network I/O,
Abathur can scale to tens of thousands of open connections. And
coroutine makes it easier to program.

Abathur is available on *nix system. Requires Boost{context, coroutine} and libcurl.


# Hello, Wrold

```c++
#include <iostream>

#include "abathur/abathur.hpp"

#define LISTEN_PORT 8000
#define LISTEN_ADDR "::"


class HTTPEchoHandler : public HTTPHandler{
    public:
        HTTPEchoHandler() : HTTPHandler() {};
        HTTPResponse* handle_get(const HTTPRequest& request) override {

            auto resp = new HTTPResponse();
            auto s = std::string(
                    request.get_body()->data_to_read(),
                    request.get_body()->size()
            );
            resp->write(s);
            finish();

            return resp;
        }
};

int main(int , const char**) {

    InetAddress* addr;
    addr = new InetAddress(LISTEN_ADDR, LISTEN_PORT);

    std::cout << addr->to_string() << std::endl;

    auto http_server = new HTTPServer(addr);
    http_server->init();
    http_server->set_http_handler<HTTPEchoHandler>("/");

    IOLoop::current()->start();
    return 0;
}
```


# How to build 

Clone this repo and make build dir.
```sh
git clone https://github.com/neveralso/Abathur.git
cd Abathur
mkdir build
cd build
```

Use cmake to automatically build and find depends.
```sh
cmake ..
make
```

Or specify depends' dir by arguments.
```sh
cmake -DBOOST_ROOT=${BOOST_ROOT} -DCURL_INCLUDE_DIR=${CURL_ROOT}/include -DCURL_LIBRARY=${CURL_ROOT}/lib ..
```

Build example.
```sh
cmake -DBUILD_EXAMPLE=on ..
../bin/http_echo_server.out

```

Then

```sh
telnet 127.0.0.1 8000
```

have fun ~

