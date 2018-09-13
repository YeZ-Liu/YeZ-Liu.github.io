#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

// Definition for singly-linked list.

struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
 };

class Solution
{
public:
    ListNode* addTwoNumbers(ListNode*, ListNode*);
};

ListNode* Solution::addTwoNumbers(ListNode* l1, ListNode* l2)
{
	int add = 0;
	ListNode* none = new ListNode(0);
	ListNode* temp = new ListNode(-1);
	ListNode* head = temp;
	ListNode* p = l1;
	ListNode* q = l2;
	while(true)
	{
		int mid = add;
		if(p->next==NULL || q->next==NULL)
		{
			if(p->next==NULL&&q->next==NULL)
			{
				mid += p->val+q->val;
				if(temp->val!=-1)
				{
					ListNode* TEMP_1 = new ListNode(mid%10);
					temp->next = TEMP_1;
					if(mid/10!=0)
					{
						temp = temp->next;
						ListNode* TEMP_2 = new ListNode(mid/10);
						temp->next = TEMP_2;
					}
					return head;
				}
				else
				{
					temp->val = mid%10;
					if(mid/10!=0)
					{
						ListNode* TEMP_1 = new ListNode(mid/10);
						temp->next = TEMP_1;
					}
					return head;
				}
			//	temp = temp->next;
			}
			if(p->next==NULL&&q->next!=NULL)
			{
				mid += p->val;
				p = none;
			}
			if(p->next!=NULL&&q->next==NULL)
			{
				mid += q->val;
				q = none;
			}
		}
		if(p->next!=NULL)
		{
			mid+=p->val;
			p = p->next;
		}
		if(q->next!=NULL)
		{
			mid+=q->val;
			q = q->next;
		}
		if(temp->val == -1)
		{
			temp->val = mid%10;
			add = mid/10;
		}
		else
		{
			ListNode* TEMP = new ListNode(mid%10);
			add = mid/10;
			temp->next = TEMP;
			temp = temp->next;
		}
	}
	return head;
}

void print(ListNode* p)
{
	if(p->next==NULL)
	{
		cout << p->val;
		return;
	}
	print(p->next);
	cout << p->val;
}

ListNode* import(string s)
{
	int len = s.size();
	ListNode* temp = new ListNode(-1);
	ListNode* head = temp;
	for(int i = 0;i < len;i++)
	{
		if(i==0) temp->val = s[0]-48;
		else
		{
			ListNode* Temp = new ListNode(s[i]-48);
			Temp -> next = temp;
			temp = Temp;
			head = Temp;
		}
	}
}

int main()
{
	ListNode* l1 = new ListNode(1);
	l1 -> next = new ListNode(9);
	l1 -> next->next = new ListNode(3);
	ListNode* l2 = new ListNode(2);
	l2 -> next = new ListNode(9);
	l2 -> next->next = new ListNode(9);
	Solution solo;
	print(solo.addTwoNumbers(l1,l2));
	return 0;
}
