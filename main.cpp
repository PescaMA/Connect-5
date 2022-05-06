#include <iostream>
#include <string.h>;
using namespace std;
short board[105][105];
short n,m,safe;
#pragma region
void SetBoard()
{
    for(int i=1;i<=n;i++)
        board[i][0]=board[i][m+1]=1;
    for(int j=1;j<=m;j++)
        board[0][j]=board[n+1][j]=2;
    board[0][0]=3;
    board[n+1][0]=4;
    board[0][m+1]=5;
    board[n+1][m+1]=6;
}
void CClear()
{ /// clears console
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system ("clear");
    #endif
}
void ShowBoard()
{
    CClear();
    char ch[69];
    if(safe)
        strcpy(ch," |=++++XO#");
    else
    {   /// it only works when converting to char (like here)
        int v[]={32,186,205,201,200,187,188,5,232,177};
        /// is  [spc]║   ═   ╔   ╚    ╗   ╝ ♣  Φ   ▒
        for(int i=0;i<10;i++)
            ch[i]=v[i];
        ch[10]='\0';
    }

    for(int i=0;i<=n+1;i++)
    {
        for(int j=0;j<=m+1;j++)
            cout<<ch[ board[i][j] ];
        cout<<'\n';
    }
}
template <class T,class S,class TT,class TTT>
void ReadNR(T &x ,S tryy, TT mn, TTT mx)
{ /// very normal function with no excesive complications
    string error;
    while(!(cin>>x) || (x<mn || x>mx))
    {
        cout<<tryy;
        if(cin.fail())
        {
            cin.clear();
            cin>>error;
        }
    }
    if(cin.peek()!=' ' && cin.peek()!='\n')
        cin>>error;
}
void SetSize()
{
    string unu100="Valoarea trebuie sa fie numar 1-99, incercati din nou: ";
    string zero1="Valoarea trebuie sa fie 1(da) sau 0, incercati din nou: ";
    cout<<"Introduceti inaltimea tablei ";
    ReadNR(n,unu100,1,99);
    CClear();
    cout<<"Introduceti latimea tablei ";
    ReadNR(m,unu100,1,99);
    CClear();
    cout<<"Vreti grafica simpla, dar 100% functionala(0 sau 1)? ";
    ReadNR(safe,zero1,0,1);
    SetBoard();
}
#pragma endregion
int scor1,scor2;
int const scormx=50;
bool finished()
{
    if(scor1>scormx || scor2>scormx)
        return true;
    for(int j=1;j<=m;j++)
        if(!board[1][j])
            return false;
    return true;
}
void ending()
{
    cout<<"Scorul tau este "<<scor1;
    cout<<"\nScorul AI-ului este: "<<scor2<<'\n';
    if(scor1>scor2)
        cout<<"Ai castigat!";
    else if(scor1<scor2)
        cout<<"Ai-ul a castigat!";
    else
        cout<<"Egalitate!";
}
bool legal(int col)
{
    return board[1][col]==0;
}
int c;
void dfs(int x,int y,int nr,int nr2,int cmx)
{
    if(board[x][y]!=nr || c==cmx)
        return;
    c++;
    board[x][y]=nr2;
    dfs(x+1,y,nr,nr2,cmx);dfs(x,y+1,nr,nr2,cmx);
    dfs(x-1,y,nr,nr2,cmx);dfs(x,y-1,nr,nr2,cmx);
}
bool cinci(int x,int y,int nr)
{
    c=0;
    bool pp=false;
    dfs(x,y,nr,100,5);
    if(c==5)
        pp=true;
    dfs(x,y,100,nr,5);
    return pp;
}
void movee(int col,int nr)
{
    int lin;
    for(lin=1;lin<=n && !board[lin][col];lin++);
    lin--;
    board[lin][col]=nr+6;
    if(cinci(lin,col,nr+6))
    {
        c=0;
        dfs(lin,col,nr+6,1,10000);
        if(nr==1)
            scor1+=c;
        else
            scor2+=c;
    }
}
void AI_move()
{
    int rnd=rand()%m+1;
    if(legal(rnd))
    {
        movee(rnd,2);
        return;
    }
    AI_move();
}
void Play()
{
    while(true)
    {
        ShowBoard();
        if(finished())
            return ending();
        cout<<"Pe ce coloana doresti sa pui: ";
        int col;
        string invalid="Valoare invalida, ziceti un nr de col libera: ";
        while(true)
        {
            ReadNR(col,invalid,1,m);
            if(legal(col))
            {
                movee(col,1);
                break;
            }
            else
                cout<<invalid;
        }
        if(finished())
            return ending();
        AI_move();
    }
}
int main()
{
    SetSize();
    Play();

}
