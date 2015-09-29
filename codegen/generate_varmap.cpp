#include <bits/stdc++.h>


using namespace std;

map<string, map< string, int > >varmap;
map<string, int>paranum;
int sz;

int main(){
	ifstream in;
	size_t found;
	in.open("../tmpvar.txt");
	string line;
	string cur_func="";
	while(getline(in, line)){
		//cout << "2\n";
		found = line.find(":");
		if(found!=string::npos){
			string label = line.substr(0, found);
			string numstr = line.substr(found+1);
			int num = atoi(numstr.c_str());
			cur_func=label;
			paranum.insert(pair<string, int>(cur_func, num));
			map<string, int>tmp;
			varmap.insert(pair<string, map< string, int > >(cur_func, tmp));
		}else{
			found = line.find("=");
			if(found!=string::npos){
				string variable = line.substr(0, found);
				string indxstr = line.substr(found+1);
				int idx = atoi(indxstr.c_str());
				map<string, map< string, int > >::iterator it;
				it = varmap.find(cur_func);
				if(it!=varmap.end()){
					(it->second).insert(pair<string, int>(variable, idx));
				}
			}
		}
	}

	/*map<string, map<string, int> >::iterator mit;
	map<string, int>::iterator fit;
	int sz;
	for(mit=varmap.begin();mit!=varmap.end();++mit){
		sz=(mit->second).size();
		printf("\n%s:%d\n", (mit->first).c_str(), sz);
		for(fit=(mit->second).begin(); fit!=(mit->second).end(); ++fit ){
			printf("%s=%d\n", (fit->first).c_str(), fit->second);
		}
	}*/

	in.close();
}