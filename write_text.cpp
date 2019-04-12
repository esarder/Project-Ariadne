#include <iostream>
#include <fstream>
using namespace std;

bool write_text(string filename, string U_NAME, string EC_NAME, string EC_EMAIL,
                  string EVENT_TITLE)
{
    ofstream myfilestream;
    myfilestream.open(filename);
    if (myfilestream.is_open())
    {
        myfilestream << "From: '" << "Project Ariadne" << "' <project.";
        myfilestream << "ariadne2270@gmail.com>" << endl;
        myfilestream << "To: '" << EC_NAME << "' <" << EC_EMAIL << ">" << endl;
        myfilestream << "Subject: This is an Emergency Alert Concerning ";
        myfilestream << U_NAME << "!" << endl;
        myfilestream << endl;
        myfilestream << "Hello, " << EC_NAME << endl;
        myfilestream << endl;
        myfilestream << "You were selected by " << U_NAME;
        myfilestream << " as an emergency contact for their Project Ariadne" << endl;
        myfilestream << "profile. For their safety, " << U_NAME <<
        myfilestream << " set up a timer, which in the event that they" << endl;
        myfilestream << "did not declare themselves safe after " << EVENT_TITLE;
        myfilestream << ", would notify you." << endl;
        myfilestream << endl;
        myfilestream << U_NAME << " has not checked in and could need ";
        myfilestream << "assistance. Please reach out to" << endl;
        myfilestream << U_NAME << " immediately." << endl;
        myfilestream << endl;
        myfilestream << "In the event of an emergency, contact your local";
        myfilestream << " police department by dialing" << endl;
        myfilestream << "911." << endl;
        myfilestream << endl;
        myfilestream << " - Project Ariadne" << endl;
    return true;
    }
    else
    {
    return false;
    }
}


int main(){
  write_text("test_email.txt", "UserName", "EmergencyContact", "emergencycontact@email.com", "hiking the CDT");
  return 0;
}
