#ifndef _CALL_HPP_
#define _CALL_HPP_

#include "Arduino.h"
#include "Timer.hpp"
#include "ILoopable.hpp"

namespace async{
/**
 * @brief 
 * Asychronous call containing chains of lambdas
 * that are executed one by one in order.
 */
class Call :
public ILoopable
{
private:
    uint32_t chain_link = 0;
    bool push_forward   = false;
    std::vector<std::function<bool()>> code_chain;
    async::Timer async_timer = async::Timer(1000);
    uint32_t expire_time = 0;
public:
    Call();
    ~Call() override;
    
    Call* then(const std::function<bool()> &&code_block);
    Call* then(const std::function<void()> &&code_block);
    Call* wait(const uint32_t &time);

    void loop() override;
};

inline Call* call(){
    return new Call();
};

}
#endif