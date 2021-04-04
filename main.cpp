/******************************************************************************
*                                                                             *
*   Program : Transactions Lists & Claims                                     *
*                                                                             *
*                                                                             *
*                                                                             *
*   Programmer : Nikita Seliverstov (nikselko)                                *
*                                                                             *
*                                                                             *
******************************************************************************/

#include "TransFunc.h"

int main()
{
    string file_name = ask_file_name();

    TransactionList transactions;
    
    if (!transactions.read_from_file(file_name))
    {
        std::cout << "Error opening file\n";

        return 0;
    }
    else
    {
        Menu program{ transactions };
        program.menu(file_name);

        return 1;
    }
}
    
