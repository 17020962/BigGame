#include <iostream>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <vector>
#include<string.h>

#define frameBottom 30
#define frameLeft 30
#define frameRight 51
#define frameTop 5
#define lengthBasket 8


using namespace std;

void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = {1, CursorVisibility};
    SetConsoleCursorInfo(handle, &cursor);
}

// Hàm tô màu.
void textcolor(int x)
{
    HANDLE mau;
    mau = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(mau, x);
}

// Hàm d?ch chuy?n con tr? d?n t?a d? x, y.
void gotoxy(int x, int y)
{
     HANDLE hConsoleOutput;
     COORD Cursor_an_Pos = { x - 1, y - 1 };
     hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

//hàm xóa màn hình

void deleteScreen(void)
{
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
HANDLE hConsoleOut;
COORD Home = {0,0};
DWORD dummy;

hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);

FillConsoleOutputCharacter(hConsoleOut,' ',csbiInfo.dwSize.X * csbiInfo.dwSize.Y,Home,&dummy);
csbiInfo.dwCursorPosition.X = 0;
csbiInfo.dwCursorPosition.Y = 0;

}

//Một số hàm hiệu ứng mang tính cho có không quan trọng lắm

void Name_Game(){
	gotoxy(15,5);
	cout<<" $$$$$$$       $       $$$$$$$$$$$   $$$$$$$  $       $";
	gotoxy(15,6);
	cout<<"$           $     $	  $       $         $       $"<<endl;
	gotoxy(15,7);
	cout<<"$          $$$$$$$$$        $       $         $$$$$$$$$"<<endl;
	gotoxy(15,8);
	cout<<"$         $         $       $       $         $       $"<<endl;
	gotoxy(15,9);
	cout<<"$         $         $       $       $         $       $"<<endl;
	gotoxy(15,10);
	cout<<" $$$$$$$  $         $       $	   $$$$$$$  $       $"<<endl<<endl<<endl;
	gotoxy(25,14);
	cout<<" $$$$$$$   $$$$$$$     $$$$$$$"<<endl;
	gotoxy(25,15);
	cout<<"$         $           $"<<endl;
	gotoxy(25,16);
	cout<<"$$$$$$$   $           $"<<endl;
	gotoxy(25,17);
	cout<<"$         $   $$$$$   $   $$$$$"<<endl;
	gotoxy(25,18);
	cout<<"$         $     $     $     $"<<endl;
	gotoxy(25,19);
	cout<<" $$$$$$$    $$$$$$      $$$$$$"<<endl;
}

struct Coolidare{

    int x,y;

};

struct ShapeBasket{

    char a[lengthBasket];

};

class basket{

    public:
        Coolidare coolidareBasket;
        ShapeBasket shapeBasket;
        int speedBasket = 3;
        int scores = 0;
    public:
        basket();
        ~basket();
       void displayBasket();
       void deleteBasket();
       void paintBasket();
       void controlBasket();
       int returnCoolidareBasketX();
       int returnCoolidareBasketY();
       void caculatedScores(int Xegg, int Yegg);
       void displayScores();
       void gameOver(int Xegg, int Yegg);
};

basket::basket(){
    textcolor(2);
    coolidareBasket.x = (frameLeft+frameRight)/2-3;
    coolidareBasket.y = frameBottom-1;
    for(int i = 0; i<lengthBasket ; i++){
        shapeBasket.a[i] = 219;
    }
    //textcolor(7);

}

basket::~basket(){}

void basket::deleteBasket(){

    for(int i = 0; i<lengthBasket; i++){
        shapeBasket.a[i] = ' ';
    }
    gotoxy(coolidareBasket.x,coolidareBasket.y);
    for(int i = 0; i<lengthBasket; i++){
        cout<<shapeBasket.a[i];
    }

}

void basket::paintBasket(){
    textcolor(2);
    for(int i = 0; i<lengthBasket; i++){
        shapeBasket.a[i] = 219;
    }
    gotoxy(coolidareBasket.x,coolidareBasket.y);
    for(int i = 0; i<lengthBasket; i++){
        cout<<shapeBasket.a[i];
    }
    textcolor(6);

}

void basket::controlBasket(){

    if(GetAsyncKeyState(VK_LEFT)&&coolidareBasket.x>frameLeft+1){
        basket::deleteBasket();
        coolidareBasket.x -= speedBasket;
        basket::returnCoolidareBasketX();
        basket::paintBasket();
    }
    if(GetAsyncKeyState(VK_RIGHT)&&coolidareBasket.x<frameRight-8){
        basket::deleteBasket();
        coolidareBasket.x += speedBasket;
        basket::returnCoolidareBasketX();
        basket::paintBasket();
    }

}

void basket::displayBasket(){
    textcolor(6);
    for(int i = 0; i<lengthBasket ; i++){
        gotoxy(coolidareBasket.x+i,coolidareBasket.y);
        cout<<char(shapeBasket.a[i]);
    }
}

int basket::returnCoolidareBasketX(){

    return coolidareBasket.x;

}

int basket::returnCoolidareBasketY(){

    return coolidareBasket.y;

}

void basket::caculatedScores(int Xegg, int Yegg){

    int dx,dy;
    dx = Xegg-coolidareBasket.x;
    dy = Yegg-coolidareBasket.y;

    if(dy==0&&dx>=0&&dx<=8){
        scores++;
    }
    basket::gameOver(Xegg,Yegg);

}

void basket::displayScores(){

    gotoxy((frameLeft+frameRight)/2-5,frameTop-1);
    cout<<"Your Scores: "<<scores;

}

void basket::gameOver(int Xegg, int Yegg){

    int dx = Xegg - coolidareBasket.x;
    int dy = Yegg - coolidareBasket.y;

    if(dy==0&&dx>8){
        gotoxy(frameRight+3,frameTop+5);
        cout<<"You Lose!!!!!!!!!!";
        getch();
        gotoxy(frameRight+3,frameTop+6);
        cout<<"better luck next time"<<endl;
        getch();
        system("pause");
        exit(0);

    }
    if(dy==0&&dx<0){
        gotoxy(frameRight+3,frameTop+5);
        cout<<"You Lose!!!!!!!!!!";
        getch();
        gotoxy(frameRight+3,frameTop+6);
        cout<<"better luck next time"<<endl;
        getch();
        system("pause");
        exit(0);

    }


}

struct ShapeEgg{

    char a;

};

class egg{

    public:
        ShapeEgg shapeEgg;
        Coolidare coolidareEgg;
    private:
        void createCoolidareEgg();
    public:
        egg();
        ~egg();
        void displayEgg();
        void moveEgg(int Xo, int Yo);
        void deleteEgg();
        void paintEgg();
        //void createCoolidareEgg();
        //void paintPoint();
        int returnCoolidareEggX();
        int returnCoolidareEggY();
};

egg::egg(){

    coolidareEgg.x = frameLeft+1 + rand()%5;
    coolidareEgg.y = frameTop + 2;
    textcolor(2);
    shapeEgg.a = 'O';

}

egg::~egg(){}

int egg::returnCoolidareEggX(){

    return coolidareEgg.x;

}

int egg::returnCoolidareEggY(){

    return coolidareEgg.y;

}

void egg::displayEgg(){

    gotoxy(coolidareEgg.x,coolidareEgg.y);
    cout<<char(shapeEgg.a);
}

void egg::deleteEgg(){

    shapeEgg.a = ' ';
    gotoxy(coolidareEgg.x,coolidareEgg.y);
    cout<<shapeEgg.a;

}

void egg::paintEgg(){

    shapeEgg.a = 'O';
    gotoxy(coolidareEgg.x,coolidareEgg.y);
    cout<<shapeEgg.a;

}

void egg::moveEgg(int Xo, int Yo){
        egg::deleteEgg();
        //coolidareEgg.y++;
        if(coolidareEgg.y<frameBottom-1&&coolidareEgg.x<frameRight-1){
            int dx = Xo - coolidareEgg.x;
            int dy = Yo - coolidareEgg.y;
            coolidareEgg.y++;
            egg::paintEgg();
        }
        else{
            egg::createCoolidareEgg();
        }

}

void egg::createCoolidareEgg(){

    coolidareEgg.x = frameLeft+1 + rand()%(frameRight-1);
    coolidareEgg.y = frameTop - 5;

}

class egg1: public egg{

//đã được kế thừa từ egg
    public:
        egg1();
        ~egg1();
        void createCoolidareEgg();


};

egg1::egg1(){

    coolidareEgg.x = frameLeft+1 + rand()%5;
    coolidareEgg.y = frameTop + 2;

}

egg1::~egg1(){}

void egg1::createCoolidareEgg(){

    coolidareEgg.x = frameLeft+1 + rand()%5;
    coolidareEgg.y = frameTop + 2;

}

class egg2: public egg{

//đã được kế thừa từ egg

    public:
        egg2();
        ~egg2();
       // void createCoolidareEgg();

};

egg2::egg2(){

    coolidareEgg.x = frameLeft+1 + rand()%5;
    coolidareEgg.y = frameTop + 10;

}

egg2::~egg2(){}

//void egg2::createCoolidareEgg(){
//
//    coolidareEgg.x = frameLeft+1 + rand()%5;
//    coolidareEgg.y = frameTop + 10;
//
//}

class frame{

    public:
       void displayTop();
       //void displayLeft();
       //void displayRight();
       //void displayBottom();
};

void frame::displayTop(){

    for(int i = frameLeft; i<=frameRight; i++){
        textcolor(7);
        gotoxy(i,frameTop);
        cout<<char(219);
    }
    for(int i = frameLeft; i<=frameRight; i++){
        textcolor(7);
        gotoxy(i,frameBottom);
        cout<<char(219);
    }
    for(int i = frameTop; i<=frameBottom; i++){
        textcolor(7);
        gotoxy(frameLeft,i);
        cout<<char(219);
    }
    for(int i = frameTop; i<=frameBottom; i++){
        textcolor(7);
        gotoxy(frameRight,i);
        cout<<char(219);
    }


}




int main(){
    srand(time(0));
    basket basket;
    frame frame;
    egg egg;
    egg1 egg1;
    egg2 egg2;
    ShowCur(0);
    Name_Game();
    getch();
    deleteScreen();
    frame.displayTop();
    int Xo,Yo;
    Xo = basket.returnCoolidareBasketX();
    Yo = basket.returnCoolidareBasketY();
    int Xegg,Yegg,Xegg1,Yegg1,Xegg2,Yegg2;
    Xegg = egg.returnCoolidareEggX();
    Yegg = egg.returnCoolidareEggY();
    while(1){
    //trả về tọa độ của cái rổ
    Xo = basket.returnCoolidareBasketX();
    Yo = basket.returnCoolidareBasketY();
    //trả về giá trị của tọa độ quả trứng khi di chuyển
    Xegg = egg.returnCoolidareEggX();
    Yegg = egg.returnCoolidareEggY();
    Xegg1 = egg1.returnCoolidareEggX();
    Yegg1 = egg1.returnCoolidareEggY();
    Xegg2 = egg2.returnCoolidareEggX();
    Yegg2 = egg2.returnCoolidareEggY();
    // hiển thị hình dạng các đối tượng
    egg.displayEgg();
    egg1.displayEgg();
    egg2.displayEgg();
    // chuyển động của trứng
    egg.moveEgg(Xo,Yo);
    egg1.moveEgg(Xo,Yo);
    egg2.moveEgg(Xo,Yo);
    // hiển thị khung chơi
    frame.displayTop();
    // hiển thị cái rổ
    basket.displayBasket();
    // điều khiển cái rổ
    basket.controlBasket();
    //hiển thị điểm
    basket.caculatedScores(Xegg,Yegg);
    basket.displayScores();
    basket.caculatedScores(Xegg1,Yegg1);
    basket.displayScores();
    basket.caculatedScores(Xegg1,Yegg1);
    basket.displayScores();
    Sleep(100);
    }
	return 0;
}
