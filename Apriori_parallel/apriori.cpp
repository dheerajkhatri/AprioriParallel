#include <bits/stdc++.h>
#include <string>
using namespace std;
class Apriori{
private:
	int minSup;
	int curLevel;
	set<set<int> > frequent[256];
	set<set<int> > closedFrequent;
	map<set<int>,int> support;
public:
	void setSupport(int sup){
		minSup = sup;
	}
	void doApriori(){
		set<set<int> > candidates;
		for(set<set<int> >::const_iterator it = frequent[curLevel-1].begin();it!=frequent[curLevel-1].end();it++){
			set<set<int> >::const_iterator jt = it;
			jt++;
			for(;jt!=frequent[curLevel-1].end();jt++){
				set<int>::const_iterator kt = (*it).begin();
				set<int>::const_iterator kt2 = (*jt).begin();
				set<int> temp;
				int l = 0;
				int flag=0;
				for(;(kt)!=(*it).end();kt++,kt2++){
					temp.insert(*kt);
					if(((*kt) == (*kt2)) && (flag==0)) l++;
					if((*kt) != (*kt2)){
						flag=1;
						temp.insert(*kt2);
					}
				}
				if(l == (*it).size() - 1) candidates.insert(temp);
			}
		}
		map<set<int>,int> frequency;
		string trans;
		ifstream ifs ("input.txt");
		if(ifs){
			ifs.seekg(0,ifs.beg);
			while(getline(ifs,trans)){
				string temp = "";
				set<int> v;
				for(int j=0;j<trans.length();j++){
					if(trans[j]==' '){
						v.insert(stoi(temp));
						temp="";
					}
					else temp += trans[j];
				}
				v.insert(stoi(temp));
				for(set<set<int> > ::const_iterator it = candidates.begin();it!=candidates.end();it++){
					int flag=0;
					for(set<int>::const_iterator jt = (*it).begin();jt!=(*it).end();jt++){
						if(v.find(*jt)==v.end()) flag=1;
					}
					if(flag==0) frequency[*it]++;
				}
			}
			ifs.close();
		}
		for(map<set<int>,int> :: const_iterator it = frequency.begin();it!=frequency.end();it++){
			support[it->first] = it->second;
			if(it->second >= minSup){
				frequent[curLevel].insert(it->first);
			}
		}
		if(frequent[curLevel].size()!=0){
			curLevel++;
			doApriori();
		}
	}
	void generateLevelOne(){
		ifstream ifs ("input.txt");
		if(ifs){
			ifs.seekg(0,ifs.beg);
			string s;
			map<int,int> m;
			while(getline(ifs,s)){
				string temp = "";
				for(int j=0;j<s.length();j++){
					if(s[j]==' '){
						m[stoi(temp)]++;
						temp="";
					}
					else temp += s[j];
				}
				m[stoi(temp)]++;
			}
			ifs.close();
			for(map<int,int >::const_iterator it = m.begin();it!=m.end();it++){
				set<int> ss;
				ss.insert(it->first);
				support[ss] = it->second;
				if(it->second >= minSup){
					frequent[0].insert(ss);
				}
			}
		}
		curLevel = 1;
	}
	void display(){
		for(int i=0;i<curLevel;i++){
			for(set<set<int> > :: const_iterator it = frequent[i].begin();it!=frequent[i].end();){
				for(set<int>::const_iterator jt = (*it).begin();jt!=(*it).end();jt++){
					cout << *jt;
				}
				cout << "," <<  support[*it];
				it++;
				if(it!=frequent[i].end()) cout << " ";
			}
			cout << "\n";
		}
	}
};
int main(){
	Apriori apr;
	ifstream ifs ("input.txt");
	if(ifs){
		ifs.seekg(0,ifs.beg);
		string s;
		getline(ifs,s);
		apr.setSupport(stoi(s));
		ifs.close();
	}
	apr.generateLevelOne();
	apr.doApriori();
	apr.display();
	return 0;
}
