#include <iostream>
#include <vector>
#include <queue>
using namespace std;

template<class comp = less<int>>
struct minStack{
	deque<pair<int, int>> q;
	int cnt_added = 0;
	int cnt_removed = 0;
	minStack(){
		q.clear();
		cnt_added = 0;
		cnt_removed = 0;
	}
	int top(){
		if (q.empty()) return 0;
		return q.front().first;
	}
	void push(int new_element){
		while (!q.empty() && !comp{}(q.back().first, new_element))
			q.pop_back();
		q.push_back({new_element, cnt_added});
		cnt_added++;
	}
	void pop(){
		if (!q.empty() && q.front().second == cnt_removed)
			q.pop_front();
		cnt_removed++;
	}
};