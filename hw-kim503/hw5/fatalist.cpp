#include <vector>
#include <algorithm>
#include "msort.h"

using namespace std;

//struct comparator for pairs, organized by 104 grades (pair.first)
struct PairCompFirst 
{
  bool operator()(const pair<int,int>& lhs, const pair<int,int>& rhs)
  { // Compares pairs by pair.first, just the 104 grades we are sorting;
    // only if 104 grade of lhs was lower than rhs,
    return (lhs.first < rhs.first || (lhs.first==rhs.first && lhs.second < rhs.second));
  }
};

//struct comparator for pairs, organized by 170 grades (pair.second)
struct PairCompSecond
{
  bool operator()(const pair<int,int>& lhs, const pair<int,int>& rhs)
  { // Compares pairs by pair.second, just the 170 grades we are sorting;
    // only if 170 grade of lhs was lower than rhs,
    return (lhs.second < rhs.second || (lhs.second==rhs.second && lhs.first < rhs.first));
  }
};

bool FatalistHypothesis(vector< pair<int,int> > grades)
{
	//will automatically be true for if 0 or 1 student
	if(grades.size() == 0 || grades.size() == 1)
	{
		return true;
	}

	PairCompFirst comparator_104;
	PairCompSecond comparator_170;

	//do copies so that each separate class is compared, at least size = 2 now


	/*
	int kmerge = 2;
	if(grades.size() > 999)
	{	//for efficiency?
		kmerge = 10;
		if(grades.size() > 99999)
			kmerge = 1000;
	}
	*/


	//because we know that our mergeSort does theta(kn) + theta(n*logk(n)) and we know that
	//k will be more or less a constant, theta(n) + theta(n*logk(n)) = theta(nlogn)
	//do 2-way merge sort for O(nlogn) sort
	vector< pair<int,int> > grades_104 = grades;
	sort(grades_104.begin(), grades_104.end(), comparator_104);
	//mergeSort(grades_104, kmerge, comparator_104);
	
	//do 2-way merge sort for O(nlogn) sort
	vector< pair<int,int> > grades_170 = grades_104;
	sort(grades_170.begin(), grades_170.end(), comparator_170);
	//mergeSort(grades_170, kmerge, comparator_170);


	//this is O(n) check
	bool is_fatalist_Right = true;
	for(unsigned int i = 0; i<grades.size(); i++)
	{
		//means they are out of order, if same order of grades for 104/170 then means fatalist is right
		if(grades_170[i] != grades_104[i])
		{
			is_fatalist_Right = false;
		}
	}

	// O(nlogn) + O(nlogn) + O(n) = O(nlogn)

	return is_fatalist_Right;
}