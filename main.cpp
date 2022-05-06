#include <iostream>
#include <string.h>;
using namespace std;
short board[105][105];
short n,m;
bool safe=true;
void SetBoard()
{
    for(int i=1;i<=n;i++)
        board[i][0]=1,board[i][m+1]=2;
    for(int j=1;j<=m;j++)
        board[0][j]=3,board[n+1][j]=4;
    board[0][0]=5;
    board[n+1][0]=6;
    board[0][m+1]=7;
    board[n+1][m+1]=8;
}
void ShowBoard()
{
    char ch[69];
    if(safe)
        strcpy(ch," ||==++++XO");
    else ///       0123456789
        strcpy(ch,"sup");
    for(int i=0;i<=n+1;i++)
    {
        for(int j=0;j<=m+1;j++)
            cout<<ch[ board[i][j] ];
        cout<<'\n';
    }
}
void CClear()
{ /// clears console
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system ("clear");
    #endif
}
template <typename T> void ReadNR(T &x)
{
    string error;
    while(!(cin>>x) || (x<1 || x>99))
    {
        cout<<"Valoarea trebuie sa fie numar 1-99, incercati din nou: ";
        if(cin.fail())
        {
            cin.clear();
            cin>>error;
        }
    }
    if(cin.peek()!=' ' && cin.peek()!='\n')
        cin>>error;
    CClear();
}
void SetSize()
{
    cout<<"Introduceti inaltimea tablei ";
    ReadNR(n);
    cout<<"Introduceti latimea tablei ";
    ReadNR(m);
    SetBoard();
}
int main()
{
    SetSize();
    ShowBoard();
}
