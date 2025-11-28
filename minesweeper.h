#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <vector>
#include <string>
using namespace std;

extern char ch[16][16];
extern bool is_mine[16][16];
extern bool is_open[16][16];
extern vector<int> mine_x;
extern vector<int> mine_y;
extern int size_map;
extern int mine_num;
extern int open_count;
extern int target_open;
extern time_t start_time;
extern const string RECORD_FILE;

void init();
void set_mine(int inx, int iny);
int count_mine(int x, int y);
void expand(int x, int y);
void print();
double readBestRecord(int mode);
void updateBestRecord(int mode, double new_time);
void showBestRecord(int mode);

#endif
