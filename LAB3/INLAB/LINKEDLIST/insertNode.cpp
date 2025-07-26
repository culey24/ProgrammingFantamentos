#include <iostream>
using namespace std;
struct node
{
  int data;
  node *next;
};

int listSize(node* head) {
    if (!head) return 0;
    int count = 0;
    node* cursor = head;
    while (cursor != nullptr) {
        count++;
        cursor = cursor->next;
    }
    return count;
}

node *createLinkedList(int n); // The implementation is provided implicitly

node *insertNode(node *head, node *newNode, int position)
{
  // TO DO
  if (position <= 0) return head;
  if (!head) return newNode;
  int oldSize = listSize(head);
  if (position > oldSize) {
      node* cursor = head;
      while (cursor->next != nullptr) {
          cursor = cursor->next;
      }
      cursor->next = newNode;
  }
  else {
      int index = 1; // head
      node* cursor = head;
      while (index < position - 1) {
          cursor = cursor->next;
          index++;
      }
      node* oldNode = cursor->next;
      cursor->next = newNode;
      cursor = cursor->next;
      cursor->next = oldNode;
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
  node *head = createLinkedList(n);
  node *newNode = new node();
  cin >> newNode->data;
  int position = 0;
  cin >> position;
  head = insertNode(head, newNode, position);
  print(head);
  return 0;
}


