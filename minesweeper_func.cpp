#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include "minesweeper.h"

// Global variables definition
char ch[16][16];
bool is_mine[16][16];
bool is_open[16][16];
vector<int> mine_x;
vector<int> mine_y;
int size_map;
int mine_num;
int open_count = 0;
int target_open;
time_t start_time;
const string RECORD_FILE = "minesweeper_records.txt";

// Initialize game grid and reset states
void init() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            ch[i][j] = '#';
            is_mine[i][j] = false;
            is_open[i][j] = false;
        }
    }
    mine_x.clear();
    mine_y.clear();
    open_count = 0;
}

// Generate mines randomly (avoid first click area)
void set_mine(int inx, int iny) {
    srand((unsigned)time(NULL));
    int count = 0;
    while (count < mine_num) {
        int x = rand() % size_map;
        int y = rand() % size_map;
        if ((abs(x - inx) <= 1 && abs(y - iny) <= 1) || is_mine[x][y]) {
            continue;
        }
        is_mine[x][y] = true;
        mine_x.push_back(x);
        mine_y.push_back(y);
        count++;
    }
}

// Count mines in 8 surrounding cells
int count_mine(int x, int y) {
    int cnt = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < size_map && ny >= 0 && ny < size_map) {
                if (is_mine[nx][ny]) cnt++;
            }
        }
    }
    return cnt;
}

// Recursively expand empty cells (0 surrounding mines)
void expand(int x, int y) {
    if (x < 0 || x >= size_map || y < 0 || y >= size_map || is_open[x][y] || is_mine[x][y]) {
        return;
    }
    is_open[x][y] = true;
    open_count++;
    int cnt = count_mine(x, y);
    if (cnt > 0) {
        ch[x][y] = '0' + cnt;
        return;
    }
    ch[x][y] = ' ';
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            expand(x + dx, y + dy);
        }
    }
}

// Print game grid with coordinates
void print() {
    cout << "   ";
    for (int j = 0; j < size_map; j++) {
        printf("%2d", j);
    }
    cout << endl;
    for (int i = 0; i < size_map; i++) {
        printf("%2d ", i);
        for (int j = 0; j < size_map; j++) {
            printf("%2c", ch[i][j]);
        }
        cout << endl;
    }
}

// Read best time from record file (mode:1=easy,2=hard)
double readBestRecord(int mode) {
    ifstream file(RECORD_FILE);
    double best_time = -1.0;
    string line;
    int file_mode;
    double file_time;
    
    if (!file.is_open()) {
        ofstream new_file(RECORD_FILE);
        new_file << "1 -1.0\n2 -1.0\n";
        new_file.close();
        return -1.0;
    }
    
    while (getline(file, line)) {
        stringstream ss(line);
        if (ss >> file_mode >> file_time) {
            if (file_mode == mode) {
                best_time = file_time;
                break;
            }
        }
    }
    file.close();
    return best_time;
}

// Update record if new time is faster
void updateBestRecord(int mode, double new_time) {
    double current_best = readBestRecord(mode);
    if (current_best < 0 || new_time < current_best) {
        ifstream infile(RECORD_FILE);
        ofstream outfile("temp.txt");
        string line;
        int file_mode;
        double file_time;
        
        while (getline(infile, line)) {
            stringstream ss(line);
            if (ss >> file_mode >> file_time) {
                if (file_mode == mode) {
                    outfile << mode << " " << fixed << setprecision(2) << new_time << endl;
                } else {
                    outfile << line << endl;
                }
            }
        }
        infile.close();
        outfile.close();
        
        remove(RECORD_FILE.c_str());
        rename("temp.txt", RECORD_FILE.c_str());
        
        cout << "New best record! " << fixed << setprecision(2) << new_time << " seconds\n";
    } else {
        cout << "Current best record: " << fixed << setprecision(2) << current_best << " seconds\n";
    }
}

// Show best record for selected mode
void showBestRecord(int mode) {
    double best_time = readBestRecord(mode);
    cout << "\n=== Best Record ===" << endl;
    if (mode == 1) {
        cout << "Easy Mode (10x10, 10 mines): ";
    } else {
        cout << "Hard Mode (16x16, 40 mines): ";
    }
    if (best_time < 0) {
        cout << "No record yet" << endl;
    } else {
        cout << fixed << setprecision(2) << best_time << " seconds" << endl;
    }
    cout << "===================\n" << endl;
}
