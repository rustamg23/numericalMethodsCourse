#include <iostream>
#include <math.h>
#include <bitset>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void Replace(int n, int i, int j, vector<string>& sdnfS, vector<string>& sdnfS2, int count1, vector<string>& useful) {
    sdnfS2.push_back(sdnfS[i]);
    for (int k = 0; k < n; k++) {
        if (sdnfS[i][k] != sdnfS[j][k]) {
            useful.push_back(sdnfS[i]);
            sdnfS2[count1].replace(k, 1, "-");
        }
    }
}

void clean(vector<string>& vec) {
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
}

void splice(int count, vector<string>& sdnf1, vector<string>& sdnf2, int n, vector<string>& useless, vector<string>& useful) {
    int count1 = 0, remK, count2;
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            count2 = 0;
            for (int k = 0; k < n; k++) {
                if (sdnf1[i][k] != sdnf1[j][k]) {
                    count2++; remK = k;
                    if (count2 > 1) {
                        useless.push_back(sdnf1[j]);
                        break;
                    }
                }
            }
            if (count2 == 1) {
                if (n - 1 == remK || n - 2 == remK || n - 3 == remK || n - 4 == remK || n - 5 == remK) {

                    Replace(n, i, j, sdnf1, sdnf2, count1, useful); count1++;
                }
            }
        }
    }
    clean(sdnf2);
}

string trans(string str) {
    string set = "xyzwt";
    string output = "";
    int size = str.size();
    for (int i = 0; i < size; i++) {
        if (str[i] == '0') output.push_back(set[i]);
        else if (str[i] == '1') output.push_back(set[i] - 32);
        else if (str[i] == '-') continue;
    }
    return output;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    int n, inL = 0, inL2 = 0, inL3 = 0, inL4 = 0, count = 0, count2 = 0;

    string input;

    cin >> n >> input;
    cout << "xY znachit (not x and y)" << endl;
    cout << "minimizaciya metodom Kvayna: " ;
    inL = input.length();
    vector<string> sdnfS, sdnfS2, sdnfS3, sdnfS4, sdnfS5, useless, useful, final;

    for (int i = 0; i < inL; i++) {
        if (input[i] == '1') {
            sdnfS.push_back((bitset<8>(i).to_string().substr(8 - n, n)));
            count++;
        }
    }
    int len = sdnfS.size();
    inL = count;
    splice(inL, sdnfS, sdnfS2, n, useless, useful);
    inL = sdnfS2.size();
    if (inL > 1) {
        splice(inL, sdnfS2, sdnfS3, n, useless, useful);
        inL2 = sdnfS3.size();
        if (inL2 > 1) {
            splice(inL2, sdnfS3, sdnfS4, n, useless, useful);
            inL3 = sdnfS4.size();

            if (inL3 > 1) {
                splice(inL3, sdnfS4, sdnfS5, n, useless, useful);
                inL4 = sdnfS5.size();
            }
            else if (inL3 == 1) final.push_back(sdnfS4[0]);
        }
        else if (inL2 == 1) final.push_back(sdnfS3[0]);
    }
    else if (inL == 1) final.push_back(sdnfS2[0]);

    clean(useless);
    clean(useful);

    int len1 = useless.size();
    bool uselessSubUseful[100] = { false };
    int len2 = useful.size();

    for (int q = 0; q < len1; q++)
        for (int w = 0; w < len2; w++) {
            if (useless[q] == useful[w])
                uselessSubUseful[q] = true;
        }
    for (int e = 0; e < len1; e++) {
        if (uselessSubUseful[e] == false)
            final.push_back(useless[e]);
    }

    int len3 = final.size(), table[50][50] = { 0 }, tableNew[50][50] = { 0 }, tableCols[50] = { 0 };
    int tableRaws[50] = { 0 }, tableNewCols[50] = { 0 }, tableNewRaws[50] = { 0 }, sameCount = 0, hyphenCount = 0;

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len3; j++) {
            for (int k = 0; k < n; k++) {
                if (final[j][k] == '-') hyphenCount++;
            }
            for (int k = 0; k < n; k++) {
                if (sdnfS[i][k] == final[j][k]) sameCount++;
            }
            if (n - hyphenCount == sameCount) table[i][j] = 1;
            sameCount = 0, hyphenCount = 0;
        }
    }

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len3; j++) {
            if (table[i][j] == 1) {
                tableRaws[j]++;
                tableCols[i]++;
            }
        }
    }

    for (int j = 0; j < len; j++) {
        if (tableCols[j] == 1)
            for (int k = 0; k < len3; k++) {
                if (table[j][k] == 1) {
                    for (int q = 0; q < len; q++) {
                        tableNew[q][k] = table[q][k];
                    }
                }
            }
    }

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len3; j++) {
            if (tableNew[i][j] == 1) {
                tableNewRaws[j]++;
                tableNewCols[i]++;
            }
        }
    }

    for (int a = 0; a < len3; a++) {
        if (tableNewRaws[a] == tableRaws[a]) {
            count2++;
        }

    }

    if (len3 == count2) {
        for (int a = 0; a < len3; a++) {

            cout << trans(final[a]);
            if (len3 - a > 1) cout << " v ";
        }
        if (len3 == 0 && inL == 0)
            for (int a = 0; a < len; a++) {

                cout << trans(sdnfS[a]);
            }
        else if (len3 == 0 && len == 0)
            for (int a = 0; a < inL; a++) {
                
                    cout << trans(sdnfS2[a]);
            }
    }
    else {  
        for (int j = 0; j < len3; j++) {
            if (tableNewRaws[j] == 0 && tableRaws != 0) {
                for (int j = 0; j < len3; j++) {
                    if (tableNewRaws[j] != 0 && len3 != 0)
                        cout << trans(final[j]) << " v ";
                }
                cout << trans(final[j]) << endl;
            }
        }
    }
    cout << endl;

    system("pause");
    return 0;
}

