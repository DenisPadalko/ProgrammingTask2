#include "Matrix.h"
#include "Container.h"
#include "Container.cpp"

int main(int argc, char* argv[])
{
    Container<Matrix> SomeDataContainer;
    SomeDataContainer.LoadFromFile();
    SomeDataContainer.LoadFromConsole();
    SomeDataContainer.ReadActionsFromFile();
    cout << "Result of all actions: " << endl << SomeDataContainer.Calculate() << endl;
    return 0;
}
