/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <sstream>
template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
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
  return List<T>::ListIterator(nullptr);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode* curr = head_;
  while(curr != nullptr) {
    ListNode* prev;
    prev = curr;
    curr = curr->next;
    delete prev;
  }
  tail_ = nullptr;
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
  ListNode *curr = new ListNode(ndata);
  if (head_ == nullptr) {
    curr->prev = nullptr;
    curr->next = nullptr;
    head_ = curr;
    tail_ = curr;
  } else {
      curr->prev = nullptr;
      curr->next = head_;
      head_->prev = curr;
      head_ = curr;
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
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = NULL;
  newNode -> prev = tail_;
  if (length_ == 0) {
    head_ = newNode;
    tail_ = newNode;
  } else {
    tail_ -> next = newNode;
    tail_ = newNode;
  }

  length_++;

}
  /// @todo Graded in MP3.1

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
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
   ListNode * curr = start;

  if(curr == nullptr){
    return nullptr;
  }

  if(splitPoint == 0){
    return curr;
  }

  for (int i = 0; i < splitPoint && curr != nullptr; i++) {
      curr = curr->next;
  }

  if(curr != nullptr) {
    curr->prev->next = nullptr;
    curr->prev = nullptr;
  }

  return curr;

}
/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode* a = nullptr;
  ListNode* b = nullptr;
  ListNode* c = nullptr;
  ListNode* temp = head_;
  while (temp != nullptr) {
    a = temp;
    if (a -> next == nullptr) {
      break;
    } else {
      b = a -> next;
    }
    if (b -> next == nullptr) {
      break;
    } else {
      c = b -> next;
    }
    if (a == head_) head_ = b;
    if (c == tail_) tail_ = a;
    b -> prev = a -> prev;
    if (b -> prev != nullptr) {
      b -> prev-> next = b;
    }
    a -> next = c -> next;
    if (a -> next != nullptr) {
      a -> next -> prev = a;
    }
    a -> prev = c;
    c -> next = a;
    temp = a -> next;
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
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
	if (startPoint != endPoint) {
		ListNode * curr  = startPoint;
		ListNode * endNext  = endPoint->next;
    ListNode * startPrev = startPoint->prev;
		ListNode * start = startPoint;
    ListNode * end = endPoint;
	  
		while (curr != endNext) {
			swap(curr->prev, curr->next);
			curr = curr->prev;
		}
		if (startPrev == NULL) {
			end->prev = NULL;
			head_ = end;
		} else {
			startPrev->next = end;
			end->prev = startPrev;
		}

		if (endNext == NULL) {
			start->next = NULL;
			tail_ = start;
		} else {
			endNext->prev = start;
			start->next = endNext;
		}
		startPoint = end;
		endPoint = start;
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
  /// @todo Graded in MP3.2
  if (length_ == 0 || length_ == 1) return;
  ListNode* start = head_;
  ListNode* end = head_;

  while (end != NULL) {
    for (int i = 0; i < n - 1; i++) {
      if (end->next == NULL) {
        reverse(start, end);
        return;
      }
      end = end->next;
    }
    reverse(start, end);
    if (end->next == NULL) return;
    else {
      start = end->next;
      end = start;
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
  if (first == NULL) return second;
  if (second == NULL) return first;
  ListNode* head = NULL;
  ListNode* tail = NULL;
  if (first->data < second->data) {
    head = first;
    tail = first;
    first = first->next;
  } else {
    head = second;
    tail = second;
    second = second->next;
  }
  while (first != NULL && second != NULL) {
    if (first->data < second->data) {
      tail->next = first;
      tail = first;
      first = first->next;
    } else {
      tail->next = second;
      tail = second;
      second = second->next;
    }
  }
  if (first != NULL) tail->next = first;
  else tail->next = second;
  return head;
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

  if (start == NULL ||  chainLength == 1) {
    return start;
  }
  int middlePoint = (chainLength / 2);
  ListNode* second = split(start, middlePoint);
  return merge(mergesort(start, middlePoint), mergesort(second, chainLength - middlePoint));
}
