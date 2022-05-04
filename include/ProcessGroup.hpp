#ifndef _PROCESSGROUP_HPP_
#define _PROCESSGROUP_HPP_

#include "Arduino.h"
#include "Process.hpp"

namespace async{
class ProcessGroup :
    public std::vector<Process*>
{
private:
    String name = "";
    void new_id();
public:
    ProcessGroup();
    template<typename ...Processes>
    ProcessGroup(Processes&... processes){
        auto proc_list = {&processes...};
        this->reserve(proc_list.size());
        for (auto &&process : proc_list){
            this->emplace_back(process);
        }
    };
    ~ProcessGroup();

    const char* get_name() const;
    void        set_name(const char*& name);
    void        set_name(const char*&& name);

    void avg_looptime() const; //TODO

    void start_all();
    void toggle_all();
    void work_all();
    void stop_all();
    void shutdown_all();
    void kill_all();

    Process* select_process(const String& name);
    Process* select_process(const String&& name);
    Process* select_process(const uint16_t& id);
    Process* select_process(const uint16_t&& id);
};
}
#endif
