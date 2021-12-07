# GLUT Double Pendulum Simulation

![Sample GIF](./img/sample.gif)

## Build & Run

```sh
cmake -B build
cd ./build/
make
./pendulum.out /path/to/config.yaml
```

Example configuration files are in `example/`.

## References

- "2重振り子" (https://www.aihara.co.jp/~taiji/pendula-equations/present-node2.html) (referenced on 2021/10/29)
- "4次ルンゲ・クッタ法 | シキノート" (https://slpr.sakura.ne.jp/qp/rk4/) (referenced on 2021/10/29)
