#include <iostream>
#include <string>
#include <bitset>
using namespace std;

int main()
{
    int n, count = 0;
    string buff, set = "xyzwq", res;
    cin >> n >> buff;
    int len = buff.length();
    if (len != pow(2, n))
    {
        cout << "Error! Invalid vector.";
        return 0;
    }

    for (int i = 0; i < len; i++)
    {                             
        res = "";                           
        if (buff[i] == '1')
        {
            count++;
            string temp = bitset<8>(i).to_string().substr(8 - n, n);
            for (int j = 0; j < temp.length(); j++)
            {
                if (temp[j] - 48) res += (char)set[j] - 32;  //если значение 1, то заглавная буква. Заглавные буквы начинаются на 32 символа раньше.
                else res += (char)set[j];                    //если значение 0, то строчная.
            }
            if (count == 1) cout << res;
            else cout << " v " << res;
        }
        
    }
    system("pause");
    return 0;
}