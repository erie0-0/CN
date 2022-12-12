#include <iostream>
#include <string>
#include <sstream> //string stream
#include <cstdlib>
using namespace std;

class Polynomial {
    private:
        int *arr;
    public:
        int degree;
        Polynomial() {
            cout << "Enter highest degree of polynomial: ";
            cin >> degree;

            arr = new int[degree];

            for (int i = degree; i >= 0; i--) {
                int coeff;
                cout << "Enter coefficient for x^" << i << " : ";
                cin >> arr[i];
            }
        }
        string getBinaryStream() {
            string bs = "";
            for (int i = degree; i >= 0; i--) {
                if (arr[i] != 0) bs += "1";
                else bs += "0";
            }
            return bs;
        }
};

//string XOR(string x, string y) {
//    string out = "";
//    for (int i = 0; i < x.length(); i++) out += (x[i] == y[i]) ? "0" : "1";
//    return out;
//}
string XOR(string a, string b)
{
	
	// Initialize result
	string result = "";
	
	int n = b.length();
	
	// Traverse all bits, if bits are
	// same, then XOR is 0, else 1
	for(int i = 1; i < n; i++)
	{
		if (a[i] == b[i])
			result += "0";
		else
			result += "1";
	}
	cout << "XOR " << result << endl;
	return result;
}

string binaryDiv(string divident, string divisor)
{
	
	// Number of bits to be XORed at a time.
	int index = divisor.length();
	
	// Slicing the divident to appropriate
	// length for particular step
	string tmp = divident.substr(0, index);
	
	int n = divident.length();
	
	while (index < n)
	{
		if (tmp[0] == '1') {
		
		
			// Replace the divident by the result
			// of XOR and pull 1 bit down
			tmp = XOR(divisor, tmp) + divident[index];
			cout << "tmp  " << tmp << endl;
		}
		else {
		
		
			// If leftmost bit is '0'.
			// If the leftmost bit of the dividend (or the
			// part used in each step) is 0, the step cannot
			// use the regular divisor; we need to use an
			// all-0s divisor.
			tmp = XOR(std::string(index, '0'), tmp) + divident[index];
			cout << "tmp  " << tmp << endl;
		}
		// Increment index to move further
		index += 1;
	}
	
	// For the last n bits, we have to carry it out
	// normally as increased value of index will cause
	// Index Out of Bounds.
	if (tmp[0] == '1') {
		tmp = XOR(divisor, tmp);
		cout << "tmp  " << tmp << endl;
	}
		
	else {
		tmp = XOR(std::string(index, '0'), tmp);
		cout << "tmp  " << tmp << endl;
	}
				
	return tmp;
}

string CRCEncoder(string dataword, Polynomial p) {
    //Step 1 - Generate Binary stream from polynomial
    string bs = p.getBinaryStream();

    //Step 2 - Append n zeroes at LSB to data word, where n is highest degree of polynomial
    string d = dataword + string(p.degree, '0');
    cout << "Appended " << d << endl;

    //Step 3 - Perform binary division to obtain CRC bits.
    string CRC = binaryDiv(bs, d);
    cout << endl << CRC << endl;

    //Step 4 - Append CRC bits at LSB within dataword and return dataword as codeword.
    return dataword + CRC;
}

bool CRCChecker(string codeword, Polynomial p) {
    string rem = binaryDiv(codeword, p.getBinaryStream());
    for (int i = 0; i < rem.length(); i++) {
        if (rem[i] != '0') return false;
    }
    return true;
}


int main() {
    string s;
    cout << "Enter dataword: ";
    cin >> s;
    Polynomial p;
    string codeword = CRCEncoder(s, p);

	for (int i = 0; i < 10; i++) {
		int random = (int)rand() % 16;
		cout << "SentWord           ReceivedWord" << endl;
		string sentWord = codeword;
		cout << codeword << "     ";
		if (random < codeword.length()) {
			codeword[random] == '0' ? sentWord.replace(random, 1, "1") : sentWord.replace(random, 1, "0");
		}
		
		bool result = CRCChecker(sentWord, p);
		
		cout << sentWord << endl;
		sentWord = codeword;
		if (result) cout << "Data is good.\n";
    	else cout << "Corrupted Data found\n";
    	cout << endl << "----------------" << endl;
	}
    
}
