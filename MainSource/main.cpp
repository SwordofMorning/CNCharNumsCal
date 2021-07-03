#include <iostream>
#include <algorithm>
#include <string>
#include <map>

std::map<char, int> Numbers;    //��
std::map<int, int> Digit;       //��λ����ʮ��ǧ��
std::map<int, int> Level;       //�������ڡ��򡢸���

void init();
int Cal(const std::string& str_p);

int main()
{
    init();
    //��ʼ��

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
    Numbers['0'] = 13;  //��
    Numbers['1'] = 1;   //һ
    Numbers['2'] = 2;   //��
    Numbers['3'] = 3;   //��
    Numbers['4'] = 5;   //��

    Numbers['5'] = 4;   //��_
    Numbers['6'] = 4;   //��
    Numbers['7'] = 2;   //��
    Numbers['8'] = 2;   //��
    Numbers['9'] = 2;   //��
    /*---end---*/

    /*---Digit init---*/
    Digit[0] = 0;       //��
    Digit[1] = 2;       //ʮ
    Digit[2] = 6;       //��
    Digit[3] = 3;       //ǧ
    /*---end---*/

    /*---Level init---*/
    Level[0] = 0;               //��
    Level[1] = 3 + Level[0];    //���
    Level[2] = 2 + Level[1];    //�����
    //����eg��333,888,888�������ڡ���ǧ�˰ٰ�ʮ�ˡ��򡱰˰ٰ�ʮ��
    /*---end---*/
}

int Cal(const std::string& str_p)
{
    int re_level = Level[(str_p.length() - 1) / 4];
    //***��������ıʻ�***

    std::string str_f(str_p);
    //����str_f�����Ϊx��xxxx��xxxx
    while (str_f.length() < 9)
    {
        str_f.insert(str_f.begin(), { '0' });
    }

    std::reverse(str_f.begin(), str_f.end());
    //��ת

    int re_digit(0);
    //***��λ�ʻ�***

    str_f.back() == '0' ? re_digit += 0 : re_digit += Numbers[str_f.back()];
    //�ڼ�

    std::string str_dig = str_f.substr(0, 4);
    std::string str_tTh = str_f.substr(4, 4);
    //���� �� �򼶵��������ַ���

    if (str_dig.find_first_not_of('0') != std::string::npos)
    {
        for (std::string::const_iterator it = str_dig.begin() + str_dig.find_first_not_of('0');
            it != str_dig.end(); ++it)
        {
            re_digit += Numbers[*it];
            //����
            if (*it == '0')
            {
                int a = it - str_dig.begin();
                //����λ
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
            //����
            if (*it == '0')
            {
                int a = it - str_tTh.begin();
                //����λ
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
