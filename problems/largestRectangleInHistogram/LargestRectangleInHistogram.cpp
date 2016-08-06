#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>

using namespace std;

namespace LargestRectangleInHistogram {
	static int largestRectangleArea(vector<int>& heights) {
        if(heights.size() == 0)
            return 0;

        // neither include the bar itself
        int bestLeftwards[heights.size()];
        int bestRightwards[heights.size()];

        // (value, position)
        stack<pair<int,int> > candidates;

        // bestLeftwards
        for(int i=0; i<heights.size(); i++) {
            int value = heights[i];
            while(!candidates.empty()) {
                pair<int,int> top = candidates.top();
                if(value <= top.first) {
                    candidates.pop();
                }
                else {
                    candidates.emplace(pair<int,int>(heights[i],i));
                    bestLeftwards[i] = i - top.second - 1;
                    break;
                }
            }

            // this means the current thing is a better candidate (smaller) than all in stack
            if(candidates.empty()) {
                candidates.emplace(pair<int,int>(heights[i], i));
                bestLeftwards[i] = i;
            }
        }

        // clear the stack
        while(!candidates.empty())
            candidates.pop();

        // bestRightwards
        for(int i=heights.size()-1; i>=0; i--) {
            int value = heights[i];
            while(!candidates.empty()) {
                pair<int,int> top = candidates.top();
                if(value <= top.first) {
                    candidates.pop();
                }
                else {
                    candidates.emplace(pair<int,int>(heights[i],i));
                    bestRightwards[i] = top.second - i - 1;
                    break;
                }
            }

            // this means the current thing is a better candidate (smaller) than all in stack
            if(candidates.empty()) {
                candidates.emplace(pair<int,int>(heights[i], i));
                bestRightwards[i] = heights.size() - i - 1;
            }
        }

        // all together now
        int bestArea = 0;
        for(int i=0; i<heights.size(); i++) {
            int proposedArea = heights[i]*(bestLeftwards[i] + bestRightwards[i] + 1);
            if(proposedArea > bestArea) {
                bestArea = proposedArea;
            }
        }

        return bestArea;
    }
}
