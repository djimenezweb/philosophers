# Philosophers

## Subject

TODO: Add subject

## Arguments
```bash
./philo n tt_die tt_eat tt_sleep [max_loops]
```
`n` philosophers eat for `tt_eat` ms, sleep for `tt_sleep` ms and have `tt_die - tt_eat - tt_sleep` ms to start eating again.

For example, `5 800 200 100` means that `5` philosophers eat for `200`ms, sleep for `100`ms and have `500`ms to start eating again before they die.

```bash
./philo   1  800 200 200        One philo should die
./philo   1  800 200 200  10    One philo should die

./philo   2  130  60  60        No one should die (strict)
./philo   2  500 250 250        No one should die 
./philo   2  500 299 201        One philo should die
./philo   2  500 317 183        One philo should die
./philo   2  800 200 200  10    No one should die, simulation should stop after 10 
./philo   2 1000 200 200  50    No one should die, simulation should stop after 50 

./philo   3  310 103 103        No one should die (strict)
./philo   3  310 104 104        One philo should die

./philo   4  200 205 200        One philo should die
./philo   4  310 200 100        One philo should die
./philo   4  410 200 200        No one should die
./philo   4  410 200 200  10    No one should die, simulation should stop after 10 eats
./philo   4  410 200 200 200    No one should die, simulation should stop after 200 eats
./philo   4  610 200 100  10    No one should die, simulation should stop after 10 eats

./philo   5  310 100 200        No one should die
./philo   5  600 150 150        No one should die
./philo   5  800 200 200        No one should die
./philo   5  800 200 200   7    No one should die, simulation should stop after 7 eats
./philo   5  800 200 200  30    No one should die, simulation should stop after 30 eats
./philo   5 1000 200 200   7    No one should die, simulation should stop after 7 eats
./philo   5 1000 200 200  30    No one should die, simulation should stop after 30 eats

./philo 100  800 200 200        No one should die
./philo 105  800 200 200        No one should die
./philo 181  400 200 200        One philo should die
./philo 199  800 200 200 200    No one should die, simulation should stop after 200 eats
./philo 200  800 200 200        No one should die
./philo 200 1000 200 200   3    No one should die, simulation should stop after 3 eats
./philo 200 1000 200 200 200    No one should die, simulation should stop after 200 eats
```

## How to detect data races

Compile and link your program with `-fsanitize=thread`. To get a reasonable performance add `-O1` or higher. Use `-g` to get file names and line numbers in the warning messages.