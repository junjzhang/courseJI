#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>

#define INT_MAX 2147483647

using namespace std;

int test(int num, int num_t);
int tr_ts(int num);
int pa_ts(int num);
int od_ts(int num);
int ex_ts(int num);

int main()
{
    bool in_flag;
    int num,num_t;

    in_flag = true;

    while (in_flag)
    {
        cout << "Please enter the integer and the test number:"<<endl;
        cin >> num >> num_t;
        if (cin.good() && num > 0 && num <= 1e7 && num_t > 0 && num_t < 5)
        {
            in_flag = false;
        }
        cin.clear();
        cin.ignore(INT_MAX,'\n');
    }

    cout<<to_string(test(num,num_t))<<endl;


    return 0;
}

int test(int num, int num_t)
{
    switch(num_t)
    {
    case 1:
        return tr_ts(num);
    case 2:
        return pa_ts(num);
    case 3:
        return od_ts(num);
    case 4:
        return ex_ts(num);
    default:
        return 0;
    }
}

int tr_ts(int num)
{
    int num_ap = int(floor(sqrt(double(2)*num)));

    return ((num_ap)*(num_ap+1) == 2*num);
}

int pa_ts(int num)
{
    string num_s = to_string(num);
    int len = num_s.size();
    for (int iter = 0; iter < len/2 ; iter++)
    {
        if ((num_s[iter]) != (num_s[len-iter-1]))
            return 0;
    }
    return 1;
}

int od_ts(int num)
{
    int num_o = 0;

    while (num != 0)
    {
        num_o += num%2;
        num = num/2;
    }
    return (num%2);
}

int ex_ts(int num)
{
    int digit_n = (to_string(num)).size();
    int digit_pf = 0;
    int pw;

    for (int fact = 2; fact <= num; fact++)
    {
        if (num%fact != 0)
            continue;
        else
        {
            pw = 0;
            while(num%fact==0)
            {
                pw += 1;
                num = num/fact;
            }
            if (pw <= 1)
                digit_pf += int((to_string(pw)).size());
            else
            {
                digit_pf += (int((to_string(pw)).size())+int((to_string(fact)).size()));
            }
        }
    }
    return int(digit_n<digit_pf);
}
