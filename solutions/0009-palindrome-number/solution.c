#include <stdbool.h>

bool isPalindrome(int x) {
    // 排除负数（负数肯定不是回文数）
    if (x < 0) {
        return false;
    }

    // 计算数字的位数，并求出最高位对应的除数
    int digits = 1;//位数默认，至少有1位
    long long divisor = 1;   // divisor = 10^(digits-1)
    int temp = x;
    while (temp >= 10) {
        temp /= 10;
        digits++;
        divisor *= 10;
    }

    int num = x;

    // 比较 digits/2 的长度的首位数字
    for (int i = 0; i < digits / 2; i++) {
        int firstDigit = (num / divisor) % 10;  // 当前最高位
        int lastDigit = num % 10;               // 当前最低位

        if (firstDigit != lastDigit) {
            return false;
        }

        // 把已经比较过的数字排除
        num = (num % divisor) / 10;  // 去掉最高位和最低位
        divisor /= 100;               // 除数缩小两位，指向新的最高宽度
    }

    return true;
}

