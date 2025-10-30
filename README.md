# Philosophers

## Subject

TODO: Add subject

## Tests

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

./philo * * * * -fsanitize=thread

./philo   1  800 200 200		Muere
./philo   5  800 200 200		Viven
./philo   5  800 200 200   7	Viven y cada uno come 7 veces
./philo   4  410 200 200		Viven
./philo   4  310 200 100		Muere
./philo   3  310 103 103		Tienen que vivir
./philo   3  310 104 104		Tienen que morir
./philo 181  400 200 200		Muere

./philo   1  800 200 200  10
./philo   1  800 200 200  10
./philo   2  800 200 200  10
./philo   2  500 250 250
./philo   2  500 299 201
./philo   2  500 317 183
./philo   2 1000 200 200  50
./philo   4  410 200 200 200
./philo   4  310 200 100
./philo   4  610 200 100  10
./philo   5  800 200 200  30
./philo   5  800 200 200   7
./philo   5 1000 200 200   7
./philo   5 1000 200 200  30
./philo 199  800 200 200 200
./philo 200 1000 200 200   3
./philo 200 1000 200 200 200

./philo   1  800 200 200		One philo should die
./philo   2  130  60  60		No one should die (preciso)
./philo   3  310 103 103		No one should die (preciso)
./philo   4  310 200 100		One philo should die
./philo   4  200 205 200		One philo should die
./philo   4  410 200 200		No one should die
./philo   4  410 200 200  10	No one should die, simulation should stop after 10 eats
./philo   5  800 200 200   7	No one should die, simulation should stop after 7 eats
./philo   5  800 200 200		No one should die
./philo   5  600 150 150		No one should die
./philo 100  800 200 200		No one should die
./philo 105  800 200 200		No one should die
./philo 200  800 200 200		No one should die

```
