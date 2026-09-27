
mt19937  rnd(chrono::steady_clock::now().time_since_epoch().count());  #creating a random generator called mt there is also mt19937ll  
#int x=rnd();
# the code above gives a random number from 0 to 2^31 however using modulo to bound the range will introduce modulo bias so the soultion is to use uniform_int_distribuation
int x=uniform_int_distribution<int>(0,1e9)(rnd);
# auto r=unifor_int_distribuation<int>(0,1e9);

