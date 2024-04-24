#include <iostream>      // 包含输入输出流库
#include <fstream>       // 包含文件流库
#include <vector>        // 包含向量库
#include <string>        // 包含字符串库
#include <unordered_map> // 包含无序映射库
#include <stack>         // 包含栈库
#include <sstream>       // 包含字符串流库
#include <map>           // 包含映射库
#include "tokens.h"      // 包含 tokens.h 头文件
#include "print.h"       // 包含 print.h 头文件

using namespace std;




// 词法分析器类
class Lexer
{
private:
    ifstream inputFile;                        // 输入文件流
    unordered_map<string, TokenType> keywords; // 关键字映射表

public:
    Lexer(const string &filename)
    {

        inputFile.open(filename); // 打开指定文件

        keywords["int"] = TokenType::KEYWORD_INT;       // 整型关键字
        keywords["return"] = TokenType::KEYWORD_RETURN; // 返回关键字
        keywords["main"] = TokenType::KEYWORD_MAIN;     // 主函数关键字
        keywords["println_int"] = TokenType::PRINT;     // 输出关键字
    }

    ~Lexer()
    { // 析构函数，关闭文件流
        if (inputFile.is_open())
            inputFile.close(); // 如果文件流处于打开状态，则关闭文件流
    }

    // 从文件中读取一个 Token
    Token getNextToken()
    {                // 读取并返回下一个 Token
        Token token; // 定义一个 Token 对象
        char ch;     // 定义一个字符变量

        // 读取一个字符
        inputFile.get(ch); // 从文件中读取一个字符

        // 确定 Token 的类型
        if (isalpha(ch) || ch == '_')
        { // 如果是字母
            string word;
            while (isalpha(ch) || isdigit(ch) || ch == '_')
            {                      // 读取连续的字母或数字
                word += ch;        // 将字符添加到单词中
                inputFile.get(ch); // 读取下一个字符
            }

            inputFile.putback(ch); // 将读取的多余字符放回输入流
            if (keywords.find(word) != keywords.end())
            {
                token.type = keywords[word]; // 如果是关键字，则设置 Token 类型为关键字类型
            }
            else
            {
                token.type = TokenType::IDENTIFIER; // 否则设置为标识符类型
            }
            token.value = word; // 设置 Token 的值为单词
        }
        else if (isdigit(ch))
        { // 如果是数字
            string number;
            while (isdigit(ch))
            {                      // 读取连续的数字
                number += ch;      // 将字符添加到数字字符串中
                inputFile.get(ch); // 读取下一个字符
            }
            inputFile.putback(ch);            // 将读取的多余字符放回输入流
            token.type = TokenType::CONSTANT; // 设置 Token 类型为常量类型
            token.value = number;             // 设置 Token 的值为数字字符串
        }
       
        else if (ch == '+')
        {                                     // 如果是加号
            token.type = TokenType::OPERATOR; // 设置 Token 类型为运算符类型
            token.value = "+";                // 设置 Token 的值为加号
        }
        else if (ch == '-')
        {                                     // 如果是减号
            token.type = TokenType::OPERATOR; // 设置 Token 类型为运算符类型
            token.value = "-";                // 设置 Token 的值为减号
        }
        else if (ch == '*')
        {                                     // 如果是乘号
            token.type = TokenType::OPERATOR; // 设置 Token 类型为运算符类型
            token.value = "*";                // 设置 Token 的值为乘号
        }
        else if (ch == '/')
        {                                     // 如果是除号
            token.type = TokenType::OPERATOR; // 设置 Token 类型为运算符类型
            token.value = "/";                // 设置 Token 的值为除号
        }
        else if (ch == '(' || ch == ')')
        {                                     // 如果是左括号或右括号
            token.type = TokenType::OPERATOR; // 设置 Token 类型为运算符类型
            token.value = ch;                 // 设置 Token 的值为左括号或右括号
        }
        else if (ch == ';')
        {                                      // 如果是分号
            token.type = TokenType::DELIMITER; // 设置 Token 类型为分隔符类型
            token.value = ";";                 // 设置 Token 的值为分号
        }
        else if (inputFile.eof())
        {                                // 如果是文件末尾
            token.type = TokenType::END; // 设置 Token 类型为结束符类型
        }
        else if (ch == '=')
        {
            string word;
            word += ch;
            inputFile.get(ch);
            if (ch == '=')
            {
                word += ch;
                token.type = TokenType::OPERATOR; // 设置 Token 类型为运算符类型
                token.value = word;               // 设置 Token 的值为等于号
            }
            else
            {
                token.type = TokenType::OPERATOR; // 设置 Token 类型为运算符类型
                token.value = word;               // 设置 Token 的值为赋值号
                inputFile.putback(ch);            // 将读取的多余字符放回输入流
            }
        }

        else if (ch == '<')
        {
            string word;
            word += ch;
            inputFile.get(ch);
            if (ch == '=')
            {
                word += ch;
                token.type = TokenType::OPERATOR; // 设置 Token 类型为运算符类型
                token.value = word;               // 设置 Token 的值为小于等于号
            }
            else
            {
                token.type = TokenType::OPERATOR; // 设置 Token 类型为运算符类型
                token.value = word;               // 设置 Token 的值为小于号
                inputFile.putback(ch);            // 将读取的多余字符放回输入流
            }
        }
        else if (ch == '>')
        {
            string word;
            word += ch;
            inputFile.get(ch);
            if (ch == '=')
            {
                word += ch;
                token.type = TokenType::OPERATOR; // 设置 Token 类型为运算符类型
                token.value = word;               // 设置 Token 的值为大于等于号
            }
            else
            {
                token.type = TokenType::OPERATOR; // 设置 Token 类型为运算符类型
                token.value = word;               // 设置 Token 的值为大于号
                inputFile.putback(ch);            // 将读取的多余字符放回输入流
            }
        }
        else if (ch == '!')
        {
            string word;
            word += ch;
            inputFile.get(ch);
            if (ch == '=')
            {
                word += ch;
                token.type = TokenType::OPERATOR; // 设置 Token 类型为运算符类型
                token.value = word;               // 设置 Token 的值为不等于号
            }
            else
            {
                token.type = TokenType::OPERATOR; // 设置 Token 类型为运算符类型
                token.value = word;               // 设置 Token 的值为非号
                inputFile.putback(ch);            // 将读取的多余字符放回输入流
            }
        }
        else if (ch == '&')
        {
            string word;
            word += ch;
            inputFile.get(ch);
            if (ch == '&')
            {
                word += ch;
                token.type = TokenType::OPERATOR; // 设置 Token 类型为运算符类型
                token.value = word;               // 设置 Token 的值为与号
            }
            else
            {
                token.type = TokenType::OPERATOR; // 设置 Token 类型为运算符类型
                token.value = word;               // 设置 Token 的值为与号
                inputFile.putback(ch);            // 将读取的多余字符放回输入流
            }
        }
        else if (ch == '|')
        {
            string word;
            word += ch;
            inputFile.get(ch);
            if (ch == '|')
            {
                word += ch;
                token.type = TokenType::OPERATOR; // 设置 Token 类型为运算符类型
                token.value = word;               // 设置 Token 的值为或号
            }
            else
            {
                token.type = TokenType::OPERATOR; // 设置 Token 类型为运算符类型
                token.value = word;               // 设置 Token 的值为或号
                inputFile.putback(ch);            // 将读取的多余字符放回输入流
            }
        }
        else if (ch == '^')
        {
            token.type = TokenType::OPERATOR; // 设置 Token 类型为运算符类型
            token.value = "^";                // 设置 Token 的值为异或号
        }
        else if (ch == '%')
        {
            token.type = TokenType::OPERATOR; // 设置 Token 类型为运算符类型
            token.value = "%";                // 设置 Token 的值为取模号
        }
       
        else
        {
            // 忽略其他字符
            token = getNextToken(); // 递归调用获取下一个 Token
        }
        return token; // 返回获取的 Token
    }
};

// 代码生成器类
class CodeGenerator
{
public:
    // 生成对应于变量声明语句的汇编代码
    static void generateVariableDeclaration(const int &offset)
    {
        cout << "mov DWORD PTR [ebp-" << offset << "], 0 " << endl; // 生成变量声明的汇编代码
    }

    // 生成对应于赋值语句的汇编代码
    static void generateAssignment(const int &offset, const string &value)
    {
        cout << "mov DWORD PTR [ebp-" << offset << "], " << value << endl; // 生成赋值语句的汇编代码
    }

    // 生成对应于表达式语句的汇编代码
    static void generateExpression(const string &expression, const string &resultIdentifier, map<string, int> para_table)
    {
        stringstream ss(expression); // 创建一个字符串流对象，并初始化为 expression
        string token;
        stack<string> ops;

        int j = 0;
        while (ss >> token)
        { // 从字符串流中读取每个 Token
            if (isdigit(token[0]))
            {

                // 如果是数字
                cout << "mov eax, " << token << endl;                                                  // 将常量加载到 eax 寄存器
                cout << "mov DWORD PTR [ebp-" << para_table[resultIdentifier] * 4 << "], eax" << endl; // 将 eax 中的值存储到指定变量的内存中
                cout << "push eax" << endl;                                                             // 将 eax 中的值压入栈中
             

              
            }
            else if (isalpha(token[0]) || token[0] == '_')
            {                                                                               // 如果是字母
                cout << "mov eax, DWORD PTR [ebp-" << para_table[token] * 4 << "]" << endl; // 将变量的值加载到 eax 寄存器
                cout << "push eax" << endl;

                // 将 eax 中的值压入栈中
                
            }
            else if (token == "(")
            {                    // 如果是左括号
                ops.push(token); // 将左括号压入运算符栈中
                
            }
            else if (token == ")")
            { // 如果是右括号
                while (!ops.empty() && ops.top() != "(")
                {                         // 当运算符栈非空且栈顶不是左括号时
                    print_opt(ops.top()); // 执行栈顶运算符对应的汇编操作
                    ops.pop();            // 弹出栈顶运算符
                }
                ops.pop(); // 弹出 "("
             
            }
            else if (token == "<=" || token == ">=" || token == ">" || token == "<")
            {
                while (!ops.empty() && (ops.top() == "<" || ops.top() == "<=" || ops.top() == ">" || ops.top() == ">=" || ops.top() == "+" || ops.top() == "-" || ops.top() == "*" || ops.top() == "/" || ops.top() == "%"))
                {
                    print_opt(ops.top()); // 执行栈顶运算符对应的汇编操作
                    ops.pop();            // 弹出栈顶运算符
                }

                ops.push(token); // 将当前运算符压入运算符栈中
               
            }
            else if (token == "&")
            {
                while (!ops.empty() && (ops.top() == "<" || ops.top() == "<=" || ops.top() == ">" || ops.top() == ">=" || ops.top() == "+" || ops.top() == "-" || ops.top() == "*" || ops.top() == "/" || ops.top() == "%" || ops.top() == "&" || ops.top() == "!=" || ops.top() == "=="))
                {
                    print_opt(ops.top()); // 执行栈顶运算符对应的汇编操作
                    ops.pop();            // 弹出栈顶运算符
                }

                ops.push(token); // 将当前运算符压入运算符栈中
              
            }
            else if (token == "==" || token == "!=")
            { // 如果是乘号或除号
                while (!ops.empty() && (ops.top() == "<" || ops.top() == "<=" || ops.top() == ">" || ops.top() == ">=" || ops.top() == "+" || ops.top() == "-" || ops.top() == "*" || ops.top() == "/" || ops.top() == "%" || ops.top() == "!=" || ops.top() == "=="))
                {
                    print_opt(ops.top()); // 执行栈顶运算符对应的汇编操作
                    ops.pop();            // 弹出栈顶运算符
                }
                ops.push(token); // 将当前运算符压入运算符栈中
              
            }
            else if (token == "^")
            { // 如果是小于号或大于号
                while (!ops.empty() && (ops.top() == "<" || ops.top() == "<=" || ops.top() == ">" || ops.top() == ">=" || ops.top() == "+" || ops.top() == "-" || ops.top() == "*" || ops.top() == "/" || ops.top() == "%" || ops.top() == "&" || ops.top() == "!=" || ops.top() == "==" || ops.top() == "^"))
                {
                    print_opt(ops.top()); // 执行栈顶运算符对应的汇编操作
                    ops.pop();            // 弹出栈顶运算符
                }
                ops.push(token); // 将当前运算符压入运算符栈中
               
            }
            else if (token == "*" || token == "/" || token == "%")
            { // 如果是乘号或除号
                while (!ops.empty() && (ops.top() == "*" || ops.top() == "/" || ops.top() == "%"))
                {
                    print_opt(ops.top()); // 执行栈顶运算符对应的汇编操作
                    ops.pop();            // 弹出栈顶运算符
                }
                ops.push(token); // 将当前运算符压入运算符栈中
               
            }

            else if (token == "+" || token == "-")
            { // 如果是加号或减号
                while (!ops.empty() && (ops.top() == "+" || ops.top() == "-" || ops.top() == "*" || ops.top() == "/" || ops.top() == "%"))
                {
                    print_opt(ops.top()); // 执行栈顶运算符对应的汇编操作
                    ops.pop();            // 弹出栈顶运算符
                }
                ops.push(token); // 将当前运算符压入运算符栈中
              
            }
            else if (token == "|")
            { // 如果是取模运算
                while (!ops.empty() && (ops.top() == "<" || ops.top() == "<=" || ops.top() == ">" || ops.top() == ">=" || ops.top() == "+" || ops.top() == "-" || ops.top() == "*" || ops.top() == "/" || ops.top() == "%" || ops.top() == "&" || ops.top() == "!=" || ops.top() == "==" || ops.top() == "^" || ops.top() == "|"))

                {
                    print_opt(ops.top()); // 执行栈顶运算符对应的汇编操作
                    ops.pop();            // 弹出栈顶运算符
                }
                ops.push(token); // 将当前运算符压入运算符栈中
               
            }
        }

        while (!ops.empty())
        {                         // 当运算符栈非空时
            print_opt(ops.top()); // 执行栈顶运算符对应的汇编操作
            ops.pop();            // 弹出栈顶运算符
          
        }
       
            cout << "pop eax" << endl;
            cout << "mov DWORD PTR [ebp-" << para_table[resultIdentifier] * 4 << "], eax" << endl;
        
    }
};

// 主函数
int main(int argc, char *argv[])
{
    map<string, int> para_table; // 定义参数表，用于记录变量名和对应的偏移量

    if (argc != 2)
    {                                                            // 如果命令行参数数量不为 2
        cerr << "Usage: " << argv[0] << " <input_file>" << endl; // 输出提示信息
        return 1;                                                // 返回错误码 1
        exit(1);
    }

    Lexer lexer(argv[1]); // 创建 Lexer 对象，用于词法分析
    cout << ".intel_syntax noprefix" << endl;
    cout << ".global main" << endl;
    cout << ".extern printf" << endl;
    cout << ".data" << endl;
    cout << "format_str:" << endl;
    cout << "  .asciz \"%d\\n\"" << endl;
    cout << ".text" << endl;

    // 词法分析
    Token token; // 定义一个 Token 对象
    while ((token = lexer.getNextToken()).type != TokenType::END)
    { // 循环读取 Token，直到文件结束
        if (token.type == TokenType::KEYWORD_INT)
        {                                     // 如果是整型关键字
            Token var = lexer.getNextToken(); // 获取下一个 Token，应该是标识符
            if (var.type == TokenType::KEYWORD_MAIN)
            {
                cout << "main:" << endl;            // 输出主函数标签
                cout << "push ebp" << endl;         // 保存当前栈底指针
                cout << "mov ebp, esp" << endl;     // 设置新的栈底指针
                cout << "sub esp, 0x100" << endl;   // 为局部变量分配空间
                lexer.getNextToken();               //(
                Token token = lexer.getNextToken(); // 获取下一个 Token
                if (token.type == TokenType::KEYWORD_INT)
                {
                    lexer.getNextToken(); // argc
                    lexer.getNextToken(); //,
                    lexer.getNextToken(); // int
                    lexer.getNextToken(); // argv
                }
            }
            else if (var.type != TokenType::KEYWORD_MAIN)
            {
                Token t = lexer.getNextToken(); // 获取下一个 Token，可能是分隔符或运算符
                if (t.type == TokenType::DELIMITER)
                {                                                         // 如果是分隔符
                    para_table.emplace(var.value, para_table.size() + 1); // 记录变量名和对应的偏移量
                    // CodeGenerator::generateVariableDeclaration(para_table[var.value] * 4); // 生成变量声明的汇编代码
                }
                else if (t.type == TokenType::OPERATOR)
                {                                                                                 // 如果是运算符
                    Token constant = lexer.getNextToken();                                        // 获取下一个 Token，应该是常量
                    para_table.emplace(var.value, para_table.size() + 1);                         // 记录变量名和对应的偏移量
                    CodeGenerator::generateAssignment(para_table[var.value] * 4, constant.value); // 生成赋值语句的汇编代码
                }
            }
        }
        if (token.type == TokenType::PRINT)
        { // 单个输出
            lexer.getNextToken();
            token = lexer.getNextToken(); // 获取下一个 Token

            if (token.type == TokenType::IDENTIFIER)
            {
                cout << "push DWORD PTR [ebp-" << para_table[token.value] * 4 << "]" << endl; // 将变量的值加载到 eax 寄存器
                cout << "push offset format_str" << endl;
                cout << "call printf" << endl;
                cout << "add esp, 8" << endl;
                token = lexer.getNextToken(); // 获取下一个 Token
            }
            else if (token.type == TokenType::CONSTANT)
            {
                cout << "mov edx, " << token.value << endl;
                cout << "push edx" << endl; // 将常量加载到 eax 寄存器
                cout << "push offset format_str" << endl;
                cout << "call printf" << endl;
                cout << "add esp, 8" << endl;
                token = lexer.getNextToken(); // 获取下一个 Token
            }
            lexer.getNextToken();
        }
        if (token.type == TokenType::IDENTIFIER)
        {                                    // 如果是标识符
            string identifier = token.value; // 获取标识符的值
            token = lexer.getNextToken();    // 获取下一个 Token
            if (token.value == "=")
            { // 如果是赋值操作符 "="
                // 表达式语句
                string expression;
                token = lexer.getNextToken(); // 获取下一个 Token
                Token token1;
                token1.value = "0";
                while (token.type != TokenType::END && token.type != TokenType::DELIMITER)
                {
                    if (token1.value == token.value && token1.value == "=")
                    {
                        token = lexer.getNextToken(); // 获取下一个 Token
                        continue;
                    }
                    expression += token.value;           // 将 Token 的值添加到表达式中
                    token1 = lexer.getNextToken(); // 获取下一个 Token
                    if (token1.value == token.value&&token1.value=="=")
                    {
                        expression += token1.value;
                    }
                 
                    expression += " "; // 添加空格
                    token = token1;    // 获取下一个 Token
                }
                // 计算表达式的值并生成赋值语句
                CodeGenerator::generateExpression(expression, identifier, para_table); // 生成表达式的汇编代码
            }
        }

        if (token.type == TokenType::KEYWORD_RETURN)
        { // 如果是返回关键字
            // 返回语句
            token = lexer.getNextToken(); // 获取下一个 Token
            if (token.type == TokenType::IDENTIFIER)
            {
                cout << "mov eax, DWORD PTR [ebp-" << para_table[token.value] * 4 << "]" << endl; // 将变量的值加载到 eax 寄存器
            }
            else if (token.type == TokenType::CONSTANT)
            {
                cout << "mov eax, " << token.value << endl; // 将常量加载到 eax 寄存器
            }
            cout << "leave" << endl; // 恢复栈底指针
            cout << "ret" << endl;   // 返回
        }
    }

    return 0; // 返回正常退出码
}
