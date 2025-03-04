// Method 1
class Solution {
public:
	vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
		int count[101]={0};//計數陣列,範圍 0-100  //Count=1 (assignment)
		int n=num.size();//陣列長度  //Count=1 
		vector<int> result(n);//vector<int>是動態陣列,在執行分配記憶體時,可以根據 num.size()自動調整大小  //Count=1 

	//計算每個數字的出現次數,此迴圈遍歷 nums,並統計每個數字 num 出現的次數
	for(int num:nums){ count[num]++;} //Count=2 (Array access + addition)
	
	//計算比當前數字小的數量
	for(int i=1; i<101; i++){
		// Loop initialization: Count = 1 (assignment i = 1)
		// Each iteration:
		// - Comparison: Count = 1 (i < 101)
		// - Increment: Count = 1 (i++)
		count[i]+=count[i-1]; //Count=3 (Array access*2 + addition)
	}
	
	//計算 result 陣列
	for(int i=0; i<n; i++){
		// Loop initialization: Count = 1 (assignment i = 0)
		// Each iteration:
		// - Comparison: Count = 1 (i < n)
		// - Increment: Count = 1 (i++)
		result[i]=(nums[i]==0)?0:count[nums[i]-1]; //Count=2 (Array access + Comparisons)
	//count[nums[i]-1]代表比 nums[i]小的數的數量,nums[i]==0 時則直接返回 0
	}
	return result; //Count = 1 (return)
}
// 3 (initial) 
// + n * 2 (第一個 for迴圈loop operations)
// + n * 3 (第二個 for迴圈loop operations)
// + n * 2 (第三個 for迴圈loop operations)
// + 1 (return) 
// = 7n + 4 

_______________________________________________________________________________________
// Method 2
class Solution {
public:
	vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
		vector<int> result; // 存結果  //Count = 1
		int count; // 計數器  //Count = 1

		// 外層迴圈遍歷 nums 陣列中的每個元素
		for (int i = 0; i < nums.size(); i++) {
			// Loop initialization: Count = 1 (assignment i = 0)
			// Each iteration:
			// - Comparison: Count = 1 (i < nums.size())
			// - Increment: Count = 1 (i++)
			count = 0; // 每次重新計算當前元素的較小數量  
					   //Count = 1 (assignment)

			// 內層迴圈再次遍歷 nums 陣列,統計比 nums[i] 小的元素數量
			for (int j = 0; j < nums.size(); j++) {
				// Loop initialization: Count = 1 (assignment j = 0)
				// Each iteration:
				// - Comparison: Count = 1 (j < nums.size())
				// - Increment: Count = 1 (j++)
				if (nums[j] < nums[i]) { count++; } // 如果nums[j]比nums[i]小,則計數器+1
				//Count = 2 (Comparisons + addition)
			}
			result.push_back(count); // 將計算出的數量存入 result  
									 //Count = 1
		}
		return result; //Count = 1 (return)
	}
};
// 2 (initial) 
// + [n * 1 (loop operations) + 1]*[n * 2 (loop operations) + 1]
// + n (result.push_back(count))
// + 1 (return) 
// = 2n^2 + 4n + 4
