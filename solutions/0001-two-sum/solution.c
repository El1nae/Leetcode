/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

// 哈希表节点：记录"数值 -> 下标"
typedef struct {
    int key;    // 数组里的数值
    int value;  // 该数值对应的下标
    int used;   // 这个槽位有没有被占用
} HashNode;

#define TABLE_SIZE 20000  // 简单起见，桶的数量固定大一点

int hashFunc(int key, int tableSize) {
    // 处理负数，保证结果非负
    int h = key % tableSize;
    if (h < 0) h += tableSize;
    return h;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    HashNode* table = (HashNode*)calloc(TABLE_SIZE, sizeof(HashNode));

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i]; // 我需要找的"另一半"

        // 在哈希表里查 complement 是否已经出现过
        int idx = hashFunc(complement, TABLE_SIZE);
        while (table[idx].used) {
            if (table[idx].key == complement) {
                // 找到了！
                int* result = (int*)malloc(2 * sizeof(int));
                result[0] = table[idx].value;
                result[1] = i;
                *returnSize = 2;
                free(table);
                return result;
            }
            idx = (idx + 1) % TABLE_SIZE; // 冲突了，往后找下一个空位（开放寻址法）
        }

        // 没找到配对，把当前数字存进哈希表，供后面的数字来查
        int putIdx = hashFunc(nums[i], TABLE_SIZE);
        while (table[putIdx].used) {
            putIdx = (putIdx + 1) % TABLE_SIZE;
        }
        table[putIdx].key = nums[i];
        table[putIdx].value = i;
        table[putIdx].used = 1;
    }

    free(table);
    *returnSize = 0;
    return NULL;
}
