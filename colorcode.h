#include <string>

std::string ColorBlue(char z)
{
    return "\e[01;34m" + std::string(1, z) + "\e[0m";
}

std::string ColorBlue(std::string z)
{
    return "\e[01;34m" + z + "\e[0m";
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
        return ColorRed(s);
    if (s == 'X')
        return ColorYellow(s);
    else
        return ColorBlue(s);
}

