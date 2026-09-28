class Utils {
  public:
    static int max_p2_less_n(int n) {
        return __builtin_clz(1) - __builtin_clz(n);
    }
    static long long max_p2_less_n(long long n) {
        return __builtin_clzll(1) - __builtin_clzll(n);
    }
    template<typename T>
    static T max(T a,T b) {
        return std::max(a,b);
    }
    template<typename T>
    static T min(T a,T b) {
        return std::min(a,b);
    }

};

class SparseTable {

    int max_power_of_two;
    int sparse_table_size;
    vector<vector<int>> sparse_table;
    function<int(int,int)> compare_function;

  public:
    SparseTable(vector<int>& v, function<int(int,int)>compare) {
        compare_function=compare;
        sparse_table_size=v.size();
        max_power_of_two= Utils::max_p2_less_n(sparse_table_size);
        sparse_table.assign(max_power_of_two+1,vector<int>(sparse_table_size));

        for(int i=0; i<sparse_table_size; i++) {
            sparse_table[0][i]=v[i];
        }

        for(int i=1; i<=max_power_of_two; i++) {
            for(int j=0; j<sparse_table_size; j++) {
                sparse_table[i][j]=compare(sparse_table[i-1][j],sparse_table[i-1][j + (1 << (i-1))]);
            }
        }

    }

    int get(int l, int r) {
        int ans=INT_MAX;
        int crnt_segment_size=(r-l+1);
        int crnt_segment_max_p2=Utils::max_p2_less_n(crnt_segment_size);
        return compare_function(sparse_table[crnt_segment_max_p2][l],sparse_table[crnt_segment_max_p2][r- (1<<crnt_segment_max_p2)+1]);
    }



int main(){

  vector<int> v ={1,2,3};
  SparseTable sparse_table(v,Utils::min)
  cout<<sparse_table.get(0,2);
  return 0;
}
  



};
