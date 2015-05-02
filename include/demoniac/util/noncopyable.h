//
// Created by Neveralso on 15/3/16.
//

#ifndef _DEMONIAC_UTIL_NONCOPYABLE_H_
#define _DEMONIAC_UTIL_NONCOPYABLE_H_


namespace demoniac {
namespace util {


class Noncopyable {
protected:
    Noncopyable() {
    }

    ~Noncopyable() {
    }

private:
    Noncopyable(const Noncopyable &);

    Noncopyable &operator=(const Noncopyable &);

public:
};


}
}


#endif //_DEMONIAC_NONCOPYABLE_H_
