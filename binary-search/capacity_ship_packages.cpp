class Solution {
public:
int daysNeeded(vector<int>& weights, int capacity) {
        // Initialize count of days to 1 (start with day one)
        int days = 1;

        // Variable to track the current load on the ship for a day
        int currentLoad = 0;

        // Loop through each package weight in the array
        for (int w : weights) {
            // Check if adding current package exceeds ship capacity for the day
            if (currentLoad + w > capacity) {
                // Need a new day to ship this package, so increment day count
                days++;

                // Start new day's load with current package weight
                currentLoad = w;
            } else {
                // If capacity not exceeded, add current package weight to the day's load
                currentLoad += w;
            }
        }

        // Return total number of days needed with this capacity
        return days;
    }
    int shipWithinDays(vector<int>& weights, int days) {
         int left = *max_element(weights.begin(), weights.end());

        // Calculate the sum of all package weights as maximum capacity (ship all at once)
        int right = accumulate(weights.begin(), weights.end(), 0);

        // Binary search loop to find optimal capacity between left and right
        while (left < right) {
            // Calculate mid value as potential capacity to test
            int mid = left + (right - left) / 2;

            // Calculate how many days needed if ship capacity is mid
            int needed = daysNeeded(weights, mid);

            // If days needed is less or equal to allowed days,
            // try to reduce capacity by moving right boundary
            if (needed <= days) {
                right = mid;
            } else {
                // If days needed is more than allowed, increase capacity by moving left boundary
                left = mid + 1;
            }
        }

        // Left is now the minimum capacity that can ship packages within d days
        return left;
    }
    
};