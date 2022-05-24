#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include "Arduino.h"
#include "ILoopable.hpp"
#include "Runtime.hpp"
#include "Params.hpp"

namespace async{
class Timer : 
public ILoopable
{
protected:
    uint32_t read_time() const;
    bool pulse = false;
    uint8_t  state = 0;
    uint8_t resolution = 0;
    uint32_t base_value = 0;
    uint32_t start_time = 0;
    uint32_t target_time = 0;
public:
    enum State{
        idle = 0,
        countdown = 1,
        finished = 2
    }; 

    enum Resolution{
        millis_res = 0,
        micros_res = 1
    };

    Timer();
    Timer(const Params &&builder);
    Timer(const uint32_t &time, const bool &auto_start = false, const bool &pulse = false);
    virtual ~Timer() override;

    const uint8_t get_state() const;
    void set_time(const uint32_t &time);
    void add_time(const int32_t &time);
    uint32_t get_base_time() const;
    uint32_t get_start_time() const;
    uint32_t get_time_passed() const;
    void set_resolution(const Resolution &&resolution);
    void set_pulsing(const bool &is_pulsing = true);
    void start();
    void clear();
    const bool is_finished() const;
    const bool at_state(const Timer::State &&state) const;
    const bool have_passed(const uint32_t &time) const;
    virtual void loop() override;
};
};


#endif