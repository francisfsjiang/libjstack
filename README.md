# Demoniac

```c++
    #include <iostream>
    #include <cstdio>
    #include <string>
    #include <vector>
    #include <map>
    #include <algorithm>
    #include <thread>
    #include <exception>

    #include <ctime>

    #include <stdio.h>

    #define debug(x)  cout<<#x<<" = "<<x<<endl;
    #define debugs(arr,num) cout<<#arr<<" = ";for(int zz=0;zz<num;zz++)cout<<arr[zz]<<" ";cout<<endl;

    using namespace std;

    class Application {
    public:
        map<string, function<void*()>> router_map;
        template<typename T>
        void add_handler(string url){
            auto f = [=](){return (void*)(new T);};
            router_map.insert(make_pair(url, f));
        }
    };

    class BASE {
    public:
        virtual string get() = 0;
    };

    class A: public BASE {
    public:
        virtual string get() {
            return "A";
        }
    };

    class B: public BASE {
    public:
        virtual string get() {
            return "B";
        }
    };

    int main() {
        cout<<"Let's rock and roll."<<endl;
        Application app;
        app.add_handler<A>("/A");
        app.add_handler<B>("/B");
        BASE* handler = (BASE*)app.router_map["/A"]();
        cout<<handler->get()<<endl;
        handler = (BASE*)app.router_map["/B"]();
        cout<<handler->get()<<endl;
        return 0;
    }

```