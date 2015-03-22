//
// Created by Neveralso on 15/3/16.
//

#include <Python/Python.h>
#include "error.h"

namespace dc {

BaseError::BaseError(string e) : event(e) {
}

IOLoopConstructorError::IOLoopConstructorError(string e) : BaseError(e) {
}

SocketError::SocketError(string e) : BaseError(e) {

}

IllegalFunctionError::IllegalFunctionError(string e) : BaseError(e) {

}

NotSupportYetError::NotSupportYetError(string e) : BaseError(e) {

}

}