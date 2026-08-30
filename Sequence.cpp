#include "Sequence.h"
Sequence::Sequence() {
    dummy.next = &dummy;
    dummy.prev = &dummy;
    m_size = 0;


}
Sequence::Sequence(const Sequence& other) {
    //Copy constructor
    //When a brand new Sequence is created as a copy of an existing Sequence, enough new nodes must be allocated to hold a duplicate of the original list.
    dummy.next = &dummy;
    dummy.prev = &dummy;
    m_size = 0;
    for (Node* p = other.dummy.next; p != &other.dummy; p = p->next) {
        insert(m_size, p->val);
    }
}
Sequence& Sequence :: operator=(const Sequence& rhs) {
    //Assignment operator
   // When an existing Sequence(the left - hand side) is assigned the value of another Sequence(the right - hand side), the result must be that the left - hand side object is a duplicate of the right - hand side object, with no memory leak of list nodes(i.e.no list node from the old value of the left - hand side should be still allocated yet inaccessible).
    if (this != &rhs) {
        Sequence temp(rhs);
        swap(temp);
    }
    return *this;
}
Sequence:: ~Sequence() {
    //   Destructor 
    // When a Sequence is destroyed, the nodes in the linked list must be deallocated.
    Node* p = dummy.next;
    while (p != &dummy) {
        Node* n = p->next;
        delete p;
        p = n;

    }
}


bool Sequence::empty() const {
    return m_size == 0;
}

int Sequence::size() const {
    return m_size;
}
// Insert value into the sequence so that it becomes the item at
     // position pos.  The original item in position pos and those that
     // follow it end up in positions one greater than they were at before.
     // Return pos if 0 <= pos <= size() and the value could be
     // inserted.
     // Otherwise,leave the sequence unchanged and return -1.  Notice that
     // if pos is equal to size(), the value is inserted at the end.
int Sequence::insert(int pos, const ItemType& value) {
    if (pos < 0 || pos > size()) {
        return -1;
    }
    Node* p = dummy.next;
    Node* holder = new Node;
    holder->val = value;

    for (int i = 0; i < pos; i++) {
        p = p->next;
    }
    holder->prev = p->prev;
    holder->next = p;
    p->prev->next = holder;
    p->prev = holder;
    m_size++;
    return pos;

}
// Let p be the smallest integer such that value <= the item at
     // position p in the sequence; if no such item exists (i.e.,
     // value > all items in the sequence), let p be size().  Insert
     // value into the sequence so that it becomes the item in position
     // p.  The original item in position p and those that follow it end
     // up in positions one greater than before.  Return p if the value
     // was actually inserted.
int Sequence::insert(const ItemType& value) {

    Node* p;
    Node* holder = new Node;
    holder->val = value;
    int count = 0;
    for (p = dummy.next; p != &dummy; p = p->next) {
        if (value <= p->val) {
            holder->prev = p->prev;
            holder->next = p;
            p->prev->next = holder;
            p->prev = holder;
            m_size++;
            return count;
        }
        count++;

    }
    holder->prev = dummy.prev;
    holder->next = &dummy;
    dummy.prev->next = holder;
    dummy.prev = holder;
    m_size++;
    return count;
}
// If 0 <= pos < size(), remove the item at position pos from
      // the sequence (so that all items that followed that item end up at
      // positions one lower than they were at before), and return true.
      // Otherwise, leave the sequence unchanged and return false.
bool Sequence::erase(int pos) {
    if (pos < 0 || pos >= size()) {
        return false;
    }
    Node* p = dummy.next;
    for (int i = 0; i < pos; i++) {
        p = p->next;
    }
    p->prev->next = p->next;
    p->next->prev = p->prev;
    m_size--;
    delete p;
    return true;

}
// Erase all items from the sequence that == value.  Return the
      // number of items removed (which will be 0 if no item == value).
int Sequence::remove(const ItemType& value) {
    Node* p = dummy.next;
    int count = 0;
    while (p != &dummy) {
        Node* next = p->next;
        if (p->val == value) {
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p;
            m_size--;
            count++;
        }
        p = next;
    }
    return count;
}
// If 0 <= pos < size(), copy into value the item in position pos
      // of the sequence and return true.  Otherwise, leave value unchanged
      // and return false.
bool Sequence::get(int pos, ItemType& value) const {
    Node* p;
    int count = 0;
    for (p = dummy.next; p != &dummy; p = p->next) {
        if (count == pos) {
            value = p->val;
            return true;
        }
        count++;

    }
    return false;
}
// If 0 <= pos < size(), replace the item at position pos in the
   // sequence with value and return true.  Otherwise, leave the sequence
   // unchanged and return false.
bool Sequence::set(int pos, const ItemType& value) {
    Node* p;
    int count = 0;
    for (p = dummy.next; p != &dummy; p = p->next) {
        if (count == pos) {
            p->val = value;
            return true;
        }
        count++;

    }
    return false;
}
// Let p be the smallest integer such that value == the item at
  // position p in the sequence; if no such item exists, let p be -1.
  // Return p.
int Sequence::find(const ItemType& value) const {
    Node* p;
    int count = 0;
    for (p = dummy.next; p != &dummy; p = p->next) {
        if (p->val == value) {
            return count;
        }
        count++;

    }
    return -1;
}

// Exchange the contents of this sequence with the other one.
void Sequence::swap(Sequence& other) {


    Node* tmpNext = dummy.next;
    dummy.next = other.dummy.next;
    other.dummy.next = tmpNext;

    Node* tmpPrev = dummy.prev;
    dummy.prev = other.dummy.prev;
    other.dummy.prev = tmpPrev;

    int tmpSize = m_size;
    m_size = other.m_size;
    other.m_size = tmpSize;


    if (dummy.next == &other.dummy)
        dummy.next = dummy.prev = &dummy;
    else {
        dummy.next->prev = &dummy;
        dummy.prev->next = &dummy;
    }

    if (other.dummy.next == &dummy)
        other.dummy.next = other.dummy.prev = &other.dummy;
    else {
        other.dummy.next->prev = &other.dummy;
        other.dummy.prev->next = &other.dummy;
    }
}


int subsequence(const Sequence& seq1, const Sequence& seq2) {
    //Consider all the items in seq2; let's call them seq20, seq21, ..., seq2n.
    // If there exists at least one k such that seq1k == seq20 and seq1k+1 == seq21 and ...
    // and seq1k+n == seq2n, and k+n < seq1.size(), then this function returns the smallest such k.
    // (In other words, if seq2 is a consecutive subsequence of seq1, the function returns the 
    // earliest place in seq1 where that subsequence starts.) If no such k exists or if seq2 is empty,
    // the function returns -1.

    ItemType value1;
    ItemType value2;
    if (seq2.size() == 0) {
        return -1;
    }
    for (int i = 0; i <= seq1.size() - seq2.size(); i++) {
        int count = 0;
        for (int j = 0; j < seq2.size(); j++) {
            seq1.get(i + j, value1);
            seq2.get(j, value2);
            if (value1 == value2) {
                count++;
            }
            if (count == seq2.size()) {
                return i;
            }

        }

    }
    return -1;
}

void largers(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
    //This function produces as a result a sequence of each element of seq1 
    // that is >= the element at the same position in seq2. The elements in the
    // result are in the same order as they are in seq1
    ItemType value1;
    ItemType value2;
    int size;
    Sequence temp;
    if (seq1.size() > seq2.size()) {
        size = seq2.size();
    }
    else
        size = seq1.size();

    for (int i = 0; i < size; i++) {
        seq1.get(i, value1);
        seq2.get(i, value2);
        if (value1 >= value2) {
            temp.insert(temp.size(), value1);
        }

    }
    for (int i = size; i < seq1.size(); i++) {
        seq1.get(i, value1);
        temp.insert(temp.size(), value1);
    }
    result = temp;

}