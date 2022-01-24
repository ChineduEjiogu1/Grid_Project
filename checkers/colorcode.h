#include <string>

std::string ColorBlue(char z)
{
    return "\e[01;34m" + std::string(1, z) + "\e[0m";
}

std::string ColorBlue(std::string z)
{
    return "\e[01;34m" + z + "\e[0m";
}

std::string ColorRed(std::string w)
{
    return "\e[033;31m" + w + "\e[0m";
}

std::string ColorBlack(char w)
{
    return "\e[033;30m" + std::string(1, w) + "\e[0m";
}

std::string ColorYellow(char q)
{
    return "\e[01;33m" + std::string(1, q) + "\e[0m";
}

std::string ColorRed(char w)
{
    return "\e[033;31m" + std::string(1, w) + "\e[0m";
}

std::string colorElement(char s)
{
    if (s == 'O')
        return ColorYellow(s);
    if (s == 'X')
        return ColorBlue(s);
    else
        return ColorBlack(s);
}

