#include "illini_book.hpp"

#include "utilities.hpp"


IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {

  std::ifstream ifs(people_fpath);
  int val = 0;
  while (ifs.good()) {
    ifs >> val;
    AddVertex(val);
  }
  std::ifstream ifs2(relations_fpath);
  std::string line;
  std::vector<std::vector<std::string>> vect;
  while (ifs2.good()) {
    ifs2 >> line;
    vect.push_back(utilities::Split(line, ','));
  }
  AddEdges(vect);
}

std::map<int, std::list<std::pair<int, std::string>>> IlliniBook::GetGraph() {
  return graph_;
}

void IlliniBook::AddVertex(const int& vertex) {
  graph_.insert({vertex, std::list<std::pair<int, std::string>>()});
}

void IlliniBook::AddEdges(std::vector<std::vector<std::string>> vect) {
  for (size_t i = 0; i < vect.size(); i++) {
    std::pair<int, std::string> connection1;
    connection1.first = std::stoi(vect.at(i).at(0));
    connection1.second = vect.at(i).at(2);
    std::pair<int, std::string> connection2;
    connection2.first = std::stoi(vect.at(i).at(1));
    connection2.second = vect.at(i).at(2);
    graph_.at(std::stoi(vect.at(i).at(0))).push_back(connection2);
    graph_.at(std::stoi(vect.at(i).at(1))).push_back(connection1);
  }
}

void PrintList(std::list<std::pair<int, std::string>> list) {
  while (!list.empty()) {
    std::cout << list.front().first << "  " << list.front().second << "  ";
    list.pop_front();
  }
  std::cout << std::endl;
} 

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  std::map<int, bool> visited;
  for (auto i: graph_) {
    visited.insert({i.first, false});
  }
  visited.at(uin_1) = true;
  std::queue<int> queue;
  queue.push(uin_1);
  while (!queue.empty()) {
    int start = queue.front();
    if (start == uin_2) {
      return true;
    }
    queue.pop();
    for (auto i : graph_.at(start)) {
      if (!visited.at(i.first)) {
        visited.at(i.first) = true;
        queue.push(i.first);
      }
    }
  }
  return false;
}

bool IlliniBook::AreRelated(int uin_1,
                            int uin_2,
                            const std::string& relationship) const {
  std::map<int, bool> visited;
  for (auto i: graph_) {
    visited.insert({i.first, false});
  }
  visited.at(uin_1) = true;
  std::queue<int> queue;
  queue.push(uin_1);
  while (!queue.empty()) {
    int start = queue.front();
    if (start == uin_2) {
      return true;
    }
    queue.pop();
    for (auto i : graph_.at(start)) {
      if (!visited.at(i.first) && i.second == relationship) {
        visited.at(i.first) = true;
        queue.push(i.first);
      }
    }
  }
  return false;
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
    if (!AreRelated(uin_1, uin_2)) {
        return -1;
    }
    std::map<int, bool> visited;
    for (auto i: graph_) {
      visited.insert({i.first, false});
    }
    std::map<int, int> distance;
    for (auto i: graph_) {
      distance.insert({i.first, 0});
    }
    visited.at(uin_1) = true;
    std::queue<int> queue;
    queue.push(uin_1);
    while (!queue.empty()) {
        int start = queue.front();
        queue.pop();
        for (auto i: graph_.at(start)) {
            if (!visited.at(i.first)) {
                distance.at(i.first) = distance[start] + 1;
                visited.at(i.first) = true;
                queue.push(i.first);
            }

            if (start == uin_2) {
                return distance.at(uin_2);
            }
        }
    }
    return 0;
} 

int IlliniBook::GetRelated(int uin_1,
                           int uin_2,
                           const std::string& relationship) const {
  if (!AreRelated(uin_1, uin_2)) {
    return -1;
  }
  std::map<int, bool> visited;
    for (auto i: graph_) {
      visited.insert({i.first, false});
    }
  std::map<int, int> distance;
  for (auto i: graph_) {
    distance.insert({i.first, 0});
  }
  visited.at(uin_1) = true;
  std::queue<int> queue;
  queue.push(uin_1);
  while (!queue.empty()) {
    int start = queue.front();
    queue.pop();
    for (auto i : graph_.at(start)) {
      if (!visited.at(i.first) && i.second == relationship) {
        distance.at(i.first) = distance[start] + 1;
        visited.at(i.first) = true;
        queue.push(i.first);
      }

      if (start == uin_2) {
        return distance[uin_2];
      }
    }
  }
  return -1;
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
    std::map<int, bool> visited;
    std::map<int, int> distance;
    visited[uin] = true;
    std::queue<int> queue;
    queue.push(uin);
    while (!queue.empty()) {
        int start = queue.front();
        queue.pop();
        for (auto i: graph_.at(start)) {
            if(!visited[i.first]) {
                distance[i.first] = distance[start] + 1;
                visited[i.first] = true;
                queue.push(i.first);
            }
        }
        if (distance[start] == n) {
          break;
        } 
    }
    std::vector<int> step_vect;
    for (auto i: distance) {
      if (i.second == n) {
        step_vect.push_back(i.first);
      }
    }
    return step_vect;
}

void IlliniBook::DFS(const int &vertex, std::map<int, bool> &visited) const {
  visited.at(vertex) = true;
  for (auto i: graph_.at(vertex)) {
    if (!visited.at(i.first)) {
      DFS(i.first, visited);
    }
  }
}

size_t IlliniBook::CountGroups() const {
  std::map<int, bool> visited;
  for (auto i: graph_) {
    visited.insert({i.first, false});
  }
  int count = 0;
  for (auto i: graph_) {
    if (!visited.at(i.first)) {
      DFS(i.first, visited);
      count++;
    }
  }
  return count;
}

void IlliniBook::DFS(const int &vertex, std::map<int, bool> &visited, const std::string& relationship) const {
  visited[vertex] = true;
  for (auto i: graph_.at(vertex)) {
    if (i.second == relationship && !visited[i.first]) {
      DFS(i.first, visited, relationship);
    }
  }
}

size_t IlliniBook::CountGroups(const std::string& relationship) const {
  std::map<int, bool> visited;
  for (auto i: graph_) {
    visited.insert({i.first, false});
  } 
  int count = 0;
  for (auto i: graph_) {
    if (!visited[i.first]) {
      DFS(i.first, visited, relationship);
      count++;
    }
  }
  return count;
}

void IlliniBook::DFS(const int &vertex, std::map<int, bool> &visited, const std::vector<std::string>& relationships) const {
  visited[vertex] = true;
  for (auto i: graph_.at(vertex)) {
    for (auto j: relationships) {
      if (i.second == j && !visited[i.first]) {
        DFS(i.first, visited, relationships);
        break;
      }
    }
  }
}


size_t IlliniBook::CountGroups(
    const std::vector<std::string>& relationships) const {
      std::map<int, bool> visited;
  int count = 0;
  for (auto i: graph_) {
    if (!visited[i.first]) {
      DFS(i.first, visited, relationships);
      count++;
    }
  }
  return count;
}
