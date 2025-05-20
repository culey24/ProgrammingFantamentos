#include <iostream>
using namespace std;
struct node
{
  int data;
  node *next;
};

node *createLinkedList(int n); // The implementation is provided implicitly

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

void replace(node* head, int position, int value)
{
  //TODO
  // index(head) = 0 ?
  if (position < 0) return;
  int size = listSize(head);
  if (position > size - 1) return;
  int index = 0;
  node* cursor = head;
  while (index != position) {
      cursor = cursor->next;
      index++;
  }
  cursor->data = value;
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
  int pos, val;
  cin>>pos>>val;
  replace(head, pos, val);
  print(head);
  return 0;
}
