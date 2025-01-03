#include<iostream>
using namespace std;
int main() {
	int n;
	cin >> n;
	getchar();
	int* indegree = new int[n];
	int* cost = new int[n];
	int** a = new int* [n];
	int* visited = new int[n];
	for (int i = 0; i < n; i++) {
		indegree[i] = 0;
		cost[i] = 0;
		a[i] = new int[n];
		visited[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[i][j] = 0;
		}
	}
	char input[100];
	for (int i = 0; i < n; i++) {
		cin.getline(input, 100);
		int start;
		int j = 0;
		int u;
		int t = 0;
		int n = 0;
		while (1) {
			if (input[j] - '0' >= 0 && input[j] - '0' <= 9) {
				t++;
				if (t == 1)
					u = input[j] - '0';
				else {
					u = u * 10 + input[j]-'0';
					t = 0;
				}
			}
			if (input[j] == ' ' || input[j] == ';') {
				n++;
				t = 0;
				if (n == 1) {
					start = u - 1;
				}
				else if (n == 2) {
					cost[start] = u;
				}
				else if(input[j]!='\n') {
					a[u - 1][start] = 1;
					indegree[start]++;
				}
			}
			else if (input[j] == 0) {
				if (n == 1)
					cost[start] = u;
				break;
			}
			j++;
		}
	}
	int* final = new int[n];
	for (int i = 0; i < n; i++) {
		final[i] = 0;
	}
	int* stack = new int[n];
	int start = 0;
	int end = -1;
	for (int i = 0; i < n; i++) {
		if (indegree[i] == 0) {
			end++;
			stack[end] = i;
			visited[i] = 1;
			break;
		}
	}
	while (1) {
		int t = stack[start];
		start++;
		for (int i = 0; i < n; i++) {
			if (a[t][i] != 0) {
				indegree[i]--;
				int u = final[t] + cost[t];
				if (u > final[i])
					final[i] = u;
			}
		}
		for (int i = 0; i < n; i++) {
			if (indegree[i] == 0 && visited[i] == 0) {
				end++;
				stack[end] = i;
				visited[i]++;
			}
		}
		if (start > end)
			break;
	}
	int max = 0;
	int t = 0;
	for (int i = 0; i < n; i++)
		if (final[i] > max) {
			max = final[i];
			t = i;
		}
	if (start == n)
		cout << max + cost[t];
	else
		cout << "error";
}