#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif

// 補助関数：文字列の先頭と末尾の空白文字を除去する
std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

bool isQuitCommand(const std::string& s) {
    std::string t = trim(s);
    return (t == "q" || t == "Q" ||
            t == "quit" || t == "QUIT" ||
            t == "exit" || t == "EXIT");
}

int main() {
#ifdef _WIN32
    // Windows コンソールのコードページを UTF-8 に設定し、日本語・中国語の文字化け問題を解決する
    // これは Windows 上の C++ コンソールプログラムで多言語を表示/入力するための一般的な必須手順です
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::cout << "==============================" << std::endl;
    std::cout << "   C++ 簡易計算機 v1.1" << std::endl;
    std::cout << "   対応演算: + - * /   (加算 減算 乗算 除算)" << std::endl;
    std::cout << "   プロンプトに従って順番に入力してください" << std::endl;
    std::cout << "   どのステップでも q / quit / exit と入力すると終了します" << std::endl;
    std::cout << "==============================" << std::endl << std::endl;

    while (true) {
        double num1 = 0.0;
        double num2 = 0.0;
        char op = '\0';

        // ===== 最初の数字を入力 =====
        std::cout << "最初の数字を入力してください: ";
        std::cout.flush();

        std::string line1;
        if (!std::getline(std::cin, line1)) {
            break; // 入力終了またはエラー
        }
        line1 = trim(line1);
        if (isQuitCommand(line1)) {
            break;
        }

        std::istringstream iss1(line1);
        if (!(iss1 >> num1)) {
            std::cout << "エラー: 有効な数字を入力してください (例: 12 または 3.14 または -5)" << std::endl << std::endl;
            continue;
        }

        // ===== 演算子を入力 =====
        std::cout << "演算子を入力してください (+ - * / または 加 減 乗 除 / 足す 引く 掛ける 割る): ";
        std::cout.flush();

        std::string op_line;
        if (!std::getline(std::cin, op_line)) {
            break;
        }
        op_line = trim(op_line);
        if (isQuitCommand(op_line)) {
            break;
        }
        if (op_line.empty()) {
            std::cout << "エラー: 演算子を入力してください" << std::endl << std::endl;
            continue;
        }

        // 複数の入力方式をサポート（記号または中国語・日本語）
        std::string o = op_line;
        if (o == "+" || o == "加" || o == "足す" || o == "プラス" || o == "加算") {
            op = '+';
        } else if (o == "-" || o == "減" || o == "减" || o == "引く" || o == "マイナス" || o == "減算") {
            op = '-';
        } else if (o == "*" || o == "乗" || o == "乘" || o == "掛ける" || o == "かける" || o == "×" || o == "x" || o == "X" || o == "乗算") {
            op = '*';
        } else if (o == "/" || o == "除" || o == "割る" || o == "わる" || o == "÷" || o == "除算") {
            op = '/';
        } else if (o.length() >= 1) {
            op = o[0];  // フォールバック：最初の文字を取る
        }

        // ===== 2番目の数字を入力 =====
        std::cout << "2番目の数字を入力してください: ";
        std::cout.flush();

        std::string line2;
        if (!std::getline(std::cin, line2)) {
            break;
        }
        line2 = trim(line2);
        if (isQuitCommand(line2)) {
            break;
        }

        std::istringstream iss2(line2);
        if (!(iss2 >> num2)) {
            std::cout << "エラー: 有効な数字を入力してください (例: 12 または 3.14)" << std::endl << std::endl;
            continue;
        }

        // ===== 計算を実行 =====
        double result = 0.0;
        bool has_error = false;

        switch (op) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                if (num2 == 0.0) {
                    std::cout << "エラー: 除数がゼロです！" << std::endl << std::endl;
                    has_error = true;
                } else {
                    result = num1 / num2;
                }
                break;
            default:
                std::cout << "エラー: サポートされていない演算子 '" << op << "' です。+ - * / （または 加 減 乗 除 / 足す 引く 掛ける 割る）を使用してください" << std::endl << std::endl;
                has_error = true;
                break;
        }

        if (!has_error) {
            std::cout << "計算結果: "
                      << std::setprecision(12)
                      << num1 << " " << op << " " << num2
                      << " = " << result << std::endl << std::endl;
        }
    }

    std::cout << std::endl << "ご利用ありがとうございました。さようなら！" << std::endl;
    return 0;
}
