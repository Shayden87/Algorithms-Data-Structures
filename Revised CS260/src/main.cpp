//============================================================================
// Name        			: Main.cpp
// Author      			: Spencer Hayden
// Original Date        : 07/25/2020
// Revision Date		: 01/28/2022
// Version     			: 1.3
// Copyright   			: Copyright © 2017 SNHU COCE
/* Description 			: User interface that provides menu for user to
 * initiate vector sorting by calling functions from the VectorSorting class.
 * Utilizes switch statement to get user input selection to allow user to load
 * bids, display bids, and sort bids added to a vector array from CSV files.
 * Sorting tailored to specific example CSV file to sort by either title, id,
 * or fund. VectorSorting class can be modified to sort by any column chosen
 * per layout of CSV file.
 */
//============================================================================

#include "VectorSorting.cpp"

using namespace std;

int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
    }

    // Define a vector to hold all the bids
    vector<Bid> bids;

    // Define a timer variable
    clock_t ticks;

    // Create instance of VectorSorting class
    VectorSorting v;

    // Display user menu
    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl; // Calls loadBid function
        cout << "  2. Display All Bids" << endl; // Calls displayBid function
        cout << "  3. Sort By Title" << endl; // Calls titleSort function
        cout << "  4. Sort By ID" << endl; // Calls idSort function
        cout << "  5. Sort By Fund" << endl; // Calls fundSort function
        cout << "  9. Exit" << endl; // Ends program
        cout << "Enter choice: ";
        cin >> choice;


        switch (choice) {

        // Load Bids
        case 1:
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            bids = v.loadBids(csvPath);

            // Outputs bids vector size
            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        // Display all bids
        case 2:
            /* Loop and display the bids read
             *
             * Must be selected after every sort
             */
            for (unsigned int i = 0; i < bids.size(); ++i) {
                v.displayBid(bids[i]);
            }
            cout << endl;

            break;

        // Sort by title
        case 3:
        	// Initialize a timer variable before loading bids
        	ticks = clock();

            // Complete the method call to titleSort the bids
        	v.titleSort(bids);

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        // Sort by id
        case 4:
        	// Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to idSort the bids
            v.idSort(bids);

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        // Sort by fund
        case 5:
        	// Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to fundSort the bids
            v.fundSort(bids);

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        // Default if any other user input is entered
        default:

        	cout << "Please make valid selection" << endl;

        	break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
