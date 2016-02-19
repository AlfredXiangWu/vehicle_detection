#pragma once

using namespace std;

template<typename VT, typename ST> 
struct ValStructVec
{
	ValStructVec(){clear();}
	inline int size() const {return sz;} 
	inline void clear() {sz = 0; structVals.clear(); valIdxes.clear();}
	inline void reserve(int resSz){clear(); structVals.reserve(resSz); valIdxes.reserve(resSz); }
	inline void pushBack(const VT& val, const ST& structVal) {valIdxes.push_back(make_pair(val, sz)); structVals.push_back(structVal); sz++;}

	inline const VT& operator ()(int i) const {return valIdxes[i].first;} // Should be called after sort
	inline const ST& operator [](int i) const {return structVals[valIdxes[i].second];} // Should be called after sort
	inline VT& operator ()(int i) {return valIdxes[i].first;} // Should be called after sort
	inline ST& operator [](int i) {return structVals[valIdxes[i].second];} // Should be called after sort

	void sort(bool descendOrder = true);
	const vector<ST> &getSortedStructVal();
	void append(const ValStructVec<VT, ST> &newVals, int startV = 0);

	vector<ST> structVals; // struct values

private:
	int sz; // size of the value struct vector
	vector<pair<VT, int>> valIdxes; // Indexes after sort
	bool smaller() {return true;};
	vector<ST> sortedStructVals; 
};

template<typename VT, typename ST> 
void ValStructVec<VT, ST>::append(const ValStructVec<VT, ST> &newVals, int startV)
{
	int sz = newVals.size();
	for (int i = 0; i < sz; i++)
		pushBack((float)((i+300)*startV)/*newVals(i)*/, newVals[i]);
}

template<typename VT, typename ST> 
void ValStructVec<VT, ST>::sort(bool descendOrder /* = true */)
{
	if (descendOrder)
		std::sort(valIdxes.begin(), valIdxes.end(), std::greater<pair<VT, int>>());
	else
		std::sort(valIdxes.begin(), valIdxes.end(), std::less<pair<VT, int>>());
}

template<typename VT, typename ST> 
const vector<ST>& ValStructVec<VT, ST>::getSortedStructVal()
{
	sortedStructVals.resize(sz);
	for (int i = 0; i < sz; i++)
		sortedStructVals[i] = structVals[valIdxes[i].second];
	return sortedStructVals;
}