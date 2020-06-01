/*
 Algorithm written for recruitment purposes.
 Author: Ernest Nguyen Hung
 Problem: Plakatowanie, XV Olimpiada Informatyczna
*/


#include <iostream>

// Poster's structure.
struct Poster {
    int height;
    Poster *previous;
};
// Poster's stack implementation.
class PostersStack {
private:
    Poster *top;
public:
    PostersStack();
    void Push(int);
    void Pop();
    int Top();
    bool IsEmpty();
};
PostersStack::PostersStack() {
    this->top = NULL;
}
void PostersStack::Push(int poster_height) {
    Poster *tmp = new Poster;
    tmp->height = poster_height;
    tmp->previous = this->top;
    this->top = tmp;
}
void PostersStack::Pop() {
    Poster *tmp = this->top;
    this->top = this->top->previous;
    delete tmp;
}
int PostersStack::Top() {
    return this->top->height;
}
bool PostersStack::IsEmpty() {
    if (this->top == NULL) {
        return true;
    }
    return false;
}

// Maximum number of buildings standing in a row equals 250000.
// In this case, array is used to store input data (indexing from 1 to 250000).
// That's why maximum array size equals 250001.
const int MAX=250001;

// Input data array declaration.
int blocks_height[MAX];

int blocks_amount, block_width, posters_amount;

int main(int argc, const char * argv[]) {

    // Poster's stack declaration.
    PostersStack *posters = new PostersStack();

    posters_amount = 0;

    // Read input data.
    // The width of the block is irrelevant, so it is skipped.
    scanf("%d\n",&blocks_amount);
    for (int i=1; i<=blocks_amount; i++)
        scanf("%d %d\n",&block_width, &blocks_height[i]);

    // Iterate through all blocks.
    for (int i=1; i<=blocks_amount; i++) {
        // While height of the unfinished poster on the top
        // is greater than height of the current block,
        // finish the poster which means
        // pop it from the stack.
        while (!(posters->IsEmpty()) && (posters->Top() > blocks_height[i])) {
            posters->Pop();
        }

        // If there are no unfinished posters on the stack
        // or height of the unfinished poster on the top
        // is smaller than height of the current block,
        // push unfinished poster onto stack and
        // increment total amount of posters.
        if ((posters->IsEmpty()) || (posters->Top() < blocks_height[i])) {
            posters->Push(blocks_height[i]);
            posters_amount++;
        }
    }

    // Print total amount of posters.
    printf("%d\n",posters_amount);

    // Release allocated memory for poster's stack.
    delete posters;
    return 0;
}
