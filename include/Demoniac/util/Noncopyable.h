//
// Created by Neveralso on 15/3/16.
//

#ifndef _DEMONIAC_NONCOPYABLE_H_
#define _DEMONIAC_NONCOPYABLE_H_


namespace dc {
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


#endif //_DEMONIAC_NONCOPYABLE_H_
