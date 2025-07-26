#include <iostream>
using namespace std;
struct node
{
  int data;
  node *next;
};
node *createLinkedList(int n) {
    if (n <= 0) return nullptr;
    int temp;
    cin>>temp;

    node* head = new node();
    head->data = temp;
    head->next = nullptr;

    node* cursor = nullptr;
    for (int i = 0; i < n - 1; i++) {
        int temp;
        cin>>temp;
        
        cursor = head;
        
        node* newNode = new node();
        newNode->next = head;
        newNode->data = temp;
        
        head = newNode;
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