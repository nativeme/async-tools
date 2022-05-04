/**
 * @file Process.hpp
 * @author Łukasz Kaniak - nativeme (lukaszkaniak@gmail.com)
 * @brief
 * Defines the "Process" class for "async-tools".
 * @version 0.1
 * @date 2022-04-03
 * 
 * @copyright Copyright (c) 2022
 */

#ifndef _PROCESS_HPP_
#define _PROCESS_HPP_

#include "Params.hpp"
#include "Timer.hpp"
#include "ILoopable.hpp"
#include "Runtime.hpp"

namespace async{
class Process :
    public ILoopable
{
private:
    int16_t id = -1;
    uint8_t state = 0;
    uint32_t avg_looptime_value;

    enum State{
        state_created,
        state_stoped,
        state_working,
        state_shutting_down,
    };
    
    void new_id();     
    Timer internal_timer = Timer(1000, true, true);
    String name = "";
public:
    std::function<void(void)> on_create   = [](){};
    std::function<void(void)> on_start    = [](){};
    std::function<void(void)> on_working  = [](){};
    std::function<void(void)> on_stop     = [](){};
    std::function<void(void)> on_shutdown = [](){};

    Process();
    Process(Params &&builder);
    ~Process() override;


    const String get_name() const;
    void         set_name(const char*& name);
    void         set_name(const char*&& name);
    
    const int16_t get_id() const;
    
    const uint32_t get_interval() const;
    void           set_interval(const uint32_t &&interval);
    void           set_interval(const uint32_t &interval);

    void set_resolution(const Timer::Resolution &&resolution);
    
    void avg_looptime() const {}; //TODO

    void start();
    void toggle();
    void work();
    void stop();
    void shutdown();
    void kill();

    void loop() override;
};
}
#endif
