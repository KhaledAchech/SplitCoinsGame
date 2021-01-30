#include <bits/stdc++.h>

using namespace std;

/******************* Author : *****************************************/
/******************* Khaled Achech. ***********************************/
/******************* Last Update : January the 13th :) . **************/
/****** Subject : A Game of dividing a pile of coins ******************/
/****** where the first player "Max" is asked to divide the pile ******/
/****** Into 2 non even piles and the second player "Min" is also *****/
/****** asked to do the same; when one of them reach a point when *****/
/****** where he can't divide the piles anymore the other wins.   *****/
/****************** Algorithme : MinMax algorithme . ******************/
/**********************************************************************/

/******************* Trace : ******************************************/
/* Am using trace here to display in each turn the depth and the nodes*/
/* so basicaly it's used to show the progression of the algorithme.   */
/**********************************************************************/
vector <pair<int, vector<int>>> trace[10];

int dfs(int turn, vector<int>& node, int depth = 0) // Am using dfs to go through the graph s values.
{
	// So here am making a copy of our node and passing to the trace vector so we can trace the graph progress.
	vector<int> copy = node;
	trace[depth].push_back({turn, copy});


	for(int i = 0; i < node.size(); i++){
		if (node[i] > 2) // Basicaly saying if the node is divisable then :
		{
			vector<int> new_node = node; // make a new node that will be divided into two new nodes.
			new_node.erase(new_node.begin() + i);

			for(int pile1 = 1; pile1 * 2 < node[i]; pile1++) // pile1 will be the first division (is the lower half of the node[i]).
			{
				int pile2 = node[i] - pile1; // pile2 will be the second division (the rest of the node[i]).

				//adding the two piles to the new node.
				new_node.push_back(pile1);
				new_node.push_back(pile2);

				int outcome = dfs(-turn, new_node, depth + 1); // calling the next turn.

				if (outcome == turn)
					return outcome; // getting the result.

				//removing the two newly added piles.
				new_node.pop_back();
				new_node.pop_back();
			}
		}
	}
	//basicaly saying that if the current player doesn't have any move the other player wins.
	return -turn;
}

int main() {

	vector<int> pile = {7}; // our main pile of 7 coins.
	printf("Player %s wins\n", dfs(1, pile) == 1 ? "Max" : "Min"); // Winner output.

	//Printing the progress of the algorithme with the trace vector :) .
	for(int i = 0; i < 10; i++){
		if (trace[i].size()){
			printf("Depth %d:\n", i);
			for(auto v : trace[i]){
				printf("%s: [", v.first == 1 ? "Max" : "Min");
				for(auto x: v.second){
					printf("%d ", x);
				}
				printf("]\n");
			}
			printf("\n\n");
		}
	}
}