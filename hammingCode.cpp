#include <iostream>
#include <math.h>
#include <bitset>
#include <cstdlib>
using namespace std;

//Function to generate codeword using the Hamming Code method
string hammingCode(string dataword, int r) {
	
	//Calculate total redundant bits
	int m = dataword.length();
	int h = m + r;
	//Make array for codeword
	string cw[h];
	int lastIndex = m - 1, pow2 = 0;
	for (int i = 0; i < h; i++) {
		if ((i+1) == pow(2,pow2)) {
			cw[i] = ("R");
			pow2++;
		}
		else {
			cw[i] = dataword[lastIndex];
			lastIndex--;
		}
	}
	
	int rs[r] = {0};
	for (int i = 1; i <= h ; i++) {
		
		string bin = bitset<8>(i).to_string().substr(8-r);
		for (int j = 0; j < r; j++) {
			if (bin[j] == '1') {	
				if (cw[i-1] != "R" && cw[i-1] != "0") {
					rs[j] ++;
				}
			}
		}
		
	}
	string rs2[r];
	for (int i = 0; i < r; i++) {
		if (rs[i] % 2 == 0) {
			rs2[i] = "0";
		}
		else {
			rs2[i] = "1";
		}
	}
	int rsIndex = r-1;
	for (int i = 0; i < h; i++) {
		if (cw[i] == "R") {
			cw[i] = rs2[rsIndex];
			rsIndex--;
		}
	}
	string rword = "";
	for (int i = h-1; i >= 0; i--) {
		rword += cw[i];
	}
	return rword;
}

string hammingCodeChecker(string codeword, int r) {
	int rs[r] = {0};
	int h = codeword.length();
	//111001101
	for (int i = 0; i < h ; i++) {
		
		string bin = bitset<8>(i+1).to_string().substr(8-r);
		for (int j = 0; j < r; j++) {
			if (bin[j] == '1') {	
				if (codeword[h-i-1] != '0') {
					rs[j]++;
				}
			}
		}
		
	}
	for (int i = 0; i < r; i++) {
		if (rs[i] % 2 == 0) {
			rs[i] = 0;
		}
		else {
			rs[i] = 1;
		}
		//cout << rs[i];
	}

	//Converting binary to decimal
	int num = 0;
	int pow2 = 0;
	for (int i = r-1; i >= 0; i--) {
		if (rs[i] == 1) {
			num += pow(2,pow2);
		}
		pow2++;
	}
	//cout << num;
	if (num != 0) {
		cout << "\nThere is an error at " << num << "position\n";
		codeword[h - num] == '0' ? codeword.replace(h-num, 1, "1") : codeword.replace(h-num, 1, "0");
		return codeword;
	}
	cout<<"No error"<<endl;
	return codeword;
	
	
}

int main() {
	string dataword;
	cout << "Enter dataword: ";
	cin >> dataword;
	int m = dataword.length(), r = 1;
	while (true) {
		if (pow(2,r) >= (m + r + 1)) break;
		r++;
	}
	//cout << r;
	string codeword = hammingCode(dataword, r);
	cout << "Codeword: " << codeword << endl;
	
	for (int i = 0; i < 10; i++) {
		int random = (int)rand() % 18;
		cout << "SentWord           ReceivedWord" << endl;
		string sentWord = codeword;
		cout << codeword << "     ";
		if (random < codeword.length()) {
			sentWord[random] == '0' ? sentWord.replace(random, 1, "1") : sentWord.replace(random, 1, "0");
		}

		cout << sentWord << endl;
		string result = hammingCodeChecker(sentWord, r);
		cout << "Correct DataWord: " << result << endl;	
	}

}