template <typename T = int>
vector<T> randomvec(int n){
    vector<T> vec(n);
    unsigned seed=chrono::system_clock::now()
                .time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_real_distribution<double> distribution(0.0,200.0);
    for(T &num:vec) num=distribution(generator);
    return vec;
}