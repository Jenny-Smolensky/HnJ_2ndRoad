//
// Created by jenny on 1/14/19.
//

#ifndef HNJ_2NDROAD_STATE_H
#define HNJ_2NDROAD_STATE_H
#define COMMA ","

#include <string>
#include "vector"

using namespace std;
enum DIRECTION {
    UP, DOWN, RIGHT, LEFT
};

template<class Type>
class SearchNode {
public:
    Type *value;
    double cost;
    SearchNode *parent;
    SearchNode *up;
    SearchNode *down;
    SearchNode *right;
    SearchNode *left;
    DIRECTION cameFromFirection;

    vector<SearchNode<Type> *> *getFriends() {
        auto *friends = new vector<SearchNode<Type> *>();
        friends->insert(up);
        friends->insert(down);
        friends->insert(right);
        friends->insert(left);
        return friends;

    }

};

class POINT {
public:
    int x;
    int y;

    string pointToString() {
        string res;
        res += to_string(x);
        res += COMMA;
        res += to_string(y);
        return res;
    }


};


#endif //HNJ_2NDROAD_STATE_H
