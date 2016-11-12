#ifndef MAXIMUM_GATES_H
#define MAXIMUM_GATES_H

#include <vector>
#include <set>
using std::vector;
using std::set;

// TODO: Your answer for question 2 goes here


int maximumGates(vector<int> arrives, vector<int> departs){
	set<int> gatesLastTime;
	gatesLastTime.insert(-1); //1 gates initially, time is -1
	for(int i = 0; i < arrives.size(); ++i){
		//try to find a gate
        set<int>::iterator iter = gatesLastTime.lower_bound(arrives[i]);
		if(iter != gatesLastTime.begin()){ //available one
            --iter;
			gatesLastTime.erase(iter);  //departed
			gatesLastTime.insert(departs[i]);  //settle down
		}
		else{  //none, then add one
			gatesLastTime.insert(departs[i]);  //settle down
		}
	}
	int maxGates = gatesLastTime.size();
	return maxGates;
}


// Do not write any code below this line


#endif
