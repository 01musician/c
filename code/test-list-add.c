/**
 *  * Definition for singly-linked list.
 *   * struct ListNode {
 *    *     int val;
 *     *     struct ListNode *next;
 *      * };
 *       */


struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    int remain, over = 0;
    struct ListNode *pl1 = l1;
    struct ListNode *pl2 = l2;
    struct ListNode *pn;

    while((pl1->next != NULL) && (pl2->next != NULL))
    {
        remain = (pl1->val + pl2->val + over) % 10;
        over   = (pl1->val + pl2->val + over) / 10;

        pl1->val = pl2->val = remain;

        pl1= pl1->next;
        pl2= pl2->next;
    }

    if (pl1->next != NULL)
    {
        while(pl1->next != NULL)
        {

            remain = (pl1->val + over) % 10;
            over   = (pl1->val + over) / 10;

            pl1->val = remain;
            pl1=pl1->next;
        }

        if (over != 0)
        {
            pn = malloc(sizeof())
            pn->val = over;


    }
        



}

