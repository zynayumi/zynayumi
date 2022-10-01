#include <iostream>
#include <string>
#include <memory>
using namespace std;

struct Base
{
    Base()
    {
    }
    virtual void printLabel();
    string label;
    int x;
    int y;
};

struct DerivedA : public Base
{
    DerivedA()
    {
    }
      void printLabel() override{
        cout << label << endl;
    }
};

struct DerivedB : public Base
{
    DerivedB()
    {
    }
    float foo;
};

struct Item
{
    int id;
    shared_ptr<Base> ptr;
    int x;
    int y;
};

int main(int argc, char const *argv[])
{
    auto a = make_shared<DerivedA>();
    auto b = make_shared<DerivedB>();
    Item items[2]{
        {1, a, 10, 10},
        {2, b, 15, 15},
    };
    for (int i = 0; i < 2; i++)
    {
        items[i].ptr->x = items[i].x;
        items[i].ptr->y = items[i].y;
    }
    items[0].ptr->label="test";
    cout << a->x << ", " << a->y << "\n";
    cout << b->x << ", " << b->y << "\n";

    return 0;
}
