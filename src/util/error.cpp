//
// Created by Neveralso on 15/3/16.
//

#include "error.hpp"

using namespace dc;

BaseError::BaseError(string e):event(e) {}

IOLoopConstructorError::IOLoopConstructorError(string e):BaseError(e) {}