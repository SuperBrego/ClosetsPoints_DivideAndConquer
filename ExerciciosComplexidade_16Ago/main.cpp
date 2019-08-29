#include <stdio.h>
#include <vector>
#include <math.h>
#include <iostream>
#include <algorithm>    // std::min

using namespace std;

#define INFINITO 999999.9f;
pair<pair<float, float>, pair<float, float>> closest;

vector<pair<float, float>> getSplit(vector<pair<float, float>> listPtn, float x, bool lowerUpper);
void sortByX(vector<pair<float, float>> list);
float divideAndConquer(vector<pair<float, float>> list);

struct imAmDoneWithThis {
	float distance;
	pair<pair<float, float>, pair<float, float>> closest;
};

void main() {

	int out;

	// Fixed points
	vector<pair<float, float>> listPairs = {
		make_pair(-13, 0.5),	make_pair(-10.5, -11.5),
		make_pair(-10, 9),		make_pair(-4.5, -2),
		make_pair(-1, 8.5),		make_pair(0.5, 6),
		make_pair(0.5, -12),	make_pair(2, 12.5),
		make_pair(3.5, 11),		make_pair(5.5, 3),
		make_pair(5.5, -7),		make_pair(5, 11.5),
		make_pair(6.5, 3.2),	make_pair(7, -10),
		make_pair(9, -5),		make_pair(11.5, -4)
	};

	sortByX(listPairs);
	float  minDistance = divideAndConquer(listPairs);
	printf("Menor distancia: %.2f\n", minDistance);
	printf("O par mais proximo eh: (%.2f, %.2f) - (%.2f, %.2f)\n", closest.first.first, closest.first.second, closest.second.first, closest.second.second);
	cin >> out;

}

float divideAndConquer(vector<pair<float, float>> list) {

	float x1, x2;
	float y1, y2;

	if (list.size() <= 1) return INFINITO;
	if (list.size() == 2) {
		x1 = list.at(0).first;
		x2 = list.at(1).first;

		y1 = list.at(0).first;
		y2 = list.at(1).first;

		closest = make_pair(list.at(0), list.at(1));

		return (pow((x1 - x2), 2) + pow((y1 - y2), 2));
	}
	
	float d1, d2, d3;

	int n = list.size() / 2;
	vector<pair<float, float>> p1(list.begin(), list.begin() + n);
	vector<pair<float, float>> p2(list.begin() + n + 1, list.end());

	d1 = divideAndConquer(p1);
	d2 = divideAndConquer(p2);
	
	// d = SQRT( (x1-x2)^2 + (y1-y2)^2 ) 
	// d3 = calcula d considerando P1[n-1] e P2[0]; // pontos entre as partições!
	pair<float, float> lastP1 = p1.at(p1.size() - 1);
	pair<float, float> firstP2 = p2.at(0);
	d3 = (pow((lastP1.first + firstP2.first), 2) + pow((lastP1.second + firstP2.second), 2));

	return min(min(d1, d2), d3);

}

vector<pair<float, float>> getSplit(vector<pair<float, float>> listPtn, float x, bool belowX) {

	vector<pair<float, float>> list_p;

	for (int i = 0; i < listPtn.size(); i++) {
		if (belowX) 
			if (listPtn.at(i).first < x){
				list_p.push_back(listPtn.at(i));
			}
		else 
			if (listPtn.at(i).first >= x){
				list_p.push_back(listPtn.at(i));
			}
		
	}

	sortByX(list_p);

	return list_p;
}

void sortByX(vector<pair<float, float>> list) {

	for (int i = 0; i < list.size(); i++) {

		for (int j = 0; j < list.size() - i - 1; j++) {
			if (list.at(j).first > list.at(j + 1).first) {
				pair<float, float> dump = list.at(j);
				list.at(j) = list.at(j + 1);
				list.at(j + 1) = dump;
			}
		}
	}
}
