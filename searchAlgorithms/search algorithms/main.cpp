#include<iostream>
#include<random>
#include<cstdlib>
#include<ctime>
#include<chrono>
#include<thread>

using namespace std;

class Timer
{
private:
	// Type aliases to make accessing nested type easier
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void BubbleSort(int arrayToSort[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arrayToSort[j] > arrayToSort[j + 1])
			{
				swap(&arrayToSort[j], &arrayToSort[j + 1]);
			}
		}
	}
}

void GnomeSort(int arrayToSort[], int n)
{
	int index = 0;
	while (index < n)
	{
		if (index == 0)
			index++;
		if (arrayToSort[index] >= arrayToSort[index - 1])
		{
			index++;
		}
		else {
			swap(arrayToSort[index], arrayToSort[index - 1]);
			index--;
		}
	}
	return;
}


void CocktailSort(int arrayToSort[], int n)
{
	bool swapped = true;
	int start = 0;
	int end = n - 1;

	while (swapped)
	{
		//!< Reset the swapped flag on entering the loop.
		//!< This is because it might be true from a previous iteration.

		swapped = false;

		//!< This is similar to bubble sorting as it loops from left to right.

		for (int i = start; i < end; ++i)
		{
			if (arrayToSort[i] > arrayToSort[i + 1])
			{
				swap(arrayToSort[i], arrayToSort[i + 1]);
				swapped = true;
			}
		}
		
		if (!swapped) //!< If nothing is moved then the array is sorted.
			break;

		swapped = false;

		--end;

		//!< from right to left, doing the 
		//!< same comparison as in the previous stage 
		for (int i = end - 1; i >= start; --i)
		{
			if (arrayToSort[i] > arrayToSort[i + 1])
			{
				swap(arrayToSort[i], arrayToSort[i + 1]);
				swapped = true;
			}
		}

		++start;

	}


}


void PrintArray(int arrayToPrint[], int n)
{
	for (int i = 0; i < n; i++)
		cout << arrayToPrint[i] << endl;
}


int BinarySearch(int arrayToSearch[], int l, int r, int x)
{
	if (r >= 1)
	{
		int mid = l + (r - 1) / 2;
		if (arrayToSearch[mid] == x) //!< If the element is present in the middle.
		{
			return mid;
		}
		if (arrayToSearch[mid] > x) //!< If the element is smaller than the mid, this means it can only be present in the left subarray.
		{
			return BinarySearch(arrayToSearch, l, mid - 1, x);
		}

		return BinarySearch(arrayToSearch, mid + 1, r, x); //!< If its not smaller than the mid then it can only be present in the right subarray.
	}
	return -1;
}

int LinearSearch(int arrayToSearch[], int n, int goal)
{
	for (int i = 0; i < n; i++)
	{
		if (arrayToSearch[i] == goal)
		{
			return i;
		}
	}
	return -1;
}



int main()
{
	Timer timer;
	srand((unsigned)time(0));
	
	int nums;
	int listOfNums[10000];

	for (int i = 0; i < 10000; i++)
	{
		nums = (rand() % 10000) + 1;
		listOfNums[i] = { nums };
	}
	

	int goal = 12;
	int n = sizeof(listOfNums) / sizeof(listOfNums[0]);
	//int result = LinearSearch(listOfNums, n, goal);
	/*
	int result = BinarySearch(listOfNums, 0, n - 1, goal);

	if (result == -1)
	{
		cout << "> ELEMENT IS NOT PRESENT IN THIS ARRAY." << endl;
	}
	else {
		cout << "> ELEMENT WAS FOUND AT INDEX: " << result;
	}*/
	//CocktailSort(listOfNums, n);
	//BubbleSort(listOfNums, n);
	GnomeSort(listOfNums, n);

	cout << "SORTED ARRAY" << endl;
	PrintArray(listOfNums, n);
	cout << "TIME TAKEN GNOME SORT: " << timer.elapsed() << " Seconds" << endl;

	system("pause");
}