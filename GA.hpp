#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <random>

using namespace std;

class GA {
private:
    size_t mSize;
    size_t mChromoLength;
    vector<vector<int>>  mPGeneration; //親世代
    vector<vector<int>>  mNGeneration; //次世代
    vector<int>          mRoulette;    //評価値に比例したポケットの大きさ。適応度が入っている。
    vector<array<int,2>> mGoods;
    size_t  mMaxWeight = 300; //最大重量
    void    init(size_t size, size_t length); //染色体の数,遺伝子の長さ
    void    initGoods();        //荷物の価値、重量の初期化
    int     rndRange(int a, int b);     //a以上b未満の乱数

    void mating();
        size_t rouletteSelection(int r);
            int createRoulette(size_t num, vector<vector<int>> &gene); //num個のポケットのルーレットを作る。(個数)
                int fitness(size_t No, vector<vector<int>> &gene); //染色体の適応度を計算する。今回はナップサックに入れた荷物の価値の合計
        void crossover(size_t p1, size_t p2, size_t ChildrenNo); //一点交叉,(親1の添え字,親2の添え字)

    void    childrenSelection();
        void    mutation();                 //突然変異
            void    flipBit(size_t No, size_t pos);
            const double  mRate;

    enum goodsAttribute{
        weight,
        price,
    };
public:
    GA(size_t size, size_t length, double r);     //(初期の染色体集団の要素数、染色体の長さ)
};
