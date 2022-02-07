//============================================================================
// Name        			: Main.cpp
// Author      			: Spencer Hayden
// Original Date        : 07/25/2020
// Revision Date		: 01/29/2022
// Version     			: 1.3
// Copyright   			: Copyright © 2017 SNHU COCE
/* Description 			: Program for parsing a CSV file in order to read file
 * row by row and store cell values as strings into two vectors (_header and
 * _values.
 */
//============================================================================

#ifndef     _CSVPARSER_HPP_
# define    _CSVPARSER_HPP_

# include <stdexcept>
# include <string>
# include <vector>
# include <list>
# include <sstream>

// Creates namespace csv to hold multiple classes
namespace csv
{
	// Creates class Error to provide error message if parsing CSV file fails
    class Error : public std::runtime_error
    {

      public:
        Error(const std::string &msg):
          std::runtime_error(std::string("CSVparser : ").append(msg))
        {
        }
    };

    // Creates class Row to allow rows of CSV file to be read/parsed
    class Row
    {
    	// Creates public instance of string storing vector of class Row
    	public:
    	    Row(const std::vector<std::string> &);
    	    ~Row(void);

    	// Initializes size variable, creates public functions push and set to utilize with vector manipulation
    	public:
            unsigned int size(void) const;
            void push(const std::string &);
            bool set(const std::string &, const std::string &);

        // Sets up two vectors _header and _values for storing data from CSV as strings
    	private:
    		const std::vector<std::string> _header;
    		std::vector<std::string> _values;

    	// Allows values at index of _values vector to be converted to string and be returned
        public:

            template<typename T>
            const T getValue(unsigned int pos) const
            {
                if (pos < _values.size())
                {
                    T res;
                    std::stringstream ss;
                    ss << _values[pos];
                    ss >> res;
                    return res;
                }
                throw Error("can't return this value (doesn't exist)");
            }
            const std::string operator[](unsigned int) const;
            const std::string operator[](const std::string &valueName) const;
            friend std::ostream& operator<<(std::ostream& os, const Row &row);
            friend std::ofstream& operator<<(std::ofstream& os, const Row &row);
    };

    enum DataType {
        eFILE = 0,
        ePURE = 1
    };

    // Creates Parser class
    class Parser
    {

    // Creates Parser object that takes CSV file as input
    public:
        Parser(const std::string &, const DataType &type = eFILE, char sep = ',');
        ~Parser(void);

    // Creates getRow, rowCount, columnCount, getHeader, getHeaderElement, and getFileName function to be utilized by external code
    public:
        Row &getRow(unsigned int row) const;
        unsigned int rowCount(void) const;
        unsigned int columnCount(void) const;
        std::vector<std::string> getHeader(void) const;
        const std::string getHeaderElement(unsigned int pos) const;
        const std::string &getFileName(void) const;

    // Creates deleteRow, addRow, and sync function to be utilized as needed by external code
    public:
        bool deleteRow(unsigned int row);
        bool addRow(unsigned int pos, const std::vector<std::string> &);
        void sync(void) const;

    // Allows parsing of both header of CSV file and values
    protected:
    	void parseHeader(void);
    	void parseContent(void);

    //
    private:
        std::string _file;
        const DataType _type;
        const char _sep;
        std::vector<std::string> _originalFile;
        std::vector<std::string> _header;
        std::vector<Row *> _content;

    public:
        Row &operator[](unsigned int row) const;
    };
}

#endif /*!_CSVPARSER_HPP_*/
