#pragma once
#include <string>

using namespace std;

string GetLastName(string name)
{
    size_t last_space = name.rfind(' ');
    string last_name = name;

    if (last_space != string::npos)
    {
        last_name = name.substr(last_space + 1);
    }
    return last_name;
}