#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <fstream>

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
    std::string m_flightNumber;
    std::string m_date;
    std::string m_time;
    std::string m_departVenue;
    std::string m_arriveVenue;
    std::string m_seats;
};

class FlightDock
{
    public:
        FlightDock(int numberOfInitFlight);
        virtual ~FlightDock();

        unsigned int getFlightCount() { return m_counter; }
        bool findFlight(const string& flightNumber, Flight* myFlight = NULL);
        void addFlight(string flightNumber, string data, string time, string departVenue, string arriveVenue, string seats);
        bool bookSeat(string flightNumber, string seat);

    private:
        unsigned int m_counter;
        struct Flight* m_flightArray;
        unsigned int m_maxFlightCounter;
};


FlightDock::FlightDock(int numberOfFlight)
{
    m_flightArray = (Flight*) malloc(numberOfFlight * sizeof(Flight));
    m_counter = 0;
    m_maxFlightCounter = 5;
}

FlightDock::~FlightDock()
{
    delete[] m_flightArray;
}

bool FlightDock::findFlight(const string& flightNumber, Flight* myFlight)
{
    const string flightNumberTrimed = trim(flightNumber);
    bool found = false;

    for( int i = 0; i < m_counter; i++)
    {
        if(m_flightArray[i].m_flightNumber == flightNumber)
        {
            found = true;

            if(myFlight != NULL)
            {
                myFlight = &m_flightArray[i];
            }
            break;
        }
    }
    return found;
}
// still thinkn to print information af a required flight
void getFlightDetails(Flight* myFlight)
{
   	
}

void FlightDock::addFlight(string flightNumber, string date, string time, string departVenue, string arriveVenue, string seats)
{
    if(m_counter == m_maxFlightCounter)
    {
        m_flightArray = (Flight*)realloc(m_flightArray, (m_maxFlightCounter+5) * sizeof(Flight));
        m_maxFlightCounter += 5;
    }

    m_flightArray[m_counter].m_flightNumber   = trim(flightNumber);
    m_flightArray[m_counter].m_date           = trim(date);
    m_flightArray[m_counter].m_time           = trim(time);
    m_flightArray[m_counter].m_departVenue    = trim(departVenue);
    m_flightArray[m_counter].m_arriveVenue    = trim(arriveVenue);
    m_flightArray[m_counter].m_seats          = trim(seats);

    m_counter++;
}

bool FlightDock::bookSeat(string flightNumber, string seat)
{
    Flight * myFlight;
    bool booked = false;
    if(!findFlight(flightNumber, myFlight))
    {
        cerr<<"invalid flight number"<<cout;
        return false;
    }

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

void collectData(FlightDock fd)
{
	string line;
  int lineNumber = 1;
  
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
    	cout<< line<<'\n';
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
	int command;
	Menu();
	cin>>command;
	
	FlightDock fd(5);
	//collectData(fd);
    
    
    
    Flight* fl;
    string number;
switch(command){
    case 1 :
         cout << "Excellent!" << endl; 
         break;
    case 2 :
    	 cout << "View Flight! " << endl;
    	 cout<<"Enter Flight number : ";
    	 cin>> number;
    	 if (fd.findFlight(number))
    	 {
    	 	cout << "Flight found! " << endl;
    	 	getFlightDetails(number);
		 }
		 else 
		 {
			cout << "Flight not found! " << endl;
		 }
		 break; 
    case 3 :
         
         break;
    case 4 :
         
         break;
    case 5 :
         
         break;
}

  
    return 0;
}



