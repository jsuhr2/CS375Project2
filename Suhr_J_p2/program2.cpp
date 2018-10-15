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
		Node(int i, int p);
};

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
		void print();
};

Heap::Heap(){
}

void Heap::siftdown(int i){
	if((i < 0) || (i >= arr.size()))
		return;
	while((2*i + 1) < arr.size()){
		int left = 2*i + 1;
		int right = 2*i + 2;
		if(right >= arr.size() || arr.at(left).points <= arr.at(right).points){
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
}

void Heap::heapify(){
	for(int i = (arr.size() - 2)/2; i >= 0; i--){
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
	if(size == 0)
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

void Heap::print(){
	ofstream output;
	output.open("output.txt", ios_base::app);
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
	clear.open("output.txt", ofstream::out | ofstream::trunc);
	clear.close();

	ifstream input(argv[1], ios::in);
	
	ofstream output;
	output.open("output.txt", ios_base::app);

	input >> size;

	while(!input.eof()){
		input >> command;
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

		}
		else if(!(command.compare("eliminateWeakest"))){

		}
		else if(!(command.compare("earnPoints"))){

		}
		else if(!(command.compare("losePoints"))){

		}
		else if(!(command.compare("showContestants"))){
			heap.print();
		}
		else if(!(command.compare("showHandles"))){

		}
		else if(!(command.compare("showLocation"))){

		}
		else if(!(command.compare("crownWinner"))){

		}
		else{
			cout << "Not a valid command." << endl;
		}
	}
	input.close();
	return 0;
}
