#include<iostream>
using namespace std;

class Outer
{
private:
int privateData;
public:
int publicData;
Outer(int pr,int pu): privateData(pr), publicData(pu){}
class Inner
{
public:
void printPublic(const Outer& otr)
{
cout<<"Public Member of outer: "<<otr.publicData<<endl;
}

void printPrivate(const Outer& otr)
{
cout<<"Private Member of outer: "<<otr.privateData<<endl;
}

};
};

int main()
{
Outer otr(2,3);
Outer::Inner inr;
inr.printPublic(otr);
inr.printPrivate(otr);
}
