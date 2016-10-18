#ifndef _SERIAL_COMMANDER_H_
#define _SERIAL_COMMANDER_H_

#include "InterruptRoutine.h"

class SerialCommander
{
public:
    typedef void (*fn_callback)(const char* args);

    SerialCommander();

    void init();
    void update();
    void setCommandCallback(const char* command, fn_callback callback);

private:
    void executeCommand();

    static const int max_callbacks = 20;
    static const int max_command_length = 100;

    struct CommandCallback
    {
        const char* command;
        fn_callback callback;
    };

    int callback_count;
    CommandCallback callback_array[max_callbacks];

    int command_length;
    char command_buffer[max_command_length + 1];
};

#endif // _SERIAL_COMMANDER_H_

