
#include "ISearchable.h"
#include "MatrixSearchProblem.h"
#include "vector"
#include "../Utils.h"


#define ENDLINE "|"


#ifndef HNJ_2NDROAD_MATRIX_H
#define HNJ_2NDROAD_MATRIX_H

class Matrix : public ISearchable<int, POINT> {
    vector<vector<SearchNode<int>*>> matrix;
    int colNum;

public:
    Matrix() {
        colNum = 0;

    }

    void addRow(string row) {
        if (!row.empty()) {
            auto *realRow= new vector<SearchNode<int>*>() ;
            createRow(Utils::split(row, ','),realRow);
            colNum = (int) realRow->size();
            matrix.push_back(*realRow);
        }
    }

    void createRow(vector<string> row, vector<SearchNode<int>*> *result) {
        for (const string &value:row) {
            int x = atoi(value.data());
            auto node= new SearchNode<int >();
            createNode(&x,node);
            result->push_back(node);
        }

    }

    virtual SearchNode<int> *get(POINT searchFor) {
        if (matrix.empty() || colNum - 1 < searchFor.x || matrix.size() - 1 < searchFor.y || searchFor.x < 0 ||
            searchFor.y < 0) {
            //matrix is empty || in valid request ||
            return nullptr;
        }
        if (*(matrix[searchFor.y][searchFor.x]->value) == -1) {
            return nullptr;
        }
        return matrix[searchFor.y][searchFor.x];
    }

    virtual vector<SearchNode<int> *> *getNeighbours(SearchNode<int> *searchFor) {
        auto *friends = new vector<SearchNode<int> *>();

        //assign friends (real) the direction they were reached from
        if (searchFor->right != nullptr) {
          //  searchFor->right->cameFromFirection = RIGHT;
            friends->push_back(searchFor->right);
        }
        if (searchFor->left != nullptr) {
            //searchFor->left->cameFromFirection = LEFT;
            friends->push_back(searchFor->left);
        }
        if (searchFor->up != nullptr) {
            //searchFor->up->cameFromFirection = UP;
            friends->push_back(searchFor->up);
        }
        if (searchFor->down != nullptr) {
            //searchFor->down->cameFromFirection = DOWN;
            friends->push_back(searchFor->down);
        }
/*
        //assign parent situation
        for (SearchNode<int> *node:*friends) {
            node->parent = searchFor;
        }
        */
        return friends;

    }

    void createNode(int *x,SearchNode<int>*nodeMatrix) {
        nodeMatrix->value = x;
        nodeMatrix->cost = *x;
        nodeMatrix->parent = NULL;
        nodeMatrix->up = nullptr;
        nodeMatrix->left = nullptr;
        nodeMatrix->right = nullptr;
        nodeMatrix->down = nullptr;
     

    }

    void assignFriends() {
        int y = 0;
        for (vector<SearchNode<int>*> v: matrix) {
            int x = 0;
            for (SearchNode<int> *node:v) {
                node->up = get(POINT(x, y - 1));
                node->down = get(POINT(x, y + 1));
                node->right = get(POINT(x + 1, y));
                node->left = get(POINT(x - 1, y));
                x++;
            }
            //move to other line
            y++;
        }
    }

    virtual string matToString() {
        string result;
        for (vector<SearchNode<int>*> s:matrix) {
            for (SearchNode<int> *c: s) {
                int val = *c->value;
                result += to_string(val);
                result += COMMA;
            }
            result += ENDLINE;
        }
        return result;
    }


};


#endif
