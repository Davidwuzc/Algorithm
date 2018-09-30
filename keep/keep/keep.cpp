// keep.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
//#include <iostream>
//#include <string>
//using namespace std;
//const int maxn = 50000 + 10;
//int arr[maxn];
//int n;
//int bit[maxn + 1];
//
//void add(int u, int v) {//Point upd
//	for (u++; u <= n; u += u&-u)
//		bit[u] += v;
//}
//
//int psum(int u) {//Sum of arr
//	int ans = 0;
//	for (u++; u >= 1; u -= u&-u)
//		ans += bit[u];
//	return ans;
//}
//
//int main()
//{
//	int t;
//	cin >> t;
//	int id = 1;
//	while (t--) {
//		cin >> n;
//		for (int i = 1; i <= n; i++) {
//			cin >> arr[i];
//			add(i, arr[i]);
//		}
//		cout << "Case " << id << ":" << endl;
//		id++;
//		string s;
//		int a, b;
//		while (true) {
//			cin >> s;
//			if (s == "Add") {
//				cin >> a >> b;
//				add(a, b);
//			}
//			else if (s == "Sub") {
//				cin >> a >> b;
//				add(a, -b);
//			}
//			else if (s == "Query") {
//				cin >> a >> b;
//				cout << psum(b) - psum(a - 1) << endl;;
//			}
//			else {
//				break;
//			}
//		}
//	}
//	return 0;
//}
//#include<bits/stdc++.h>
#include <string>
#include <stdlib.h>
#include <iostream>
using namespace std;
const int maxn = 200020;
const int INF = 100000;
int n;
int SGMT[maxn << 1];
int max(int a, int b)
{
	if (a < b)
		return b;
	return a;
}
//build tree
void build() {
	for (int i = n - 1; i; i--) {
		//SGMT[i] = SGMT[i << 1] + SGMT[i << 1 | 1];
		SGMT[i] = max(SGMT[i << 1], SGMT[i << 1 | 1]);
	}
}

//count the sum from u to v
int sum_range(int l, int r) {
	int ans = -INF;
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l & 1)
			ans = max(ans,SGMT[l++]);
		if (r & 1) {
			ans = max(SGMT[--r],ans);
		}
	}
	return ans;
}

//update the value
void upd(int p, int val) {
	for (SGMT[p += n] = val; p > 1; p >>= 1)
		SGMT[p >> 1] = max(SGMT[p], SGMT[p ^ 1]);
}
int main() {
	int m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> SGMT[i+n];
	build();
	char C;
	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> C >> a >> b;
		if (C == 'Q') {
			cout << sum_range(a - 1, b) << endl;
		}
		else {
			upd(a - 1, b);
		}
	}
	return 0;
}

//int main()
//{
//	int t;
//	scanf("%d", &t);
//	int case1 = 1;
//	while (t--)
//	{
//		scanf("%d", &n);
//		memset(SGMT, 0, sizeof(SGMT));
//		for (int i = 0; i < n; i++)
//			scanf("%d", &arr[i]);
//		build();
//		char ch[10];
//		printf("Case %d:\n", case1++);
//		while (~scanf("%s", ch))
//		{
//			if (ch[0] == 'E')
//				break;
//			else if (ch[0] == 'Q')
//			{
//				int l, r;
//				scanf("%d %d", &l, &r);
//				int sum = sum_range(l-1,r);
//				printf("%d\n", sum);
//			}
//			else if (ch[0] == 'A')
//			{
//				int p, val;
//				scanf("%d %d", &p, &val);
//				upd(p-1, val);
//			}
//			else {
//				int p, val;
//				scanf("%d %d", &p, &val);
//				upd(p-1, -val);
//			}
//		}
//	}
//	return 0;
//}
//const int maxn = 5e4 + 10;
//int a[maxn], bit[maxn];
//int n;
//void add(int u, int v) {//Point upd
//	for (; u <= n; u += u&-u)
//		bit[u] += v;
//}
//
//int psum(int u) {//Sum of arr
//	int ans = 0;
//	for (; u>=1; u -= u&-u)
//		ans += bit[u];
//	return ans;
//}
//int main()
//{
//	int t;
//	scanf("%d", &t);
//	int case1 = 1;
//	while (t--)
//	{
//		scanf("%d", &n);
//		memset(bit, 0, sizeof(bit));
//		for (int i = 1; i <= n; i++)
//			scanf("%d", &a[i]), add(i, a[i]);
//		char ch[10];
//		printf("Case %d:\n", case1++);
//		while (~scanf("%s", ch))
//		{
//			if (ch[0] == 'E')
//				break;
//			else if (ch[0] == 'Q')
//			{
//				int l, r;
//				scanf("%d %d", &l, &r);
//				int sum = psum(r) - psum(l - 1);
//				printf("%d\n", sum);
//			}
//			else if (ch[0] == 'A')
//			{
//				int p, val;
//				scanf("%d %d", &p, &val);
//				add(p, val);
//			}
//			else {
//				int p, val;
//				scanf("%d %d", &p, &val);
//				add(p, -val);
//			}
//		}
//	}
//	return 0;
//}
//#include <iostream>
//#include <string>
//using namespace std;
//const int maxn = 50000+10;
//int arr[maxn];
//int n;
//int bit[maxn + 1];
//
//void add(int u, int v) {//Point upd
//	for (u++; u <= n; u += u&-u)
//		bit[u] += v;
//}
//
//int psum(int u) {//Sum of arr
//	int ans = 0;
//	for (u++; u>=1; u -= u&-u)
//		ans += bit[u];
//	return ans;
//}
//
//int main()
//{
//	int t;
//	cin >> t;
//	int id = 1;
//	while (t--) {
//		cin >> n;
//		for (int i = 1; i <= n; i++) {
//			cin >> arr[i];
//			add(i, arr[i]);
//		}
//		cout << "Case " << id << ":" << endl;
//		id++;
//		string s;
//		int a, b;
//		while (true) {
//			cin >> s;
//			if (s == "Add") {
//				cin >> a >> b;
//				add(a, b);
//			}
//			else if (s == "Sub") {
//				cin >> a >> b;
//				add(a, -b);
//			}
//			else if (s == "Query") {
//				cin >> a >> b;
//				cout << psum(b) - psum(a-1) << endl;;
//			}
//			else {
//				break;
//			}
//		}
//	}
//	return 0;
//}

