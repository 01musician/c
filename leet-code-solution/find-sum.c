/**
 *  * Note: The returned array must be malloced, assume caller calls free().
 *   */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
	
	int i, j;

    int *retI;

    retI = malloc(2*int);
    if (NULL == retI)
        return NULL;

	for (i=0; i<numsSize; i++)
        for (j=i+1; j<numsSize; j++)
        {
            if(nums[i] + nums[j] == target)
            {
                retI[0] = i;
                retI[1] = j;
                *returnSize = 2;
                return retI;
            }
        }

    return NULL;
}
