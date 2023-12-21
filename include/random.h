#pragma once
#include <random>
namespace MyUno
{
    class MyRandom
    {
    private:
        MyRandom();
        std::random_device randomDevice;
        std::mt19937 generator;
    public:
        MyRandom(MyRandom const&) = delete;
        void operator=(MyRandom const&) = delete;
        std::mt19937& GetGenerator() { return generator; }
        static MyRandom& GetInstance() 
        {
            static MyRandom instance;
            return instance;
        }
    };
}