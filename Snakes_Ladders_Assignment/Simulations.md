Simulation 1 Run 1: Classic Game without heavy traps or anything else.
-> Command that was run: ./a.out --size 100 --sides 6 --steps 1000 --runs 10000 --snakes 98 54 70 55 52 42 25 2 --ladders 3 22 5 8 11 26 20 29

Statistics:
 --->Simulation Stats<---
Board size: 100, Amount of Dice sides: 6
Number of Simulations run: 10000
Number of Wins: 10000 (100.00%)

 --->Dice Stats<---
Average rolls needed to win the game: 48.96
Shortest win in all Simulations that have been run took (16) rolls: 6 5 6 6 5 6 6 4 6 6 1 6 6 6 5 4 

 --->Snakes / Ladders Stats<---
Snakes Used:
  >>> Snake at field 25 used 1942 times
  >>> Snake at field 52 used 4173 times
  >>> Snake at field 70 used 8499 times
  >>> Snake at field 98 used 11177 times
Ladders Used:
  >>> Ladder at field 3 used 2638 times
  >>> Ladder at field 5 used 3021 times
  >>> Ladder at field 11 used 2373 times
  >>> Ladder at field 20 used 2019 times

Simulation 1 Run 2:
 --->Simulation Stats<---
Board size: 100, Amount of Dice sides: 6
Number of Simulations run: 10000
Number of Wins: 10000 (100.00%)

 --->Dice Stats<---
Average rolls needed to win the game: 49.13
Shortest win in all Simulations that have been run took (18) rolls: 3 4 3 6 4 4 6 6 4 6 6 5 3 4 5 2 4 5 

 --->Snakes / Ladders Stats<---
Snakes Used:
  >>> Snake at field 25 used 1960 times
  >>> Snake at field 52 used 4083 times
  >>> Snake at field 70 used 8655 times
  >>> Snake at field 98 used 11201 times
Ladders Used:
  >>> Ladder at field 3 used 2570 times
  >>> Ladder at field 5 used 3015 times
  >>> Ladder at field 11 used 2412 times
  >>> Ladder at field 20 used 1950 times


Simulation 2 Run 1: Board that is very Ladder heavy, with less Snakes
Command: ./a.out --size 100 --sides 6 --steps 500 --runs 10000 --snakes 87 24 93 73 --ladders 2 90 4 50 10 60 22 80 30 70

Statistics:
 --->Simulation Stats<---
Board size: 100, Amount of Dice sides: 6
Number of Simulations run: 10000
Number of Wins: 10000 (100.00%)

 --->Dice Stats<---
Average rolls needed to win the game: 28.45
Shortest win in all Simulations that have been run took (3) rolls: 2 4 5 

 --->Snakes / Ladders Stats<---
Snakes Used:
  >>> Snake at field 87 used 4568 times
  >>> Snake at field 93 used 3410 times
Ladders Used:
  >>> Ladder at field 2 used 1918 times
  >>> Ladder at field 4 used 2275 times
  >>> Ladder at field 10 used 1567 times
  >>> Ladder at field 22 used 1212 times
  >>> Ladder at field 30 used 2521 times


Simulation 2 Run 2: 

Statistics:
 --->Simulation Stats<---
Board size: 100, Amount of Dice sides: 6
Number of Simulations run: 10000
Number of Wins: 10000 (100.00%)

 --->Dice Stats<---
Average rolls needed to win the game: 28.10
Shortest win in all Simulations that have been run took (3) rolls: 2 6 3 

 --->Snakes / Ladders Stats<---
Snakes Used:
  >>> Snake at field 87 used 4511 times
  >>> Snake at field 93 used 3362 times
Ladders Used:
  >>> Ladder at field 2 used 1967 times
  >>> Ladder at field 4 used 2212 times
  >>> Ladder at field 10 used 1576 times
  >>> Ladder at field 22 used 1219 times
  >>> Ladder at field 30 used 2591 times


Simulation 3 Run 1: Snake Heavy Board, hard to get through
Commands: ./a.out --size 100 --sides 6 --steps 2000 --runs 10000 --snakes 98 1 90 2 80 3 70 4 60 5 --ladders 3 10 8 12

Statistics: 
 --->Simulation Stats<---
Board size: 100, Amount of Dice sides: 6
Number of Simulations run: 10000
Number of Wins: 10000 (100.00%)

 --->Dice Stats<---
Average rolls needed to win the game: 175.54
Shortest win in all Simulations that have been run took (20) rolls: 6 5 4 3 6 6 5 2 6 5 6 5 6 3 6 4 6 3 6 6 

 --->Snakes / Ladders Stats<---
Snakes Used:
  >>> Snake at field 60 used 23491 times
  >>> Snake at field 70 used 16637 times
  >>> Snake at field 80 used 11933 times
  >>> Snake at field 90 used 8452 times
  >>> Snake at field 98 used 11262 times
Ladders Used:
  >>> Ladder at field 3 used 5815 times
  >>> Ladder at field 8 used 20317 times

Simulation 3 Run 2:

Statistics:
 --->Simulation Stats<---
Board size: 100, Amount of Dice sides: 6
Number of Simulations run: 10000
Number of Wins: 10000 (100.00%)

 --->Dice Stats<---
Average rolls needed to win the game: 173.54
Shortest win in all Simulations that have been run took (21) rolls: 6 4 6 2 5 6 6 3 6 6 6 2 6 5 4 6 3 2 3 6 6 

 --->Snakes / Ladders Stats<---
Snakes Used:
  >>> Snake at field 60 used 23098 times
  >>> Snake at field 70 used 16472 times
  >>> Snake at field 80 used 11774 times
  >>> Snake at field 90 used 8486 times
  >>> Snake at field 98 used 10994 times
Ladders Used:
  >>> Ladder at field 3 used 5755 times
  >>> Ladder at field 8 used 20049 times

Simulation 4 Run 1: Big Board, even bigger dice, fat rolls and very fast traversal (probably) + unpredictable

Commands: ./a.out --size 1000 --sides 24 --steps 300 --runs 10000 --snakes 998 880 850 610 790 450 510 670 320 460 140 390 90 --ladders 300 15 150 25 375 35 550 45 610 60 720 75 800

Statistics:
 --->Simulation Stats<---
Board size: 1000, Amount of Dice sides: 24
Number of Simulations run: 10000
Number of Wins: 9930 (99.30%)

 --->Dice Stats<---
Average rolls needed to win the game: 127.89
Shortest win in all Simulations that have been run took (45) rolls: 21 17 8 10 24 5 9 12 21 13 7 4 11 19 2 18 5 17 21 16 15 23 7 13 16 20 3 13 24 21 15 12 14 22 13 5 18 21 16 14 2 14 9 12 8 

 --->Snakes / Ladders Stats<---
Snakes Used:
  >>> Snake at field 140 used 1267 times
  >>> Snake at field 320 used 1000 times
  >>> Snake at field 510 used 1172 times
  >>> Snake at field 790 used 940 times
  >>> Snake at field 850 used 893 times
  >>> Snake at field 998 used 10002 times
Ladders Used:
  >>> Ladder at field 150 used 1230 times
  >>> Ladder at field 300 used 1100 times
  >>> Ladder at field 375 used 883 times
  >>> Ladder at field 550 used 1018 times
  >>> Ladder at field 610 used 919 times
  >>> Ladder at field 720 used 1042 times


Simulation 4 Run 2:
 --->Simulation Stats<---
Board size: 1000, Amount of Dice sides: 24
Number of Simulations run: 10000
Number of Wins: 9916 (99.16%)

 --->Dice Stats<---
Average rolls needed to win the game: 128.43
Shortest win in all Simulations that have been run took (43) rolls: 3 7 19 17 13 18 14 13 21 15 12 8 21 19 6 6 21 10 10 7 8 13 15 22 11 19 5 4 8 22 5 10 21 15 18 9 24 24 13 21 14 24 4 

 --->Snakes / Ladders Stats<---
Snakes Used:
  >>> Snake at field 140 used 1274 times
  >>> Snake at field 320 used 1006 times
  >>> Snake at field 510 used 1069 times
  >>> Snake at field 790 used 891 times
  >>> Snake at field 850 used 848 times
  >>> Snake at field 998 used 10172 times
Ladders Used:
  >>> Ladder at field 150 used 1210 times
  >>> Ladder at field 300 used 1116 times
  >>> Ladder at field 375 used 950 times
  >>> Ladder at field 550 used 1012 times
  >>> Ladder at field 610 used 943 times
  >>> Ladder at field 720 used 1060 times

Simulation 5 Run 1: Same Board as above, but with less steps allowed and less runs

Commands: ./a.out --size 1000 --sides 24 --steps 200 --runs 1000 --snakes 998 880 850 610 790 450 510 670 320 460 140 390 90 --ladders 300 15 150 25 375 35 550 45 610 60 720 75 800

Statistics:
 --->Simulation Stats<---
Board size: 1000, Amount of Dice sides: 24
Number of Simulations run: 1000
Number of Wins: 915 (91.50%)

 --->Dice Stats<---
Average rolls needed to win the game: 118.36
Shortest win in all Simulations that have been run took (48) rolls: 4 20 16 16 10 20 8 11 20 15 12 7 17 11 15 21 24 6 12 20 19 21 22 6 6 10 22 18 23 23 19 18 19 10 10 20 22 17 23 17 23 10 23 15 12 13 12 11 

 --->Snakes / Ladders Stats<---
Snakes Used:
  >>> Snake at field 140 used 138 times
  >>> Snake at field 320 used 106 times
  >>> Snake at field 510 used 120 times
  >>> Snake at field 790 used 95 times
  >>> Snake at field 850 used 87 times
  >>> Snake at field 998 used 947 times
Ladders Used:
  >>> Ladder at field 150 used 136 times
  >>> Ladder at field 300 used 93 times
  >>> Ladder at field 375 used 77 times
  >>> Ladder at field 550 used 90 times
  >>> Ladder at field 610 used 79 times
  >>> Ladder at field 720 used 110 times


Simulation 5 Run 2:
 --->Simulation Stats<---
Board size: 1000, Amount of Dice sides: 24
Number of Simulations run: 1000
Number of Wins: 907 (90.70%)

 --->Dice Stats<---
Average rolls needed to win the game: 117.91
Shortest win in all Simulations that have been run took (54) rolls: 21 11 21 17 24 21 15 4 6 6 12 16 1 18 11 15 22 9 16 8 7 17 19 10 22 1 6 22 16 20 12 12 22 24 21 21 20 3 24 1 8 12 17 9 21 19 15 18 4 6 18 10 14 4 

 --->Snakes / Ladders Stats<---
Snakes Used:
  >>> Snake at field 140 used 122 times
  >>> Snake at field 320 used 114 times
  >>> Snake at field 510 used 87 times
  >>> Snake at field 790 used 99 times
  >>> Snake at field 850 used 90 times
  >>> Snake at field 998 used 897 times
Ladders Used:
  >>> Ladder at field 150 used 120 times
  >>> Ladder at field 300 used 111 times
  >>> Ladder at field 375 used 87 times
  >>> Ladder at field 550 used 94 times
  >>> Ladder at field 610 used 91 times
  >>> Ladder at field 720 used 96 times

