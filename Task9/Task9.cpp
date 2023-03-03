#include "Matrix.h"
#include "Container.h"
#include "Container.cpp"

int main(int argc, char* argv[])
{
    Container<Matrix> SomeDataContainer;
    SomeDataContainer.LoadFromFile();
    SomeDataContainer.LoadFromConsole();
    Container<Matrix> AnotherContainer(SomeDataContainer.GetQuickSort(), SomeDataContainer.GetSize());
    for(int i = 0; i < AnotherContainer.GetSize(); ++i)
    {
        cout << AnotherContainer[i] << endl;
    }
    return 0;
}
