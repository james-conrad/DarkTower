#ifndef _ANSI_TERM_H_
#define _ANSI_TERM_H_

class AnsiTerm
{
public:
    AnsiTerm(Stream& stream);

    enum Attribute
    {
        NONE       = 0,
        BOLD       = 1,
        UNDERLINE  = 2,
        BLINK      = 3,
        REVERSE    = 4,

        FG_Black   = 30,
        FG_Red     = 31,
        FG_Green   = 32,
        FG_Yellow  = 33,
        FG_Blue    = 34,
        FG_Magenta = 35,
        FG_Cyan    = 36,
        FG_White   = 37,

        BG_Black   = 40,
        BG_Red     = 41,
        BG_Green   = 42,
        BG_Yellow  = 43,
        BG_Blue    = 44,
        BG_Magenta = 45,
        BG_Cyan    = 46,
        BG_White   = 47,
    };

    void clearAll();
    void clear();
    void eraseLine();

    void cursor(uint8_t line = 0, uint8_t column = 0);
    void cursorUp(uint8_t count = 1);
    void cursorDown(uint8_t count = 1);
    void cursorForward(uint8_t count = 1);
    void cursorBackward(uint8_t count = 1);
    void saveCursor();
    void restoreCursor();

    void attr(Attribute a1 = NONE, Attribute a2 = NONE, Attribute a3 = NONE);

    size_t print(const String& s);
    size_t print(const char s[]);
    size_t print(char c);
    size_t print(unsigned char c, int f = DEC);
    size_t print(int n, int f = DEC);
    size_t print(unsigned int n, int f = DEC);
    size_t print(long n, int f = DEC);
    size_t print(unsigned long n, int f = DEC);
    size_t print(double n, int p = 2);
    size_t print(const Printable& p);

    size_t println(const String& s);
    size_t println(const char s[]);
    size_t println(char c);
    size_t println(unsigned char c, int f = DEC);
    size_t println(int n, int f = DEC);
    size_t println(unsigned int n , int f = DEC);
    size_t println(long n, int f = DEC);
    size_t println(unsigned long n, int f = DEC);
    size_t println(double n, int p = 2);
    size_t println(const Printable& p);
    size_t println();

private:
    Stream& _stream;
};

#endif // _ANSI_TERM_H_
