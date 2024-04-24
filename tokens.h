#ifndef TOKENS_H
#define TOKENS_H
#include <string>
using namespace std;

// Token 类型枚举
enum class TokenType
{                   // 枚举 Token 的各种类型
    KEYWORD_INT,    // 整型关键字
    KEYWORD_RETURN, // 返回关键字
    KEYWORD_MAIN,   // 主函数关键字
    IDENTIFIER,     // 标识符
    CONSTANT,       // 常量
    OPERATOR,       // 运算符
    DELIMITER,      // 分隔符
    PRINT,          // 输出
    END             // 结束符
};

// Token 结构体
struct Token
{                   // 定义 Token 结构体，用于表示 Token 的类型和值
    TokenType type; // Token 的类型
    string value;   // Token 的值
};

#endif /* TOKENS_H */
