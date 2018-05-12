// This program is used for testing the 'propagate' class

#include <iostream>
using std::cout;


#include "propagate.h"


int main ()
{
    cout << "Beginning of program 'TestPropagate'." << '\n';
    
    
    
    propagate prop(5,5);
    prop.propagateEpoch();
    
    
    cout << "End of program 'TestPropagte'." << '\n';
    return 0;
}

