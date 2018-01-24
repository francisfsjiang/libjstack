# Abathur

[![Build Status](https://travis-ci.org/neveralso/Abathur.svg?branch=dev)](https://travis-ci.org/neveralso/Abathur)  [![GPLV2](https://img.shields.io/badge/License-GPLV2-brightgreen.svg)](http://www.gnu.org/licenses/gpl-2.0.html)  [![Join the chat at https://gitter.im/AbathurFreamwork](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/Abathur?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

Abathur is a C++ web framework and asynchronous networking library.
By using non-blocking network I/O,
Abathur can scale to tens of thousands of open connections.

Abathur is available on *nix system.


# Hello, Wrold

```c++
#include <iostream>
#include "Abathur.h"

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
	dc::IOLoop::Current()->Start();
}
```


## First example is available

Has been tested on :

- Mac OS X 10.10.2 : (Apple LLVM version 6.0)

- Ubuntu 14.10 : (g++ (Ubuntu 4.9.1-16ubuntu6) 4.9.1)

- FreeBSD 10.1 : (FreeBSD clang version 3.4.1)


```sh
git clone https://github.com/neveralso/Abathur.git
cd Abathur
cmake .
make
cd example
make
./echo_server.out
```

then

```sh
telnet 127.0.0.1 8000
```

have fun~~~

# STILL IN DEVELOPING →_→
