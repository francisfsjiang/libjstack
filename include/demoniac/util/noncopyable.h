//
// Created by Neveralso on 15/3/16.
//

#ifndef _DEMONIAC_UTIL_NONCOPYABLE_H_
#define _DEMONIAC_UTIL_NONCOPYABLE_H_


namespace demoniac {
namespace util {

/*
 * Like boost::noncopyable
 */


class Noncopyable {
protected:
    Noncopyable() = default;

    ~Noncopyable() = default;

private:
    Noncopyable(const Noncopyable &) = delete;

    const Noncopyable& operator=(const Noncopyable &) = delete;

public:
};


}
}


#endif //_DEMONIAC_NONCOPYABLE_H_
