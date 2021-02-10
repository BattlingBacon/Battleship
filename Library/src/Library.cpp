// This file should only contain function definitions -Bacon

#include "Library.h"
#include <iostream>
#include <vector>

using namespace std;

namespace library
{
    bool InputVal(char optionTrue, char optionFalse, string prompt)
    {
        char choice;
        cout << prompt;
        cin >> choice;
        while (true)
        {
            if (choice == 'q' || choice == 'Q')
                exit(0);
            if (choice == optionTrue || choice == optionTrue + 32)
                return true;
            if (choice == optionFalse || choice == optionFalse + 32)
                return false;
        }
    }
}
