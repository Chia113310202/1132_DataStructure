class Solution {
public:
    int findLucky(vector<int>& arr) {
        int largestLucky = -1;//先設-1代表還沒找到 // Count = 1 (assignment)

        for(int i=1; i < arr.size(); i++)
        // Loop initialization: Count = 1 (assignment i = 1)
		// Each iteration:
		// - Comparison: Count = 1 (i < arr.size())
		// - Increment: Count = 1 (i++)
        {
            int count=0;//記錄出現幾次 // Count = 1 (assignment)
			
			//計算數字出現幾次 
            for(int j=0; j < arr.size(); j++)
            // Loop initialization: Count = 1 (assignment j = 0)
			// Each iteration:
			// - Comparison: Count = 1 (j < arr.size())
			// - Increment: Count = 1 (j++)
            {
                if(arr[i] == arr[j]) // Count = 1 (comparison)
                {
                    count++; // Count = 1 (addition)
                }
            }

            if(arr[i] == count) // Count = 1 (comparison)
            {
                if(arr[i] > largestLucky)//找最大值 // Count = 1 (comparison)
                {
                    largestLucky = arr[i]; // Count = 1 (assignment)
                }
            }
        }
        return largestLucky; // Count = 1 (return)
    }
};
// 1 (initial) +  (n + 3)*(2n + 2) + 3 + 1 (return)
// = 2n^2 + 8n + 11
