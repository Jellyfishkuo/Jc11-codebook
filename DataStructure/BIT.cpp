template <class T> class BIT {
private:
	int size;
	vector<T> bit;
	vector<T> arr;

public:
	BIT(int sz=0):
    size(sz), bit(sz+1), arr(sz) {}

	/** Sets the value at index idx to val. */
	void set(int idx, T val) {
    add(idx, val - arr[idx]);
  }

	/** Adds val to the element at index idx. */
	void add(int idx, T val) {
		arr[idx] += val;
		for (++idx; idx<=size; idx+=(idx & -idx))
      bit[idx] += val;
	}

	/** The sum of all values in [0, idx]. */
	T pre_sum(int idx) {
		T total = 0;
		for (++idx; idx>0; idx-=(idx & -idx))
      total += bit[idx];
		return total;
	}
};
