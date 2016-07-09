#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>

using namespace std;

namespace Skyline {
	static vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        multimap<int, int> sortedBuildings;
		for(int i=0; i<buildings.size(); i++) {
			vector<int> building = buildings[i];
			int start = building[0];
			int end = building[1];
			int height = building[2];
			sortedBuildings.insert(pair<int,int>(start, height));
			sortedBuildings.insert(pair<int,int>(end, -height));
		}

		vector< pair<int,int> > output;

		int currentMaxHeight = 0;
		// first param is height, second param is count
		// (number of buildings at that height)
		map<int,int> activeBuildings;
		for(auto it=sortedBuildings.cbegin(); it != sortedBuildings.cend(); ) {
		    int pos = it->first;
		    auto range = sortedBuildings.equal_range(it->first);
		    for(; it != range.second; it++) {
				int height = it->second;
				cout << "height is: " << height << endl;
				if(height > 0) {
					if(activeBuildings.find(height) == activeBuildings.end()) {
						// new building at this height
						activeBuildings[height] = 1;
					}
					else {
						// another building at this height
						activeBuildings[height]++;
					}
				}
				else {
					activeBuildings[-height]--;
					if(activeBuildings[-height] == 0) {
						activeBuildings.erase(-height);
					}
				}
		    }

			auto biggest = activeBuildings.rbegin();
			if(biggest == activeBuildings.rend()) {
			    currentMaxHeight = 0;
			    output.push_back(pair<int,int>(pos, currentMaxHeight));
			}
			else if(biggest->first != currentMaxHeight) {
				currentMaxHeight = biggest->first;
				output.push_back(pair<int,int>(pos, currentMaxHeight));
			}
		}
		return output;
    }
}
