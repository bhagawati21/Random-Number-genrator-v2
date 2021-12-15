#include "randnum.h"
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string.h>

RANDNUM::RANDNUM()
{
    char_str = "0123456789""!@#$%&*/\?""abcdefghijklmnopqrstuvwxyz""ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    num_str = "0123456789";
    schar_str = "!@#$%&*/\?";
    alpha_str = "abcdefghijklmnopqrstuvwxyz""ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    alpha_num = "0123456789""abcdefghijklmnopqrstuvwxyz""ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    alpha_schar = "!@#$%&*/\?""abcdefghijklmnopqrstuvwxyz""ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    num_schar = "0123456789""!@#$%&*/\?";
    srand(time(NULL));
}

string RANDNUM::GenerateRandNum(bool Schar, bool Num, bool Alpha, int length)
{
    string RandNumber;
    if(Schar && !Num && !Alpha)
        for (int i=1; i<=length; i++)
        RandNumber.push_back(schar_str[rand() % schar_str.length()]);

    else if(Num && !Alpha && !Schar)
        for (int i=1; i<=length; i++)
        RandNumber.push_back(num_str[rand() % num_str.length()]);

    else if(Alpha && !Num && ! Schar)
        for (int i=1; i<=length; i++)
        RandNumber.push_back(alpha_str[rand() % alpha_str.length()]);

    else if(Alpha && Num && !Schar)
        for (int i=1; i<=length; i++)
        RandNumber.push_back(alpha_num[rand() % alpha_num.length()]);

    else if(Alpha && Schar && ! Num)
        for (int i=1; i<=length; i++)
        RandNumber.push_back(alpha_schar[rand() % alpha_schar.length()]);

    else if(Num && Schar && !Alpha)
        for (int i=1; i<=length; i++)
        RandNumber.push_back(num_schar[rand() % num_schar.length()]);

    else
        for (int i=1; i<=length; i++)
        RandNumber.push_back(char_str[rand() % char_str.length()]);

    return RandNumber;
}

char* RANDNUM::AddPrefix(char* SrcStr, char* Prefix)
{
    int PrefixLen = strlen(Prefix);
    for(int i=0 ; i < PrefixLen ; i++)
        SrcStr[i] = Prefix[i];
    return SrcStr;
}

char* RANDNUM::AddSuffix(char* SrcStr, char* Suffix)
{
    int SuffixLen = strlen(Suffix);
    int SrcStrLen = strlen(SrcStr);
    int i = SrcStrLen - SuffixLen;
    for(int j = 0 ; i <= SrcStrLen ; i++, j++)
        SrcStr[i] = Suffix[j];
    return SrcStr;
}

string RANDNUM::AddSeparator(char *SrcStr, char *Separator, unsigned int after)
{
    stringstream SS;
    for(unsigned int i = 0, j = 0; i < strlen(SrcStr) && after > 0;)
    {
        if(j < after)
        {
            SS << SrcStr[i++];
            j++;
        }
        else
        {
            SS << Separator;
            j = 0;
        }
    }
    if(after)
        return SS.str();
    else
        return SrcStr;
}
