#include <iostream>
using namespace std;

struct node
{
  int data;
  node *next;
};

node *createLinkedList(int n); // The implementation is provided implicitly

void insertNewBack(node*& head, node* insertNode) {
    if (!insertNode) return;
    if (head == nullptr) {
        head = new node();
        head->data = insertNode->data;
        head->next = nullptr;
        return;
    }
    node* cursor = head;
    while(cursor->next) {
        cursor = cursor->next;
    }
    cursor->next = new node();
    cursor = cursor->next;
    cursor->data = insertNode->data;
    return;
}

void deleteLinkedList(node*& head) {
    node* cursor = head;
    while (cursor) {
        node* temp = cursor;
        cursor = cursor->next;
        delete temp;
    }
    head = nullptr;
}

node* evenThenOddLinkedList(node *head)
{
  //TODO
  node* cursor = head;
  node* oddHead = nullptr;
  node* evenHead = nullptr;
  while (cursor) {
      if (cursor->data % 2 == 0) {
          insertNewBack(evenHead, cursor);
      }
      else {
          insertNewBack(oddHead, cursor);
      }
      cursor = cursor->next;
  }
  deleteLinkedList(head); // README
  if (!evenHead) return oddHead;
  cursor = evenHead;
  while (cursor->next) {
      cursor = cursor->next;
  }
  cursor->next = oddHead;
  return evenHead;
}
void print(node *head)
{
  while (head != nullptr)
  {
    cout << head->data << " ";
    head = head->next;
  }
  cout<<endl;
}
int main()
{
  int n = 0;
  cin >> n;
  node *head = createLinkedList(n);
  print(head);
  head = evenThenOddLinkedList(head);
  print(head);
  return 0;
}