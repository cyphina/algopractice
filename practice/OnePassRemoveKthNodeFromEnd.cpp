struct SinglyLinkedListNode
{
   int                   data;
   SinglyLinkedListNode* next;
};

SinglyLinkedListNode* removeKthNodeFromEnd(SinglyLinkedListNode* head, int k)
{
   if(!head)
   {
      return head;
   }

   SinglyLinkedListNode* first{head};
   SinglyLinkedListNode* second{head};

   int numHops{k + 1};
   while(numHops > 0 && second->next != nullptr)
   {
      second = second->next;
      --numHops;
   }

   if(numHops == 1)
   {
      return first->next;
   }
   else if(numHops > 0)
   {
      return head;
   }

   while(second->next != nullptr)
   {
      first  = first->next;
      second = second->next;
   }

   first->next = first->next->next;
   return head;
}

int main()
{
}
