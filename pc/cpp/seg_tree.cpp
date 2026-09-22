#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3E6;

struct Node {
    int l = 0;
    int r = 0;
    int cnt = 0;
    i64 sum = 0;
    int max = -1E9;
    int min = 1E9;
    int tag = 0;
};

int tot = 0;
std::vector<Node> t(N);

void pull(int p) {
    t[p].cnt = t[t[p].l].cnt + t[t[p].r].cnt;
    t[p].sum = t[t[p].l].sum + t[t[p].r].sum;
    t[p].max = std::max(t[t[p].l].max, t[t[p].r].max);
    t[p].min = std::min(t[t[p].l].min, t[t[p].r].min);
}

void add(int p, int v) {
    if (!p) {
        return;
    }
    t[p].sum += 1LL * t[p].cnt * v;
    t[p].tag += v;
}

void push(int p) {
    if (t[p].tag) {
        add(t[p].l, t[p].tag);
        add(t[p].r, t[p].tag);
    }
    t[p].tag = 0;
}

void add(int &p, int l, int r, int x, int y, int i) {
    if (!p) {
        p = ++tot;
        t[p] = {};
    }
    if (r - l == 1) {
        t[p].cnt += 1;
        t[p].sum += y;
        t[p].min = t[p].max = i;
        return;
    }
    int m = (l + r) / 2;
    push(p);
    if (x < m) {
        add(t[p].l, l, m, x, y, i);
    } else {
        add(t[p].r, m, r, x, y, i);
    }
    pull(p);
}

int query(int p, int l, int r, int x, int y) {
    if (!p || l >= y || r <= x) {
        return 0;
    }
    if (l >= x && r <= y) {
        return t[p].cnt;
    }
    int m = (l + r) / 2;
    push(p);
    return query(t[p].l, l, m, x, y) + query(t[p].r, m, r, x, y);
}

std::pair<int, int> split(int p, int v) {
    if (t[p].min >= v) {
        return {0, p};
    }
    if (t[p].max < v) {
        return {p, 0};
    }
    push(p);
    int q = ++tot;
    t[q] = {};
    auto [a, b] = split(t[p].l, v);
    auto [c, d] = split(t[p].r, v);
    t[p].l = a;
    t[p].r = c;
    t[q].l = b;
    t[q].r = d;
    add(b, -t[c].cnt);
    pull(p);
    pull(q);
    return {p, q};
}

void solve() {
    int n;
    std::cin >> n;

    tot = 0;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;
    }
    std::vector<int> o(n);
    std::iota(o.begin(), o.end(), 0);
    std::sort(o.begin(), o.end(),
        [&](int i, int j) {
            return a[i] < a[j] || (a[i] == a[j] && i < j);
        });
    for (int i = 0; i < n; i++) {
        a[o[i]] = i;
    }

    int rt = 0;
    for (int i = 0; i < n; i++) {
        int v = query(rt, 0, n, a[i] + 1, n);
        add(rt, 0, n, a[i], v, i);
    }

    std::map<int, int> seg;
    seg[0] = rt;
    seg[n] = -1;
    std::multiset<i64> s{t[rt].sum};

    i64 ans;
    for (int i = 0; i < n; i++) {
        ans = *s.rbegin();
        std::cout << ans << " \n"[i == n - 1];

        i64 p;
        std::cin >> p;
        p ^= ans;
        p--;

        if (p < 0 || p >= n) {
            continue;
        }

        auto it = std::prev(seg.upper_bound(p));
        int l = it->first, r = l + t[it->second].cnt;
        int nd = it->second;
        seg.erase(it);
        // std::cerr << "(" << l << ", " << r << ")\n";

        s.extract(t[nd].sum);
        auto [L, MR] = split(nd, p);
        auto [M, R] = split(MR, p + 1);
        // std::cerr << p << " " << t[L].sum << " " << t[R].sum << "\n";
        if (L) {
            s.insert(t[L].sum);
            seg[l] = L;
        }
        if (R) {
            s.insert(t[R].sum);
            seg[p + 1] = R;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
