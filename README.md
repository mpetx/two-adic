# two-adic
two-adicは2進数演算のためのヘッダーオンリーライブラリーです。

## 例

```cpp
#include <iostream>
#include <two-adic/two-adic.hpp>

int main() {
  two_adic::two_adic<64> x { 3 };
  std::cout << " -3 = " << -x << std::endl;
  std::cout << "1/3 = " << x.inverse() << std::endl;
}
```

```console:output
 -3 = 1111111111111111111111111111111111111111111111111111111111111101P0
1/3 = 1010101010101010101010101010101010101010101010101010101010101011P0
```

## API
### コンストラクタ
```cpp
two_adic(two_adic const & x); // 1
two_adic(two_adic && x); // 2
two_adic & operator=(two_adic const & x); // 3
two_adic & operator=(two_adic && x); // 4

template <typename I>
two_adic(I x); // 5
```

1から4はデフォルトコンストラクタ。

5は値が`x`である2進数を構築する。`I`は整数型でなければならない。

### 算術演算子
```cpp
two_adic operator+(two_adic const & x) const;
two_adic operator-() const;
two_adic operator-(two_adic const & x) const;
two_adic operator*(two_adic const & x) const;
two_adic operator/(two_adic const & x) const;
two_adic operator<<(std::size_t offset) const;
two_adic operator>>(std::size_t offset) const;
```
和差積商演算子はその和差積商を計算する。

シフト演算子は2の累乗倍を計算する。

### `inverse`
```cpp
two_adic inverse() const;
```
逆数を計算する。

### `norm`
```cpp
double norm() const;
```
ノルムを計算する。

### `distance`
```cpp
static double distance(two_adic const & x, two_adic const & y);
```
両数の距離（差のノルム）を計算する。


### 代入演算子
```cpp
two_adic & operator=(two_adic const & x);
two_adic & operator=(two_adic && x);
two_adic & operator+=(two_adic const & x);
two_adic & operator-=(two_adic const & x);
two_adic & operator*=(two_adic const & x);
two_adic & operator/=(two_adic const & x);
two_adic & operator<<=(std::size_t offset);
two_adic & operator>>=(std::size_t offset);
```

### `operator<<`
```cpp
std::ostream & operator<<(std::ostream & out, two_adic const & x);
```

`x`を`out`に出力する。
