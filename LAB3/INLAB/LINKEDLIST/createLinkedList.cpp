#include <iostream>
using namespace std;
struct node
{
  int data;
  node *next;
};
node *createLinkedList(int n)
{
  // TO DO
  if (n <= 0) return nullptr;
  int value;
  cin>>value;
  node* head = new node();
  head->data = value;
  node* cursor = head;
  for (int i = 0; i < n - 1; i++) {
      cin>>value;
      cursor->next = new node();
      cursor = cursor->next;
      cursor->data = value;
  }
  return head;
}
void print(node *head)
{
  while (head != nullptr)
  {
    cout << head->data << endl;
    head = head->next;
  }
}
int main()
{
  int n = 0;
  cin >> n;
  if (n > 0)
  {
    node *head = createLinkedList(n);
    print(head);
  }
  else
  {
    cout << "Invalid n" << endl;
  }
  return 0;
}
