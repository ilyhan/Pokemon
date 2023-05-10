#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include "Header.h"
using namespace std;

enum Type {Normal, Insects, Poisonous, Herbal, Water, Fiery, Earthy, Combat, Stone, Magic, Electric,
           Mental, ghostly, Draconic, Ice, Flying, Steel, Dark};

struct Pockemon {
    string name;
    Type TypePock;
    int status = 1;
    int hp;
    int attack;
    int ulta;
    int block;
    string weakness;
    string advantage;
};

int main()
{
    setlocale(LC_ALL, "Ru");
    srand(time(NULL));
    int n = countStrings();//количество покемонов
    Pockemon* po = new Pockemon[n];
    initStructpo(po,n);

    //вывод покемонов
    //for (int i = 0; i < n; i++) {
    //    cout << po[i].name << "  " << po[i].attack << "  " << po[i].TypePock << endl;
    //}

    bool flag = true;
    int mypock, enemypock, k;
    while (flag) {
        cout << "Доступные покемоны"<<endl << endl;
        coutAllPock(po, n);
        cout << "Выберете покемона, указав его имя" << endl << endl;
        mypock = searchMyPock(po, n);
        enemypock = rand() % n;
        while(enemypock==mypock) enemypock = rand() % n;

        cout << "ВАШ ПРОТИВНИК:" << po[enemypock].name << endl<<endl;
        cout << "Создайте вашу стратегию, использовав 5 шагов. \n1 - использовать атаку \
            \n2 - использовать ульту (можно использовать 1 раз)\n3 - использовать блок\n " << endl;


        int myst[5], enemyst[5];
        bool f = true;
        while (f) {
            for (int i = 0; i < 5; i++) {
                cin >> myst[i];
            }
            f = provStrat(myst);
        }
        k = 0;
        for (int i = 0; i < 5; i++) {
            enemyst[i] = rand() % 3 + 1;
            if (enemyst[i] == 2) k++;
            while (k > 1) {
                enemyst[i] = rand() % 3 + 1;
                if (enemyst[i] != 2) k--;
            }
        }

        cout << "Ваша стратегия:" << endl;
        coutStrat(myst);
        cout <<endl<< "Стратегия противника:" << endl;
        coutStrat(enemyst);

        int winner;
        if (po[mypock].weakness == po[enemypock].advantage) winner = generationBattle(po, myst, enemyst, 2, mypock, enemypock);
        else if (po[enemypock].weakness == po[mypock].advantage) winner = generationBattle(po, myst, enemyst, 2, mypock, enemypock);
        else winner = generationBattle(po, myst, enemyst, 1, mypock, enemypock);
        cout << "\nИТОГ СРАЖЕНИЯ: ";
        if (winner == -1) {
            cout << "Боевая ничья";
        }else cout << "Выиграл " << po[winner].name<< endl;
        cout << "\n-----------------------------------------\n";
        cout << "\n\nВведите 0, если хотите закончить или любое число для продолжения" << endl;
        cin >> k;
        if (k == 0) flag = false;
    }
}