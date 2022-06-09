//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <MPlayer.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel1;
  TLabel *Label1;
  TTimer *Timer1;
  TButton *shootUp;
  TButton *speedUp;
  TButton *powerUp;
  TButton *money;
  TButton *levelUp;
  TMediaPlayer *music;
  TTimer *Timer2;
  TButton *replay;
  TTimer *Timer3;
  TTimer *Timer4;
  TImage *Image1;
  TImage *Image2;
  TTimer *Timer5;
  TLabel *Label2;
  void __fastcall Timer1Timer(TObject *Sender);
  void __fastcall powerUpClick(TObject *Sender);
  void __fastcall shootUpClick(TObject *Sender);
  void __fastcall speedUpClick(TObject *Sender);
  void __fastcall levelUpClick(TObject *Sender);
  void __fastcall replayClick(TObject *Sender);
  void __fastcall Timer3Timer(TObject *Sender);
  void __fastcall moneyClick(TObject *Sender);
  void __fastcall Timer5Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
class bullet{
  friend class air;
  friend class brick;
  private:
    //void __fastcall Timer1Timer(TObject *Sender);
    TShape*circle;
    TTimer*times;
    void __fastcall timer(TObject *Sender);
    int x, y;                    //  座標變化量
    int pHeight, pWidth;
    int size, power;             //  大小  火力
  public:
    int mark;
    int getLeft();
    int getTop();
    ~bullet();
    bullet(TPanel*panel, int x, int y, int speed, int size, int power, int coor_x, int coor_y);
};

class type{
  friend class bullet;
  friend class brick;
  protected:
    int pWidth1;
    int pHeight1;
    int hpAir;                //  擋板生命值
    TImage*rectangle;
  public:
    void __fastcall timed(TObject *Sender);
    TTimer*time;
    int getLeft();
    int getTop();
    ~type();
    type(TPanel*panel);
};

class air:public type{
  public:
    air(TPanel*panel, int speed);
    
};

class super:public type{
  public:
    super(TPanel*panel, int speed);
};

class brick{
  friend bullet;
  friend air;
  public:
    TTimer*timing;
    void __fastcall timez(TObject *Sender);
    int hpBrick, coin;          //  磚塊生命值  分數
    int allCoin;
    TShape*square;
    ~brick();
    brick(TPanel*panel, int x_, int y_, int color);
};

#endif
