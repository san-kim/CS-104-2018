#include <vector>

//helper function split
template <typename T>
std::vector< std::vector<T> > split(std::vector< std::vector<T> >& subarrays, int k)
{
	std::vector< std::vector<T> > result;

	//split all subarrays into k smaller subarrays
	//run until they are all size 1 subarrays
	while(subarrays.size() > 0)
	{
		//only evaluate at subarrays[0] like queue, split subarrays at back, pop subarrays[0] after split
		int startingsize = subarrays.size();
		for(int i = 0; i<startingsize; i++)
		{	
			//if it is a split that splits all elements of subarrays[i] into subarrays size 1
			//base case split into subarrays of size 1, always evaluate at front of subarrays like queue
			if((unsigned int)k >= subarrays[0].size())
			{
				//this whole forloop will be CONSTANT runtime if single element cirlced around
				for(unsigned int j = 0; j<subarrays[0].size(); j++)
				{
					std::vector<T> single_value;
					//push back each individual elements of that subarray in vector
					single_value.push_back(subarrays[0][j]);
					//we push back here because we will pop front to iterate only through
					//the subarrays at index 0, popping front every time we finish evaluating
					result.push_back(single_value);
					//pop the first element of subarrays, the one we just evaluated
				}
				subarrays.erase(subarrays.begin());
				//now subarrays[0] will be the next unsplit element
			}

			//when k is less than the subarray we are currently evaluating
			else
			{
				//SPLIT USING MIDPOINTS, more than just k elemenmts
				//for all k splits
				for(int j = 0; j < k; j++)
				{
					//size of each subarray
					unsigned int splitsize = subarrays[0].size() / k;
					//where the split subarray starts, from 0 to splitsize*(k-1)
					unsigned int split_startingindex = splitsize * j;
					std::vector<T> splitarray;

					//our forloop upper bound, for number of elements for divided subarrays
					unsigned int upperbound = splitsize;
					//if it is the last element, needs to capture from startingindex to end
					if(j == k-1)
					{	
						//to capture from startingindex to end
						upperbound = subarrays[0].size() - split_startingindex;
					}

					for(unsigned int n = 0; n < upperbound; n++)
					{
						splitarray.push_back(subarrays[0][split_startingindex + n]);
					}

					//push back the split array
					subarrays.push_back(splitarray);
				}	
				//pop the front one so it will pop only original however many arrays
				subarrays.erase(subarrays.begin());
			}
		}
	}
	return result;
}


//helper function merge
template <typename T, typename Comparator>
std::vector<T> merge(std::vector< std::vector<T> > & splitarrays, int k, 
					 unsigned int original_size, Comparator AlessthanB)
{
	//do k-merge until it is one array of original size
	while(splitarrays[0].size() != original_size)
	{
		//the number of splitarrays we are merging at once
		int num_merges = k;
		//if there are fewer splitarrays than k, resize accordingly
		if(splitarrays.size() < (unsigned int)k)
		{
			num_merges = splitarrays.size();
		}

		// **we are trying to merge the FIRST num_merges arrays in splitarrays**

		//indexes for all num_merges split lists we are currently looking at
		//we will increment indexes and pop both index and array when at end
		std::vector<int> indexes;
		for(int i = 0; i<num_merges; i++)
		{
			indexes.push_back(0);
		}

		//resulting merged list we will push to back of splitarrays at end
		std::vector<T> mergedList;

		//once indexes.size() reaches 0, both its splitarray and indexes gets removed
		while(indexes.size() > 0)
		{
			//start at index 0 of splitarray 0
			T minVal = splitarrays[0][indexes[0]];
			//start at splitarrays 0
			int minSplitIndex = 0;
			for(unsigned int i = 0; i<indexes.size(); i++)
			{
				//indexes[i] for the corresponding index
				//using comparator, is LHS < RHS ? if so then change minVal
				if(AlessthanB(splitarrays[i][indexes[i]], minVal))
				{
					minVal = splitarrays[i][indexes[i]];
					minSplitIndex = i;
				}
			}

			//push back minimum value
			mergedList.push_back(minVal);
			//increment index of the one we just found
			indexes[minSplitIndex]++;

			//if it is the case that we have reached the end of this indexes[]
			//we must pop those indexes and splitarrays until indexes size is 0
			if((unsigned int)indexes[minSplitIndex] == splitarrays[minSplitIndex].size())
			{
				//erase that location for both indexes and splitarrays
				indexes.erase(indexes.begin() + minSplitIndex);
				splitarrays.erase(splitarrays.begin() + minSplitIndex);
			}

		}
		//after while loop all splitarrays we looked at should be popped & sorted in mergedList
		splitarrays.push_back(mergedList);
	}

	//result one dimensional vector, add to until it is original size
	std::vector<T> result = splitarrays[0];
	return result;
}


//main mergesort function
template <typename T, typename Comparator>
void mergeSort(std::vector<T>& myArray, int k, Comparator comp)
{
	//vector of vectors, represents all subarrays from splitting and merging
	std::vector< std::vector<T> > subarrays;

	//initially subarrays will be size 1 and will have the full myArray as element
	subarrays.push_back(myArray);

	//k-way split the arrays
	std::vector< std::vector<T> > splitresult = split(subarrays, k);

	//k-way merge the split resulting arrays, pass in the comparator to do comparison
	myArray = merge(splitresult, k, myArray.size(), comp);
}
