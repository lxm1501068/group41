# group41
team member: Aaron Luo(3036387375)
My game is a classical minesweeper game with two difficulties in c++ form.
In this game, numbers will show the mines' number around it, and you have to deduce which block is safe and enter their coordinates.
1: random events: mines randomly appear in the map except the 3*3 area around the first click.
2: data structure: a map is used to store information such as mine place and mines' number surronding.
3: dynamic function management: a recursive function is used to ensure a block is not expanding twice while expanding safe blocks.
4: file input and output: I use a .txt to storage the fastest record of player.
5: program code in multiple file: I put all the functions in minesweeper.h

run the game by g++ minesweeper_main.cpp minesweeper_func.cpp -o minesweeper
