/**
 * 给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。
 * 如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。
 *您可以假设除了数字 0 之外，这两个数都不会以 0 开头。
 *示例：

  输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
  输出：7 -> 0 -> 8
 原因：342 + 465 = 807

   来源：力扣（LeetCode）
   链接：https://leetcode-cn.com/problems/add-two-numbers
   著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
   */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
  int carry = 0;

    struct ListNode *pre=NULL, *head=NULL, *temp, *over;
    struct ListNode *ll1, *ll2;

    ll1 = l1;
    ll2 = l2;

    if (ll1==NULL || ll2==NULL)
        return NULL;
    
    while((ll1 != NULL) && (ll2 != NULL))
    {
        temp = (struct ListNode *)malloc(sizeof(struct ListNode));
        if (temp == NULL)
            return NULL;

        temp->val = (ll1->val + ll2->val + carry)%10;
        carry = (ll1->val + ll2->val + carry)/10;
        temp->next = NULL;

        if (head == NULL)
        {
            head = temp;
            pre  = temp;
        }
        else {
            pre->next = temp;
            pre = temp;
        }
        ll1 = ll1->next;
        ll2 = ll2->next;
    }

    over = ll1;

    if(over == NULL)
        over = ll2;

    if(over == NULL)
    {
        if (carry != 0)
        {
            temp = (struct ListNode *)malloc(sizeof(struct ListNode));
            if (temp == NULL)
                return NULL;
            temp->val = carry;
            temp->next = NULL;

            pre->next = temp;
        }
        return head;
    }

    while(over != NULL)
    {
        temp = (struct ListNode *)malloc(sizeof(struct ListNode));
        if (temp == NULL)
            return NULL;
        temp->val = (carry + over->val)%10;
        carry = (carry + over->val)/10;
        temp->next = NULL;

        pre->next = temp;
        pre = temp;
        
        over = over->next;
    }

    if (carry != 0)
    {
        temp = (struct ListNode *)malloc(sizeof(struct ListNode));
        if (temp == NULL)
            return NULL;
        temp->val = carry;
        temp->next = NULL;

        pre->next = temp;
    }

    return head;
}
