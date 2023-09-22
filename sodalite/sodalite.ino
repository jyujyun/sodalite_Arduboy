#include<Arduboy2.h>

Arduboy2 arduboy;

// ============================================================================

#include "dango.h"

void setup() {

  arduboy.begin();
  arduboy.clear();

  arduboy.initRandomSeed();
    init_set();
  //フレームレートを固定
  arduboy.setFrameRate(30);
}
int x = 64;
int y = 32;

int pli = m1; //自分の画像
int plm = m1_mask; //マスク


char block_map[12][8];

void loop() {
      if (!arduboy.nextFrame()) return;
    arduboy.clear();
    draw_map();
    arduboy.setCursor(96, 0);
    arduboy.print(x % 8);
    arduboy.print(x / 8);
    arduboy.setCursor(96, 8);
    arduboy.print(y % 8);
    arduboy.print(y / 8);
    if (arduboy.pressed(LEFT_BUTTON) == 1 && x > 0)
    {
        pli = m5;
        plm = m5_mask;
        if (x % 8 == 0 && (block_map[(x / 8) - 1][y / 8] > 19 || ( y % 8 != 0 &&  block_map[(x / 8) - 1][(y / 8) + 1] > 19)))
        {

        }
        else
        {
          x -= 1;      
        }


    }
    if (arduboy.pressed(UP_BUTTON) == 1 && y > 0)
    {
        pli = m3;
        plm = m1_mask;
        if (y % 8 == 0 && (block_map[x / 8][(y / 8) - 1] > 19 || ( x % 8 != 0 &&  block_map[(x / 8) + 1][(y / 8) - 1] > 19)))
        {

        }
        else
        {
          y -= 1;      
        }   
    }
    if (arduboy.pressed(RIGHT_BUTTON) == 1 && x < 88)
    {
        pli = m7;
        plm = m7_mask;
        if (x % 8 == 0 && (block_map[(x / 8) + 1][y / 8] > 19 || ( y % 8 != 0 &&  block_map[(x / 8) + 1][(y / 8) + 1] > 19)))
        {

        }
        else
        {
          x += 1;      
        }   
    }
    if (arduboy.pressed(DOWN_BUTTON) == 1 && y < 56)
    {
        pli = m1;
        plm = m1_mask;
        if (y % 8 == 0 && (block_map[x / 8][y / 8 + 1] > 19 || ( x % 8 != 0 &&  block_map[(x / 8) + 1][(y / 8) + 1] > 19)))
        {

        }
        else
        {
          y += 1;      
        }   
    }
    Sprites::drawExternalMask(x, y, pli, plm, 0, 0);
    arduboy.display();
}
void init_set(void)
{
  char i,j;
  for (i=0;i<=11;i++)
  {
    for (j=0;j<=7;j++)
    {
      if (random(10) == 0)
      {
        block_map[i][j] = 20;
      }
      else if (random(5) == 0)
      {
        block_map[i][j] = 19;
      }
      else
      {
        block_map[i][j] = 0;
      }
      

    }
  }

}
void draw_map(void)
{
  char i,j;
  for (i=0;i<=11;i++)
  {
    for (j=0;j<=7;j++)
    {
      if (block_map[i][j] == 20)
      {
        arduboy.drawBitmap(i*8,j*8,block,8,8,WHITE);
      }
      else if(block_map[i][j] == 19)
      {
        arduboy.drawBitmap(i*8,j*8,flower,8,8,WHITE);
      }
    }
  }

}
