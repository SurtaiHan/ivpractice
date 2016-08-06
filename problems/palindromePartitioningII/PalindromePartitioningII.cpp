#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>

using namespace std;

namespace Skyline {
	static int minCuts(string str) {

		// observe that there must be a "last" palindrome segment

		// first construct a lookup table
		bool isPalin[str.length()][str.length()];
        for(int i=0; i<str.length(); i++)
        for(int j=0; j<str.length(); j++)
        isPalin[i][j] = false;

		for (int incr = 0; incr < str.length(); incr++) {
			for(int lowerBound = 0; lowerBound < str.length() - incr; lowerBound++) {
				int upperBound = lowerBound + incr;
				int len = incr + 1;

				if(len == 1) {
					isPalin[lowerBound][upperBound] = true;
				}
				else if(len == 2 &&
						str[lowerBound] == str[upperBound]) {
					isPalin[lowerBound][upperBound] = true;
				}
				else {
					if(str[lowerBound] == str[upperBound] &&
					   isPalin[lowerBound+1][upperBound-1]) {
						isPalin[lowerBound][upperBound] = true;
					}
				}
			}
		}

		// then find the proper "last" palin chunk at each ending index
		int minCutsToMakePalin[str.length()];
		for(int i=0; i<str.length(); i++) {
		    minCutsToMakePalin[i] = INT_MAX;
		}

		for (int end = 0; end < str.length(); end++) {
			for(int start = 0; start <= end; start++) {
                //cout << "start: " << start << " end: " << end << endl;

				if(isPalin[start][end]) {
					if(start == 0) {
						minCutsToMakePalin[end] = 0;
						cout << "1: position " << end << " updated to " << minCutsToMakePalin[end] << endl;
					}
					else {
					    //cout << "here with end as " << end << " and start as " << start << endl;
					    if(minCutsToMakePalin[start-1] + 1 < minCutsToMakePalin[end]) {
					        minCutsToMakePalin[end] = minCutsToMakePalin[start-1] + 1;
					        cout << "2: position " << end << " updated to " << minCutsToMakePalin[end] << endl;
					    }
					}
				}

			}
		}

		for(int i=0; i<str.length(); i++) {
		    cout << "minCuts[" << i << "]= " << minCutsToMakePalin[i] << endl;
		}

		return minCutsToMakePalin[str.length() - 1];
    }
}
