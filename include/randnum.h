#ifndef RANDNUM_H
#define RANDNUM_H

#include <iostream>

using namespace std;

class RANDNUM
{
    public:
        string GenerateRandNum(bool,bool,bool,int);
        char* AddPrefix(char*, char*);
        char* AddSuffix(char*, char*);
        string AddSeparator(char*, char*, unsigned int);
        RANDNUM();
    protected:

    private:
        string char_str, num_str, schar_str, alpha_str, alpha_num, alpha_schar, num_schar;
};

#endif // RANDNUM_H
