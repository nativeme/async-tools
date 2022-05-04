#include "ProcessGroup.hpp"
namespace async{

    ProcessGroup::ProcessGroup(){};
    ProcessGroup::~ProcessGroup(){};

    const char* ProcessGroup::get_name() const{
        return this->name.c_str();
    };
    void        ProcessGroup::set_name(const char*& name){
        this->name = name;
    };
    void        ProcessGroup::set_name(const char*&& name){
        this->name = name;
    };

    void ProcessGroup::avg_looptime() const {

    }; //TODO

    void ProcessGroup::start_all(){
        for (auto &&process : *this){
            process->start();   
        }
    };
    void ProcessGroup::toggle_all(){
        for (auto &&process : *this){
            process->toggle();           
        }
    };
    void ProcessGroup::work_all(){
        for (auto &&process : *this){
            process->work();
        }
    };
    void ProcessGroup::stop_all(){
        for (auto &&process : *this){
            process->stop();
        }
    };
    void ProcessGroup::shutdown_all(){
        for (auto &&process : *this){
            process->shutdown();
        }        
    };
    void ProcessGroup::kill_all(){
        for (auto &&process : *this){
            process->kill();
        }
    };

    Process* ProcessGroup::select_process(const String& name){
        auto found = std::find_if(this->begin(), this->end(), [&name](const Process* proc){
            return proc->get_name() == name;
        });

        if(found != this->begin())
            return *found;
        else
            return nullptr;
    };
    Process* ProcessGroup::select_process(const String&& name){
        auto found = std::find_if(this->begin(), this->end(), [&name](const Process* proc){
            return proc->get_name() == name;
        });

        if(found != this->end())
            return *found;
        else
            return nullptr;
    };
    Process* ProcessGroup::select_process(const uint16_t& id){
        auto found = std::find_if(this->begin(), this->end(), [&id](const Process* proc){
            return proc->get_id() == id;
        });

        if(found != this->end())
            return *found;
        else
            return nullptr;
    };
    Process* ProcessGroup::select_process(const uint16_t&& id){
        auto found = std::find_if(this->begin(), this->end(), [&id](const Process* proc){
            return proc->get_id() == id;
        });

        if(found != this->end())
            return *found;
        else
            return nullptr;
    };
}
