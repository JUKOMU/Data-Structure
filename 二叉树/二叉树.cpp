#include <iostream>
#include <cmath>
#include <queue>
#include <Windows.h>
#include <string>
using namespace std;
using std::cout;
using std::cin;
using std::endl;


// 光标居中
void middleCursor(string str) {
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    GetConsoleScreenBufferInfo(hOutput, &bInfo);
    int dwSizeX = bInfo.dwSize.X;
    int dwSizeY = bInfo.dwSize.Y;
    int len = str.length();
    int x = dwSizeX / 2 - len / 2;
    for (int i = 0; i < x; i++) {
        cout << " ";
    }
}




// 二叉树的节点结构体

class TreeNote
{
public:
    int data;
    TreeNote* left_child;
    TreeNote* right_child;
    TreeNote(int data) {
        this->data = data;
        this->left_child = nullptr;
        this->right_child = nullptr;
    }
};


class BinaryTree
{
private:
    
    int layer; // 记录层数
    int size; // 记录二叉树最后一层节点个数
    // 添加一个节点
    void add(TreeNote* note, int temp_layer) {
        if (note->left_child == nullptr && temp_layer == layer) {
            int temp;
            cin >> temp;
            if (temp != NULL) {
                TreeNote* new_node = new TreeNote(temp);
                note->left_child = new_node;
                this->size += 1;
            }
        }
        if (note->right_child == nullptr && temp_layer == layer) {
            int temp;
            cin >> temp;
            if (temp != NULL) {
                TreeNote* new_node = new TreeNote(temp);
                note->right_child = new_node;
                this->size += 1;
                return;
            }
        }
        add(note->left_child, temp_layer + 1);
        add(note->right_child, temp_layer + 1);
    }

public:
    TreeNote* root;

    // 构造函数
    BinaryTree(int root_data) {
        this->root = new TreeNote(root_data);
        this->size = 1;
        this->layer = 1;
    }

    // 添加一层节点
    void addNote() {
        cout << "请输入第" << layer+1 << "层的节点数据(NULL表示为空节点)，您需要输入" << 2*size << "个数据，每个数据间用空格隔开：" << endl;
        this->size = 0;
        add(root,1); // 进入该层来添加节点
        this->layer += 1; // 层数加1
    }
    
    // 前序遍历二叉树
    void preOrder(TreeNote* root) {
        if (root == nullptr) {
            return;
        }
        cout << root->data << " ";
        preOrder(root->left_child);
        preOrder(root->right_child);
    }

    // 中序遍历二叉树
    void inOrder(TreeNote* root) {
        if (root == nullptr) {
            return;
        }
        inOrder(root->left_child);
        cout << root->data << " ";
        inOrder(root->right_child);
    }
    // 后序遍历二叉树
    void postOrder(TreeNote* root) {
        if (root == nullptr) {
            return;
        }
        postOrder(root->left_child);
        postOrder(root->right_child);
        cout << root->data << " ";
    }

    // 非递归遍历二叉树，并统计节点数、叶子节点数、度为1和度为2的节点数，以及最大值和最小值
    void traversal(TreeNote* root) {
        std::queue<TreeNote*> q;
        q.push(root);
        int nodeCount = 0, leafCount = 0, degree1Count = 0, degree2Count = 0, maxValue = INT_MIN, minValue = INT_MAX;
        while (!q.empty()) {
            TreeNote* note = q.front();
            q.pop();
            nodeCount++;
            if (note->left_child == nullptr && note->right_child == nullptr) {
                leafCount++;
            }
            else if (note->left_child == nullptr || note->right_child == nullptr) {
                degree1Count++;
            }
            else {
                degree2Count++;
            }
            maxValue = max(maxValue, note->data);
            minValue = min(minValue, note->data);
            if (note->left_child != nullptr) {
                q.push(note->left_child);
            }
            if (note->right_child != nullptr) {
                q.push(note->right_child);
            }
        }
        cout << "节点数：" << nodeCount << endl;
        cout << "叶子节点数：" << leafCount << endl;
        cout << "度为1的节点数：" << degree1Count << endl;
        cout << "度为2的节点数：" << degree2Count << endl;
        cout << "最大值：" << maxValue << endl;
        cout << "最小值：" << minValue << endl;
    }

    // 按层次顺序遍历二叉树
    void levelOrder(TreeNote* root) {
        if (root == nullptr) {
            return;
        }
        std::queue<TreeNote*> q;
        q.push(root);
        int o = 0; // 记录层数
        while (!q.empty()) {
            int levelSize = q.size();
            string str = "";
            for (int k = 0; k<int(pow(2, o)*2-1); k++) {
                str += "a";
            }
            middleCursor(str);
            for (int i = 0; i < levelSize; i++) {
                TreeNote* node = q.front();
                q.pop();
                cout << node->data << " ";
                if (node->left_child != nullptr) {
                    q.push(node->left_child);
                }
                if (node->right_child != nullptr) {
                    q.push(node->right_child);
                }
            }
            cout << endl;
            o += 1;
        }
    }
};



// 打印提示信息
int chooseOperation() {
    int flag;
    cout << "请选择要进行的操作：0(结束程序),1(继续添加节点),2(先序历遍),3(中序历遍),4(后续历遍),5(非递归历遍),6(按层次顺序历遍)：";
    cin >> flag;
    return flag;
}


int main() {
    int flag = 1;
    BinaryTree tree = BinaryTree(1);
    tree.addNote();
    flag = chooseOperation();
    while (flag != 0) {
        if (flag == 1) {
            tree.addNote();
            cout << endl;
            flag = chooseOperation();
            continue;
        }
        if (flag == 2) {
            cout << "先序遍历结果：" << endl;
            tree.preOrder(tree.root);
            cout << endl;
            flag = chooseOperation();
            continue;
        }
        if (flag == 3) {
            cout << "中序遍历结果：" << endl;
            tree.inOrder(tree.root);
            cout << endl;
            flag = chooseOperation();
            continue;
        }
        if (flag == 4) {
            cout << "后序遍历结果：" << endl;
            tree.postOrder(tree.root);
            cout << endl;
            flag = chooseOperation();
            continue;
        }
        if (flag == 5) {
            cout << "非递归遍历结果：" << endl;
            tree.traversal(tree.root);
            cout << endl;
            flag = chooseOperation();
            continue;
        }
        if (flag == 6) {
            cout << "按层次顺序遍历结果：" << endl;
            tree.levelOrder(tree.root);
            cout << endl;
            flag = chooseOperation();
            continue;
        }
        if (flag > 6) {
            cout << endl;
            flag = chooseOperation();
            continue;
        }
    }
    return 0;
}
