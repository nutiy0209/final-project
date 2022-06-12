//---------------------------------------------------------------------------

#include <vcl.h>

#include <math.h>

#pragma hdrstop#include <time.h>

#include <jpeg.hpp>


#include "Unit1.h"
 //---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 * Form1;
bullet * make[100];
air * plane1;
super * plane2;
brick * strip[16][8];
int p = 0;
int count = 0;
int everyCoin = 0, countCoin = 0, totalCoin = 0;
int coor_x = 0, coor_y = 0;
int speed = 50, power = 1;
int sec = 0, change = 0;;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent * Owner): TForm(Owner) {
  srand(time(NULL));
  plane1 = new air(Panel1, speed);
  for (int x = 0; x < 16; x++) { //  製造磚塊
    for (int y = 0; y < 8; y++) {
      strip[x][y] = new brick(Panel1, x * 45, y * 45, rand() % 10);
    }
  }
  music -> Open();
  music -> Play();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject * Sender) {
  count = 0;
  if (plane1 != NULL) {
    coor_x = plane1 -> getLeft() + 27;
    coor_y = plane1 -> getTop();
  } else {
    coor_x = plane2 -> getLeft() + 50;
    coor_y = plane2 -> getTop();
  }
  everyCoin = 0;
  if (plane1 != NULL) {
    make[p] = new bullet(Panel1, 8, 10, 15, 25, power, coor_x, coor_y);
  } else {
    make[p] = new bullet(Panel1, 8, 10, 15, 25, power, plane2 -> getLeft() - 15, coor_y);
    make[p + 1] = new bullet(Panel1, 8, 10, 15, 25, power, coor_x, coor_y);
    make[p + 2] = new bullet(Panel1, 8, 10, 15, 25, power, plane2 -> getLeft() + 120, coor_y);
  }
  for (int m = 0; m < 16; m++) {
    for (int n = 0; n < 8; n++) {
      if (strip[m][n] != NULL) {
        strip[m][n] -> square -> Top = strip[m][n] -> square -> Top + 4;
        everyCoin += strip[m][n] -> allCoin;
      }
    }
  }
  Label2 -> Caption = "金幣\n:" + String(totalCoin + everyCoin + countCoin);
  p += 3;
  for (int x = 0; x < 16; x++) {
    for (int y = 0; y < 8; y++) {
      if (strip[x][y] != NULL && strip[x][y] -> hpBrick <= 0) {
        count++;
      }
    }
  }
  if (count == 128) {
    Timer1 -> Enabled = false;
    ShowMessage("通關勝利");
  }
}
void __fastcall TForm1::Timer3Timer(TObject * Sender) {
  if (p > 40) {
    for (int i = 0; i < 100; i++) {
      if (make[i] != NULL) {
        make[i] -> ~bullet();
        make[i] = NULL;
      }
    }
    p = 0;
  }
}
void __fastcall TForm1::Timer5Timer(TObject * Sender) {
  if (count == 128 && (sec % 10) == 0) {
    music -> Close();
    music -> Open();
    music -> FileName = "victory.mp3";
    music -> Play();
  }
  sec++;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::powerUpClick(TObject * Sender) {
  if (totalCoin + everyCoin + countCoin > 10) {
    power += 2;
    countCoin -= 10;
  }
  if (power > 10) {
    powerUp -> Caption = "MAX";
    powerUp -> Enabled = false;
  }
}

void __fastcall TForm1::shootUpClick(TObject * Sender) {
  if (totalCoin + everyCoin + countCoin > 10) {
    Timer1 -> Interval -= 20;
    countCoin -= 10;
  }
  if (Timer1 -> Interval < 300) {
    shootUp -> Caption = "MAX";
    shootUp -> Enabled = false;
  }
}

void __fastcall TForm1::speedUpClick(TObject * Sender) {
  if (totalCoin + everyCoin + countCoin > 10) {
    speed -= 5;
    countCoin -= 10;
  }
  if (speed < 25) {
    speedUp -> Caption = "MAX";
    speedUp -> Enabled = false;
  }
}

void __fastcall TForm1::levelUpClick(TObject * Sender) {
  if (totalCoin + everyCoin + countCoin > 1000) {
    plane1 -> ~air();
    plane1 = NULL;
    plane2 = new super(Panel1, speed);
    countCoin -= 1000;
    levelUp -> Enabled = false;
  }
}

void __fastcall TForm1::replayClick(TObject * Sender) {
  for (int i = 0; i < 100; i++) {
    if (make[i] != NULL) {
      make[i] -> ~bullet();
      make[i] = NULL;
    }
  }
  p = 0;
  totalCoin += everyCoin;
  for (int m = 0; m < 16; m++) {
    for (int n = 0; n < 8; n++) {
      if (strip[m][n] != NULL) {
        delete strip[m][n];
      }
    }
  }
  for (int x = 0; x < 16; x++) { //  製造磚塊
    for (int y = 0; y < 8; y++) {
      strip[x][y] = new brick(Panel1, x * 45, y * 45, rand() % 10);
    }
  }
  Timer1 -> Enabled = true;
  music -> Close();
  music -> Open();
  music -> FileName = "first.mp3";
  music -> Play();
}

void __fastcall TForm1::moneyClick(TObject * Sender) {
  countCoin += 1000;
}

void __fastcall TForm1::hardClick(TObject * Sender) {
  if ((change % 2) == 0) {
    Panel1 -> Color = clBlack;
    hard -> Caption = "普通模式";
  } else {
    Panel1 -> Color = clWhite;
    hard -> Caption = "地獄模式";
  }
  change++;
}

//---------------------------------------------------------------------------
bullet::~bullet() {
  times -> ~TTimer();
  circle -> ~TShape();
}

bullet::bullet(TPanel * panel, int x, int y, int speed, int size, int power, int coor_x, int coor_y) {
  circle = new TShape(panel); //  括號裡放要生成的容器
  circle -> Parent = panel; //  生成可視物件
  this -> x = x;
  this -> y = y;
  this -> power = power;
  circle -> Left = coor_x;
  circle -> Top = coor_y;
  circle -> Width = size;
  circle -> Height = size;
  circle -> Shape = stCircle; //  調形狀
  circle -> Brush -> Color = (TColor) random(0xffffff);
  times = new TTimer(panel);
  times -> Interval = 15; //  每秒速度
  times -> Enabled = true;
  times -> OnTimer = timer; //  事件函式名稱
  pHeight = panel -> Height;
  pWidth = panel -> Width;
  mark = 0;
}
void __fastcall bullet::timer(TObject * Sender) {

  /*========移動========*/
  circle -> Top = circle -> Top - y;

  /*========磚塊碰撞========*/

  for (int m = 0; m < 16; m++) {
    for (int n = 0; n < 8; n++) {
      if (strip[m][n] != NULL && strip[m][n] -> hpBrick > 0) {
        if (circle -> Top < strip[m][n] -> square -> Top + strip[m][n] -> square -> Height &&
          circle -> Left + circle -> Width >= strip[m][n] -> square -> Left &&
          circle -> Left <= (strip[m][n] -> square -> Left + strip[m][n] -> square -> Width)) { //  磚塊下方
          strip[m][n] -> hpBrick = strip[m][n] -> hpBrick - power;
          circle -> Left += 1000;
          y = 0;
        }
      }
    }
  }
}
bullet::getLeft() {
  return circle -> Left;
}
bullet::getTop() {
  return circle -> Top;
}
//---------------------------------------------------------------------------
type::type(TPanel * panel) {
  rectangle = new TImage(panel);
  rectangle -> Parent = panel;
  rectangle -> Left = 360;
  rectangle -> Top = 600;
  rectangle -> Height = 75;
  rectangle -> Width = 75;
  rectangle -> Picture -> LoadFromFile("./block1.bmp");
  rectangle -> Stretch = true;
  rectangle -> Transparent = true;
  time = new TTimer(panel);
  time -> Interval = 50;
  time -> Enabled = true;
  time -> OnTimer = timed;
  pWidth1 = panel -> Width;
  pHeight1 = panel -> Height;
  hpAir = 180;
}
type::~type() {
  time -> ~TTimer();
  rectangle -> ~TImage();
}
type::getLeft() {
  return rectangle -> Left;
}
type::getTop() {
  return rectangle -> Top;
}
void __fastcall type::timed(TObject * Sender) {
  if (rectangle -> Left >= 0) { //  方向鍵移動
    if (GetAsyncKeyState(37) & 0x8000) {
      rectangle -> Left = rectangle -> Left - 8;
    }
  }
  if (rectangle -> Left + rectangle -> Width <= pWidth1) {
    if (GetAsyncKeyState(39) & 0x8000) {
      rectangle -> Left = rectangle -> Left + 8;
    }
  }
  if (rectangle -> Top >= 0) {
    if (GetAsyncKeyState(38) & 0x8000) {
      rectangle -> Top = rectangle -> Top - 8;
    }
  }
  if (rectangle -> Top + rectangle -> Height <= pHeight1) {
    if (GetAsyncKeyState(40) & 0x8000) {
      rectangle -> Top = rectangle -> Top + 8;
    }
  }
}
air::air(TPanel * panel, int speed): type(panel) {
  time -> Interval = speed;
}

super::super(TPanel * panel, int speed): type(panel) {
  rectangle -> Picture -> LoadFromFile("./block2.bmp");
  time -> Interval = speed;
  rectangle -> Width = 120;
  rectangle -> Height = 120;
}
//---------------------------------------------------------------------------
brick::brick(TPanel * panel, int x_, int y_, int color) {
  allCoin = 0;
  square = new TShape(panel);
  square -> Parent = panel;
  square -> Left = x_;
  square -> Top = y_;
  square -> Width = 45;
  square -> Height = 45;
  if (color == 1) { //金磚
    square -> Brush -> Color = TColor(255215);
    hpBrick = 8;
    coin = 10;
  } else if (color == 2 || color == 3) { //銀磚
    square -> Brush -> Color = clSilver;
    hpBrick = 5;
    coin = 8;
  } else if (color == 4 || color == 5 || color == 6) { //陷阱
    square -> Brush -> Color = clBlack;
    hpBrick = 3;
    coin = -30;
  } else { //木磚
    square -> Brush -> Color = clMaroon;
    hpBrick = 1;
    coin = 1;
  }
  timing = new TTimer(panel);
  timing -> Interval = 30;
  timing -> Enabled = true;
  timing -> OnTimer = timez;
}

void __fastcall brick::timez(TObject * Sender) {
  if (hpBrick <= 0 && square -> Top < 800) { //  金幣
    square -> Width = 25;
    square -> Shape = stEllipse;
    square -> Top += 8;
  }
  if (plane1 != NULL && hpBrick <= 0) {
    if (square -> Top + square -> Height >= plane1 -> rectangle -> Top &&
      square -> Top + square -> Height <= plane1 -> rectangle -> Top + plane1 -> rectangle -> Height &&
      square -> Left + square -> Width >= plane1 -> rectangle -> Left &&
      square -> Left <= (plane1 -> rectangle -> Left + plane1 -> rectangle -> Width)) {
      square -> Top += 720;
      allCoin = coin;
    }
  }
  if (plane2 != NULL && hpBrick <= 0) {
    if (square -> Top + square -> Height >= plane2 -> rectangle -> Top &&
      square -> Top + square -> Height <= plane2 -> rectangle -> Top + plane2 -> rectangle -> Height &&
      square -> Left + square -> Width >= plane2 -> rectangle -> Left &&
      square -> Left <= (plane2 -> rectangle -> Left + plane2 -> rectangle -> Width)) {
      square -> Top += 720;
      allCoin = coin;
    }
  }
}
brick::~brick() {
  timing -> ~TTimer();
  square -> ~TShape();
}

//---------------------------------------------------------------------------
