#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

class Node{
	public:
		int id;
		int points;
		Node();
		Node(int i, int p);
};

Node::Node(){
}

Node::Node(int i, int p){
	id = i;
	points = p;
}

class Heap{
	public:
		vector<Node> arr;
		Heap();
		void siftdown(int);
		void heapify();
		void addNode(Node newNode);
		Node getNode(int);
		bool empty();
		Node removeHead();
		int size;
		void crownWinner();
		bool nodeExists(int);
		void print(char*);
		bool isLeaf(int);
};

Heap::Heap(){
}

bool Heap::isLeaf(int i){
	if(((2*i)+1) > arr.size())
		return true;
	return false;
}

void Heap::siftdown(int i){
/*
	if((i < 0) || (i >= arr.size()))
		return;
	while(!isLeaf(i)){
		int left = 2*i + 1;
		int right = 2*i + 2;
		if(right >= arr.size() || arr.at(left).points < arr.at(right).points){
			if(arr.at(i).points <= arr.at(left).points){
				return;
			}
			iter_swap(arr.begin() + i, arr.begin() + left);
			i = left;
		}
		else{
			if(arr.at(i).points >= arr.at(right).points){
				return;
			}
			iter_swap(arr.begin() + i, arr.begin() + right);
			i = right;
		}
	}
*/
/*
	while(!isLeaf(i)){
		int swapNode = ((2*i)+1);
		if((swapNode+1 < arr.size()) && (arr.at(swapNode).points > arr.at(swapNode+1).points))
			swapNode++;
		if(arr.at(i).points > arr.at(swapNode).points)
			return;
		iter_swap(arr.begin()+i, arr.begin()+swapNode);
		i = swapNode;
	}
*/

	int l = (2*i)+1;
	int r = (2*i)+2;
	int smallest = i;
	if(l < arr.size() && r < arr.size()){
		if(arr.at(l).points > arr.at(r).points)
			iter_swap(arr.begin()+l, arr.begin()+r);
	}
	if(l < arr.size() && arr.at(l).points < arr.at(i).points)
		smallest = l;
	if(r < arr.size() && arr.at(r).points < arr.at(i).points)
		smallest = r;
	if(smallest != i){
		iter_swap(arr.begin()+i, arr.begin()+smallest);
		siftdown(smallest);
	}

}

void Heap::heapify(){
	for(int i = (arr.size()-2)/2; i >= 0; i--){
		siftdown(i);
	}
}

void Heap::addNode(Node newNode){
	arr.push_back(newNode);
	heapify();
}

Node Heap::removeHead(){
	Node n = arr.front();
	arr.erase(arr.begin());
	heapify();
	return n;
}

bool Heap::empty(){
	if(arr.size() == 0)
		return true;
	return false;
}

bool Heap::nodeExists(int i){
	for(auto j : arr){
		if(j.id == i)
			return true;
	}
	return false;
}

void Heap::print(char* ar){
	ofstream output;
	output.open(ar, ios_base::app);
	int pos = 1;
	for(auto i : arr){
		output << "Contestant <" << i.id << "> in the extended heap location <" << pos << "> with score <" << i.points << ">." << endl;
		pos++;
	}
	output.close();
}

int main(int argc, char** argv){
	string command;
	int numContestants = 0;
	int size;
	string in1;
	string in2;
	int contestantId;
	int score;
	int pointsChange;
	Heap heap;
	
	ofstream clear;
	clear.open(argv[2], ofstream::out | ofstream::trunc);
	clear.close();

	ifstream input(argv[1], ios::in);
	
	ofstream output;
	output.open(argv[2], ios_base::app);

	input >> size;

	while(true){
		input >> command;
		if(input.eof())
			break;
		if(!(command.compare("insertContestant"))){
			input >> in1;
			input >> in2;

			output << command << " " << in1 << " " << in2 << endl;

			in1.erase(remove(in1.begin(), in1.end(), '<'), in1.end());
			in1.erase(remove(in1.begin(), in1.end(), '>'), in1.end());
			in2.erase(remove(in2.begin(), in2.end(), '<'), in2.end());
			in2.erase(remove(in2.begin(), in2.end(), '>'), in2.end());
			
			contestantId = atoi(in1.c_str());
			score = atoi(in2.c_str());
			if(!(heap.nodeExists(contestantId))){
				if(numContestants < size){
					heap.addNode(Node(contestantId, score));
					numContestants++;
					output << "Contestant <" << in1 << "> inserted with initial score <" << in2 <<">." << endl;
				}else
					output << "Contestant <" << in1 << "> could not be inserted because the extended heap is full." << endl;
			}else
				output << "Contestant <" << in1 << "> is already in the extended heap: cannot insert." << endl;
		}
		else if(!(command.compare("findContestant"))){
			int temp;
			input >> in1;

			output << command << " " << in1 << endl;

			in1.erase(remove(in1.begin(), in1.end(), '<'), in1.end());
			in1.erase(remove(in1.begin(), in1.end(), '>'), in1.end());
			
			contestantId = atoi(in1.c_str());
		
			if(heap.nodeExists(contestantId)){
				for(auto i = heap.arr.begin(); i != heap.arr.end(); i++){
					if((*i).id == contestantId){
						temp = (*i).points;
					}
				}
				output << "Contestant <" << contestantId << "> is in the extended heap with score <" << temp << ">." << endl;
			}else
				output << "Contestant <" << contestantId << "> is not in the extended heap." << endl;
		}
		else if(!(command.compare("eliminateWeakest"))){
			output << command << endl;
			if(!(heap.empty())){
				Node n = heap.removeHead();
				output << "Contestant <" << n.id << "> with current lowest score <" << n.points << "> eliminated." << endl;
			}else
				output << "No contestant can be eliminated since the extended heap is empty." << endl;
		}
		else if(!(command.compare("earnPoints"))){
			int temp;
			input >> in1;
			input >> in2;

			output << command << " " << in1 << " " << in2 << endl;

			in1.erase(remove(in1.begin(), in1.end(), '<'), in1.end());
			in1.erase(remove(in1.begin(), in1.end(), '>'), in1.end());
			in2.erase(remove(in2.begin(), in2.end(), '<'), in2.end());
			in2.erase(remove(in2.begin(), in2.end(), '>'), in2.end());
			
			contestantId = atoi(in1.c_str());
			score = atoi(in2.c_str());
			if(heap.nodeExists(contestantId)){
				for(auto i = heap.arr.begin(); i != heap.arr.end(); i++){
					if((*i).id == contestantId){
						(*i).points += score;
						temp = (*i).points;
					}
				}
				output << "Contestant <" << contestantId << ">'s score increased by <" << score << "> points to <" << temp << ">." << endl;
			}else
				output << "Contestant <" << contestantId << "> is not in the extended heap." << endl;
		}
		else if(!(command.compare("losePoints"))){
			int temp;
			input >> in1;
			input >> in2;

			output << command << " " << in1 << " " << in2 << endl;

			in1.erase(remove(in1.begin(), in1.end(), '<'), in1.end());
			in1.erase(remove(in1.begin(), in1.end(), '>'), in1.end());
			in2.erase(remove(in2.begin(), in2.end(), '<'), in2.end());
			in2.erase(remove(in2.begin(), in2.end(), '>'), in2.end());
			
			contestantId = atoi(in1.c_str());
			score = atoi(in2.c_str());
			if(heap.nodeExists(contestantId)){
				for(auto i = heap.arr.begin(); i != heap.arr.end(); i++){
					if((*i).id == contestantId){
						(*i).points -= score;
						temp = (*i).points;
					}
				}
				output << "Contestant <" << contestantId << ">'s score decreased by <" << score << "> points to <" << temp << ">." << endl;
			}else
				output << "Contestant <" << contestantId << "> is not in the extended heap." << endl;
		}
		else if(!(command.compare("showContestants"))){
			output << command << endl;
			heap.print(argv[2]);
		}
		else if(!(command.compare("showHandles"))){
			output << command << endl;
			for(int j = 1; j <= size; j++){
				if(heap.nodeExists(j)){	
					int pos = 1;
					int temp;
					for(auto i : heap.arr){
						if(i.id == j)
							temp = pos;
						pos++;
					}
					output << "Contestant <" << j << "> stored in extended heap location <" << temp << ">." << endl;
				}else
					output << "There is no Contestant <" << j << "> in the extnded heap: handle[<" << j << ">] = -1." << endl;
			}
		}
		else if(!(command.compare("showLocation"))){
			input >> in1;

			output << command << " " << in1 << endl;

			in1.erase(remove(in1.begin(), in1.end(), '<'), in1.end());
			in1.erase(remove(in1.begin(), in1.end(), '>'), in1.end());
			
			contestantId = atoi(in1.c_str());
			
			if(heap.nodeExists(contestantId)){	
				int pos = 1;
				int temp;
				for(auto i : heap.arr){
					if(i.id == contestantId)
						temp = pos;
					pos++;
				}
				output << "Contestant <" << contestantId << "> stored in extended heap location <" << temp << ">." << endl;
			}else
				output << "There is no Contestant <" << contestantId << "> in the extnded heap: handle[<" << contestantId << ">] = -1." << endl;
		}
		else if(!(command.compare("crownWinner"))){
			output << command << endl;
			Node winner;
			int maxScore = heap.arr.at(0).points;
			for(auto i = heap.arr.begin(); i != heap.arr.end(); i++){
				if((*i).points >= maxScore){
					winner = (*i);
					maxScore = (*i).points;
				}
			}
			heap.arr.clear();
			heap.arr.push_back(winner);
			output << "Contestant <" << heap.arr.front().id << "> wins with score <" << heap.arr.front().points << ">!" << endl;
		}
		else{
			cout << "Not a valid command." << endl;
		}
		heap.heapify();
	}
	input.close();
	output.close();
	return 0;
}
