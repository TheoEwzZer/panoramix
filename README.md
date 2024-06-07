# PANORAMIX

## Context

The year is 50 BC. Gaul is entirely occupied by the Romans. Well, not entirely. . . One small village of indomitable Gauls still holds out against the invaders. And life is not easy for the Roman legionaries who garrison the fortified camps of Totorum, Aquarium, Laudanum and Compendium...

In this village the druid prepares a cooking pot of magic potions. The villagers get a serving of potion and then procede to beat roman soldiers. When the pot is empty, the villager wakes up the druid and waits until the druid has refilled the pot.

## Project

The purpose of this project is to study examples of threads and mutex programming and the algorithmic difficulties that go with it.

To do that, you must create a program that simulate the described behavior.

```
B-CCP-400> ./panoramix
USAGE: ./panoramix <nb_villagers> <pot_size> <nb_fights> <nb_refills>
```

```
✓ nb_villagers: indicates the number of villagers (must be >0);
✓ pot_size: indicates the maximum number that can be contained in the cooking pot (must
be >0);
✓ nb_fights: indicates the maximum number of fights a villager will engage in (must be >0);
✓ nb_refills: incicates the maximum number of time the druid will refill the pot (must be >0).
```

The program must follow these rules:

```
✓ You MUST make use of semaphores;
✓ You MUST make use of mutexes;
✓ Each villager (and the druid) MUST run in its own thread;
✓ The cooking pot is full at the start of the program:
✓ A villager’s thread must stop when all the fights have been done (and hopefully won);
✓ The druid’s thread must stop when he has no ingredients left (aka:nb_refills) to refill the pot;
✓ The program must stop gracefully when all the villager’s threads have stopped.
```

## Final Mark

### Mark: 15 / 20 (75.0%)

-   Preliminaries (2 / 2)
-   Error handling (2 / 2)
-   Usage of mutex (3 / 3)
-   Usage of semaphore (3 / 3)
-   Dead lock (-5 / 0)
-   Working as intended (10 / 10)
