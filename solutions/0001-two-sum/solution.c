//解法：哈希表——把数值本身，通过某种计算，直接变成一个存放位置
// 哈希表，记录数值和下标
typedef struct {
    int key;    // 数组里的数值
    int value;  // 该数值对应的下标
    int used;   // 这个槽位有没有被占用
} HashNode;

/*
struct:相当于一个标准的变量表，把一系列变量打包，不同的事件只需要在固定的变量类型中填入自己的数值即可。类似小学一个班的人在表格上填自己的姓名和学号

typedef struct {
    abcd
} yyyy;    用于取别名，相当于给这个 struct 起名为 yyyy，这样以后调用比较简单，不用每次都写 struct
*/


#define TABLE_SIZE 20000  // 设置大一点空间，放数值可以有更多余量

int hashFunc(int key, int tableSize) {
    int h = key % tableSize;   // 如果 key 小于 tableSize，余数就是它自己；如果 key 比这个范围还大，取余也能把它压缩到 0~tableSize-1 这个区间里
    if (h < 0) h += tableSize;  // 处理负数，保证结果非负。因为 C 语言里,负数取余的结果也可能是负数，数组下标不能是负的所以必须排查
    return h;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    HashNode* table = (HashNode*)calloc(TABLE_SIZE, sizeof(HashNode));
 /*
    calloc是用于分配内存的函数，会自动把分配的内存全部清零。哈希表初始化
    (HashNode*) 是强制类型转换，因为 calloc 返回的是通用指针类型,需要告诉编译器"这块内存我要当成 HashNode 数组来用"
 */

for (int i = 0; i < numsSize; i++) {  
    // int i = 0：造一个计数器 i，从 0 开始（数组第一个位置的编号就是 0）
    // i < numsSize：条件，只要 i 还没超过数组长度，就继续循环
    // i++：意思是 i = i + 1，每循环一轮，i 自己加 1
    // { }：花括号包住的是循环体，也就是每一轮要重复做的事情
    // 这一行整体意思：把数组从头到尾，一个一个数字地遍历过去

    int complement = target - nums[i];
    // int complement：声明一个新的整数变量，取名叫 complement（"另一半"的意思）
    // target - nums[i]：target 是目标和，nums[i] 是当前这一轮拿到的数字
    // 减法算出"还差多少"，也就是"要另外配对的那个数字应该是多少"
    // = ：赋值符号，把右边算出来的结果，存进左边的 complement 里

    //目标：拿到一个数字之后先看柜子里有没有别的数字，没有的话就把自己放进去
    // 在哈希表里查 complement 是否已经出现过
    int idx = hashFunc(complement, TABLE_SIZE);
    // int idx：声明一个整数变量，存"柜子编号"
    // hashFunc(...)：调用之前写好的函数，传入两个参数：
    //     第一个参数 complement：要查的这个数字
    //     第二个参数 TABLE_SIZE：柜子总共有多少个（20000）
    // 函数算完后会返回一个 0~19999 之间的编号，存进 idx

    while (table[idx].used) {
        // table：哈希表数组，前面 calloc 出来的那一大排柜子
        // table[idx]：用方括号 [ ] 取出编号是 idx 的那个柜子
        // .used：用点号 . 取出这个柜子里的 used 这一项（是不是被占用的标记）
        // 整体意思：只要这个柜子里"有人"（used 不是 0），就继续检查

        if (table[idx].key == complement) {
            // if：条件判断语句，如果括号里成立，就执行下面的代码
            // table[idx].key：取出这个柜子里存的数字
            // == ：判断"是否相等"（注意两个等号，不是赋值的一个等号）
            // 整体意思：如果柜子里的数字，正好就是我要找的 complement

            // 找到complement，目标数
            int* result = (int*)malloc(2 * sizeof(int));
            // int* result：声明一个"指针"变量叫 result
            //     * 表示这个变量存的不是普通数字，而是"内存地址"
            //     可以理解成 result 是一个"数组的入口"
            // malloc(...)：申请一块新的内存空间
            //     2 * sizeof(int)：算出需要多大空间
            //     sizeof(int) 是"一个 int 占多少字节"，通常是 4
            //     2 * 4 = 8，也就是申请能装下 2 个整数的空间
            // (int*)：强制类型转换，告诉编译器"这块内存我要当成 int 数组用"
            // = ：把申请到的这块内存地址，存进 result 里

            result[0] = table[idx].value;
            // result[0]：result 这个数组的第 0 个位置（第一个格子）
            // table[idx].value：柜子里存的那个数字，在原数组里的下标
            // 整体意思：把"之前存进去的那个数字，它的位置"，填进答案的第一格

            result[1] = i;
            // result[1]：result 数组的第 1 个位置（第二个格子）
            // i：当前这一轮，正在处理的这个数字的下标
            // 整体意思：把"我自己现在的位置"，填进答案的第二格

            *returnSize = 2;
            // returnSize：这是函数参数里传进来的一个"指针"
            // *returnSize：星号在这里表示"取出指针指向的那个真正的变量"
            //     可以理解成：不是改 returnSize 这个地址本身，而是改它指向的那个值
            // = 2：把这个值设成 2，告诉外面"答案数组里有 2 个数字"

            free(table);
            // free：专门用来"归还"之前用 malloc/calloc 申请的内存
            // (table)：要归还的是 table 这一整块内存
            // 整体意思：柜子不用了，把空间还给电脑，避免浪费

            return result;
            // return：函数执行到这里就结束，并把值交出去
            // result：交出去的就是装着答案的这个数组
        }
        // } ：结束 if 判断的花括号

        idx = (idx + 1) % TABLE_SIZE;
        // 冲突了，往后找下一个空位（开放寻址法）
        // idx + 1：把柜子编号加 1，也就是往右边挪一格
        // % TABLE_SIZE：取余数，防止编号超过 19999
        //     比如 19999 + 1 = 20000，20000 % 20000 = 0，正好绕回第 0 号柜子
        // = ：把算出来的新编号，重新存回 idx，下一轮 while 就用这个新编号检查
    }
    // } ：结束这个 while 循环的花括号
    // 走到这里说明：要么找到了 complement（上面已经 return 结束了）
    //             要么柜子是空的（used 是 0），循环自然停止，往下继续走

    // 没找到配对，把当前数字存进哈希表，供后面的数字来查

        int putIdx = hashFunc(nums[i], TABLE_SIZE)  ;
        // int putIdx：声明一个新变量，专门用来存"我自己要放进第几号柜子"
        // hashFunc(nums[i], TABLE_SIZE)：
        //     注意这次传进去的是 nums[i]（我自己这个数字），不是 complement
        // = ：把算出来的柜子编号，存进 putIdx

        while (table[putIdx].used) {
            // 检查这个编号的柜子，是不是已经被别人占用了
            putIdx = (putIdx + 1) % TABLE_SIZE;
            // 如果被占用了，就挪到下一个柜子编号，继续检查
            // 直到找到一个真正空的柜子（used 是 0），循环才会停止
        }

        table[putIdx].key = nums[i];
        // table[putIdx]：找到的那个空柜子
        // .key：柜子里"存的数字"这一项
        // = nums[i]：把我自己这个数字，填进这一项

        table[putIdx].value = i;
        // .value：柜子里"数字的位置"这一项
        // = i：把我自己现在的下标，填进这一项

        table[putIdx].used = 1;
        // .used：柜子的"有没有被占用"标记
        // = 1：把它设成 1，意思是"这个柜子现在有人了"，以后别人经过要跳过它
    }
    // } ：结束最外层 for 循环的花括号
    // 走到这里，说明这一轮数字已经处理完了（要么存进去了，要么已经 return 了）
    // 接下来 i++，进入下一轮，处理数组里的下一个数字

    free(table);
    // 如果 for 循环从头到尾都跑完了，说明整个数组都检查过了
    // 但是一直没有 return（没找到任何一对能凑成 target 的数字）
    // 这时候把柜子占用的内存还给电脑

    *returnSize = 0;
    // 通过指针，把外面那个变量设成 0
    // 告诉调用者："没有找到答案，返回的数组长度是 0"

    return NULL;
    // NULL：表示"空指针"，也就是"什么都没有"
    // 把 NULL 返回出去，告诉调用者"没有找到任何答案"
}
