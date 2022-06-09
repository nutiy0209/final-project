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
ball * make[100];
air * block;
super * block2;
brick * strip[16][8];
int p = 0;
int power = 1;
int count=0;
int everyCoin = 0, countCoin = 0, totalCoin = 0;
int coor_x = 0, coor_y = 0;
int sec=0;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent * Owner): TForm(Owner) {
  srand(time(NULL));
  block = new air(Panel1);
  for (int x = 0; x < 16; x++) { //  製造磚塊
    for (int y = 0; y < 8; y++) {
      strip[x][y] = new brick(Panel1, x * 45, y * 45, rand() % 10);
    }
  }
  music->Open();
  music->Play();
}

ball::~ball() {
  times -> ~TTimer();
  circle -> ~TShape();
}

ball::ball(TPanel * panel, int x, int y, int speed, int size, int power, int coor_x, int coor_y) {
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

void __fastcall ball::timer(TObject * Sender) {

  /*========移動========*/
  circle -> Top = circle -> Top - y;

  /*========磚塊碰撞========*/

  for (int m = 0; m < 16; m++) {
    for (int n = 0; n < 8; n++) {
      if (strip[m][n]!=NULL && strip[m][n] -> hpBrick > 0) {
        if (circle -> Top < strip[m][n] -> square -> Top + strip[m][n] -> square -> Height &&
          circle -> Left + circle -> Width >= strip[m][n] -> square -> Left &&
          circle -> Left <= (strip[m][n] -> square -> Left + strip[m][n] -> square -> Width)) { //  磚塊下方
          strip[m][n] -> hpBrick = strip[m][n] -> hpBrick - power;
          circle -> Left += 1000;
          y=0;
        }
      }
    }
  }
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
air::air(TPanel * panel): type(panel) {}

super::super(TPanel * panel): type(panel) {
  rectangle -> Picture -> LoadFromFile("./block2.bmp");
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
brick::brick(TPanel * panel, int x_, int y_, int color) {
  allCoin = 0;
  square = new TShape(panel);
  square -> Parent = panel;
  square -> Left = x_;
  square -> Top = y_;
  square -> Width = 45;
  square -> Height = 45;
  if (color == 1) {   //金磚
    square -> Brush -> Color = TColor(255215);  
    hpBrick = 8;
    coin = 10;
  } else if (color == 2 || color == 3) {   //銀磚
    square -> Brush -> Color = clSilver;  
    hpBrick = 5;
    coin = 8;
  } else if (color == 4 || color == 5 || color == 6) {  //陷阱
    square -> Brush -> Color = clBlack;   
    hpBrick = 3;
    coin = -50;
  } else {  //木磚
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
  if (hpBrick <= 0  && square->Top < 800 ) {
    square -> Width = 25;
    square -> Shape = stEllipse;
    square -> Top += 8;
  }
  if (block != NULL && hpBrick <= 0) {
    if (square -> Top + square -> Height >= block -> rectangle -> Top &&
      square -> Top + square -> Height <= block -> rectangle -> Top + block -> rectangle -> Height &&
      square -> Left + square -> Width >= block -> rectangle -> Left &&
      square -> Left <= (block -> rectangle -> Left + block -> rectangle -> Width)) {
      square -> Top += 720;
      allCoin = coin;
    }
  }
  if (block2 != NULL && hpBrick <= 0) {
    if (square -> Top + square -> Height >= block2 -> rectangle -> Top &&
      square -> Top + square -> Height <= block2 -> rectangle -> Top + block2 -> rectangle -> Height &&
      square -> Left + square -> Width >= block2 -> rectangle -> Left &&
      square -> Left <= (block2 -> rectangle -> Left + block2 -> rectangle -> Width)) {
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

void __fastcall TForm1::Timer1Timer(TObject * Sender) {
  if (block != NULL) {
    coor_x = block -> getLeft() + 27;
    coor_y = block -> getTop();
  } else {
    coor_x = block2 -> getLeft() + 27;
    coor_y = block2 -> getTop();
  }
  everyCoin = 0;
  if (block != NULL) {
    make[p] = new ball(Panel1, 8, 10, 15, 25, power, coor_x, coor_y);
  } else {
    make[p] = new ball(Panel1, 8, 10, 15, 25, power, block2 -> getLeft()-22, coor_y);
    make[p + 1] = new ball(Panel1, 8, 10, 15, 25, power, coor_x, coor_y);
    make[p + 2] = new ball(Panel1, 8, 10, 15, 25, power, block2 -> getLeft() + 75, coor_y);
  }
  for (int m = 0; m < 16; m++) {
    for (int n = 0; n < 8; n++) {
      if(strip[m][n] != NULL){
        strip[m][n] -> square -> Top = strip[m][n] -> square -> Top + 4;
        everyCoin += strip[m][n] -> allCoin;
      }
    }
  }
  Label2 -> Caption = "金幣" + String(totalCoin + everyCoin + countCoin);
  p += 3;
}


ball::getLeft() {
  return circle -> Left;
}
ball::getTop() {
  return circle -> Top;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject * Sender) {
  if(totalCoin + everyCoin + countCoin > 10){
    power += 2;
    countCoin -= 10;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject * Sender) {
  if(totalCoin + everyCoin + countCoin > 10){
    Timer1 -> Interval -= 20;
    countCoin -= 10;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject * Sender) {
  if(totalCoin + everyCoin + countCoin > 10){
    if (block != NULL) {
      block -> time -> Interval -= 1;
    } else {
      block2 -> time -> Interval -= 1;
    }
    countCoin -= 10;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject * Sender) {
  block -> ~air();
  block = NULL;
  block2 = new super(Panel1);
  Button5 -> Enabled = false;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------23
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
  for (int i = 0; i < 100; i++) {
    if (make[i] != NULL) {
      make[i] -> ~ball();
      make[i] = NULL;
    }
  }
  p = 0;
  totalCoin+=everyCoin;
  for (int m = 0; m < 16; m++) {
    for (int n = 0; n < 8; n++) {
      if(strip[m][n] != NULL){
        delete strip[m][n];
      }
    }
  }
  for (int x = 0; x < 16; x++) {  //  製造磚塊
    for (int y = 0; y < 8; y++) {
      strip[x][y] = new brick(Panel1, x * 45, y * 45, rand() % 10);
    }
  }
  Timer4->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer3Timer(TObject *Sender)
{
  if(p > 60){
    for (int i = 0; i < 100; i++) {
      if (make[i] != NULL) {
        make[i] -> ~ball();
        make[i] = NULL;
      }
    }
    p = 0;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
  countCoin += 1000;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer4Timer(TObject *Sender)
{
  count=0;
  for (int x = 0; x < 16; x++) {
    for (int y = 0; y < 8; y++) {
      if(strip[x][y] !=NULL && strip[x][y]->hpBrick <= 0){
        count++;
      }
    }
  }
  if(count==128){
    ShowMessage("遊戲勝利");
    Timer4->Enabled=false;
  }
}
//---------------------------------------------------------------------------

