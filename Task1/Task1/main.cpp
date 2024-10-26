#include<iostream>
#include<future>	
#include<chrono>
#include<vector>
#include<thread>

using namespace std;
void findMinElement(const vector<int>& V,int start, promise<int>minIndexPromise)
{
	int minIndex = start;

	for (int j = start + 1; j < V.size(); j++) {
		if (V[j] < V[minIndex]) {
			minIndex = j;
		
		}
	
	}
	minIndexPromise.set_value(minIndex);
}

void selectionSort(vector<int>& V)
{
	int n = V.size();

	for (int i = 0; i < n - 1; ++i) 
	{
		promise<int>minIndexPromise;
		future<int>miIndexFuture = minIndexPromise.get_future();

		thread(findMinElement, cref(V), i, move(minIndexPromise)).detach();
		int minIndex = miIndexFuture.get();

		swap(V[i], V[minIndex]);

	}

}



int main() 
{
	setlocale(LC_ALL, "RU");
	vector<int> V{ 23,44,57,24,1 };
	cout << "Массив до сортировки: ";
	for (auto num : V) {
		cout << num << " ";
	
	}
	cout << endl;
	
	selectionSort(V);
	cout << "Массив после сортиовки: ";
	for (auto num : V) {
		cout << num << " ";

	}
	cout << endl;


	return 0;
}