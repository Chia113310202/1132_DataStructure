class Solution {
public:
	vector<int> runningSum(vector<int>& nums) {
		int n =nums.size();//陣列長度 
		vector<int> result(n);//vector<int>是動態陣列,在執行分配記憶體時,可以根據 num.size()自動調整大小
		
		result[0]=nums[0];// 第一個 nums就是result[0]，因為還沒有其他數字要加在一起 
		// i=1是因為第一項 result[0]=nums[0]，所以從第二項開始 
		for(int i=1; i<n; i++){ 
			result[i]=result[i-1]+nums[i];//新的 result是前一個 result加上現在的數字 
		}
		return result;//回傳數值 
	}
};
