#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Header.h"
using namespace std;

enum Type {Normal, Insects, Poisonous, Herbal, Water, Fiery, Earthy, Combat, Stone, Magic, Electric,
           Mental, Ghostly, Draconic, Ice, Flying, Steel, Dark};

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

Type F(string s) {
    string str[18] = { "Normal", "Insects", "Poisonous", "Herbal", "Water", "Fiery", "Earthy", "Combat", "Stone", "Magic","Electric",
                       "Mental", "Ghostly", "Draconic", "Ice", "Flying", "Steel", "Dark" };
    for (int i = 0; i < 18; i++) if (s == str[i]) return Type(i);
}

int countStrings() {
    ifstream out("Data.txt");
    string str;
    int n = 0;
    while (getline(out, str)) n++;
    out.close();
    return n;
}

void initStructpo(Pockemon*& po, int n) {
    ifstream in("Data.txt");
    for (int i = 0; i < n; i++) {
        if (in.is_open()) {
            in >> po[i].name;
            string str;
            in >> str;
            po[i].TypePock = F(str);
            in >> po[i].hp;
            in >> po[i].attack;
            in >> po[i].ulta;
            in >> po[i].block;
            in >> po[i].weakness;
            in >> po[i].advantage;
        }
    }
    in.close();
}

bool provStrat(int a[5]) {
    int k = 0;
    for (int i = 0; i < 5; i++) {
        if (a[i] == 2) k++;
        if (a[i] > 3 || a[i] < 1) {
            cout << "Проверьте ввод и помните что в стратегии может быть только одна ульта!" << endl;
            return true;
        }
        if (k > 1) {
            cout << "Проверьте ввод и помните что в стратегии может быть только одна ульта!" << endl;
            return true;
        }
    }
    return false;
}

int searchMyPock(Pockemon* po, int n) {
    while (true) {
        string mypock;
        cin >> mypock;
        for (int i = 0; i < n; i++) {
            if (po[i].name == mypock && po[i].status == 1) {
                cout << "Покемон успешно выбран" << endl << endl;
                return i;
            }
        }
        cout << "К сожалению, данного покемона обнаружить не удалось. Повторите попытку" << endl;
    }
}

void coutAllPock(Pockemon* po, int n) {
    cout << setw(9) << "Имя |" << setw(7) << "Тип |"<<setw(6)<<"  HP  |" << setw(8) << "Атака |" << setw(5) << " Ульта | " << setw(5) << " Блок | " << setw(10) << " Слабость | " << setw(10) << " Преимущество | " << endl;
    cout << "--------+------+------+-------+-------+-------+-----------+---------------|" << endl;
    for (int i = 0; i < n; i++) {
        if (po[i].status) {
            cout << setw(7) << po[i].name<< " |" << setw(4)<<po[i].TypePock << "  |" << setw(4)<<po[i].hp << "  |" << setw(4)<<po[i].attack << "   |" << setw(4) <<po[i].ulta<< "   | " << setw(3)<<po[i].block << "   | " << setw(8) <<po[i].weakness<< "  | " << setw(10)<<po[i].advantage<< "    | " << endl;
        }
    }
    cout<<endl;
}

void coutStrat(int a[5]) {
    cout << "---------------------------------------" << endl;
    cout << "|";
    for (int i = 0; i < 5; i++) {
        switch (a[i]) {
        case 1:
            cout << " атака |";
            break;
        case 2:
            cout << " ульта |";
            break;
        case 3:
            cout << " блок |";
            break;
        }
    }
    cout << "\n---------------------------------------" << endl;
    cout << endl;
}


int generationBattle(Pockemon*&po, int as[5],int bs[5] ,int k, int a, int b) { 
    int p = whoWin(po[a], po[b]);
    if (p == 0) {
        if (p == 1) {
            po[b].status = 0;
            return a;
        }
        if (p == 2) {
            po[a].status = 0;
            return b;
        }
    }
    for (int i = 0; i < 5; i++) {
        if (as[i] == 1) {
            po[b].hp -= po[a].attack;
            if (bs[i] == 1) po[a].hp -= po[b].attack * k;
            else if (bs[i] == 2) po[a].hp -= po[b].ulta * k;
            else {
                if (po[a].attack < po[b].block) po[b].hp += po[a].attack;
                else po[b].hp += po[b].block;
            }
        }
        else if (as[i] == 2) {
            po[b].hp -= po[a].ulta;
            if (bs[i] == 1) po[a].hp -= po[b].attack * k;
            else if (bs[i] == 2) po[a].hp -= po[b].ulta * k;
            else {
                if (po[a].ulta < po[b].block) po[b].hp += po[a].ulta;
                else po[b].hp += po[b].block;
            }
        }
        else {
            if (bs[i] == 1) po[a].hp -= po[b].attack*k;
            else if (bs[i] == 2) po[a].hp -= po[b].ulta*k;
            if (po[b].attack * k < po[a].block) po[a].hp += po[b].attack * k;
            else po[a].hp += po[a].block;
        }
        p = whoWin(po[a], po[b]);
        if (p == 1) {
            po[a].hp *= 1.4;
            po[b].status = 0;
            return a;
        }
        if (p == 2) {
            po[b].hp *= 1.4;
            po[a].status = 0;
            return b;
        }
        if (i == 4) {
            return -1;
        }
    }
}

int whoWin(Pockemon a, Pockemon b) {
    if (a.hp <= 0)  return 2;
    else if (b.hp <= 0) return 1;
    else return 0;
}
