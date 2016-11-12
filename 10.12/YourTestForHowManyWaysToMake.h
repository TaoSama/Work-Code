#ifndef YOUR_TEST_FOR_HOW_MANY_WAYS_TO_MAKE_H
#define YOUR_TEST_FOR_HOW_MANY_WAYS_TO_MAKE_H

#include "HowManyWaysToMake.h"
#include <iostream>
using std::cout;
using std::endl;

int testHowManyWaysToMake() {
    // TODO: your test case for question 1b goes inside this function, instead of the next line of code:

    const int possibilities = howManyWaysToMake(10, {1,2,3,4,5});

    if (possibilities == 30) {
        cout << "2) Pass: code correctly returns that there are 30 ways to make 10 out of {1,2,3,4,5}\n";
        return 0;
    } else {
        cout << "2) Fail: code returns that there are " << possibilities << " ways to make 10 out of {1,2,3,4,5} -- but the answer is 30\n";
        return 1;
    }

    return 0;

}


// Do not write any code below this line

#endif
