/* Your code here! */
#include "dsets.h"
#include <vector>

void DisjointSets::addelements(int num) {
  for (int i = 0; i < num; i++) {
    elements_.push_back(-1);
  }
}

int DisjointSets::find(int elem) {
  if (elements_[elem] < 0) {
    return elem;
  } else {
    return find(elements_[elem]);
  }
}

void DisjointSets::setunion(int a, int b) {

  int a_set = find(a);
  int b_set = find(b);
  int temp;
  if (elements_[a_set] <= elements_[b_set]) {
    temp = elements_[b_set];
    elements_[b_set] = a_set;
    elements_[a_set] += temp;
  } else {
    temp = elements_[a_set];
    elements_[a_set] = b_set;
    elements_[b_set] += temp;
  }
  

}

int DisjointSets::size(int elem) {
  if (elements_[elem] < 0) {
    return -1 * elements_[elem];
  }

  return -1 * elements_[find(elem)];
}
