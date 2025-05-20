#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int EMPTY = NULL; // 用 NULL 代表沒有節點
class TreeNode {
public:
    int value;// 節點值
    TreeNode* left;// 左子節點
    TreeNode* right;// 右子節點

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}//初始化節點
};

class BinaryTree {
public:
    TreeNode* root;// 樹根節點

    BinaryTree() : root(nullptr) {}

    TreeNode* buildTree(const vector<int>& arr) {// 建立樹
        if (arr.empty() || arr[0] == EMPTY) return nullptr;

        queue<TreeNode**> q;//建立queue儲存待處理的節點指標
        root = new TreeNode(arr[0]);// 建立根節點 (陣列第一個元素)
        q.push(&root);// 將根節點的指標加入queue

        size_t i = 1;// 陣列索引
        while (!q.empty() && i < arr.size()) {
            TreeNode** nodePtr = q.front();// 取出queue的第一個節點指標
            q.pop();// 將該節點從queue中刪除

            // 左子節點
            if (i < arr.size()) {
                if (arr[i] != EMPTY) {
                    (*nodePtr)->left = new TreeNode(arr[i]);// 添加左子節點
                    q.push(&((*nodePtr)->left));// 將左子節點的指標加入queue
                }
                i++;
            }
            // 右子節點
            if (i < arr.size()) {
                if (arr[i] != EMPTY) {
                    (*nodePtr)->right = new TreeNode(arr[i]);// 添加右子節點
                    q.push(&((*nodePtr)->right));// 將右子節點的指標加入queue
                }
                i++;
            }
        }
        return root;
    }

    void Depth_first_search(TreeNode* node) {//深度優先搜尋
        if (node == nullptr) return;
        cout << node->value << " ";// 訪問當前節點的值
        Depth_first_search(node->left);// 遞迴遍歷左子樹
        Depth_first_search(node->right);// 遞迴遍歷右子樹
    }

    void Breadth_first_search(TreeNode* root) {
        if (root == nullptr) return;
        queue<TreeNode*> q;//建立queue儲存待處理的節點指標
        q.push(root); // 將根節點的指標加入queue

        while (!q.empty()) {
            TreeNode* current = q.front();// 取出queue的第一個節點指標
            q.pop();// 將該節點從queue中刪除
            cout << current->value << " ";
            if (current->left) q.push(current->left);  // 將左子節點的指標加入queue
            if (current->right) q.push(current->right);// 將左子節點的指標加入queue
        }
    }

    // 計算layer總和
    bool levelSum(TreeNode* root, int layer, int& levelsum) {
        queue<TreeNode*> q;
        q.push(root);
        int level = 0; // 目前層數
        levelsum = 0; // 初始化總和

        while (!q.empty()) {
            int levelsize = q.size(); // 目前層數的節點數量

            for (int i = 0; i < levelsize; ++i) {
                TreeNode* node = q.front();
                q.pop();

                // 如果目前層數是要查詢的層數
                if (level == layer) {
                    // 就把這層所有的數加起來
                    levelsum += node->value;
                }

                // 把這一層的子節點先加進queue，這樣下一次while才有節點可以處理
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            // 如果剛剛處理的是要查詢的層數，就回傳加總完了
            if (level == layer) return true;

            level++; // 到下一層
        }

        return false; // 如果層數超過樹高
    }
};

int main() {
    BinaryTree tree;
    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, NULL, NULL, 10, 11, NULL, NULL };
    tree.buildTree(arr);

    //cout << "DFS Result: ";
    //tree.Depth_first_search(tree.root);
    //cout << endl;

    cout << "BFS Result: ";
    tree.Breadth_first_search(tree.root);
    cout << endl;

    int layer;
    cout << "請輸入要查詢的層數（從 0 開始）: ";
    cin >> layer;

    int levelsum;
    if (tree.levelSum(tree.root, layer, levelsum)) {
        cout << "第 " << layer << " 層的總和為: " << levelsum << endl;
    }
    else {
        cout << "超過樹高" << endl;
    }

    system("pause");
    return 0;
}
