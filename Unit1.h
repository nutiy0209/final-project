//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel1;
  TLabel *Label1;
  TTimer *Timer1;
  TButton *Button2;
  TButton *Button3;
  TLabel *Label2;
  TButton *Button1;
  TButton *Button4;
  TButton *Button5;
  void __fastcall Timer1Timer(TObject *Sender);
  void __fastcall Button1Click(TObject *Sender);
  void __fastcall Button2Click(TObject *Sender);
  void __fastcall Button3Click(TObject *Sender);
  void __fastcall Button5Click(TObject *Sender);
  void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
class ball{
  friend class air;
  friend class brick;
  private:
    void __fastcall Timer1Timer(TObject *Sender);
    TShape*circle;
    TTimer*times;
    void __fastcall timer(TObject *Sender);
    int x, y;                    //  �y���ܤƶq
    int pHeight, pWidth;
    int size, power;             //  �j�p  ���O
  public:
    int mark;
    int getLeft();
    int getTop();
    ~ball();
    ball(TPanel*panel, int x, int y, int speed, int size, int power, int coor_x, int coor_y);
};

class type{
  friend class ball;
  friend class brick;
  protected:
    int pWidth1;
    int pHeight1;
    int hpAir;                //  �תO�ͩR��
    TImage*rectangle;
    void __fastcall timed(TObject *Sender);
  public:
    TTimer*time;
    int getLeft();
    int getTop();
    ~type();
    type(TPanel*panel);
};

class air:public type{
  public:
    air(TPanel*panel);
    
};

class super:public type{
  public:
    super(TPanel*panel);
};

class brick{
  friend ball;
  friend air;
  public:
    TTimer*timing;
    void __fastcall timez(TObject *Sender);
    int hpBrick, coin;          //  �j���ͩR��  ����
    int allCoin;
    TShape*square;
    ~brick();
    brick(TPanel*panel, int x_, int y_, int color);
};

#endif
