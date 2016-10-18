#include "Arduino.h"

#include "SerialCommander.h"

SerialCommander::SerialCommander()
    : callback_count(0)
    , callback_array()
    , command_length(0)
    , command_buffer()
{
}

void SerialCommander::init()
{
    Serial1.begin(38400);
}

void SerialCommander::setCommandCallback(const char* command, fn_callback callback)
{
    if (callback_count >= max_callbacks)
    {
        return;
    }

    callback_array[callback_count] = {
        command,
        callback
    };

    callback_count++;
}

void SerialCommander::update()
{
    while (Serial1.available() > 0)
    {
        char incoming = Serial1.read();
        if (incoming == '\n' || incoming == '\r')
        {
            command_buffer[command_length] = '\0';
            executeCommand();
            command_length = 0;
        }
        else
        {
            if (command_length < max_command_length)
            {
                command_buffer[command_length] = incoming;
                command_length++;
            }
        }
    }
}

void SerialCommander::executeCommand()
{
    int command_word_end = 0;

    for (; command_word_end < command_length; ++command_word_end)
    {
        if (command_buffer[command_word_end] == ' ')
        {
            break;
        }
    }

    CommandCallback* match = NULL;
    for (int iCommand = 0; iCommand < callback_count; ++iCommand)
    {
        CommandCallback& current = callback_array[iCommand];
        
        for (int iCompare = 0; iCompare < command_word_end; iCompare++)
        {
            char c1 = current.command[iCompare];

            if (!c1)
            {
                break;
            }

            if (c1 != command_buffer[iCompare])
            {
                break;
            }

            if (iCompare == command_word_end - 1)
            {
                match = &current;
            }
        }

        if (match)
        {
            break;
        }
    }

    if (match)
    {
        char* args = &command_buffer[command_word_end + 1];
        if (args[0] == ' ')
        {
            args++;
        }

        match->callback(args);
    }
}

