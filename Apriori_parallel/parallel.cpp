#include <bits/stdc++.h>
#include <string>
#include <pthread.h>
using namespace std;
vector<string> iFile;
//class Apriori{
//private:
int minSup;
int curLevel;
set<set<int> > frequent[256];
set<set<int> > closedFrequent;
map<set<int>,int> support;
typedef struct thread_input{
	set<set<int> > isets;
	int level;
} thi;
//public:
void setSupport(int sup){
	minSup = sup;
}
void *doApriori(void* inpu){
	thi *input = (thi *) inpu;
	set<set<int> > curSet = input->isets;
	/*for(set<set<int> >::const_iterator it = curSet.begin();it!=curSet.end();it++){
		for(set<int>::const_iterator jt = (*it).begin();jt!=(*it).end();jt++){
			cout << *jt ;
		}
		cout << "A" << endl;
	}*/
	int level = input->level;
	curLevel = max(curLevel,level);
	vector<set<set<int> > >candidates;
	for(set<set<int> >::const_iterator it = curSet.begin();it!=curSet.end();it++){
		set<set<int> >::const_iterator jt = it;
		jt++;
		set<set<int> > tempSets;
		tempSets.clear();
		for(;jt!=curSet.end();jt++){
			set<int>::const_iterator kt = (*it).begin();
			set<int>::const_iterator kt2 = (*jt).begin();
			set<int> temp;
			int l = 0;
			int flag=0;
			for(;(kt)!=(*it).end();kt++,kt2++){
				temp.insert(*kt);
				temp.insert(*kt2);
			}
			tempSets.insert(temp);
		}
		/*for(set<int>::const_iterator kt = (*it).begin();kt!=(*it).end();kt++){
			cout << *kt ;
		}
		cout << " " << tempSets.size() << "B" <<endl;*/
		candidates.push_back(tempSets);
	}
	map<set<int>,int> frequency;
	string trans;
	for(int i=0;i<iFile.size();i++){
		trans = iFile[i];
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
		for(size_t j=0;j<candidates.size();j++){
			for(set<set<int> > ::const_iterator it = candidates[j].begin();it!=candidates[j].end();it++){
				int flag=0;
				for(set<int>::const_iterator jt = (*it).begin();jt!=(*it).end();jt++){
					if(v.find(*jt)==v.end()) flag=1;
				}
				if(flag==0) frequency[*it]++;
			}
		}
	}
	for(map<set<int>,int> :: const_iterator it = frequency.begin();it!=frequency.end();it++){
		support[it->first] = it->second;
		if(it->second >= minSup){
			frequent[level].insert(it->first);
		}
	}
	pthread_t ptds[candidates.size()];
	thi temp[candidates.size()];

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	int errCode[candidates.size()] = {0};

	int cc = 0;
	int rc = 0;
	for(int i=0;i<candidates.size();i++){
		set<set<int> > tempSets;
		for(set<set<int> > :: const_iterator it = candidates[i].begin();it!=candidates[i].end();it++){
			if(frequency[*it] >= minSup){
				tempSets.insert(*it);
				frequent[level].insert(*it);
			}
		}
		//cout << "tempSets.size() = " << tempSets.size() << endl;
		if(tempSets.size()!=0){
			temp[cc].isets = tempSets;
			temp[cc].level = level+1;
			errCode[cc] = pthread_create(&ptds[cc], NULL, doApriori, (void *)&temp[cc]);
			//doApriori((void *)&temp);
			if (errCode[cc]){
				cout << "Error:unable to create thread," << errCode[cc] << endl;
				exit(-1);
			}
			else{
			//	cout << "Thread created-" << cc<<endl;
			}
			cc++;
		}
	}
	pthread_attr_destroy(&attr);
	void* status;
	rc = 0;
	for(int i=0; i < cc; i++ ){
		errCode[i] = pthread_join(ptds[i], &status);
		if (errCode[i]){
		//	cout << i << " " << *((*((temp[i].isets).begin())).begin());
			cout << "Error:unable to join," << errCode[i] << endl;
			exit(-1);
		}
		//cout << "Main: completed thread id :" << i ;
		//cout << "  exiting with status :" << status << endl;
	}
}

void generateLevelOne(){
	string s;
	map<int,int> m;
	for(int i=0;i<iFile.size();i++){
		s = iFile[i];
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
	for(map<int,int >::const_iterator it = m.begin();it!=m.end();it++){
		set<int> ss;
		ss.insert(it->first);
		support[ss] = it->second;
		if(it->second >= minSup){
			frequent[0].insert(ss);
		}
	}
	curLevel = 1;
	thi temp;
	temp.level = 1;
	temp.isets = frequent[0];
	doApriori((void *)&temp);
}
void display(){
	for(int i=0;i<=curLevel;i++){
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
//};
int main(){
	//Apriori apr;
	ifstream ifs ("input.txt");
	if(ifs){
		ifs.seekg(0,ifs.beg);
		string s;
		getline(ifs,s);
		setSupport(stoi(s));
		while(getline(ifs,s)){
			iFile.push_back(s);
		}
		ifs.close();
	}
	generateLevelOne();
	display();
	return 0;
}
