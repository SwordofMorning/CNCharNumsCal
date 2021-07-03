#include <iostream>
#include <algorithm>
#include <string>
#include <map>

std::map<char, int> Numbers;    //数
std::map<int, int> Digit;       //数位（个十百千）
std::map<int, int> Level;       //数级（亿、万、个）

void init();
int Cal(const std::string& str_p);

int main()
{
    init();
    //初始化

    std::string str;
    std::cin >> str;

    int ans = Cal(str);
    if (str.length() == 2 && str.front() == '1')
    {
        ans -= 1;
    }

    std::cout << ans << std::endl;

    return 0;
}

void init()
{
    /*---Numbers init---*/
    Numbers['0'] = 13;  //零
    Numbers['1'] = 1;   //一
    Numbers['2'] = 2;   //二
    Numbers['3'] = 3;   //三
    Numbers['4'] = 5;   //四

    Numbers['5'] = 4;   //五_
    Numbers['6'] = 4;   //六
    Numbers['7'] = 2;   //七
    Numbers['8'] = 2;   //八
    Numbers['9'] = 2;   //九
    /*---end---*/

    /*---Digit init---*/
    Digit[0] = 0;       //个
    Digit[1] = 2;       //十
    Digit[2] = 6;       //百
    Digit[3] = 3;       //千
    /*---end---*/

    /*---Level init---*/
    Level[0] = 0;               //个
    Level[1] = 3 + Level[0];    //万个
    Level[2] = 2 + Level[1];    //亿万个
    //这里eg：333,888,888：三“亿”八千八百八十八“万”八百八十八
    /*---end---*/
}

int Cal(const std::string& str_p)
{
    int re_level = Level[(str_p.length() - 1) / 4];
    //***求①数级的笔画***

    std::string str_f(str_p);
    //构造str_f以填充为x亿xxxx万xxxx
    while (str_f.length() < 9)
    {
        str_f.insert(str_f.begin(), { '0' });
    }

    std::reverse(str_f.begin(), str_f.end());
    //翻转

    int re_digit(0);
    //***数位笔画***

    str_f.back() == '0' ? re_digit += 0 : re_digit += Numbers[str_f.back()];
    //亿级

    std::string str_dig = str_f.substr(0, 4);
    std::string str_tTh = str_f.substr(4, 4);
    //个级 和 万级的两个子字符串

    if (str_dig.find_first_not_of('0') != std::string::npos)
    {
        for (std::string::const_iterator it = str_dig.begin() + str_dig.find_first_not_of('0');
            it != str_dig.end(); ++it)
        {
            re_digit += Numbers[*it];
            //②数
            if (*it == '0')
            {
                int a = it - str_dig.begin();
                //③数位
                if (str_dig.find_first_not_of('0', it - str_dig.begin()) == std::string::npos)
                {
                    re_digit -= Numbers[*it];
                    break;
                }
                else if (str_dig.find_first_not_of('0', it - str_dig.begin()) != std::string::npos)
                {
                    it += str_dig.find_first_not_of('0', it - str_dig.begin());
                    continue;
                }
            }
            else if (*it != '0')
            {
                re_digit += Digit[it - str_dig.begin()];
            }
        }
    }

    if (str_tTh.find_first_not_of('0') != std::string::npos)
    {
        for (std::string::const_iterator it = str_tTh.begin() + str_tTh.find_first_not_of('0');
            it != str_tTh.end(); ++it)
        {
            re_digit += Numbers[*it];
            //②数
            if (*it == '0')
            {
                int a = it - str_tTh.begin();
                //③数位
                if (str_tTh.find_first_not_of('0', it - str_tTh.begin()) == std::string::npos)
                {
                    re_digit -= Numbers[*it];
                    break;
                }
                else if (str_tTh.find_first_not_of('0', it - str_tTh.begin()) != std::string::npos)
                {
                    it += str_tTh.find_first_not_of('0', it - str_tTh.begin());
                    continue;
                }
            }
            else if (*it != '0')
            {
                re_digit += Digit[it - str_tTh.begin()];
            }
        }
    }

    return re_digit + re_level;
}
