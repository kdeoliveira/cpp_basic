#pragma once

#include <utility>
#include <memory>

#include <any>

template<typename T>
class Proxy{
    public:
        Proxy(T& _wrapper)
        : obj{ std::make_unique<typename std::remove_reference<T>::type>( std::forward<T>(_wrapper) ) } {

        }



    private:
        std::unique_ptr<T> obj;

        public:
            T* operator->(){
                return this->obj.get();
            }
            
};


struct test_struct{
    char buf[10];
};

int main(){

    test_struct test;

    Proxy proxy(test);

    proxy->buf[0] = 'k';
    proxy->buf[1] = '2';

    puts(proxy->buf);


    


    return 0;
}