#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
struct nodeInfo {
    int x, y, num;
    nodeInfo* left;
    nodeInfo* right;
    nodeInfo(int x, int y, int num) {
        this->x = x, this->y = y, this->num = num;
        this->left = this->right = NULL;
    }
};
nodeInfo* Tree;
void insertTree(nodeInfo* node, nodeInfo* newnode) {
    if (node->x < newnode->x) {
        if (node->right == NULL)
            node->right = newnode;
        else
            insertTree(node->right, newnode);
    }
    else {
        if (node->left == NULL)
            node->left = newnode;
        else
            insertTree(node->left, newnode);
    }
}
bool cmp(nodeInfo& a, nodeInfo& b) {
    if (a.y == b.y)
        return a.x < b.x;
    return a.y > b.y;
}
vector<int> order;
void preorder(nodeInfo* node) {
    if (node == NULL) return;
    order.push_back(node->num);
    preorder(node->left);
    preorder(node->right);
}
void postorder(nodeInfo* node) {
    if (node == NULL) return;
    postorder(node->left);
    postorder(node->right);
    order.push_back(node->num);
}
vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;
    vector<nodeInfo> node;
    for (int i = 0; i < nodeinfo.size(); i++)
        node.push_back(nodeInfo(nodeinfo[i][0], nodeinfo[i][1], i + 1));
    sort(node.begin(), node.end(), cmp);
    Tree = &node[0];
    for (int i = 1; i < node.size(); i++)
        insertTree(Tree, &node[i]);
    preorder(Tree);
    answer.push_back(order);
    order.clear();
    postorder(Tree);
    answer.push_back(order);
    return answer;
}
int main()
{
    vector<vector<int>> nodeinfo = { {5,3},{11,5},{13,3},{3,5},{6,1},{1,3},{8,6},{7,2},{2,2} };
    vector<vector<int>> ans = solution(nodeinfo);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < ans[i].size(); j++)
            cout << ans[i][j] << " ";
        cout << "\n";
    }
}
