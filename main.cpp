#include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;


// main 
int main()
{
    //  Default constructor
    ItemType v;
    Sequence a;

    //test empty() and size()

    assert(a.empty()); //test empty()
    a.insert(0, "a");
    assert(!a.empty());
    assert(a.size() == 1); //test size()
    a.insert(1, "b");
    assert(a.size() == 2);

    // Copy constructor
    Sequence original;
    original.insert(0, "a");
    original.insert(1, "b");
    original.insert(2, "c");

    Sequence copy(original);
    assert(copy.size() == 3);
    assert(copy.get(0, v) && v == "a");
    assert(copy.get(1, v) && v == "b");
    assert(copy.get(2, v) && v == "c");

    copy.set(0, "Z");     // Modifying the copy must not affect the original
    assert(original.get(0, v) && v == "a");   // still "a"

    Sequence empty;
    Sequence copyEmpty(empty);     // Copy of empty sequence
    assert(copyEmpty.empty());

    // Assignment operator 
    Sequence lhs, rhs;
    rhs.insert(0, "p");
    rhs.insert(1, "q");

    lhs = rhs;
    assert(lhs.size() == 2);
    assert(lhs.get(0, v) && v == "p");
    assert(lhs.get(1, v) && v == "q");
    assert(rhs.size() == 2);
    assert(rhs.get(0, v) && v == "p");
    assert(rhs.get(1, v) && v == "q");

    lhs.set(0, "X");
    assert(rhs.get(0, v) && v == "p"); // Independence


    lhs = lhs; // Self-assignment
    assert(lhs.size() == 2);


    Sequence empty1;
    lhs = empty1;  // Assign empty to non-empty
    assert(lhs.empty());


    Sequence big, small;
    big.insert(0, "1"); big.insert(1, "2"); big.insert(2, "3");
    small.insert(0, "a");
    big = small;  // Assign larger to smaller
    assert(big.size() == 1);
    assert(big.get(0, v) && v == "a");


    // test destructor
   
    Sequence* ts = new Sequence();
    delete ts; // destructor called here

    //  insert(pos, value)
    Sequence b;
    assert(b.insert(0, "a") == 0);     // Insert into empty list at position 0
    assert(b.size() == 1);
    assert(b.get(0, v) && v == "a");


    assert(b.insert(1, "c") == 1);     // Insert at the end
    assert(b.get(1, v) && v == "c");


    assert(b.insert(1, "b") == 1);     // Insert in the middle
    assert(b.size() == 3);
    assert(b.get(1, v) && v == "b");

    assert(b.insert(-1, "x") == -1);     // Invalid positions
    assert(b.insert(4, "x") == -1);
    assert(b.size() == 3);

    //get(pos, value)
    assert(b.get(0, v) && v == "a");
    assert(b.get(1, v) && v == "b");
    assert(b.get(2, v) && v == "c");

    //insert(value)
    Sequence s;
    // inserts in sorted position; returns that position
    assert(s.insert("dog") == 0);
    assert(s.insert("ant") == 0);   // "ant" < "dog"
    assert(s.insert("cat") == 1);   // "ant" < "cat" < "dog"
    assert(s.insert("ant") == 0);   // duplicate, goes before existing "ant"

    assert(s.size() == 4);
    assert(s.get(0, v) && v == "ant");
    assert(s.get(1, v) && v == "ant");
    assert(s.get(2, v) && v == "cat");
    assert(s.get(3, v) && v == "dog");

    //erase()
    Sequence e;
    assert(!e.erase(0));         // empty: nothing to erase

    e.insert(0, "a");
    e.insert(1, "b");
    e.insert(2, "c");

    assert(e.erase(0));     // Erase first element
    assert(e.size() == 2);
    assert(e.get(0, v) && v == "b");

    assert(e.erase(1));     // Erase last element
    assert(e.size() == 1);
    assert(e.get(0, v) && v == "b");

    assert(e.erase(0));     // Erase only remaining element
    assert(e.size() == 0);
    assert(e.empty());

    assert(!e.erase(-1));     // Invalid positions
    assert(!e.erase(0));      // now empty again

    // remove()
    Sequence f;
    assert(f.remove("a") == 0);  // empty

    f.insert(0, "a");
    f.insert(1, "b");
    f.insert(2, "a");
    f.insert(3, "c");
    f.insert(4, "a");

    assert(f.remove("a") == 3);  // removes all three "a"s
    assert(f.size() == 2);
    assert(f.get(0, v) && v == "b");
    assert(f.get(1, v) && v == "c");

    assert(f.remove("z") == 0);  // not present

    //get()
    Sequence z;
    z.insert(0, "x");
    z.insert(1, "y");

    v = "unchanged";
    assert(!z.get(-1, v) && v == "unchanged");
    assert(!z.get(2, v) && v == "unchanged");
    assert(z.get(0, v) && v == "x");
    assert(z.get(1, v) && v == "y");

    //set()
    Sequence c;
    c.insert(0, "h");

    assert(c.set(0, "w"));
    assert(c.get(0, v) && v == "w");

    assert(!c.set(-1, "b"));
    assert(!c.set(1, "b"));

    //find()
    Sequence d;
    assert(s.find("z") == -1);   // empty sequence

    d.insert(0, "a");
    d.insert(1, "b");
    d.insert(2, "a");            // duplicate

    assert(d.find("a") == 0);    // returns first occurrence
    assert(d.find("b") == 1);
    assert(d.find("z") == -1);   // not present



    // swap() 
    Sequence g, h;
    g.insert(0, "x");
    g.insert(1, "y");
    h.insert(0, "1");

    g.swap(h);
    assert(g.size() == 1);
    assert(h.size() == 2);
    assert(g.get(0, v) && v == "1");
    assert(h.get(0, v) && v == "x");
    assert(h.get(1, v) && v == "y");

    Sequence empty2;
    g.swap(empty2);  // Swap with empty
    assert(g.empty());
    assert(empty2.size() == 1);

    h.swap(h);     // Self-swap
    assert(h.size() == 2);
    assert(h.get(0, v) && v == "x");


    //subsequence()
    Sequence seq1, seq2;
    string vals1[] = { "30","21","63","42","17","63","17","29","8","32" };
    for (int i = 0; i < 10; ++i) seq1.insert(i, vals1[i]);

    seq2.insert(0, "63");
    seq2.insert(1, "17");
    seq2.insert(2, "29");
    assert(subsequence(seq1, seq2) == 5);  // 63 17 29 starts at index 5

    Sequence seq3;
    seq3.insert(0, "17"); seq3.insert(1, "63"); seq3.insert(2, "29");
    assert(subsequence(seq1, seq3) == -1);     // 17 63 29 never consecutive, returns -1

    Sequence empty3;
    assert(subsequence(seq1, empty3) == -1);     // Empty seq2, returns -1

    assert(subsequence(empty3, seq2) == -1);    // Empty seq1, returns -1

    Sequence longSeq;
    for (int i = 0; i < 20; ++i) longSeq.insert(i, to_string(i));
    assert(subsequence(seq1, longSeq) == -1);     // seq2 longer than seq1, returns -1


    Sequence single;
    single.insert(0, "30");
    assert(subsequence(seq1, single) == 0);     // seq2 is single element matching first of seq1

    Sequence copy1;
    for (int i = 0; i < 10; ++i) copy1.insert(i, vals1[i]);
    assert(subsequence(seq1, copy1) == 0);    // seq2 equals seq1 entirely, returns 0


    Sequence s1, s2;
    s1.insert(0, "a"); s1.insert(1, "b"); s1.insert(2, "a");
    s1.insert(3, "b"); s1.insert(4, "c");
    s2.insert(0, "a"); s2.insert(1, "b");
    assert(subsequence(s1, s2) == 0);     // Returns earliest occurrence when two instances exist

    // largers()
    Sequence seq_1, seq_2, result;
    int s_1[] = { 42,67,13,86,42,21 };
    int s_2[] = { 94,52,21,53,18,21 };
    for (int i = 0; i < 6; ++i) {
        seq_1.insert(i, to_string(s_1[i]));
    }
    for (int i = 0; i < 6; ++i) {
        seq_2.insert(i, to_string(s_2[i]));
    }
    largers(seq_1, seq_2, result);
    assert(result.size() == 4);

    Sequence e1, e2, r;
    largers(e1, e2, r);
    assert(r.empty());    // Both empty


    largers(e1, seq_2, r);
    assert(r.empty());     // seq1 empty, empty result

    Sequence res2;
    largers(seq_1, e2, res2);
    assert(res2.size() == seq_1.size());  // seq2 empty, result == seq1
    ItemType v1, v2;
    for (int i = 0; i < seq_1.size(); ++i) {
        seq_1.get(i, v1);
        res2.get(i, v2);
        assert(v1 == v2);
    }

    Sequence longer, shorter, res3;
    longer.insert(0, "a"); longer.insert(1, "b"); longer.insert(2, "c");
    shorter.insert(0, "z");   
    largers(longer, shorter, res3); //seq1 longer than seq2 → trailing elements of seq1 appended

    assert(res3.size() == 2);
    assert(res3.get(0, v) && v == "b");
    assert(res3.get(1, v) && v == "c");
    Sequence s3, s4, res4;
    s3.insert(0, "b");
    s4.insert(0, "a"); s4.insert(1, "c");
    largers(s3, s4, res4);   // seq2 longer than seq1 → no extra appending
    assert(res4.size() == 1);
    assert(res4.get(0, v) && v == "b");

    Sequence pre, sa, sb;
    pre.insert(0, "junk"); pre.insert(1, "junk");
    sa.insert(0, "hello");
    sb.insert(0, "world");  
    largers(sa, sb, pre);
    assert(pre.empty()); // Result is non-empty before call, is overwritten

    // Aliasing: seq1 and result refer to the same object
    Sequence alias;
    alias.insert(0, "b"); alias.insert(1, "a"); alias.insert(2, "c");
    Sequence other;
    other.insert(0, "a"); other.insert(1, "b"); other.insert(2, "b");
    largers(alias, other, alias);
    assert(alias.size() == 2);
    assert(alias.get(0, v) && v == "b");
    assert(alias.get(1, v) && v == "c");
    std::cout << "pass";
}
