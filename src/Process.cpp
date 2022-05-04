#include "Process.hpp"

namespace async{

Process::Process(){
    this->new_id();
}

Process::Process(Params &&builder){
    this->new_id();
    builder.builder();
    this->on_create();
    async::Runtime::processes.push_back(this);
}

Process::~Process(){
}

void Process::kill(){
    for (size_t i = 0; i < async::Runtime::processes.size(); i++){
        if(async::Runtime::processes[i] == this) async::Runtime::processes.erase(async::Runtime::processes.begin() + i);
    }
}

void Process::new_id(){
    static int id_counter = 0;
    this->id = id_counter++;
}

void Process::work(){
    internal_timer.start();
    on_start();
    state = Process::State::state_working;
    on_working();
};
void Process::start(){
    on_start();
    state = Process::State::state_working;
};
void Process::stop(){
    on_stop();
    state = Process::State::state_stoped;
};
void Process::toggle(){
    if(this->state == Process::State::state_working){
        on_stop();
        state = Process::State::state_stoped;
    } else if(this->state == Process::State::state_stoped){
        on_start();
        state = Process::State::state_working;
    };
};
void Process::shutdown(){
    on_shutdown();
    state = Process::State::state_shutting_down;
};

const String Process::get_name() const { 
    return this->name; 
};
void Process::set_name(const char* &name){
    this->name = name;
};
void Process::set_name(const char*&& name){
    this->name = name;
};

const int16_t Process::get_id() const {
    return this->id;
};

const uint32_t Process::get_interval() const {
    return this->internal_timer.get_base_time();
}
void Process::set_interval(const uint32_t &interval){
    this->internal_timer.set_time(interval);
};
void Process::set_interval(const uint32_t &&interval){
    this->internal_timer.set_time(interval);
};

void Process::set_resolution(const Timer::Resolution &&resolution){
    this->internal_timer.set_resolution(std::move(resolution));
};

void Process::loop(){
    switch (this->state)
    {
    case Process::State::state_working:
        if(this->internal_timer.is_finished()) on_working();
        break;
    case Process::State::state_created:
        work();
        break;
    case Process::State::state_stoped:
        break;
    case Process::State::state_shutting_down:
        break;
    default:
        break;
    }
}

}
