#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ordered_set tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update>
using namespace __gnu_pbds;




I noticed that using the comparison operator " less_equal <data_type> "
 makes the two functions " s.lower_bound(value) , s.upper_bound(value) "
 exchange their functions for any value, depending on that to erase one occurrence of some value from the set we can write "s.erase(s.upper_bound(value)) "
, just that simple, it will work efficiently



source : https://codeforces.com/blog/entry/88193
