#include <iostream>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;



class Graph
{

private:
	int** array;

	int S; //size of the List pointer i.e. array

	int t_case;

	bool impossible;

	int max_flow;

public:


	Graph(int vertices, int testcase)
	{

		S = vertices;

		max_flow = 10000;

		t_case = testcase;

		impossible = false;


		array = new int* [vertices];
		for (int i = 0; i < S; i++)
			array[i] = new int[S];


	}//func end


	void AddEdge(int i, int j, int flow)
	{
		array[i][j] = flow;

		if (flow < max_flow && i != j)
			max_flow = flow;
	}



	

	void MaxBandwidth() //modifies PRIMS algo used for max spanning tree
	{

		if (S == 1)
			cout << "Case #" << t_case << ": " << 0 << endl;

		else
		{
			int* Parent = new int[S];
			int* Key = new int[S];
			bool* check = new bool[S];

			for (int i = 0; i < S; i++)
			{
				check[i] = false;
				Key[i] = -1;
				Parent[i] = 0;
			}

			Key[0] = 0;
			Parent[0] = -1;

			for (int i = 0; i < S - 1; i++)///since n-1 vertices
			{

				int u = MaxKey(Key, check);
				check[u] = true;


				for (int j = 0; j < S; j++)
				{

					if (array[u][j] && !check[j] && array[u][j] > Key[j])
					{
						Parent[j] = u;
						Key[j] = array[u][j];
					}

				}


			}//main for loop


			impossible = CheckImpossible(Parent);

			if (!impossible)
			{
			cout << "Case #" << t_case << ": " << S - 1 << endl;
			for (int i = 1; i < S; i++)
			{

				cout << Parent[i] << " " << i << " " << array[Parent[i]][i] << "\n";

			}
			}

			else
			cout << "Case #" << t_case << ": Impossible" << endl;


			delete[] Parent;
			delete[] Key;
			delete[] check;


		}///else



	}//main function


	int MaxKey(int key[], bool check[])
	{
		// Initialize min value  
		int max = -1;
		int index = -1;

		for (int i = 0; i < S; i++)
		{
			if (!check[i] && key[i] > max)
			{
				max = key[i];
				index = i;
			}
		}

		return index;
	}

	bool CheckImpossible(int Parent[])
	{

		vector<int> F;

		std::vector<int>::iterator it;

		///POPULATING THE VECTOR
		for (int i = 0; i < S; i++)
		{
			for (int j = i+1; j < S;j++)
			{

				Population(F, array[i][j]);
			
			}
		}////

		sort(F.begin(), F.end());
	
		bool check = false;
		

		vector<int> zeus;
		for (int i = 1; i < S; i++)
		{

			Population(zeus,array[Parent[i]][i]);
		}

		sort(zeus.begin(), zeus.end());

		check = Judgement(zeus, F);


		return check;
	}


	bool Judgement(vector<int>& A, vector<int>& B)
	{

		for (auto it = A.begin(); it != A.end(); it++)
		{
			//if (*it == max_flow)
				//continue;

			for (auto it2 = B.begin(); it2 != B.end(); it2++)
			{

				if ((*it2) < (*it))
				{
					if(!(Search(A, *it2)))
						return true;

				}

			}

		}

		return false;

	}//func end


	bool Search(vector<int>& A, int value)
	{

		for (auto it = A.begin(); it != A.end(); it++)
		{
			if (*it == value)
				return true;

		}

		return false;
	}





	void Population(vector<int> &F ,int value)
	{
		std::vector<int>::iterator it;

		if (F.empty())
		{
			F.push_back(value);
			return;
		}


		else
		{
			bool present = true;

			for (auto it = F.begin(); it != F.end(); it++)
			{
				if (*it == value)
				{
					present = false;
					break;

				}

			}///for loop

			if (present)
				F.push_back(value);

		}


	}




	void Display_Graph()
	{
		for (int i = 0; i < S; i++)
		{

			for (int j = 0; j < S; j++)
			{
				cout << array[i][j] << " ";
			}

			cout << endl;
		}

	}//func end


	~Graph()
	{

		for (int i = 0; i < S; i++)
		{
			delete[] array[i];
		}
		delete[] array;
	}

};


int main() {

	int size;

	int F;

	int v;
	cin >> size;

	Graph** G = new Graph * [size];

	for (int i = 0; i < size; i++)
	{

		cin >> v;

		G[i] = new Graph(v, i + 1);

		for (int j = 0; j < v; j++)
		{

			for (int k = 0; k < v; k++)
			{

				cin >> F;

				G[i]->AddEdge(j, k, F);

			}


		}

	}//big for loop


	for (int i = 0; i < size; i++)
	{
		G[i]->MaxBandwidth();
	}


	for (int i = 0; i < size; i++)
	{
		delete G[i];
	}
	delete[]G;


	return 0;
}





