#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>

using namespace std;

namespace BurstBalloons {
	static int maxCoins(vector<int>& nums) {
        int maxCoinsBetween[nums.size()][nums.size()];

		for (int incr = 0; incr < nums.size(); incr++) {
			for (int start = 0; start < nums.size() - incr; start++) {
				int end = start + incr;

				int left = start == 0 ? 1 : nums[start-1];
				int right = end == nums.size() - 1 ? 1 : nums[end+1];

				if(start == end) {
					maxCoinsBetween[start][end] = left * nums[start] * right;
				}
				else {
					int max = 0;

					// pick somewhere to do last
					for (int i=start; i<=end; i++) {
						int proposedValue = left * nums[i] * right;
						if(i-1 >= start)
							proposedValue += maxCoinsBetween[start][i-1];
					    if(i+1 <= end)
							proposedValue += maxCoinsBetween[i+1][end];

						if(proposedValue > max)
							max = proposedValue;
					}
					maxCoinsBetween[start][end] = max;
				}
			}
		}

		return maxCoinsBetween[0][nums.size()-1];
    }

}
