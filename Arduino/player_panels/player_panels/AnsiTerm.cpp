#include "Arduino.h"

#include "AnsiTerm.h"

AnsiTerm::AnsiTerm(Stream& stream)
    : _stream(stream)
{
}

void AnsiTerm::clearAll()
{
    attr();
    clear();
    cursor();
}

void AnsiTerm::clear()
{
    const char cmd[] = {0x1B, 0x5B, '2', 'J', 0};
    _stream.print(cmd);    
}

void AnsiTerm::eraseLine()
{
    const char cmd[] = {0x1B, 0x5B, 'K', 0};
    _stream.print(cmd);        
}

void AnsiTerm::cursor(uint8_t line, uint8_t column)
{
    char cmd[] = {0x1B, 0x5B, 0};
    _stream.print(cmd);
    _stream.print(line);
    _stream.print(';');
    _stream.print(column);
    _stream.print('H'); 
}

void AnsiTerm::cursorUp(uint8_t count)
{
    char cmd[] = {0x1B, 0x5B, 0};
    _stream.print(cmd);
    _stream.print(count);
    _stream.print('A');
}

void AnsiTerm::cursorDown(uint8_t count)
{
    char cmd[] = {0x1B, 0x5B, 0};
    _stream.print(cmd);
    _stream.print(count);
    _stream.print('B');
}

void AnsiTerm::cursorForward(uint8_t count)
{
    char cmd[] = {0x1B, 0x5B, 0};
    _stream.print(cmd);
    _stream.print(count);
    _stream.print('C');
}

void AnsiTerm::cursorBackward(uint8_t count)
{
    char cmd[] = {0x1B, 0x5B, 0};
    _stream.print(cmd);
    _stream.print(count);
    _stream.print('D');
}

void AnsiTerm::saveCursor()
{
    char cmd[] = {0x1B, 0x5B, 's', 0};
    _stream.print(cmd);
}

void AnsiTerm::restoreCursor()
{
    char cmd[] = {0x1B, 0x5B, 'u', 0};
    _stream.print(cmd);
}


void AnsiTerm::attr(Attribute a1, Attribute a2, Attribute a3)
{
    char cmd[] = {0x1B, 0x5B, 0};
    _stream.print(cmd);

    _stream.print((uint8_t)a1);

    if (a2 != NONE)
    {
        _stream.print(';');
        _stream.print((uint8_t)a2);
    }

    if (a3 != NONE)
    {
        _stream.print(';');
        _stream.print((uint8_t)a3);
    }

    _stream.print('m');
}

size_t AnsiTerm::print(const String& s)
{
    return _stream.print(s);
}

size_t AnsiTerm::print(const char s[])
{
    return _stream.print(s);
}

size_t AnsiTerm::print(char c)
{
    return _stream.print(c);
}

size_t AnsiTerm::print(unsigned char c, int f)
{
    return _stream.print(c, f);
}

size_t AnsiTerm::print(int n, int f)
{
    return _stream.print(n, f);
}

size_t AnsiTerm::print(unsigned int n, int f)
{
    return _stream.print(n, f);
}

size_t AnsiTerm::print(long n, int f)
{
    return _stream.print(n, f);
}

size_t AnsiTerm::print(unsigned long n, int f)
{
    return _stream.print(n, f);
}

size_t AnsiTerm::print(double n, int p)
{
    return _stream.print(n, p);
}

size_t AnsiTerm::print(const Printable& p)
{
    return _stream.print(p);
}


size_t AnsiTerm::println(const String& s)
{
    return _stream.println(s);
}

size_t AnsiTerm::println(const char s[])
{
    return _stream.println(s);
}

size_t AnsiTerm::println(char c)
{
    return _stream.println(c);
}

size_t AnsiTerm::println(unsigned char c, int f)
{
    return _stream.println(c, f);
}

size_t AnsiTerm::println(int n, int f)
{
    return _stream.println(n, f);
}

size_t AnsiTerm::println(unsigned int n, int f)
{
    return _stream.println(n, f);
}

size_t AnsiTerm::println(long n, int f)
{
    return _stream.println(n, f);
}

size_t AnsiTerm::println(unsigned long n, int f)
{
    return _stream.println(n, f);
}

size_t AnsiTerm::println(double n, int p)
{
    return _stream.println(n, p);
}

size_t AnsiTerm::println(const Printable& p)
{
    return _stream.println(p);
}

size_t AnsiTerm::println()
{
    return _stream.println();
}

