// To be compiled using c++11


#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <iterator> 
#include <typeinfo>


using namespace std;

string z_string = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";

int main()
{	
	string sentence;

	//taking string as an input and inserting it into vector tokens
	getline(cin,sentence);
    istringstream iss(sentence);
    std::vector<string> tokens;
	copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(tokens));
	tokens.push_back(z_string);

	std::vector<string> orignal_tokens = tokens;

	//Defining and filling map
	// std::map<int,std::map<string, std::vector<int> > > entry;
	std::map<string, std::vector<int> > entry1;
	std::vector<std::vector<int> > entry0;

	std::sort(tokens.begin(),tokens.end());
	auto itr_entry1 = entry1.cbegin();
	auto itr_entry0 = entry0.cbegin();
	auto itr_tokens = tokens.begin();
	
	int i = 0;

	while(itr_tokens != tokens.end())
	{
		auto itr = std::find(orignal_tokens.begin(),orignal_tokens.end(),*itr_tokens);


		if(itr_tokens != --itr_tokens)
		{
			i++;
		}
 		++itr_tokens;
	}


	// for(int i = 0; i < tokens.size(); i++)
	// {
	// 	entry1.emplace(make_pair(tokens[i],));
	// }

	// for( itr_entry1 = *entry.map::begin(); itr_entry1 != *entry.map::end(); ++itr_entry1)
	// {
	// 	entry.insert(pair<int,std::map<string,int> >(i,entry1));
	// }
	

	return 0;
}