
#include "GenerateFattree.h"
using namespace std;
vector<vector<int> > GenerateFattree(int nodes) {
	vector<vector<int> > res;
	res.resize(1440);
	if (nodes > 578) throw "Error, too much node for fattree";
	for (int i = 0; i < 2880; i++) {
		for (int j = 0; j < 2880; j++) {
			res[j].resize(2880);
		}
	}
	for (int i = 0; i < 1152; i += 24) {
		for (int k = i; k < i + 24; k++) {
			for (int j = 1152 + i; j < 24 + i; j++) {
				res[j][k] = 1;
				res[k][j] = 1;
			}
		}
	}
	for (int i = 1152; i < 2304; i += 24) {
		for (int k = 0; k < 24; k++) {
			for (int j = 0; j < 12; j++) {
				res[i + k][2304 + j * 48 + k + 1];
				res[2304 + j * 48 + k + 1][i + k];
				res[i + k][2304 + j * 48 + k];
				res[2304 + k * 24][i + k];
			}
		}
	}

	for (int i = 576; i < 1152; i++) {
		for (int j = 1152; j < 2304; j++) {
			if (res[i][j] == 1) {
				if ((i - 576) < nodes) {
					res[i - 576][j] = 1;
					res[j][i - 576] = 1;
				}
				res[i][j] = 0;
				res[j][i] = 0;
			}
		}
	}
	return res;
}

