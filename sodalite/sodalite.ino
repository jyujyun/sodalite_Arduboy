#include <Arduboy2.h>

Arduboy2 arduboy;

// ============================================================================

#include "dango.h"
char snum = 19;
void setup() {

  arduboy.begin();
  arduboy.clear();

  arduboy.initRandomSeed();

  //フレームレートを固定
  arduboy.setFrameRate(30);
}
char mode = 2;
int x = 64;
int y = 32;
char muki = 0;
char hp = 4;
char muteki = 0;


int t1x = 32;
int t1y = 32;
char t1h = 1;

int pli = m1;       //自分の画像
int plm = m1_mask;  //マスク

char count = 0;

char alock = 0;

char i = 0;

int balls[3][4];

char block_map[12][8];

void loop() {
  if (!arduboy.nextFrame()) return;
  arduboy.clear();

  if (mode == 0)
  {

    draw_map();
    if (muteki > 0)
    {
      muteki -= 1;
    }
    if (arduboy.pressed(LEFT_BUTTON) == 1 && x > 0) {
      pli = m5;
      plm = m5_mask;
      muki = 0;
      if (x % 8 == 0 && (block_map[(x / 8) - 1][y / 8] > snum || (y % 8 != 0 && block_map[(x / 8) - 1][(y / 8) + 1] > snum))) {

      } else {
        x -= 1;
      }
    }
    //プレイヤー処理
    if (arduboy.pressed(UP_BUTTON) == 1 && y > 0) {
      pli = m3;
      plm = m1_mask;
      muki = 1;
      if (y % 8 == 0 && (block_map[x / 8][(y / 8) - 1] > snum || (x % 8 != 0 && block_map[(x / 8) + 1][(y / 8) - 1] > snum))) {

      } else {
        y -= 1;
      }
    }
    if (arduboy.pressed(RIGHT_BUTTON) == 1 && x < 88) {
      pli = m7;
      plm = m7_mask;
      muki = 2;
      if (x % 8 == 0 && (block_map[(x / 8) + 1][y / 8] > snum || (y % 8 != 0 && block_map[(x / 8) + 1][(y / 8) + 1] > snum))) {

      } else {
        x += 1;
      }
    }
    if (arduboy.pressed(DOWN_BUTTON) == 1 && y < 56) {
      pli = m1;
      plm = m1_mask;
      muki = 3;
      if (y % 8 == 0 && (block_map[x / 8][y / 8 + 1] > snum || (x % 8 != 0 && block_map[(x / 8) + 1][(y / 8) + 1] > snum))) {

      } else {
        y += 1;
      }
    }
    //敵処理
    count += 1;
    if (count == 2) {
      count = 0;
      if (t1h == 1) {
        if (x < t1x && t1x > 0) {

          if (t1x % 8 == 0 && (block_map[(t1x / 8) - 1][t1y / 8] > snum || (t1y % 8 != 0 && block_map[(t1x / 8) - 1][(t1y / 8) + 1] > snum))) {

          } else {
            t1x -= 1;
          }
        }
        if (y < t1y && t1y > 0) {

          if (t1y % 8 == 0 && (block_map[t1x / 8][(t1y / 8) - 1] > snum || (t1x % 8 != 0 && block_map[(t1x / 8) + 1][(t1y / 8) - 1] > snum))) {

          } else {
            t1y -= 1;
          }
        }
        if (x > t1x && t1x < 88) {
          if (t1x % 8 == 0 && (block_map[(t1x / 8) + 1][t1y / 8] > snum || (t1y % 8 != 0 && block_map[(t1x / 8) + 1][(t1y / 8) + 1] > snum))) {

          } else {
            t1x += 1;
          }
        }
        if (y > t1y && t1y < 56) {
          if (t1y % 8 == 0 && (block_map[t1x / 8][t1y / 8 + 1] > snum || (t1x % 8 != 0 && block_map[(t1x / 8) + 1][(t1y / 8) + 1] > snum))) {

          } else {
            t1y += 1;
          }
        }
        if (x + 8 >= t1x && x <= t1x + 8 && y + 8 >= t1y && y <= t1y + 8 && muteki == 0)
        {
            hp -= 1;
            if (hp == 0)
            {
              mode = 1;
            }
            else
            {
              muteki = 60;
            }

        }
      }
    }

    if (arduboy.pressed(A_BUTTON) == 1 && alock == 0) {
      alock = 1;
      if (balls[0][3] == 0) {
        balls[0][0] = x;
        balls[0][1] = y;
        balls[0][2] = muki;
        balls[0][3] = 1;
      } else if (balls[1][3] == 0) {
        balls[1][0] = x;
        balls[1][1] = y;
        balls[1][2] = muki;
        balls[1][3] = 1;
      } else if (balls[2][3] == 0) {
        balls[2][0] = x;
        balls[2][1] = y;
        balls[2][2] = muki;
        balls[2][3] = 1;
      }
    }
    if (arduboy.pressed(A_BUTTON) == 0) {
      alock = 0;
    }
    for (i = 0; i < 3; i++) {

      if (balls[i][3] == 1) {
        if (balls[i][2] == 0) {
          balls[i][0] -= 1;
        } else if (balls[i][2] == 1) {
          balls[i][1] -= 1;
        } else if (balls[i][2] == 2) {
          balls[i][0] += 1;
        } else if (balls[i][2] == 3) {
          balls[i][1] += 1;
        }
        if (balls[i][0] < 0 || balls[i][1] < 0 || balls[i][0] > 92 || balls[i][1] > 60 || block_map[balls[i][0] / 8][balls[i][1] / 8] > snum) {
          balls[i][3] = 2;
        }
        if (balls[i][0] >= t1x && balls[i][0] <= t1x + 8 && balls[i][1] >= t1y && balls[i][1] <= t1y + 8 && t1h == 1)
        {
          balls[i][3] = 2;
          t1h = 0;
        }

        Sprites::drawExternalMask(balls[i][0], balls[i][1], ball, ball_mask, 0, 0);
      } else if (balls[i][3] < 10 && balls[i][3] > 1) {
        balls[i][3] += 1;
        if (balls[i][3] == 10) {
          balls[i][3] = 0;
        }
        arduboy.drawBitmap(balls[i][0], balls[i][1], ball_pow, 8, 8, WHITE);
      }
    }
    if (block_map[(x + 4) / 8][(y + 4) / 8] == 1)
    {
      init_set();
    }
    Sprites::drawExternalMask(x, y, pli, plm, 0, 0);
    if (t1h > 0)
    {
      Sprites::drawExternalMask(t1x, t1y, teki, teki_mask, 0, 0);
    }
  }
  else if(mode == 1)
  {
      arduboy.setCursor(40, 16);
      arduboy.print(F("GAME OVER"));
      draw_map();
      Sprites::drawExternalMask(x, y, pli, plm, 0, 0);
      if (t1h > 0)
      {
        Sprites::drawExternalMask(t1x, t1y, teki, teki_mask, 0, 0);
      }
      if (arduboy.pressed(A_BUTTON) == 1 && alock == 0) {
        alock = 1;
        mode = 2;
      }
      if (arduboy.pressed(A_BUTTON) == 0)
      {
        alock = 0;
      }
  }
  else if (mode == 2)
  {

      arduboy.drawBitmap(0, 0, sodalite, 128, 64, WHITE);
      arduboy.setCursor(56, 32);
      arduboy.print(F("PRESS A"));
      if (arduboy.pressed(A_BUTTON) == 1 && alock == 0) {
        alock = 1;
        mode = 0;
        init_num();
      }
      if (arduboy.pressed(A_BUTTON) == 0)
      {
        alock = 0;
      }
  }
  arduboy.display();
}
void init_num(void)
{
  init_set();
  x = 64;
  y = 32;
  muki = 0;
  hp = 4;
  muteki = 0;


  t1x = 32;
  t1y = 32;
  t1h = 1;

  count = 0;

}
void init_set(void) {
  char i, j;
  char rani = 0;
  char ranb = 0;
  for (i = 0; i <= 11; i++) {
    for (j = 0; j <= 7; j++) {
      if (random(10) == 0) {
        block_map[i][j] = 20;
      } else if (random(5) == 0) {
        block_map[i][j] = 19;
      } else if (random(20) == 0) {
        rani = random(4);
        if (rani == 0) {
          rani = 5;
        } else if (rani == 1) {
          rani = 7;
        } else if (rani == 2) {
          rani = 8;
        }
        block_map[i][j] = rani;
      } else {
        block_map[i][j] = 0;
      }
    }
  }
  block_map[random(12)][random(8)] = 1;
}
void draw_map(void) {
  char i, j;
  for (i = 0; i <= 11; i++) {
    for (j = 0; j <= 7; j++) {
      if (block_map[i][j] == 20) {
        arduboy.drawBitmap(i * 8, j * 8, block, 8, 8, WHITE);
      } else if (block_map[i][j] == 19) {
        arduboy.drawBitmap(i * 8, j * 8, flower, 8, 8, WHITE);
      } else if (block_map[i][j] == 5) {
        arduboy.drawBitmap(i * 8, j * 8, f_wand, 8, 8, WHITE);
      } else if (block_map[i][j] == 7) {
        arduboy.drawBitmap(i * 8, j * 8, h_potion, 8, 8, WHITE);
      } else if (block_map[i][j] == 8) {
        arduboy.drawBitmap(i * 8, j * 8, w_potion, 8, 8, WHITE);
      } else if (block_map[i][j] == 1) {
        arduboy.drawBitmap(i * 8, j * 8, kaidan, 8, 8, WHITE);
      }
    }
  }
  if (hp > 0)
  {
    for (i = 0;i < hp; i++)
    {
      arduboy.drawBitmap((i * 8) + 96, 0, heart, 8, 8, WHITE);
    }
  }
}
