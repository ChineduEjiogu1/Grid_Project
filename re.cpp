#include <iostream>
#include <iterator>
#include <string>
#include <regex>

// upper bound for size
const std::string SIZE = "2";

// this function prints out the size and elements of the matches
void print_match(std::string s, std::smatch & matches)
{
    std::cout << "For string " <<  s << " match size is " << matches.size() << "\n";

    for( int i = 0; i < matches.size(); i++){
	std::cout << "   match result #" << i << " is :" << matches[i].str() << "\n"; 
    }

}
 
int main()
{
 
    // https://www.cplusplus.com/reference/regex/regex_match/
    std::smatch matches; // variable to hold the matches
                                             
    // pattern setup
    //	regex pattern string  :  "^([0-2]{1}) ([0-2]{1})$"
    std::string pattern_string = "^([0-" + SIZE + "]{1}) ([0-" + SIZE + "]{1})$";
    const std::regex pattern(pattern_string);
    /*
  		regex:  "^([0-2]{1}) ([0-2]{1})$"
		Very explicit:  maybe redundant to specify all of these
 		^ start of the line
		$ end of the line
                [0-2]{1} exactly one number between 0..2
 		() indicate the group what we want to keep
    */
  
    
    

    // test cases
    std::string tests[] = {"0 0","0 1","1 2","3 2","-1 0","1  0","1	0"};
                                            /*
						The following are not valid: 
                                                "3 2" --> 3 is too high
                                               "-1 0" --> -1 is not valid as index on board
                                               "1  0" --> two (2) spaces separating the numbers
				               "1	0" --> tab instead of a space
					    */
                                             
   
    /* test cases */
    for(auto s: tests){
      std::cout << "Processing string: " << s << "\n";

      if(std::regex_match (s, matches, pattern))
          print_match(s,matches);
      else
          std::cout << "no match found\n";    

      std::cout << "\n";
    }



   // test user input from keybaord 
   std::string userInput = ""; // user input
   bool show_error = false;    // flag to indicate if we want to show the error message

   do{
     if (show_error == true)
	std::cout << "\n  [ Error ] "<< userInput << "  that is not a valid input\n";

     std::cout << "Please enter location: ROW [SPACE] COL" << std::endl;
     std::getline (std::cin,userInput);
     show_error = true;

   }while(!std::regex_match (userInput, matches, pattern));

   // https://www.cplusplus.com/reference/string/stoi/
   //  extract index values
   int i =  stoi( matches[1].str() );
   int j =  stoi( matches[2].str() );

   std::cout << "i is "<< i << "\n";
   std::cout << "j is "<< j << "\n";

   return 0;
 
}
