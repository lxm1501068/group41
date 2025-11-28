#include <bits/stdc++.h>
#include <windows.h>
#include "minesweeper.h"

int main() {
    printf("Welcome to Minesweeper! For easy mode input 1, hard mode input 2: ");
    int q;
    cin >> q;
    if (q == 1) {
        size_map = 10;
        mine_num = 10;
    } else {
        size_map = 16;
        mine_num = 40;
    }
    target_open = size_map * size_map - mine_num;
    init();
    system("cls");
    
    showBestRecord(q);
    print();
    
    bool first_click = true;
    while (true) {
        int xx, yy;
        printf("Input the x and y of the safe blocks (format: x y): ");
        while (!(cin >> xx >> yy) || xx < 0 || xx >= size_map || yy < 0 || yy >= size_map) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printf("Invalid input! Please enter numbers between 0 and %d: ", size_map - 1);
        }
        
        if (is_open[xx][yy]) {
            printf("This block is already opened! Try again.\n");
            continue;
        }
        
        if (first_click) {
            set_mine(xx, yy);
            first_click = false;
            start_time = time(NULL);
        }
        
        if (is_mine[xx][yy]) {
            for (int i = 0; i < mine_x.size(); i++) {
                ch[mine_x[i]][mine_y[i]] = '*';
            }
            ch[xx][yy] = '!';
            system("cls");
            print();
            printf("BOOM! You lose!\n");
            system("pause");
            return 0;
        }
        
        expand(xx, yy);
        system("cls");
        showBestRecord(q);
        print();
        
        if (open_count >= target_open) {
            time_t end_time = time(NULL);
            double total_time = difftime(end_time, start_time);
            
            system("cls");
            print();
            printf("Congratulations! You win!\n");
            printf("Your time: %.2f seconds\n", total_time);
            
            updateBestRecord(q, total_time);
            
            system("pause");
            return 0;
        }
    }
    return 0;
}
