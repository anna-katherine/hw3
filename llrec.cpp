#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************


void llpivot (Node*& head, Node*& smaller, Node*& larger, int pivot)
{
	if (head == NULL) // if we have an empty list OR if we've iterated through the whole thing
	{
		smaller = NULL; // nothing to test
		larger = NULL;
		return;
	}
	else
	{
		if (head->val > pivot)
		{
			Node* temp = head->next;
			larger = head; // larger = head, and we call larger->next in the next call (to set it to whatever's next)
			larger->next = NULL; 
			head = temp;
			llpivot(head, smaller, larger->next, pivot);
		}
		else
		{
			Node* temp = head->next;
			smaller = head; // same with smaller
			smaller->next = NULL;
			head = temp;
			llpivot(head, smaller->next, larger, pivot);
		}
	}
}