class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1;         // nums1的最後一個位置
        int j = n - 1;         // nums2的最後一個位置
        int k = m + n - 1;     // nums1的最後一個位置（包含預留給nums2）

        // 從後面開始往前比較兩個array的值，比較大的就填到nums1[k]的尾巴
        while (i >= 0 && j >= 0) {
            if (nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--]; // i和k要往前一個
            } else {
                nums1[k--] = nums2[j--];
            }
        }

        // 如果nums2還有剩下，就補到nums1前面
        while (j >= 0) {
            nums1[k--] = nums2[j--];
        }
    }
};
