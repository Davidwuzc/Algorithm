#include <iostream>
#include <bits/stdc++.h>
using namespace std;
const int maxn = 50005;
int s[maxn], n;
int lowbit(int k)
{
	return k&(-k);
}
void add(int k, int v)//向第k个营地增加v个人 
{
	while (k <= n)
	{
		s[k] += v;
		k += lowbit(k);
	}
}
int sum(int k)
{
	int re = 0;
	while (k>0)
	{
		re += s[k];
		k -= lowbit(k);
	}
	return re;
}
int main()
{
	int t, ca = 1;
	char op[10];
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		memset(s, 0, sizeof(s));
		for (int i = 1; i <= n; i++)
		{
			int num; scanf("%d", &num);
			add(i, num);
		}
		printf("Case %d:\n", ca++);
		int i, j;
		while (scanf("%s", op) && op[0] != 'E')
		{
			scanf("%d %d", &i, &j);
			if (op[0] == 'Q')
			{
				printf("%d\n", sum(j) - sum(i - 1));
			}
			else if (op[0] == 'S')
			{
				add(i, -j);
			}
			else if (op[0] == 'A')
			{
				add(i, j);
			}
		}
	}
	return 0;
}