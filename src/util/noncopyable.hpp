//
// Created by Neveralso on 15/3/16.
//

#ifndef _DEMONIAC_NONCOPYABLE_H_
#define _DEMONIAC_NONCOPYABLE_H_


namespace dc {
    class noncopyable {
    protected:
        noncopyable(){}
        ~noncopyable(){}
    private:
        noncopyable(const noncopyable&);
        noncopyable& operator = (const noncopyable&);
    public:
    };

}


#endif //_DEMONIAC_NONCOPYABLE_H_
