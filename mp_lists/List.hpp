//#include "List.h"
/**
* @file list.cpp
* Doubly Linked List (MP 3).
*/

template <class T>
List<T>::List() : head_(NULL), tail_(NULL), length_(0){
  // @TODO: graded in MP3.1
}

/**
* Returns a ListIterator with a position at the beginning of
* the List.
*/
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
* Returns a ListIterator one past the end of the List.
*/
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1

  return List<T>::ListIterator(tail_->next);
}


/**
* Destroys all dynamically allocated memory associated with the current
* List class.
*/
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode* current = head_;
  ListNode* next;
  for (int i = 0; i < length_; i++) {
    next = current->next;
    delete current;
    current = next;
  }
  head_ = nullptr;
  length_ = 0;
}

/**
* Inserts a new node at the front of the List.
* This function **SHOULD** create a new ListNode.
*
* @param ndata The data to be inserted.
*/
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);


  if (head_ != NULL) {
    newNode->next = head_;
    newNode->prev = NULL;
    head_->prev = newNode;
    head_ = newNode;
  }
  if (tail_ == NULL) {
    head_ = newNode;
    tail_ = newNode;
  }


  length_++;

}

/**
* Inserts a new node at the back of the List.
* This function **SHOULD** create a new ListNode.
*
* @param ndata The data to be inserted.
*/
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode* newNode = new ListNode(ndata);
  if (tail_ != NULL) {
    newNode->prev = tail_;
    newNode->next = NULL;
    tail_->next = newNode;
    tail_ = newNode;
  } if (head_ == NULL) {
    head_ = newNode;
    tail_ = newNode;
  }
  //tail_ = newNode;
  length_++;
}

/**
* Helper function to split a sequence of linked memory at the node
* splitPoint steps **after** start. In other words, it should disconnect
* the sequence of linked memory after the given number of nodes, and
* return a pointer to the starting node of the new sequence of linked
* memory.
*
* This function **SHOULD NOT** create **ANY** new List or ListNode objects!
*
* This function is also called by the public split() function located in
* List-given.hpp
*
* @param start The node to start from.
* @param splitPoint The number of steps to walk before splitting.
* @return The starting node of the sequence that was split off.
*/
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode *& start, int splitPoint) {
  /// @todo Graded in MP3.1
  if (start == NULL) {
    return NULL;
  }
  //head_ = start;
  ListNode* next = start;
  if (splitPoint <= 0) {
    return start;
  } else if (splitPoint > length_) {
    return NULL;
  }
  for (int i = 0; i < splitPoint; i++) {
    next = next->next;
  }
  if (next != NULL) {
    ListNode* second_head = next;
    ListNode* prev = next->prev;
    prev->next = NULL;
    second_head->prev = NULL;
    return second_head;
  } else {
    return NULL;
  }

}

/**
* Modifies the List using the waterfall algorithm.
* Every other node (starting from the second one) is removed from the
* List, but appended at the back, becoming the new tail. This continues
* until the next thing to be removed is either the tail (**not necessarily
* the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
* Note that since the tail should be continuously updated, some nodes will
* be moved more than once.
*/
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  if (head_ == NULL || tail_ == NULL || length_ == 0) {
    return;
  } else {

    ListNode* curr = head_;
    ListNode* temp;
    for (int i = 0; curr->next != tail_; i++) {
      if (i % 2 == 0) {
        temp = curr->next;
        curr->next = temp->next;
        tail_->next = temp;
        temp->prev = tail_;
        temp->next = NULL;
        tail_ = temp;
        curr = curr->next;
      }
    }
  }

}

/**
* Reverses the current List.
*/
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
* Helper function to reverse a sequence of linked memory inside a List,
* starting at startPoint and ending at endPoaint. You are responsible for
* updating startPoint and endPoint to point to the new starting and ending
* points of the rearranged sequence of linked memory in question.
*
* @param startPoint A pointer reference to the first node in the sequence
*  to be reversed.
* @param endPoint A pointer reference to the last node in the sequence to
*  be reversed.
*/
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  // @todo Graded in MP3.2
  if(startPoint == endPoint||startPoint == NULL || endPoint == NULL) {
    return;
  }

  ListNode *curr = startPoint;
  ListNode *beg = startPoint->prev;
  ListNode *end = endPoint->next;

  while(curr != endPoint){
    ListNode *temp = curr->next;
    temp->prev = beg;

    curr->next = endPoint->next;
    curr->prev = endPoint;

    endPoint->next = curr;
    curr = temp;
  }
  endPoint = startPoint;
  startPoint = curr;
  if(beg != NULL) {
    beg->next = startPoint;
    startPoint->prev = beg;
  }
  if (end != NULL) {
    end->prev = endPoint;
    endPoint->next = end;
  }


  if(startPoint->prev == NULL){
    head_ = startPoint;
  }
  if(endPoint->next == NULL){
    tail_ = endPoint;
  }

}

/**
* Reverses blocks of size n in the current List. You should use your
* reverse( ListNode * &, ListNode * & ) helper function in this method!
*
* @param n The size of the blocks in the List to be reversed.
*/
template <typename T>
void List<T>::reverseNth(int n) {
  // @todo Graded in MP3.2
  if (n <= 0 || head_ == NULL) {
    return;
  } else if (n > length_) {
    return;
  } else if (n == length_) {
    this->reverse();
  } else {
    ListNode *curr = head_;
    ListNode *tempTail = curr;
    while (curr != NULL) {
      tempTail = curr;
      for (int i = 1; i < n; i++) {
        if (tempTail->next != NULL) {
          tempTail = tempTail->next;
        }
      }
      ListNode *tempNext = tempTail->next;
      this->reverse(curr, tempTail);
      curr = tempNext;
    }
  }

}


/**
* Merges the given sorted list into the current sorted list.
*
* @param otherList List to be merged into the current list.
*/
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
  // set up the current list
  head_ = merge(head_, otherList.head_);
  tail_ = head_;

  // make sure there is a node in the new list
  if (tail_ != NULL) {
    while (tail_->next != NULL)
    tail_ = tail_->next;
  }
  length_ = length_ + otherList.length_;

  // empty out the parameter list
  otherList.head_ = NULL;
  otherList.tail_ = NULL;
  otherList.length_ = 0;
}
/**
* Helper function to merge two **sorted** and **independent** sequences of
* linked memory. The result should be a single sequence that is itself
* sorted.
*
* This function **SHOULD NOT** create **ANY** new List objects.
*
* @param first The starting node of the first sequence.
* @param second The starting node of the second sequence.
* @return The starting node of the resulting, sorted sequence.
*/
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (first == NULL && second == NULL) {
    return NULL;
  } else if (first == NULL) {
    return second;
  } else if (second == NULL) {
    return first;
  } else {
    ListNode *curr1 = first;
    ListNode *curr2 = second;
    ListNode *newHead = NULL;
    ListNode *currHead = newHead;
    while (curr1 != NULL && curr2 != NULL) {

      if ((curr1->data < curr2->data)) {
        if (newHead == NULL) {
          newHead = curr1;
          curr1 = curr1->next;
          currHead = newHead;
        } else {
          curr1->prev = currHead;
          currHead->next = curr1;
          currHead = curr1;
          curr1 = curr1->next;
        }
      } else {
        if (newHead == NULL) {
          newHead = curr2;
          curr2 = curr2->next;
          currHead = newHead;
        } else {
          curr2->prev = currHead;
          currHead->next = curr2;
          currHead = curr2;
          curr2 = curr2->next;
        }
      }
    }
    if (curr1 != NULL) {
      curr1->prev = currHead;
      currHead->next = curr1;
    } else {
      curr2->prev = currHead;
      currHead->next = curr2;
    }
    return newHead;
  }
}

/**
* Sorts a chain of linked memory given a start node and a size.
* This is the recursive helper for the Mergesort algorithm (i.e., this is
* the divide-and-conquer step).
*
* Called by the public sort function in List-given.hpp
*
* @param start Starting point of the chain.
* @param chainLength Size of the chain to be sorted.
* @return A pointer to the beginning of the now sorted chain.
*/
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength==1) {
    return start;
  }
  return merge(mergesort(split(start,(chainLength / 2)),chainLength-(chainLength / 2)),mergesort(start,(chainLength / 2)));

}
