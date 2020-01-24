#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include<string.h>

using namespace std;

const string ESCAPECHAR = " \n\r\t\f\v";
const string WHITESPACE = " ";
const string NEWLINE = "\n";

std::string ltrim(const std::string& s)
{
    size_t start = s.find_first_not_of(ESCAPECHAR);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string& s)
{
    size_t end = s.find_last_not_of(ESCAPECHAR);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s)
{
    return rtrim(ltrim(s));
}

struct Flight
{
    string m_flightNumber;
    string m_date;
    string m_time;
    string m_departVenue;
    string m_arriveVenue;
    string m_seats;
};

class FlightDock
{
    public:
        FlightDock(int numberOfInitFlight);
        virtual ~FlightDock();

        unsigned int getFlightCount() { return m_counter; }
        bool findFlight(const string& flightNumber);
        bool findFlight(const string& flightNumber,int& myFlightIdx);
        void addFlight(string flightNumber, string data, string time, string departVenue, string arriveVenue, string seats);
        bool bookSeat(string flightNumber, string seat);
        bool displayFlight(const string& flightNumber);
        void getAll();
        bool checkAvail(string flightNumber,int num);
        void writeFile();

    private:
        unsigned int m_counter;
        struct Flight* m_flightArray;
        unsigned int m_maxFlightCounter;
};
bool FlightDock::checkAvail(string flightNumber,int num)
{
	
//    Flight * myFlight;
//    int myFlightIdx;
//    int count = 0;
//    int position=0;
//    if(!findFlight(flightNumber, myFlightIdx))
//    {
//        cerr<<"invalid flight number"<<cout;
//        return false;
//    }
//    myFlight = &m_flightArray[myFlightIdx];
//    bool avail = false;
//    
//	string seatString = myFlight->m_seats;
//     count = std::count(seatString.begin(), seatString.end(), '\n');
//     count += 1 ;
//     if (count >= num )
//     {
//     	avail = true;
//	 }
int count =0;
Flight * myFlight;
int myFlightIdx;
findFlight(flightNumber, myFlightIdx);
myFlight = &m_flightArray[myFlightIdx];
bool avail = false;
string seatString = myFlight->m_seats;
stringstream iss(seatString);
 while(iss.rdbuf()->in_avail() != 0)
    {
        int temRowNumber;
        char tempSeatClass;
        string tempSeatNumber;
        stringstream buff;
        try
        {
            if(iss.rdbuf()->in_avail() != 0)
                iss >> temRowNumber;
            else
                break;

            if(iss.rdbuf()->in_avail() != 0)
                iss >> tempSeatClass;
            else
                break;

            if(iss.rdbuf()->in_avail() != 0)
			{
				iss >> tempSeatNumber;
                count += tempSeatNumber.length();
			}
                
            else
                break;
        }
        catch (std::exception& ex)
        {
            cerr<<ex.what()<<endl;
            return false;
        }
    }
	 if (count>=num)
	 {
	 	avail = true;
	 }
return avail;	
}

bool FlightDock::displayFlight(const string& flightNumber)
{
    int myFlightIdx;
    if(!findFlight(flightNumber, myFlightIdx))
    {
        return false;
    }
    Flight *myFlight = &m_flightArray[myFlightIdx];
    cout<<"FLIGHT_NAME: "<<myFlight->m_flightNumber<<endl;
    cout<<"DATE_&_TIME: "<<myFlight->m_date<<" "<<myFlight->m_time<<endl;
    cout<<"DEPARTURE: "<<myFlight->m_departVenue<<endl;
    cout<<"ARRIVAL: "<<myFlight->m_arriveVenue<<endl;
    cout<<"SEATS AVAILABLE"<<endl;
    cout<<"---------------"<<endl;
    cout<<myFlight->m_seats<<endl<<endl;
    return true;
}
void FlightDock::writeFile()
{
	ofstream myfile;
	myfile.open ("Flights1.txt");
	if(myfile.is_open())
	{
		for( int i = 0; i < m_counter; i++)
    {
    	
        Flight *myFlight = &m_flightArray[i];
        
        
		myfile << myFlight->m_flightNumber<<endl;
		myfile << myFlight->m_date<<" "<<myFlight->m_time<<endl;
		myfile << myFlight->m_departVenue<<endl;
		myfile << myFlight->m_arriveVenue<<endl;
		myfile << myFlight->m_seats<<endl<<endl;
		
        
    }
	}
    
    myfile.close();
}
FlightDock::FlightDock(int numberOfFlight)
{
    m_flightArray = new Flight[numberOfFlight];
    m_counter = 0;
    m_maxFlightCounter = 5;
}

FlightDock::~FlightDock()
{
    delete[] m_flightArray;
}
void FlightDock::getAll()
{
	for( int i = 0; i < m_counter; i++)
    {
        displayFlight(m_flightArray[i].m_flightNumber);
        
    }
}

bool FlightDock::findFlight(const string& flightNumber)
{
    const string flightNumberTrimed = trim(flightNumber);
    bool found = false;

    for( int i = 0; i < m_counter; i++)
    {
        if(m_flightArray[i].m_flightNumber == flightNumber)
        {
            found = true;
        }
    }
    return found;
}

bool FlightDock::findFlight(const string& flightNumber, int& myFlightIdx)
{
    const string flightNumberTrimed = trim(flightNumber);
    bool found = false;

    for( int i = 0; i < m_counter; i++)
    {
        if(m_flightArray[i].m_flightNumber == flightNumber)
        {
            found = true;
            myFlightIdx = i;
        }
    }
    return found;
}


void FlightDock::addFlight(string flightNumber, string date, string time, string departVenue, string arriveVenue, string seats)
{
    if(m_counter == m_maxFlightCounter)
    {
        m_flightArray = (Flight*)realloc(m_flightArray, (m_maxFlightCounter+5) * sizeof(Flight));
        m_maxFlightCounter += 5;
    }

    m_flightArray[m_counter].m_flightNumber   = flightNumber;
    m_flightArray[m_counter].m_date           = trim(date);
    m_flightArray[m_counter].m_time           = trim(time);
    m_flightArray[m_counter].m_departVenue    = trim(departVenue);
    m_flightArray[m_counter].m_arriveVenue    = trim(arriveVenue);
    m_flightArray[m_counter].m_seats          = trim(seats);

    m_counter++;
    //displayFlight(flightNumber);
}

bool FlightDock::bookSeat(string flightNumber, string seat)
{
    Flight * myFlight;
    bool booked = false;
    int myFlightIdx;
    if(!findFlight(flightNumber, myFlightIdx))
    {
        cout<<"invalid flight number"<<cout;
        return false;
    }
    myFlight = &m_flightArray[myFlightIdx];
    stringstream iss(seat);
    int rowNumber;
    char seatClass;
    char seatNumber;

    try
    {
        if(iss.rdbuf()->in_avail() != 0)
            iss >> rowNumber;
        else
        {
            cerr<<"invalid seat description"<<endl;
            return false;
        }

        if(iss.rdbuf()->in_avail() != 0)
            iss >> seatClass;
        else
        {
            cerr<<"invalid seat description"<<endl;
            return false;
        }

        if(iss.rdbuf()->in_avail() != 0)
            iss >> seatNumber;
        else
        {
            cerr<<"invalid seat description"<<endl;
            return false;
        }

    }
    catch (std::exception& ex)
    {
        cerr<<"wrong format of seat "<<ex.what()<<endl;
        return false;
    }

    string seatString = myFlight->m_seats;

    iss.clear();
    iss.str(seatString);

    string bufferString="";

    while(iss.rdbuf()->in_avail() != 0)
    {
        int temRowNumber;
        char tempSeatClass;
        string tempSeatNumber;
        stringstream buff;
        try
        {
            if(iss.rdbuf()->in_avail() != 0)
                iss >> temRowNumber;
            else
                break;

            if(iss.rdbuf()->in_avail() != 0)
                iss >> tempSeatClass;
            else
                break;

            if(iss.rdbuf()->in_avail() != 0)
                iss >> tempSeatNumber;
            else
                break;
        }
        catch (std::exception& ex)
        {
            cerr<<ex.what()<<endl;
            return false;
        }

        if(temRowNumber == rowNumber && tempSeatClass == seatClass && !booked)
        {
            size_t found = tempSeatNumber.find(seatNumber);

            if(found != std::string::npos)
            {
                booked = true;
                tempSeatNumber.erase(found, found+1);
            }
        }
		
        buff << bufferString << temRowNumber << " " << tempSeatClass << " " << tempSeatNumber << "\n";
        bufferString = buff.str();
        
    }

    if(booked)
    {
        myFlight->m_seats = bufferString;
    }
    return booked;
}

void removeDupWord(string str,string* date, string* time) 
{ 

    // Used to split string around spaces. 
    istringstream ss(str); 
  int i=1;
    // Traverse through all words 
     while (i<3)
	{
		string word;
		if (i ==1 ) 
		{
			ss >> *date;
			i +=1;
		}
        else if (i==2)
		{
        	ss >> *time;
        	i +=1;
		}
		 
	} 
	
} 

void collectData(FlightDock& fd)
{
  int lineNumber = 1;
  
  
  string line;
  string number;
  string date;
  string time;
  string deptair;
  string arriveair;
  string seats;
  

  ifstream myfile;
  myfile.open("Flights.txt");
  //read each line and store the variables. when empty line found start new.
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
    	//cout<< line<<'\n';
    	if (lineNumber==1)
		{
			number = line;
			//cout << "Flight name "<< line << '\n';
			lineNumber +=1;
		}
		else if (lineNumber==2)
		{
			removeDupWord(line,&date,&time);
			//cout << "Flight date "<< date << '\n';
			lineNumber +=1;
		}
		else if (lineNumber==3)
		{
			deptair = line;
			//cout << "Flight deptair "<< line << '\n';
			lineNumber +=1;
		}
		else if (lineNumber==4)
		{
			arriveair = line;
			//cout << "Flight arriveair "<< line << '\n';
			lineNumber =0;
		}
		else if (line != "")
		{
			seats.append(line);
			seats.append("\n");
		}
		else 
		{
			lineNumber =1;
			fd.addFlight(number,date,time,deptair,arriveair,seats);
			seats.clear();
		}
		
      
    }
    
    myfile.close();
  }

  else cout << "Unable to open file"; 

}

void Menu(){
    
 cout<< "Select the necessary command from the menu\n";
 cout<< "1 Display all flights"<<endl;
 cout<< "2 View flight\n";
 cout<< "3 Seat Availability\n";
 cout<< "4 Seat Booking\n";
 cout<< "5 Exit\n";

}

int main()
{
	FlightDock fd(5);
	collectData(fd);
	
	int command;
	Menu();
	cin>>command;
	Flight* fl;
    string number;
    string seatLoc;
    string ccc;
    int seatCount;
    
switch(command){
    case 1 :
         cout << "Displaying all flights !" << endl;
         
         fd.getAll();
         main();
         break;
    case 2 :
    	 cout << "View Flight! " << endl;
    	 cout<<"Enter Flight number : ";
    	 cin>> number;
    	 if (fd.findFlight(number))
    	 {
    	 	cout << "Flight found! " << endl;
    	 	fd.displayFlight(number);
		 }
		 else
		 {
			cout << "Flight not found! " << endl;
		 }
		 main();
		 break;
    case 3 :
    	cout << "Enter Flight number : " ;
    	cin >> number;
    	cout << "Enter number of seats : " ;
    	 cin>>seatCount;
		 if(fd.checkAvail(number,seatCount))
		 {
		 	cout<<"Seat Available"<<endl;
		 }
		 else
		 {
		 	cout<<"Seat Not Available"<<endl;
		 }
		 main();
         break;
    case 4 :
    	cout << "Enter Flight number : " ;
    	cin>> number;
    	
    	cout << "Enter Seat location : " ;
		getline(cin,seatLoc);
		getline(cin,seatLoc);
		cout<<endl;
    	
    	
		//cin.getline(cin,seatLoc);
		
		if(fd.bookSeat(number,seatLoc))
		{
			cout << "Flight : "<<number <<" Seat : "<<seatLoc<<" Booked\n" ;
		}
		else 
		{
            cout << "Not booked"<<endl ;	
		}
		main();
         break;
    case 5 :
		 fd.writeFile();
		 
         break;
}
return 0;
    
}


