//to be compiled using c++11

#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <iterator> 
#include <cstring>



using namespace std;

char forbidden_char[4] = ".,:";
bool is_present = true;
bool printed = false;

void print_vector(std::vector<std::vector<int> > v)
{
	for(int j=0; j<v.size(); j++)
	{
		for(int i = 0; i< (v[j]).size() ; i++)
		{
			cout<<v[j][i]<<" ";
		}
		cout<<endl;
	}
}


// Removes the forbidden charecters and converts the string into lowercase
void clear_string(string &str, char* charsToRemove ) {
   for ( unsigned int i = 0; i < strlen(charsToRemove); ++i )
   {
      str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
      transform(str.begin(), str.end(), str.begin(), ::tolower);
   }
}


// Gives a map with word from the entered sentence in lexicographic order followed by a 
// vector which has positions at which it is present in the sentence.
void give_map(std::vector<string> tokens, std::map<string, std::vector<int> >& main_map)
{

	std::vector<string> sorted_sentence = tokens;
	std::sort(sorted_sentence.begin(),sorted_sentence.end());

	sorted_sentence.erase( unique( sorted_sentence.begin(), sorted_sentence.end() ), sorted_sentence.end() );
	auto itr_sorted_sentence = sorted_sentence.begin();

	while(std::distance(itr_sorted_sentence,sorted_sentence.end()) > 0 )
	{
		auto iter = tokens.begin(); 
		while ((iter = std::find(iter, tokens.end(), *itr_sorted_sentence)) != tokens.end()) 
			{ 
				int idx = std::distance(tokens.begin(), iter);
				(main_map[*itr_sorted_sentence]).push_back(idx);
				iter++; 
			}
		itr_sorted_sentence++;
	}
}

void reduce_vector(std::vector<std::vector<int> >& v)
{	
	int i=0;
	int j=0;
	int min_size = (v[0]).size();
	while(i < v.size())
	{
		i++;
		if ((v[i]).size() < min_size) min_size = (v[i]).size();
	}

	i=0;
	j=1;

	for (int k = 0; k < (v[0]).size(); k++)
	{
		while(i< v.size()-1)
		{
			if((v[i][k]+1 == v[i+1][k]) || (v[i][k]+1 == v[i+1][k+1]))
			{
				while(j < (v[i]).size()-1)
				{
					if ((v[i][j]+1 != v[i+1][j]) && (v[i][j]+1 != v[i+1][j+1]) ) is_present = false;
					j++;
				}
			}
			i++;	
		}
		if (is_present == true) {cout<<v[0][k]<<" "; printed =true; }
		// j++;
		// is_present = false;
	}
	// print_vector(v);
}


void find_in_map(std::vector<string> to_search,std::map<string, std::vector<int> > main_map)
{
	std::vector<std::vector<int> > temp;	
	auto itr_temp = to_search.begin();
	// cout << "oyo"<<endl;
	while(std::distance(itr_temp,to_search.end()) > 0 )
	{
	// cout << "oyo1"<<endl;

		if ( main_map.count(*itr_temp) == 0 ) {is_present = false; /*cout << "oyo2	"<<*itr_temp<<endl;*/return;}
		else 
		{
			// cout << "oyo3"<<endl;
			temp.push_back(main_map[*itr_temp]);
		}
		itr_temp++;
		// cout<<"pro";
	}
	// cout<<"yos!";
	reduce_vector(temp);
}

int main()
{
	string sentence;
	getline(cin,sentence);
    istringstream iss(sentence);
    std::vector<string> tokens;
	copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(tokens));

	for(auto itr = tokens.begin();std::distance(itr,tokens.end()) > 0; itr++)
		{
			clear_string( *itr, forbidden_char);
		}

	std::vector<string> to_search; // Contains search term
	auto itr_to_search = std::find(tokens.begin(),tokens.end(),"*");
	for(auto itr = std::next(itr_to_search);std::distance(itr,tokens.end()) > 0; itr++)
	{
		to_search.push_back(*itr);
	}
	tokens.erase(itr_to_search,tokens.end());

	

	std::map<string, std::vector<int> > main_map;
	give_map(tokens,main_map);
	
	if ( to_search.size() != 0 ) 
		find_in_map(to_search,main_map);
	else cout<<"No search keyword entered"<<endl;
	if (printed == false) cout<<"Keyword not found in the string"<<endl;
	
	return 0;
}
