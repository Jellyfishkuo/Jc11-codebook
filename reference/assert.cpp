
template <typename T>
bool AssertVectorIsSorted(vector<T>& vec){
    for(int i=0;i<(int)vec.size()-1;++i)
        if(vec[i]>vec[i+1]) return false;
    return true;
}