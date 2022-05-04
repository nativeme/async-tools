#include "Call.hpp"
namespace async{

Call::Call(){
    Runtime::async_calls.push_back(this);
}
Call::~Call(){

}

Call* Call::then(const std::function<bool()> &&code_block){
    this->code_chain.push_back(code_block);
    return this;
}
Call* Call::then(const std::function<void()> &&code_block){
    this->code_chain.push_back([code_block](){
        code_block();
        return true;
    });
    return this;
}
Call* Call::wait(const uint32_t &&time){
    
    code_chain.push_back([this, time](){
        switch (async_timer.get_state()){
        case Timer::State::idle:
            async_timer.set_time(time);
            async_timer.start();
            return false;
        case Timer::State::finished:
            async_timer.clear();
            return true;
        default:
            return false;
        }
        return false;
    });

    return this;
}
void Call::loop(){
    if(chain_link == code_chain.size()){
        for (size_t i = 0; i < Runtime::async_calls.size(); i++){
            if (Runtime::async_calls[i] == this){
                Runtime::async_calls.erase(Runtime::async_calls.begin() + i);
                delete this;
            }
        }
    }else{
        if(push_forward == false){
            this->push_forward = this->code_chain[chain_link]();
        }else{
            push_forward = false;
            chain_link++;
        }
    }
}
}
