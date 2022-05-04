// #include "../examples/Functions.cpp"
// #include "../examples/Call.cpp"
// #include "../examples/Processes.cpp"
// #include "../examples/FunctionAndProcess.cpp"

#include "Arduino.h"
#include "AsyncFunction.hpp"
#include "Process.hpp"
#include "CodeBlock.hpp"

// async::Process blinker = Params([](){
//     blinker.set_interval(100);
//     blinker.on_create = [](){
//         pinMode(LED_BUILTIN, OUTPUT);
//     };
//     blinker.on_working = [](){
//         digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
//     };
// });

async::CodeBlock classic_blink = [](){
    static uint32_t target = millis() + 200;
    if(millis() >= target){
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        target += 200;
    }

};

async::function<String(void)> async_readline = [](){
    static String buf;
    static bool clear = false;
    int c = Serial.read();
    bool return_if = c == '\r';

    if(clear){
        buf.clear();
        clear = false;
    } else {
        if(c >= 0 && c != '\r'){
            buf += (char)c;
            Serial.print((char)c);
        }

        if(return_if){
            Serial.print('\n');
            clear = true;
        }
    }
    returns(async_readline, return_if, buf);
};

void setup(){
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    Serial.printf("entered setup block at %lu millis\n", millis());

    Serial.println("Remember that if you using Arduino's serial monitor you should select 'Carriage return' input mode (next to baud selector).");
    Serial.println("In Platformio's serial monitor that is default mode so everything should work out of the box.");
    
    Serial.println("Enter text to echo: (builtin led should blink even while waiting for input!)");
    String out = async_readline()->await()->value();
    
    Serial.println("Enter second text to echo: (notice that code in this scope does not progress further until condition is met)");
    String out2 = async_readline()->await()->value();
    
    Serial.printf("First time you enterded: %s \n", out.c_str());
    Serial.printf("Second time you enterded: %s \n", out2.c_str());
    
    Serial.printf("left setup block at %lu millis\n", millis());
}

void loop() {
    async::Runtime::loop();
}