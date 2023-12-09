#include <fstream.h>
#include <iomanip.h>
#include <String.h>
#define _HMAP_DEBUG
#include "Hmap.h"
Hmapdeclare(String,int)
Hmapimplement(String,int)

main()
{
  ifstream infile("text");
  ofstream outfile1("test_out1");
  ofstream outfile2("test_out2");
  ofstream outfile3("test_out3");
  ofstream outfile4("test_out4");
  Hmap(String,int) m(Hmapdefault(String,int),22,2.0,10000,4);
  String word;
  if (m.size() != 0)
    {
      cout << "Error: initial size = " << m.size()
           << ", should be " << 0 << "\n";
      exit(1);
    }
  if (m.peek_bucket_cnt() != 13)
    {
      cout << "Error: initial bucket count = " << m.peek_bucket_cnt()
           << ", should be " << 13 << "\n";
      exit(1);
    }
  if (m.peek_resize_limit() != 26)
    {
      cout << "Error: initial resize limit = " << m.peek_resize_limit()
           << ", should be " << 26 << "\n";
      exit(1);
    }
  if (m.peek_bucket_index() != 6)
    {
      cout << "Error: initial bucket index = " << m.peek_bucket_index()
           << ", should be " << 6 << "\n";
      exit(1);
    }
  if (m.peek_orig_bucket_index() != 6)
    {
      cout << "Error: original bucket index = " << m.peek_orig_bucket_index()
           << ", should be " << 6 << "\n";
      exit(1);
    }
  if (m.peek_active_iters() != 0)
    {
      cout << "Error: initial active iters = " << m.peek_active_iters()
           << ", should be " << 0 << "\n";
      exit(1);
    }

  while (infile >> word) {m[word]++;}

  if (m.size() != 196)
    {
      cout << "Error: final size = " << m.size()
           << ", should be " << 196 << "\n";
      exit(1);
    }
  if (m.peek_bucket_cnt() != 127)
    {
      cout << "Error: final bucket count = " << m.peek_bucket_cnt()
           << ", should be " << 127 << "\n";
      exit(1);
    }
  if (m.peek_resize_limit() != 254)
    {
      cout << "Error: final resize limit = " << m.peek_resize_limit()
           << ", should be " << 254 << "\n";
      exit(1);
    }
  if (m.peek_bucket_index() != 18)
    {
      cout << "Error: final bucket index = " << m.peek_bucket_index()
           << ", should be " << 18 << "\n";
      exit(1);
    }
  if (m.peek_orig_bucket_index() != 6)
    {
      cout << "Error: final original bucket index = "
	   << m.peek_orig_bucket_index()
           << ", should be " << 6 << "\n";
      exit(1);
    }
  if (m.peek_active_iters() != 0)
    {
      cout << "Error: final active iters = " << m.peek_active_iters()
           << ", should be " << 0 << "\n";
      exit(1);
    }
  Hmapiter(String,int) i(m);
  while (++i)
    {
      if (m.peek_active_iters() != 1)
        {
	  cout << "Error when writing test_out1: active_iters = " <<
	       m.peek_active_iters() << ", should be 1\n";
	  exit(1);
	}
      outfile1 << setw(3) << i.value() << ": " << i.key() << "\n";
    }
  if (m.peek_active_iters() != 0)
    {
      cout << "Error after writing test_out1: active_iters = " <<
	      m.peek_active_iters() << ", should be 0\n";
      exit(1);
    }
  while (--i)
    {
      if (m.peek_active_iters() != 1)
        {
	  cout << "Error when writing test_out2: active_iters = " << 
	       m.peek_active_iters() << ", should be 1\n";
	  exit(1);
	}
      outfile2 << setw(3) << i.value() << ": " << i.key() << "\n";
    }
  static char* del_word[] =
   {"class", "It", "management", "most", "implementation",
    "hardware", "function", "This", "contains", "such", "details,", "use",
    "provides", "free", "technique", "addresses,", "degree", "safely", "at",
    "minor", "with", "determined", "concepts", "often", "in", "including"};
  static char* bogus_word[] = {"foo", "bar", "baz", "nonsense"};
  for (int k = 0; k < 26; k++)
    {
      if (m.contains(del_word[k]) != 1)
        {
	  cout << "Error: \"" << del_word[k] << "\" not contained in h-map.\n";
	  exit(1);
	}
    }
  for (k = 0; k < 4; k++)
    {
      if (m.contains(bogus_word[k]) != 0)
        {
	  cout << "Error: \"" << bogus_word[k] << "\" contained in h-map.\n";
	  exit(1);
	}
    }
  for (k = 0; k < 26; k++)
    {
      if (m.remove(del_word[k]))
        {
	  cout << "Error: couldn\'t find \"" << del_word[k] <<
		"\" to remove it.\n";
	  exit(1);
	}
    }
  for (k = 0; k < 4; k++)
    {
      if (!m.remove(bogus_word[k]))
        {
	  cout << "Error: remove says \"" << del_word[k] <<
		"\" was in table.\n";
	  exit(1);
	}
    }
    
  while (i++) outfile3 << setw(3) << i.value() << ": " << i.key() << "\n";

  if (m.size() != 170)
    {
      cout << "Error: after removing 26 elements, size = " << m.size() <<
         ", it should be " << 170 << "\n";
      exit(1);
    }

  while (i++)
    if (i.value() == 1)
      if (i.remove())
         {
	   cout << "Error: Attempted to delete vacuous element\n";
	   exit(1);
	 }

  while (i++) outfile4 << setw(3) << i.value() << ": " << i.key() << "\n";

  if (m.size() != 34)
    {
      cout << "Error: after removing all words that occurred once, size = " <<
	m.size() << ",\n it should be " << 34 << "\n";
      exit(1);
    }

  Hmapiter(String,int) j(m);
  
  if (i != j || !(i == j))
    {
      cout << "Error: two vacuous iterators for same h-map tested unequal.\n";
      exit(1);
    }
  
  if (m.peek_active_iters() != 0)
    {
      cout << "Error in iter test 1: active iters = " << m.peek_active_iters()
           << ", should be " << 0 << "\n";
      exit(1);
    }
  i++;
  if (i == j || !(i != j))
    {
      cout << "Error: two unequal iterators tested equal.\n";
      exit(1);
    }
  if (m.peek_active_iters() != 1)
    {
      cout << "Error in iter test 2: active iters = " << m.peek_active_iters()
           << ", should be " << 1 << "\n";
      exit(1);
    }
  j = i;
  if (i != j || !(i == j))
    {
      cout << "Error: two equal iterators tested unequal.\n";
      exit(1);
    }
  if (m.peek_active_iters() != 2)
    {
      cout << "Error in iter test 3: active iters = " << m.peek_active_iters()
           << ", should be " << 2 << "\n";
      exit(1);
    }
  Hmapiter(String,int) *l = new Hmapiter(String,int)(m);
  if (m.peek_active_iters() != 2)
    {
      cout << "Error in iter test 4: active iters = " << m.peek_active_iters()
           << ", should be " << 2 << "\n";
      exit(1);
    }
  (*l)--;
  if (m.peek_active_iters() != 3)
    {
      cout << "Error in iter test 5: active iters = " << m.peek_active_iters()
           << ", should be " << 3 << "\n";
      exit(1);
    }
  j--;
  if (m.peek_active_iters() != 2)
    {
      cout << "Error in iter test 6: active iters = " << m.peek_active_iters()
           << ", should be " << 2 << "\n";
      exit(1);
    }
  i = m;
  if (m.peek_active_iters() != 1)
    {
      cout << "Error in iter test 7: active iters = " << m.peek_active_iters()
           << ", should be " << 1 << "\n";
      exit(1);
    }
  delete l;
  if (m.peek_active_iters() != 0)
    {
      cout << "Error in iter test 8: active iters = " << m.peek_active_iters()
           << ", should be " << 0 << "\n";
      exit(1);
    }
  cout << "Hmmm... no obvious bugs.  Now check that:\n";
  cout <<
"test_out1 has the same lines as test_out1.ok.  (The order may be different\n"
<< "because of differences in the string hash function, so you may have to\n"
<< "sort them before comparing.)\n";
  cout <<
"test_out2 has the same lines as test_out1, but in the reverse order.\n";
  cout <<
"test_out3 has the same lines as test_out3.ok.  (The order may be different.)"
<< "\n";
  cout <<
"test_out4 has the same lines as test_out4.ok.  (The order may be different.)\n";
}
