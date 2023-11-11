#ifndef SCORE_H_
#define SCORE_H_

void score_init();
void score_update();    // Poll this often to look for goals
int score_new_goal();   // Returns goals since last time this was run

#endif