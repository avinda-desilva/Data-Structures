#include <queue>
#include <algorithm>
#include <string>
#include <list>

/**
* Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
*
* This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
* the `end` vertex as the last element in the list, and an ordered list of all vertices that must
* be traveled along the shortest path.
*
* For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
*
* You should use undirected edges. Hint: There are no edge weights in the Graph.
*
* @param start The key for the starting vertex.
* @param end   The key for the ending vertex.
*/
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  // TODO: Part 3
  std::list<std::string> path;

  std::string copyOfStart = start;
  std::string copyOfEnd = end;
  std::string temp = "";
  std::string tempsNext = "";
  std::string temp1 = copyOfEnd;

  std::queue<string> queue;
  int numberOfPaths = 0;

  std::unordered_map<string , bool> alreadyVisited;
  std::unordered_map<string , string> previous;
  std::unordered_map<string , int> dist;


  for (std::pair<std::string, V &> theElement : vertexMap) {
    auto x = theElement.first;
    int infinity = INT_MAX;

    dist.insert({x , infinity});
    previous.insert({x , temp});
    alreadyVisited.insert({x , false});
  }

  queue.push(copyOfStart);
  dist[copyOfStart] = 0;
  alreadyVisited[start] = true;

  while (queue.empty() == false) {
    temp = queue.front();
    queue.pop();

    auto iterBegin = adjList[temp].begin();
    auto iterEnd = adjList[temp].end();

    for (auto i = iterBegin; i != iterEnd; i++) {
      auto x = dist[temp] + 1;
      if ((*(*i)).get().dest().key() != temp) {
        tempsNext = (*(*i)).get().dest().key();
      }

      if ((*(*i)).get().dest().key() == temp) {
        tempsNext = (*(*i)).get().source().key();
      }

      if (alreadyVisited[tempsNext] == true && (dist[temp] + 1) < dist[tempsNext]) {
        previous[tempsNext] = temp;
        dist[tempsNext] = x;
        numberOfPaths++;

      }

      if (alreadyVisited[tempsNext] == false) {
        previous[tempsNext] = temp;
        dist[tempsNext] = x;
        alreadyVisited[tempsNext] = true;
        queue.push(tempsNext);
        numberOfPaths++;

      }

    }
  }


  while (temp1 != "") {
    path.push_front(temp1);
    temp1 = previous.at(temp1);
  }

  return path;

}
