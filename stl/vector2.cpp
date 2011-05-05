#include <iostream>
#include <vector>

using namespace std;

void process(const vector<int>& v1, vector<int>& v2)
{
    unsigned int i, j, sz1, sz2;

    sz1 = v1.size();
    sz2 = v2.size();

    for (i = j = 0; i < sz1 && j < sz2; i++, j++) {
        if (v1[i] > v2[j]) {
            v2.push_back(v1[i]);
        }
    }

    for (i = 0; i < v2.size(); i++)
        cout << v2[i] << " ";
}
/*
int main()
{
    vector<int> v1, v2;

    int i, tmp, n, m;
    cin >> n >> m;

    for (i = 0; i < n; i++) {
        cin >> tmp;
        v1.push_back(tmp);
    } 
    for (i = 0; i < m; i++) {
        cin >> tmp;
        v2.push_back(tmp);
    } 

    process(v1, v2);
    cout << endl;

    return 0;
}
*/
