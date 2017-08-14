#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace __gnu_pbds;

int main() {
  /// Ordered Set
  typedef tree< int, null_type, less<int>, rb_tree_tag,
  tree_order_statistics_node_update> ordered_set;

  ordered_set X;
  X.insert(1);
  cout<<*X.find_by_order(1)<<endl; // 2
  cout<<X.order_of_key(-5)<<endl;  // 0


  /// Ordered Multiset. Notice the less_equal<int> parameter.
  typedef tree<int, null_type, less_equal<int>, rb_tree_tag,
  tree_order_statistics_node_update> ordered_multiset;

  ordered_multiset x;

  x.insert(0);
  x.insert(1);
  x.insert(1);
  x.insert(2);

  x.erase(x.find_by_order(x.order_of_key(0))); /// erasing is tricky

  cout<<*x.find_by_order(0)<<endl;

  /// Pair <int,int> Ordered Set
  typedef tree<pair<int,int>, null_type, less_equal<pair<int,int>>, rb_tree_tag,
  tree_order_statistics_node_update> ordered_pair;

  return 0;
}
