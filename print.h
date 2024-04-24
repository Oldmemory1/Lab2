#ifndef print_h
#define print_h

#include <iostream>
#include <string>
using namespace std;
// 打印运算符对应的汇编代码
void print_opt(string opt)
{
    string operation;
    if (opt == "+")
        operation = "add"; // 加法运算
    else if (opt == "-")
        operation = "sub"; // 减法运算
    else if (opt == "*")
        operation = "imul"; // 乘法运算
    else if (opt == "/")
        operation = "idiv"; // 除法运算
    else if (opt == "%")
        operation = "mod1"; // 取模运算
    else if (opt == "<")
    {
        operation = "cmp"; // 比较运算
    }
    else if (opt == "<=")
        operation = "cmp";
    else if (opt == ">")
        operation = "cmp";
    else if (opt == ">=")
        operation = "cmp";
    else if (opt == "==")
        operation = "cmp";
    else if (opt == "!=")
        operation = "cmp";
    else if (opt == "&")
    {
        operation = "and"; // 与运算
    }
    else if (opt == "|")
    {
        operation = "or"; // 或运算
    }
    else if (opt == "^")
    {
        operation = "xor"; // 异或运算
    }

    cout << "pop ebx " << endl; // 弹出栈顶元素到 ebx 寄存器
    cout << "pop eax " << endl; // 弹出栈顶元素到 eax 寄存器
    if (operation == "idiv")
    {                                         // 如果是除法运算
        cout << "cdq" << endl;                // 扩展 eax 到 edx：eax 以准备进行除法运算
        cout << operation << " ebx " << endl; // 进行除法运算
    }
    else if (operation == "mod1")
    {
        cout << "cdq" << endl;          // 扩展 eax 到 edx：eax 以准备进行除法运算
        cout << "idiv ebx" << endl;     // 进行除法运算
        cout << "mov eax, edx" << endl; // 取余数
    }

    else if (operation == "cmp")
    {
        cout << "cmp eax, ebx " << endl; // 在 eax 和 ebx 之间进行运算
        if (opt == "<")
            cout << "setl al" << endl;
        else if (opt == "<=")
            cout << "setle al" << endl;
        else if (opt == ">")
            cout << "setg al" << endl;
        else if (opt == ">=")
            cout << "setge al" << endl;
        else if (opt == "==")
            cout << "sete al" << endl;
        else if (opt == "!=")
            cout << "setne al" << endl;

        cout << "movsx eax, al" << endl;
    }
    else
    {                                              // 其他运算
        cout << operation << " eax, ebx " << endl; // 在 eax 和 ebx 之间进行运算
    }

    cout << "push eax " << endl; // 将运算结果压入栈中
}


#endif