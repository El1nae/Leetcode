#include <stdbool.h>

bool isPalindrome(int x) {
    // 排除负数（负数肯定不是回文数）
    if (x < 0) {
        return false;
    }

    // 计算数字的位数，并求出最高位对应的除数
    int digits = 1;//位数默认，至少有1位
    int divisor = 1;   // divisor除数先设为1 = 10^(digits-1) 用于选出最高位
    int temp = x;  //写一个x的临时变量
    while (temp >= 10) { //被除成个位之前
        temp /= 10;  //除十的同时用整数除法把小数省略，达到消除最后一位的效果
        digits++;  //每循环一次，位数加一
        divisor *= 10; //除数变为10的n次方，用于除掉十进制数字每一位上的值
    }

    // 比较 digits/2 的长度的首位数字
    for (int i = 0; i < digits / 2; i++) {  //总长的一半
        int firstDigit = (x / divisor) % 10;  // 除divisor后只剩最高位，除十后的余数即当前最高位（相当于读取该值）
        int lastDigit = x % 10;               // 原数除十后读取余数，即当前最低位

        if (firstDigit != lastDigit) {
            return false;
        }

        // 把已经比较过的数字排除
        x = (x % divisor) / 10;  // 去掉最高位和最低位
        divisor /= 100;  // 除数缩小两位（首尾在上一轮被取出了），指向新的最高宽度
    }

    return true;
}

