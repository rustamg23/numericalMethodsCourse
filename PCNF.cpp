#include <iostream>
#include <string>
#include <bitset>
using namespace std;

string set = "xyzwq";

string Transf(int j, string temp) {
    string forTrans = "";
    if (temp[j] - 48) forTrans = set[j];
    else forTrans = (char)set[j]-32;
    return forTrans;
}

int main()
{
    int n, count = 0;
    string vect, snkf;
    cin >> n >> vect;
    if (vect.length() != pow(2, n))
    {
        cout << "Error! Invalid vector.";
        return 0;
    }

    for (int i = 0; i < vect.length(); i++)
    {                                          
        if (vect[i] == '0')
        {   
            snkf = "(";
            count++;
            string binaryView = bitset<8>(i).to_string().substr(8 - n, n);
            for (int j = 0; j < binaryView.length(); j++)
            {
                string increment;
                if (j == 0) {
                    increment = Transf(j, binaryView);
                }
                else if (j < binaryView.length() - 1)
                {
                    increment = " v ";
                    increment += Transf(j, binaryView);
                }
                else {
                    increment = " v ";
                    increment += Transf(j, binaryView);
                    increment += ")";
                }
                snkf.append(increment);
            }
        cout << snkf;
        }
        
    }

    system("pause");
    return 0;
}