#include "GA.hpp"

GA::GA(size_t size, size_t length, double r)
 : mSize(size), mChromoLength(length), mRate()
{
    init(size, length);
    initGoods();

    //遺伝的操作
    for(int i=0; i<100; ++i){
        mating();
        mutation();
        childrenSelection();
        for(int i = 0; i<mSize; ++i){
            cout << "price value == "<< fitness(i, mPGeneration) << endl;
        }
    }

    std::cout << "------------result--------------" << std::endl;
    int max=0;
    for(int i = 0; i<mSize; ++i){
        int fitval = fitness(i, mPGeneration);
        cout << "price value == "<< fitval << endl;
        if(max < fitval) max = fitval;
    }
    std::cout << "--------------------------------" << std::endl;
    std::cout << "max fitness == " << max << std::endl;
}

void GA::mating()
{
    int roulette = createRoulette(mSize, mPGeneration);

    for(size_t i=0; i<mSize; ++i){
        size_t p1 = rouletteSelection(roulette);
        size_t p2 = rouletteSelection(roulette);
        if(p1 != p2) crossover(p1, p2, i*2);
    }
}

void GA::mutation()
{
    for(size_t chromoNo=0; chromoNo<mSize*2; ++chromoNo){
        for(size_t pos=0; pos<mChromoLength; ++pos){
            if( (rndRange(0,100) / 100.0) <= mRate ) flipBit(chromoNo, pos);
        }
    }
}

void GA::flipBit(size_t No, size_t pos)
{
    if(mNGeneration.at(No).at(pos) == 1) {
        mNGeneration.at(No).at(pos) = 0;
    }else{
        mNGeneration.at(No).at(pos) = 1;
    }
}

void GA::childrenSelection()
{
    int roulette = createRoulette(mSize*2, mNGeneration);

try{
    for(size_t i=0; i<mSize; ++i){
        size_t childrenNo = rouletteSelection(roulette);
        mPGeneration.at(i) = mNGeneration.at(childrenNo);
    }
}catch(out_of_range &ex){
    std::cerr << "childrenSelection() " << ex.what() << std::endl;
}
}

size_t GA::rouletteSelection(int r)
{
    int selectedPos = rndRange(0, r);
    int currentPos=0;
    int selectedIndex = 0;

    for(size_t i=0; i<mSize; ++i){
        currentPos += mRoulette.at(i);
        if(selectedPos < currentPos) {
            selectedIndex = i;
            break;
        }
    }

    return selectedIndex;
}

int GA::createRoulette(size_t num, vector<vector<int>> &gene)
{
    int total=0;
try{

    mRoulette.resize(num);
    for(size_t i=0; i<num; ++i){
        mRoulette.at(i) = fitness(i, gene);
        total += mRoulette.at(i);
    }

}catch(out_of_range &ex){
    std::cerr << "createRoulette()"<< ex.what() << std::endl;
}
    return total;
}

int GA::fitness(size_t No, vector<vector<int>> &gene)
{
    int totalWeight=0;
    int totalPrice=0;
    for(size_t i=0; i<mChromoLength; ++i){
        int isPut = gene.at(No).at(i);
        if(isPut) {
            totalWeight += mGoods[i][weight];
            totalPrice  += mGoods[i][price];
        }
    }
    if(totalWeight > mMaxWeight) totalPrice = 0;

    return totalPrice;
}

//一回の交叉で子が２つ増えることに注意
void GA::crossover(size_t p1, size_t p2, size_t ChildrenNo)
{
    vector<int> child1(mChromoLength, 0);
    vector<int> child2(mChromoLength, 0);
    for(size_t front=0; front<mChromoLength/2; ++front){
        child1.at(front) = mPGeneration.at(p1).at(front);
        child2.at(front) = mPGeneration.at(p2).at(front);
    }
    for(size_t back=mChromoLength/2; back<mChromoLength; ++back){
        child1.at(back) = mPGeneration.at(p2).at(back);
        child2.at(back) = mPGeneration.at(p2).at(back);
    }
    mNGeneration.at(ChildrenNo)   = child1;
    mNGeneration.at(ChildrenNo+1) = child2;
}

int GA::rndRange(int a, int b)
{
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<> rnd(a,b-1);
    return rnd(mt);
}

void GA::init(size_t size, size_t length)
{
    std::vector<int> temp(length,0);

    mNGeneration.resize(mSize*2, temp);

    for(size_t chromosomeNo=0; chromosomeNo<size; ++chromosomeNo) {
        for(size_t position=0; position<length; ++position) {
            temp.at(position) = rndRange(0,2);
        }
        mPGeneration.push_back(temp);
        for(auto i : mPGeneration.at(chromosomeNo)){
            std::cout << i << " ";
        }std::cout << std::endl;
    }
}

void GA::initGoods()
{
    std::cout << "weight  price" << std::endl;
    array<int,2> tmp = { {0,0} };
    mGoods.resize(mChromoLength);
    for(int i=0; i<mChromoLength; ++i){
        tmp.at(weight) = rndRange(0,80);
        tmp.at(price)  = rndRange(0,80);
        mGoods.at(i) = tmp;
        cout << mGoods.at(i).at(weight) << "   " << mGoods.at(i).at(price) << endl;
    }
}
