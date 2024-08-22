#pragma once

template <class LinkedListItem>
class LinkedList
{
private:

    // A single node in the linked list
    struct LinkedListNode
    {
        // Holds the item of the node
        LinkedListItem item;

        // Points to the next node in the list
        LinkedListNode *next;
    };

    // The head of the entire linked list. Points to the front-most node.
    LinkedListNode *head;

    // The tail of the entire linked list. Points to the back-most node.
    LinkedListNode *tail;

    // The size of the linked list
    int size;
    
public:

    // Constructor of linked list
    LinkedList();

    // Destructor of linked list
    ~LinkedList();

    // Checks if linked list is empty
    bool is_empty();

    // Adds a new node to the front of linked list
    bool push_front(const LinkedListItem);

    // Adds a new node to the back of linked list
    bool push_back(const LinkedListItem);

    // Removes a node from the front of linked list
    bool pop_front(LinkedListItem&);

    // Gets item of the front of linked list
    bool peek_front(LinkedListItem&);

    // Gets item of the front of linked list
    bool peek_back(LinkedListItem&);

    // Removes all items from linked list
    void clear();

    // Gets the size of the linked list
    int get_size();
};

// Implementation code below

template <class LinkedListItem>
LinkedList<LinkedListItem>::LinkedList() : head(nullptr), tail(nullptr), size(0) {}

template <class LinkedListItem>
LinkedList<LinkedListItem>::~LinkedList()
{
    clear();
}

template <class LinkedListItem>
bool LinkedList<LinkedListItem>::is_empty()
{
    return head == nullptr && tail == nullptr && size == 0;
}

template <class LinkedListItem>
bool LinkedList<LinkedListItem>::push_front(const LinkedListItem newItem)
{
    LinkedListNode *newNode = new LinkedListNode();
    newNode->item = newItem;
    if (is_empty())
    {
        newNode->next = nullptr;
        head = newNode;
        tail = newNode;
        size++;
        return true;
    }
    else
    {
        newNode->next = head;
        head = newNode;
        size++;
        return true;
    }
    return false;
}

template <class LinkedListItem>
bool LinkedList<LinkedListItem>::push_back(const LinkedListItem newItem)
{
    LinkedListNode *newNode = new LinkedListNode();
    newNode->item = newItem;
    newNode->next = nullptr;
    if (is_empty())
    {
        head = newNode;
        tail = newNode;
        size++;
        return true;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
        size++;
        return true;
    }
    return false;
}

template <class LinkedListItem>
bool LinkedList<LinkedListItem>::pop_front(LinkedListItem& item)
{
    if (is_empty())
    {
        return false;
    }
    else if (head == tail && size == 1)
    {
        item = head->item;
        delete head;
        head = nullptr;
        tail = nullptr;
        size--;
        return true;
    }
    else
    {
        item = head->item;
        LinkedListNode *tempNode = head;
        head = head->next;
        delete tempNode;
        size--;
        return true;
    }
}

template <class LinkedListItem>
bool LinkedList<LinkedListItem>::peek_front(LinkedListItem& item)
{
    if (is_empty())
        return false;
    item = head->item;
    return true;
}

template <class LinkedListItem>
bool LinkedList<LinkedListItem>::peek_back(LinkedListItem& item)
{
    if (is_empty())
        return false;
    item = tail->item;
    return true;
}

template <class LinkedListItem>
void LinkedList<LinkedListItem>::clear()
{
    if (!is_empty())
    {
        LinkedListItem item;
        while (size != 0)
        {
            pop_front(item);
        }
    }
}

template <class LinkedListItem>
int LinkedList<LinkedListItem>::get_size()
{
    return size;
}
