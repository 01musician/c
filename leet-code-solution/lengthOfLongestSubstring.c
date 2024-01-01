#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int getLengthOfLongestSubstring(char *s, int start, int end)
{
    int i, j;
    int len = 1;

    for(i=start+1; i<end; i++)
    {
        if(!isprint(s[i]))
            return len;

        for(j=start; j<i; j++)
        {
            if(s[j] == s[i])
                return len;
        }
        len++;
    }
    return len;
}

int lengthOfLongestSubstring(char *s){
    int len;
    int *posSubLen;
    int start, i;
    int maxSubStrLen = 0;



    if (NULL == s)
        return 0;
    
    len = strlen(s);

    posSubLen = (int *)malloc(len * sizeof(int));
    if(NULL == posSubLen) 
        return -1;

    memset(posSubLen, 0, len);
    
    for(start=0; start<len; start++)
    {
        if (isprint(s[start]))
            posSubLen[start] = getLengthOfLongestSubstring(s, start, len);
        else
            continue;
    }

    for (i=0; i<len; i++)
    {
        if(posSubLen[i] > maxSubStrLen)
            maxSubStrLen = posSubLen[i];
    }
    
    free(posSubLen);

    return maxSubStrLen;
}


int main()
{
    char line[256];
    int  len;

    fgets(line, sizeof(line), stdin);
    line[strlen(line)-1] = 0;
    len = lengthOfLongestSubstring(line);

    printf("max lengthOfLongestSubstring of %s is: %d.\n", line, len);


	return 0;
}



