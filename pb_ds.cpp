#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> // Required for tree_order_statistics_node_update

using namespace __gnu_pbds; // Namespace for PBDS
using namespace std;

// Define the PBDS indexed set
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;

int main() {
    indexed_set s;

    // Insert elements into the set
    s.insert(2);
    s.insert(3);
    s.insert(7);
    s.insert(9);

    // Find the 3rd element (0-indexed)
    auto x = s.find_by_order(2); // Finds the element at index 2

    // Find the order of the key 7
    int y = s.order_of_key(7); // Finds the index of the key 7

    // Output the results
    cout << *x << " " << y << endl;

    return 0;
}
