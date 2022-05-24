#ifndef _EVENTTIMER_HPP_
#define _EVENTTIMER_HPP_
#include "Arduino.h"
#include "Timer.hpp"
#include "Params.hpp"

namespace async{
/**
 * @brief 
 * Classic timer expanded by possibility of executing
 * events at certain moment after start of the timer.
 * Pass events by event_timer.add_event( time, [](){ some_logic } );
 */
class EventTimer
:   public Timer
{
private:
    struct TimedEvent{
        const uint32_t execute_at;
        const std::function<void(void)> event;
        bool done;
        TimedEvent(const uint32_t& execute_at, const std::function<void(void)>&& event)
        :   execute_at(execute_at),
            event(event),
            done(false)
        {};
    };

    std::vector<TimedEvent> events;
    
public:
    EventTimer(const Params &&builder)
    :   Timer(std::move(builder))
    {
        builder.builder();
    };
    
    EventTimer(const uint32_t &time, const bool &auto_start = false, const bool &pulse = false)
    :   Timer(time, auto_start, pulse)
    {
        
    };
    ~EventTimer(){
        
    };

    void add_event(const uint32_t& execute_at, std::function<void(void)>&& event){
        this->events.push_back(TimedEvent(execute_at, std::move(event)));
    }

    virtual void loop() override {
        switch (state){
        case State::finished:
            if(pulse) start();
            break;
        case State::countdown:
            for (auto &&event : events){
                if(!event.done && this->have_passed(event.execute_at)){
                    event.event();
                    event.done = true;
                } 
            }

            if(read_time() >= target_time){
                state = State::finished;
                for (auto &&event : events){
                    event.done = false;
                }
            };
            break;
        case State::idle:
            break;
        default:
            break;
        }
    }
};
}
#endif
