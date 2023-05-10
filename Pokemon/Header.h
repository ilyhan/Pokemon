#pragma once
struct Pockemon;
int countStrings();
void initStructpo(Pockemon*& po, int n);
int searchMyPock(Pockemon* po, int n);
void coutStrat(int a[5]);
void coutAllPock(Pockemon* po, int n);
int generationBattle(Pockemon*& po, int as[5], int bs[5], int k, int a, int b);
int whoWin(Pockemon a, Pockemon b);
bool provStrat(int a[5]);