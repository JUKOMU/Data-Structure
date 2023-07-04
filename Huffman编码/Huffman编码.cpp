#include <iostream>
#include <cmath>
#include <queue>
#include <Windows.h>
#include <string>
using namespace std;
using std::cout;
using std::cin;
using std::endl;




// 栈节点
class StackNode
{
public:
    string letter;
    int rate;
    StackNode* next;
    StackNode(string letter, int rate) {
        this->letter = letter;
        this->rate = rate;
        this->next = nullptr;
    }
};

// 栈类
class Stack {
public:
    StackNode* top; // 栈顶
    // 构造函数
    Stack(string letter, int rate) {
        StackNode* Node = new StackNode(letter, rate);
        this->top = Node;
    }

    void push(string letter, int rate) {
        StackNode* new_Node = new StackNode(letter, rate);
        new_Node->next = this->top;
        this->top = new_Node;
    }

    StackNode* pop() {
        StackNode* temp = new StackNode(this->top->letter, this->top->rate); // 拷贝栈顶元素
        temp->next = this->top; // 记录栈顶元素地址
        this->top = this->top->next; // 栈顶指针后移
        delete temp->next; // 删除弹出的栈顶元素
        return temp; // 返回栈顶元素的拷贝
    }
};



// 二叉树的节点结构体

class TreeNode
{
public:
    string letter;
    string encode;
    TreeNode* left_child;
    TreeNode* right_child;
    TreeNode* super;
    TreeNode(string letter, string encode) {
        this->letter = letter;
        this->encode = encode;
        this->left_child = nullptr;
        this->right_child = nullptr;
        this->super = nullptr;
    }
};


class BinaryTree
{
private:

    int layer; // 记录层数
    int size; // 记录二叉树最后一层节点个数

public:
    TreeNode* root;

    // 构造函数
    BinaryTree() {
        this->root = new TreeNode("root", "0");
        this->layer = 1;
    }

    void add(string letter) {
        // 最后一层节点
        if (root->left_child == nullptr || root->right_child == nullptr) {
            // 判断是否为初始根节点
            if (root->letter == "root") {
                TreeNode* Node = new TreeNode(letter, "0");
                delete root; // 释放初始根节点
                root = Node; // 设置根节点为新节点，且新节点为右节点
            }
            else {
                TreeNode* Node = new TreeNode(letter, "1"); // 这是最后一层的左节点
                TreeNode* super_Node = new TreeNode(root->letter + letter, "0"); // 设置父节点
                root->super = super_Node;
                Node->super = super_Node;
                super_Node->left_child = Node;
                super_Node->right_child = root;
                root = super_Node; // 将根节点设置为父节点
            }
        }
        // 不是最后一层节点，则新节点为左节点
        else {
            TreeNode* Node = new TreeNode(letter, "1");
            TreeNode* super_Node = new TreeNode(root->letter + letter, "0"); // 设置父节点
            root->super = super_Node;
            Node->super = super_Node;
            super_Node->left_child = Node;
            super_Node->right_child = root;
            root = super_Node; // 将根节点设置为父节点
        }
    }

    void levelOrder(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        std::queue<TreeNode*> q;
        q.push(root);
        int o = 0; // 记录层数
        while (!q.empty()) {
            int levelSize = q.size();
            string str = "";
            for (int k = 0; k<int(pow(2, o) * 2 - 1); k++) {
                str += "a";
            }
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                cout << node->letter << " "<<node->encode<<"  ";
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

    void printLetter(string str) {
        int n = str.length();
        char zero = '0';
        TreeNode* node = this->root;
        for (int i = 0; i < n; i++) {
            if (str[i] == zero) {
                node = node->right_child;
                if (i == n - 1) {
                    cout << node->letter;
                }
            }
            else {
                node = node->left_child;
                cout << node->letter;
            }
        }
    }

    string getEncode(char codex) {
        string encode = "";
        string code;
        code = codex;
        TreeNode* node = this->root;
        while (node->right_child != nullptr) {
            if (node->left_child->letter == code) {
                encode += "1";
                break;
            }
            else {
                node = node->right_child;
                encode += "0";
            }
        }
        return encode;
    }

    void getCode(string encode) {
        int n = encode.length();
        char zero = '0';
        TreeNode* node = this->root;
        for (int i = 0; i < n; i++) {
            if (encode[i] == zero) {
                node = node->right_child;
                if (node->right_child==nullptr) {
                    cout << node->letter;
                    node = this->root;
                }
            }
            else {
                node = node->left_child;
                cout << node->letter;
                node = this->root;
            }
        }
    }
};


int main()
{
    int rate[27] = { 186,64,13,22,32,103,21,15,47,57,1,5,32,20,57,63,15,1,48,51,80,23,8,18,1,16,1 }; // 频数
    int visit[27] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }; // 记录是否已被访问
    string tempt_letter = "";
    int tempt_rate = 0;
    BinaryTree tree = BinaryTree();
    // 频数最小的元素入栈
    for (int i = 0; i < 27; i++) {
        if (rate[i] == 1){
            tempt_letter = char(i + 96);
            tempt_rate = rate[i];
            visit[i] = 1;
        }
    }

    tree.add(tempt_letter); // 添加第一个底层节点

    bool flag = true;

    while (flag) {

        int prv = 0;
        int tempt = prv + 1;

        while (tempt < 27) {

            if (visit[prv] == 1) {
                prv++;
                tempt++;
                continue;
            }
            if (visit[tempt] == 1) {
                tempt++;
                continue;
            }


            if (rate[prv] > rate[tempt]) {
                prv = tempt;
                tempt++;
                continue;
            }
            else {
                tempt++;
            }
        }

        tempt_letter = char(prv + 96);
        tempt_rate = rate[prv];
        visit[prv] = 1;
        tree.add(tempt_letter);

        flag = false;
        for (int i = 0; i < 27; i++) {
            if (visit[i] == 0) {
                flag = true;
            }
        }
        
    }

    tree.levelOrder(tree.root);

    string test = "00000000000000000000000";
    tree.printLetter(test);
    cout << endl;

    /*string code = "i`hate`your`group`so`much`i`have`a`sexual`addiction`and`you`are`sending`pictures`to`hook`my`soul`like`this`i`am`like`the evil spirit`in`hell`burning`with`desire`and`unable`to`extricate`myself`when`i`enter`the`group`at`night`and`see`the`pictures`you`posted`my`previous`efforts`are`ruined`i`cry`i`mourn`this`damn`group`has`kidnapped`my`health`and`kept`me`from`getting`rid`of`this`damn`sex`addiction`for`a`long`time`the`most`important`thing`is`i`am`still`a`fucking`virgin";*/
    string code = "i`hate`your`group`so`much`i`have`a`sexual`addiction`and`you`are`sending`pictures`to`hook`my`soul`like`this`i`am`like`the evil spirit`in`hell`burning`with`desire`and`unable`to`extricate`myself`when`i`enter`the`group`at`night`and`see`the`pictures`you`posted`my`previous`efforts`are`ruined`i`cry`i`mourn`this`damn`group`has`kidnapped`my`health`and`kept`me`from`getting`rid`of`this`damn`sex`addiction`for`a`long`time`the`most`important`thing`is`i`am`still`a`fucking`virgin";
    string encode = "";
    cout << "原码:" << code << endl;
    cout << "编码:";
    for (int i = 0; i < code.length(); i++) {
        cout << tree.getEncode(code[i]);
    }
    cout << "" << endl;

    string encode2 = "0000001100000000010001001011000000000000000001000010000000000001000000001100000000000000000001000000001000010000000000001000000000000000000110000000100001100000000000000010000000000001000000000000010000000001100000011000000000100010000000000000000000001011000110000000101000000000000000000000000000000000001000100000000001100010000000000010000000000010000001000000000000010010000001000010000011000100000100000000000110000000000000000010000100000000000011000100000000101100000001010000010000000000010000001000001000000000000000000011000000000000000000100000010000000000000100100000000000010000000010100000001100100001100000000010000100001000000000000000000000011000000000000000100000000000000000110000000100001000000000000100000000001100000000001000000100000000000000000000001011001000000000100000010000000110000001100010000000000000001100000000001000000100000000000000000000001011001000000000101000000000000000000000000100000000000000000000010000001000000000010000000000000000000000000000001000000000000000000100000010000000010000001001100000010000011000000000101000000000010000000000110000000000000000000010000000000001000000001000001000000100000100000000000000000001100000000000000001000000100100000000011000000000001010000000100000010000000010110001000001000000000001100000000000010000010001000000000000000000001000000000010110010000110100000000000000000000000001000000001000000100000000000001000100101100000000000000010000000000000000010000000101000000000010000000000000011000000000000000010000000001010000011000000110100000100101000000001100100000000010110000000000000000000100000000100001000000000000100000000000000000011000100110000010000001000000000000000000010000000001001100010000010000000000011000000010101100100000000010110000000000000000001000000100000000000001001000000000000100000000101000000011000000000000000001000010000000000001100000000000000000010000100000001001010000000000011000000000000000100000000000000000110000000000000000001000000001010000000000000000000001000000100001000000000000100000001101000000000000001000000000000001000010000000010010000000110001000000001011000000001000000000000100000010000010100000000000110000001100000000000001000000001000000000000000001100000011000000000000000100001000000000000100000000100000110010000000001000000100000001100000000000100010000000000000001000001100000000000000000001000000001000010000000000001000000000000000000110000000001000100000001100000000000000000000001000000100000000000100000100010000000000000000001000000000000000000101000000000001100000000000000010000000000000000011000000000101000100000000001001000000000110001000001000000000001100000000000000000000001010000000000000000001001100000000000000010110000000000000010000000010000100000000000000011000000000000000000010100100100000010000010000000000000000000110000000010000001000000000001100001000000000000001100100000000010000001000000011000000000001000100000000000000010000011000000010100000000000000000000000100010000000000010000000000010000001000000000000010010000001000010000011000000000000001000010000000011000110000000000100001000001000000000000000000011001000000100000000000000010110010000000001011000000000000000100001000000010011000000100000000000000010000000000000000001000010000000010010001000001001100100000000010000001000001000000000000000000011000000100000001100000011000100000000000000011000000010010000001000000000010000000000110001100000000000000100000000000010000000000000100000000000000000000001000000100000100000000000000000001100000000000000000000010000001000000001000000000000000000010000001000001";

    tree.getCode(encode2);
}