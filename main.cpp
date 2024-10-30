#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;
using vvl = vector<vl>;
using Pos = pair<ll, ll>;

ll n;
vvl B;

Pos Rotate(const Pos& p, const Pos& center) {
  auto [x, y] = p;
  const auto& [cx, cy] = center;

  x -= cx;
  y -= cy;

  return {-y + cx, x + cy};
}

void Put(ll x, ll y, ll d, ll g) {
  set<Pos> pts{};
  pts.insert({x, y});

  Pos cx;
  if (d == 0) {
    cx = {x + 1, y};
  } else if (d == 1) {
    cx = {x, y - 1};
  } else if (d == 2) {
    cx = {x - 1, y};
  } else if (d == 3) {
    cx = {x, y + 1};
  }
  pts.insert(cx);

  while (g > 0) {
    set<Pos> rot{};

    for (const auto& p : pts) {
      const auto& q = Rotate(p, cx);
      rot.insert(q);
    }

    pts.merge(rot);

    cx = Rotate({x, y}, cx);
    --g;
  }

  for (const auto& [px, py] : pts) {
    if (px < 0 || 100 < px || py < 0 || 100 < py) continue;

    B[px][py] = 1;
  }
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  B = vvl(101, vl(101, 0));

  cin >> n;
  for (auto i = 0; i < n; ++i) {
    ll x, y, d, g;
    cin >> x >> y >> d >> g;
    Put(x, y, d, g);
  }

  ll ans = 0;
  for (auto i = 0; i < 100; ++i) {
    for (auto j = 0; j < 100; ++j) {
      if (B[i][j] == 1 && B[i + 1][j] == 1 && B[i][j + 1] == 1 &&
          B[i + 1][j + 1] == 1) {
        ++ans;
      }
    }
  }

  cout << ans;

  return 0;
}