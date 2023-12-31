#include "Matrix.h"
#include "Container.h"
#include "Container.cpp"

int main(int argc, char* argv[])
{
    Container<Matrix> SomeDataContainer;
    SomeDataContainer.LoadFromFile();
    //SomeDataContainer.LoadFromConsole();
    try
    {
        SomeDataContainer.ReadActionsFromFile();
    }
    catch(OperationIsNotCorrect& Ex)
    {
        cout << Ex.GetMessage() << endl;
    }
    catch(WrongNumberOfActions& Ex)
    {
        cout << Ex.GetMessage() << endl;
    }
    cout << "Result of all actions: " << endl << SomeDataContainer.Calculate() << endl;
    return 0;
}
