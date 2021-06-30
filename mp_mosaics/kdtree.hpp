/**
* @file kdtree.cpp
* Implementation of KDTree class.
*/

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
  const Point<Dim>& second, int curDim) const
  {
    /**
    * @todo Implement this function!
    */
    if (first[curDim] < second[curDim]) {
      return true;
    } else if (first[curDim] == second[curDim]) {
      return first < second;
    }
    else {
      return false;
    }
  }

  template <int Dim>
  bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
    const Point<Dim>& currentBest,
    const Point<Dim>& potential) const
    {
      /**
      * @todo Implement this function!
      */
      int currDist = 0, potDist = 0;
      for (int i = 0; i < Dim; i++) {
        currDist += pow((target[i] - currentBest[i]), 2);
        potDist += pow((target[i] - potential[i]), 2);
      }

      if (potDist != currDist) {
        return potDist < currDist;
      }

      return potential < currentBest;
    }

    template<int Dim>
    KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
    {
      /**
      * @todo Implement this function!
      */
      count = 0;
      root = NULL;
      if (newPoints.size() == 0) {
        return;
      }
      points = newPoints;

      if(newPoints.size() != 0) {
        constructor(0, points.size()-1, 0, root);
      }
    }


    template <int Dim>
    void KDTree<Dim>::constructor(int s, int e, int d, KDTreeNode *&subroot)
    {
      int medianIndex = (s + e) / 2;
      Point<Dim> medianPoint = quickSelectSort(s, e, medianIndex, d);
      subroot = new KDTreeNode(medianPoint);
      if (s == e) {
        return;
      }
      if (e - s != 1) {
        constructor(s, medianIndex - 1, (d + 1) % Dim, subroot->left);
      }
      constructor(medianIndex + 1, e, (d + 1) % Dim, subroot->right);
    }


    template <int Dim>
    Point<Dim> KDTree<Dim>::quickSelectSort(int s, int e, int k, int d)
    {
      if (s == e) {
        return points[s];
      }
      int pivotIndex = (s+e)/2;
      pivotIndex = partition(s, e, pivotIndex, d);
      if (k <  pivotIndex) {
        return quickSelectSort(s, pivotIndex-1, k, d);
      }
      else if (k > pivotIndex) {
        return quickSelectSort(pivotIndex+1, e, k, d);
      } else {
        return points[pivotIndex];
      }
    }

    template <int Dim>
    int KDTree<Dim>::partition(int s, int e, int k, int d)
    {
      Point<Dim> start = points[s];
      swap(points[s], points[e]);
      int i = s;
      for(int j = s; j < e; j++) {
        if (smallerDimVal(points[j], start, d)) {
          swap(points[i], points[j]);
          i++;
        }
      }

      swap(points[i], points[e]);
      return i;
    }

    template <int Dim>
    KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
      /**
      * @todo Implement this function!
      */
    }


    template <int Dim>
    const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
      /**
      * @todo Implement this function!
      */

      return *this;
    }

    template <int Dim>
    KDTree<Dim>::~KDTree() {
      /**
      * @todo Implement this function!
      */
      destructor(root);
    }

    template <int Dim>
    void KDTree<Dim>::destructor(KDTreeNode *&subroot) {
      if (subroot == NULL) {
        return;
      }

      if (subroot->left == NULL && subroot->right == NULL) {
        delete subroot;
        return;
      }

      destructor(subroot->left);
      destructor(subroot->right);
      delete subroot;
    }

    template <int Dim>
    Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
    {
      /**
      * @todo Implement this function!
      */
      return *FNNHelper(query, root, 0);

    }

    template<int Dim>
    int KDTree<Dim>::distance(const Point<Dim> &a, const Point<Dim>&b) const
    {
      int value = 0;
      for (int i = 0; i < Dim; i++)
      {
        value+= pow(a[i]-b[i],2);
      }
      return value;
    }

    template <int Dim>
    Point<Dim>* KDTree<Dim>::FNNHelper(const Point<Dim>& query, KDTreeNode *subroot, int currDim) const
    {
      /**
      * @todo Implement this function!
      */
      if (subroot == NULL) {
        return NULL;
      }
      if (subroot->left == NULL && subroot->right == NULL) {
        return &subroot->point;
      }

      Point<Dim> *currentBest = NULL;
      bool side1 = false;
      if (smallerDimVal(subroot->point, query, currDim)) {
        currentBest = FNNHelper(query, subroot->right, (currDim + 1) % Dim);
      } else {
        currentBest = FNNHelper(query, subroot->left, (currDim + 1) % Dim);
        side1 = true;
      }

      if (currentBest == NULL) {
        currentBest = &subroot->point;
      }
      double currentRadiusSquared = distance(*currentBest, query);
      if (shouldReplace(query, *currentBest, subroot->point)) {
        currentBest = &subroot->point;
        currentRadiusSquared = distance(*currentBest, query);
      }

      Point<Dim> *newPotential = NULL;
      if (abs(query[currDim] - subroot->point[currDim]) <= sqrt(currentRadiusSquared)) {
        if (side1) {
          newPotential = FNNHelper(query, subroot->right, (currDim + 1) % Dim);
        } else {
          newPotential = FNNHelper(query, subroot->left, (currDim + 1) % Dim);
        }
      }
      if (newPotential == NULL) {
        newPotential = &subroot->point;
      }

      if (shouldReplace(query, *currentBest, *newPotential)) {
        currentBest = newPotential;
        currentRadiusSquared = distance(*currentBest, query);
      }
      return currentBest;
    }
