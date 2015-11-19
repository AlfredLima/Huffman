#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
#define pb push_back
#define MAX 2000010
//int back_table[MAX];
vi pre_process(string P)
{
	vi back_table(P.size() +1 );
	int i=0, j=-1; back_table[0] = -1;
	while (i < P.size() )
	{
		while (j >= 0 && P[j] != P[i])
		{
			j = back_table[j];
		}
		i++;
		j++;
		back_table[i] = j;
	}
	return back_table;
}

vi kmp_search(string T, string S)
{
	vi ans;
	vi pre = pre_process(S); 
    int i=0, j=0;
    while (i < T.size() )
    {
        while (j >=0 && T[i] != S[j] )
            j = pre[j];
        ++i;
        ++j;
        if ( j == S.size() )
        {
            ans.pb(i-j);
            j = pre[j];
        }
    }
    return ans;
}

int main()
{
	string text, pattern;
	getline(cin, text);
	getline(cin, pattern);
    vi ans;
    ans = kmp_search(text,pattern);
    printf("%d\n", (int)ans.size());
    return 0;
}