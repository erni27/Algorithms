/*
 Algorithm written for recruitment purposes.
 Author: Ernest Nguyen Hung
 Problem: Pensje, XIV Olimpiada Informatyczna
*/


#include <iostream>
#include <vector>
#include <queue>

// Maximum number of employees.
const int MAX = 1000001;

// Employee's structure.
struct Employee {
    int salary;
    int father_id;
    std::vector<int> direct_child_id;
};

// Employees' array - index indicate the number of employee.
Employee employees[MAX];

// Keys' (key = salary) array - index indicate the amount of salary
// and value indicates who makes that much money
int salary_taken[MAX];

// Employee's all child without salary - index indicate the number of employee.
int all_child[MAX];

// Employee's direct child without salary.
int direct_child[MAX];

int employees_amount;

// Auxiliary queue for counting all child.
std::queue<int> queue;

// Count all child (it takes only these without salary) given employee.
void count_child() {

    // Store calculated amount of direct child in a seperate array.
    for (int i=1; i<=employees_amount; i++) {
        direct_child[i] = employees[i].direct_child_id.size();
        // Pass these employees who don't have any child at the back of queue.
        if (direct_child[i] == 0) {
            queue.push(i);
        }
    }


    // Iterate through queue and count all child.
    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();
        if (employees[current].salary == 0) {
            // Pass employee's father if does have more than one children
            // at the back of queue.
            if (!--direct_child[employees[current].father_id]) {
                queue.push(employees[current].father_id);
            }
            // Add children's child and children
            all_child[employees[current].father_id] += all_child[current] + 1;
        }
    }
}



int main(int argc, const char * argv[]) {

    // Initialize input structures.
    scanf("%d", &employees_amount);
    // Read Input Data.
    for (int i=1; i<=employees_amount; i++) {
        scanf("%d %d\n", &employees[i].father_id, &employees[i].salary);

        // If this the boss.
        if (i == employees[i].father_id) {
            employees[i].salary = employees_amount;
        }
        else if (employees[i].salary == 0) {
                employees[employees[i].father_id].direct_child_id.push_back(i);
        }

        // Mark taken salary.
        salary_taken[employees[i].salary] = i;
    }

    // Count all child.
    count_child();
    int how_many_available = 0;
    int how_many_possible = 0;
    int i = 1;

    // Assign salary.
    while (i<=employees_amount) {
        while (i<=employees_amount && salary_taken[i] == 0) {
            how_many_possible++;
            how_many_available++;
            ++i;
        }
        while(i<=employees_amount && salary_taken[i] != 0) {
            int current = salary_taken[i];
            int tmp = i;
            how_many_available -= all_child[current];
            ++i;
            if (how_many_available == 0) {
                while (how_many_possible > 0 &&
                       employees[current].direct_child_id.size() == 1) {
                    while (salary_taken[tmp]) --tmp;
                    current = employees[current].direct_child_id[0];
                    employees[current].salary = tmp;
                    salary_taken[tmp] = current;
                    --how_many_possible;
                }
                how_many_possible = 0;
            }
            if (all_child[current] != 0) {
                how_many_possible = 0;
            }
        }
    }

    // Print result.
    for (int i = 1; i <= employees_amount; i++)
        printf("%d\n", employees[i].salary);
    return 0;
}
