#include "Timer.hpp"

namespace async{

Timer::Timer(){
}
Timer::Timer(const Params &&builder){
        builder.builder();
        Runtime::loopables.push_back(this);
    };
Timer::Timer(const uint32_t &time, const bool &auto_start, const bool &pulse){
        this->base_value = time;
        this->set_pulsing(pulse);
        Runtime::loopables.push_back(this);
        if(auto_start)
            this->start();
    };
Timer::~Timer(){
    for (size_t i = 0; i < async::Runtime::loopables.size(); i++){
        if(async::Runtime::loopables[i] == this) async::Runtime::loopables.erase(async::Runtime::loopables.begin() + i);
    }
}

void Timer::set_resolution(const Resolution &&resolution){
    this->resolution = resolution;
};
void Timer::set_pulsing(const bool &is_pulsing){
    this->pulse = is_pulsing;
}

uint32_t Timer::read_time() const {
    switch (resolution)
    {
    case Resolution::millis_res:
        return millis();
    case Resolution::micros_res:
        return micros();
    default:
        break;
    }
    return millis();
}

void Timer::set_time(const uint32_t& time){
    this->base_value = time;
    target_time = start_time + base_value;
};
void Timer::add_time(const int32_t &time){
    target_time += time;
};

uint32_t Timer::get_base_time() const {
    return this->base_value;
}

uint32_t Timer::get_start_time() const {
    return this->start_time;
};

uint32_t Timer::get_time_passed() const {
    return read_time() - start_time;
};

void Timer::start(){
    start_time = read_time();
    target_time = start_time + base_value;
    state = State::countdown;
};

void Timer::clear(){
    state = State::idle;
    start_time = 0;
    target_time = 0;
};

const uint8_t Timer::get_state() const {
    return this->state;
};

const bool Timer::is_finished() const {
    return this->state == Timer::State::finished;
};

const bool Timer::at_state(const Timer::State &&state) const {
    return this->state == state;
};

const bool Timer::have_passed(const uint32_t &time) const {
    return read_time() - start_time >= time;
};

void Timer::loop() {
    switch (state){
    case State::countdown:
        if(read_time() >= target_time){
            state = State::finished;
        };
        break;
    case State::finished:
        if(pulse) start();
        break;
    case State::idle:
        break;
    default:
        break;
    }
};

}