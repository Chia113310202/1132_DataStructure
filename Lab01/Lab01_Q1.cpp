class Solution {
public:
    bool isMonotonic(vector<int>& nums) 
    {
        bool increasing = true, decreasing = true; // count=2

        for (int i = 1; i < nums.size(); i++) 
        {
        // Count=1 (assignment i = 1)
		    // Count=1 (Comparison i < nums.size())
		    // Count=1 (i++)
			      //遞增
            if (nums[i] > nums[i - 1]) // count=1
                decreasing = false; // count=1
            //遞減
            if (nums[i] < nums[i - 1]) // count=1
                increasing = false; // count=1
            if (increasing == false && decreasing == false) // count=1 (Comparison)
                return false; // count=1
        }
        return true; // count=1
    }
};  
// 3 (initial) + n*7 (loop operations) + 2 (return)
// = 7n + 5
