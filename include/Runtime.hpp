#ifndef _RUNTIME_HPP_
#define _RUNTIME_HPP_

#include "Arduino.h"
#include "IAsyncFunction.hpp"
#include "ILoopable.hpp"

namespace async{

class Runtime{
    Runtime(){};
    ~Runtime(){};
public:
    static inline std::vector<ILoopable*> loopables;
    static inline std::vector<ILoopable*> async_calls;
    static inline std::vector<ILoopable*> processes;
    static inline std::vector<IAsyncFunction*> async_functions;

    static void loop(){
        for (auto &&loopable : loopables){ loopable->loop(); }
        for (auto &&process : processes){ process->loop(); }
        for (auto &&call : async_calls){ call->loop(); }
        for (auto &&function : async_functions){ function->loop(); }
    }
};

};



#endif