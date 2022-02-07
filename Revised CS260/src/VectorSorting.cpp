//============================================================================
// Name        			: VectorSorting.cpp
// Author      			: Spencer Hayden
// Original Date        : 07/25/2020
// Revision Date		: 01/28/2022
// Version     			: 1.3
// Copyright   			: Copyright © 2017 SNHU COCE
/* Description 			: Allows control and modification of
 * vector arrays through multiple functions. Class is called by main.cpp to
 * allow users to select functions and load, display, and sort the vector array.
 * The vector array is created by parsing through a provided CSV file through
 * help from the included CSVparser.hpp file. First a Bid struct is created to
 * hold vector array object information. VectorSorting class allows for sorting
 * of the vector array objects by id, title, or fund. These filters can be
 * adjusted or added to as needed per categories of other CSV files by adjusting
 * the referenced indices within the loadBids function.
 */
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// define a structure to hold bid information
struct Bid {
    string bidId;
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Class for all sorting/display functions
//============================================================================
class VectorSorting
{

public:

	/*
	 * Display the bid information to the console (std::out)
	 *
	 * @param bid struct containing the bid info
	 */
	void displayBid(Bid bid) {
		cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
				<< bid.fund << endl;
    return;
	}

	/*
	 * Prompt user for bid information using console (std::in)
	 *
	 * @return Bid struct containing the bid info
	 */
	Bid getBid() {
		Bid bid;

		cout << "Enter Id: ";
		cin.ignore();
		getline(cin, bid.bidId);

		cout << "Enter title: ";
		getline(cin, bid.title);

		cout << "Enter fund: ";
		cin >> bid.fund;

		cout << "Enter amount: ";
		cin.ignore();
		string strAmount;
		getline(cin, strAmount);
		bid.amount = strToDouble(strAmount, '$');

	return bid;
	}

	/*
	 * Load a CSV file containing bids into a container
	 *
	 * @param csvPath the path to the CSV file to load from project root
	 *
	 * @return a container holding all the bids read
	 */
	vector<Bid> loadBids(string csvPath) {
		cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of bids
    vector<Bid> bids;

    // Initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // Loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1]; // Id found at index 1
            bid.title = file[i][0]; // Title found at index 0
            bid.fund = file[i][8]; // Fund found at index 8
            bid.amount = strToDouble(file[i][4], '$'); // Amount found at index 4, converted from string to double and removes '$' character

            // Push this bid to the end of bids vector
            bids.push_back(bid);
        }

    // Catch Error if CSV file cannot be read
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
    return bids;
	}

	/*
	 * Partition the vector of bids into two parts, low and high
	 * Called by quickSort function
	 *
	 * @param bids Address of the vector<Bid> instance to be partitioned
	 * @param begin Beginning index to partition
	 * @param end Ending index to partition
	 */
	int partition(vector<Bid>& bids, int begin, int end) {
		int low = begin;
		int high = end;

		// Pick the middle element as the pivot point
		int pivot = begin + (end - begin) / 2;

		bool done = false;

		while (!done) {

			// Keep incrementing low as long as it is less than pivot
			while (bids.at(low).title.compare(bids.at(pivot).title) < 0) {
				++low;
			}

			// Keep decrementing high as long as it is more than pivot
			while (bids.at(pivot).title.compare(bids.at(high).title) < 0) {
				--high;
			}

			if (low >= high) {
				done = true;
			}
			else {
				// Swap the low and high bids using built-in vector method
				swap(bids.at(low), bids.at(high));


				// Move end points closer
				++low;
				--high;
			}
		}
		return high;
	}

	/*
	 * Performs a quick sort on bid title
	 * Average performance: O(n log(n))
	 * Worst case performance O(n^2))
	 *
	 * @param bids address of the vector<Bid> instance to be sorted
	 * @param begin the beginning index to sort on
	 * @param end the ending index to sort on
	 */
	void quickSort(vector<Bid>& bids, int begin, int end) {
		int mid = 0;

		// If zero or one bids to sort, then done
		if (begin >= end) {
			return;
		}

		// Partition bids into low and high parts
		mid = partition(bids, begin, end);

		// Recursively call quicksort using midpoint value (begin to mid)
		quickSort(bids, begin, mid);

		// Recursively call quicksort using midpoint value (mid +1 to end)
		quickSort(bids, mid +1, end);
	}

	/*
	 * Perform a selection sort on bid title
	 * Average performance: O(n^2))
	 * Worst case performance O(n^2))
	 *
	 * @param bid address of the vector<Bid>
	 * instance to be sorted
	 */
	void titleSort(vector<Bid>& bids) {
		// index to the current minimum bid
		unsigned int min;

		// pos is the position within the bids that marks sorted/unsorted
		for (unsigned pos = 0; pos < bids.size(); ++pos) {
		min = pos;

			for (unsigned j = pos + 1; j < bids.size(); ++j) {
				if (bids.at(j).title.compare(bids.at(min).title) < 0) {
					min = j;
				}
			}
			if (min != pos) {
				swap(bids.at(pos), bids.at(min));
			}
		}
	}

	/*
	 * Perform a selection sort on bid id
	 * Average performance: O(n^2))
	 * Worst case performance O(n^2))
	 *
	 * @param bid address of the vector<Bid>
	 * instance to be sorted
	 */
	void idSort(vector<Bid>& bids) {
		// index to the current minimum bid
		unsigned int min;

		// pos is the position within the bids that marks sorted/unsorted
		for (unsigned pos = 0; pos < bids.size(); ++pos) {
			min = pos;

			for (unsigned j = pos + 1; j < bids.size(); ++j) {
				if (bids.at(j).bidId.compare(bids.at(min).bidId) < 0) {
					min = j;
				}
			}
			if (min != pos) {
				swap(bids.at(pos), bids.at(min));
			}
		}
	}

	/*
	 * Perform a selection sort on bid fund
	 * Average performance: O(n^2))
	 * Worst case performance O(n^2))
	 *
	 * @param bid address of the vector<Bid>
	 * instance to be sorted
	 */
	void fundSort(vector<Bid>& bids) {
		// index to the current minimum bid
		unsigned int min;

		// pos is the position within the bids that marks sorted/unsorted
		for (unsigned pos = 0; pos < bids.size(); ++pos) {
			min = pos;

			for (unsigned j = pos + 1; j < bids.size(); ++j) {
				if (bids.at(j).fund.compare(bids.at(min).fund) < 0) {
					min = j;
				}
			}
			if (min != pos) {
				swap(bids.at(pos), bids.at(min));
			}
		}
	}

	/*
	 * Simple C function to convert a string to a double
	 * after stripping out unwanted char
	 *
	 * credit: http://stackoverflow.com/a/24875936
	 *
	 * @param ch The character to strip out
	 */
	double strToDouble(string str, char ch) {
		str.erase(remove(str.begin(), str.end(), ch), str.end());
		return atof(str.c_str());
	}
};



