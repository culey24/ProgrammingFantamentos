#include <iostream>
using namespace std;
struct node
{
  int data;
  node *next;
};

node *createLinkedList(int n); 

bool isEqual(node *head1, node *head2)
{
  // TO DO
    node* cursor1 = head1;
    node* cursor2 = head2;
    while (cursor1 && cursor2) {
        if (cursor1->data != cursor2->data) return false;
        cursor1 = cursor1->next;
        cursor2 = cursor2->next;
    }
    return (cursor1 == nullptr && cursor2 == nullptr);
}

int main()
{
  int n = 0;
  cin>> n;
  node *head1 = createLinkedList(n);
  int m = 0;
  cin>> m;
  node *head2 = createLinkedList(m);
  cout << isEqual(head1, head2) << endl;
  return 0;
}