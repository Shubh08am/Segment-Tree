//link - https://codeforces.com/contest/339/problem/D
#include <bits/stdc++.h>
#define ll long long
using namespace std;
class SGTree
{
	vector<ll> seg;

public:
	SGTree(ll n)
	{
		seg.resize(4 * n + 1);
	}
	void build(vector<ll> &v, ll low, ll high, ll idx, bool OR)
	{
		if (low == high)
		{
			seg[idx] = v[low];
			return;
		}
		ll mid = (low + high) / 2;
		build(v, low, mid, 2 * idx + 1, !OR);
		build(v, mid + 1, high, 2 * idx + 2, !OR);
		if (OR)
		{
			seg[idx] = (seg[2 * idx + 1] | seg[2 * idx + 2]);
		}
		else
		{
			seg[idx] = (seg[2 * idx + 1] ^ seg[2 * idx + 2]);
		}
	}
	ll query(ll l, ll r, ll low, ll high, ll idx)
	{
		// no overlap
		// [low high][l r] or [l r][low high]
		if (high < l || r < low)
		{
			return 0;
		}
		// complete overlap
		// [l low high r]
		if (l <= low && high <= r)
		{
			return seg[idx];
		}
		// partial overlap
		ll mid = (low + high) / 2;
		ll left = query(l, r, low, mid, 2 * idx + 1);
		ll right = query(l, r, mid + 1, high, 2 * idx + 2);
		return (left | right);
	}
	void update(ll i, ll val, ll low, ll high, ll idx, bool OR)
	{
		if (low == high)
		{
			seg[idx] = val;
			return;
		}
		ll mid = (low + high) / 2;
		if (i <= mid)
		{
			update(i, val, low, mid, 2 * idx + 1, !OR);
		}
		else
		{
			update(i, val, mid + 1, high, 2 * idx + 2, !OR);
		}
		if (OR)
		{
			seg[idx] = (seg[2 * idx + 1] | seg[2 * idx + 2]);
		}
		else
		{
			seg[idx] = (seg[2 * idx + 1] ^ seg[2 * idx + 2]);
		}
	}
};
int main()
{
	ll n, m, p, b;
	cin >> n >> m;
	vector<ll> v(1<<n);
	for (ll i = 0; i < (1 << n); i++)
	{
		cin >> v[i];
	}
	SGTree sgt(1<<n);
	sgt.build(v, 0, (1 << n) - 1, 0, n % 2);
	while (m--)
	{
		cin >> p >> b;
		sgt.update(p - 1, b, 0, (1<<n) - 1, 0, n % 2);
		cout << sgt.query(0, (1<<n) - 1, 0, (1<<n) - 1, 0) << '\n';
	}
	
	return 0;
}
