
![Screenshot from 2023-08-27 14-42-18](https://github.com/pcheron-root/philosophers/assets/126467996/ba4d19a7-c00e-4d9a-9640-a8a1996c413f)

# philosophers

## Table of contents
- [Overview].(#Overview)
- [Advancing tests](#🧙‍♂️ Avanced testing)

## Overview

In computer science, the dining philosophers problem is an exemple problem often used in concurrent algorithm design to illustrate symchronization issues and techniques for resolving them. 

Philosophers dine together at the same table. Each philosopher has his own plate at the table. There is a fork between each plate. The dish served is a kind of spaghetti which has to be eaten with two forks. Each philosopher can only alternately eat, sleep and think. Moreover, a philosopher can only eat his spaghetti when he has both a left and right fork. Thus two forks will only be available when his two nearest neighbors are sleeping or thinking, not eating. After an individual philosopher finishes eating, he will put down both forks. The problem is how to design a regimen (a concurrent algorithm) such that no philosopher will starve; i.e., each can forever continue to alternate between eating and thinking, assuming that no philosopher can know when others may want to eat, sleep or think (an issue of incomplete information).

## 🧙‍♂️ Avanced testing

```bash
./philo 3 610 200 80
```

🍝 philosophers must eat one by one without anyone dying. 🍝

```bash
./philo 2 310 200 100
```

💀 Philosopher who eats first must die 💀

```bash
./philo 4 350 200 50000
```

😴 program mustn't wait for <time_to_sleep> to end before stopping 😴

```bash
valgrind --tool=helgrind ./philo 4 450 200 200
```


👹 helgrind mustn't display errors 👹

```bash
valgrind --tool=helgrind ./philo 1 800 200 200
```

👹 helgrind mustn't display errors 👹

```bash
valgrind --tool=helgrind ./philo 3 700 200 200
```

👹 helgrind mustn't display errors 👹

```bash
valgrind --tool=helgrind ./philo 2 450 200 200 7
```

👹 helgrind mustn't display errors 👹

### 🤩 Oustanding project ?

- 200 philosophers

```bash
./philo 200 410 200 200
```

🍝 philosophers must eat one by one without anyone dying. 🍝

- 1000 philosophers

```bash
./philo 1000 450 200 200
```

🍝 philosophers must eat one by one without anyone dying. 🍝

- 199 philosophers

```bash
./philo 199 620 200 100
```

🍝 philosophers must eat one by one without anyone dying. 🍝

- Try whis helgrind

```bash
valgrind --tool=helgrind ./philo 4 410 200 200
```

🍝 philosophers must eat one by one without anyone dying. 🍝
