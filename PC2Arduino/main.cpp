//omdannet kode med switch case

#include <iostream>
#include <string>
#include <stdlib.h>
#include "SerialPort.h"
#include "windows.h"

using namespace std;

char output[MAX_DATA_LENGTH]; //MAX_DATA_LENGTH fra .h-filen
char port[] = "\\\\.\\COM8"; //skfit til rigtig com-port
char incoming[MAX_DATA_LENGTH];
/*
1. Speed
2. Message
3. High intensity
4. Low intensity
5. Update Attributes
*/

int toArd(string command);

int main()
{
    char selection = 0;
    int speed = 20; //8 er 1 i sekundet
    string message = "test besked";
    int lowIntensity = 1;
    int highIntensity = 10;
    string allAttributes;

    /*
    int getSpeed = uint16_t getSpeed() const;
    string getMessage = string getMessage() const;
    int getOnIntensity = uint8t getOnIntensity() const;
    int getOffIntensity = uint8t getOffIntensity() const;
    */

    char dummy[] = { 1,0,0,1,0,0,1,1,1,0,0,1,1 };
    int i = 0; //sizeof(dummy) / sizeof(dummy[0])

    do
    {
        system("CLS");
        cout << "  JUNO Communication 0.2\n";
        cout << "  ====================================\n";
        cout << "  1.  Select speed\n";
        cout << "  2.  Select message\n";
        cout << "  3.  Select intensity\n";
        cout << "  4.  Show current attributes\n";
        cout << "  5.  Update attributes\n";
        cout << "\n";
        cout << "  6.  Exit\n";
        cout << "  ====================================\n";
        cout << "  Enter your selection: ";
        cin >> selection;
        cout << endl;

        switch (selection)
        {
        case '1':
            system("CLS");
            cout << "Select speed:\n";
            cout << "Range from 1-31, 8 is once per second\n";
            cin >> speed; 
            //setSpeed(speed);
            cout << "\n";
            break;

        case '2':
            system("CLS");
            cout << "Select message:\n";
            getline(cin >> ws, message); //remove whitespace for blank spaces in message
            //setMessage(message) 
            cout << "\n";
            break;

        case '3':
            system("CLS");
            cout << "Select low intensity:\n";
            cout << "Range from 1-31\n";
                
            cin >> lowIntensity;
            
            //setOffIntensity(lowIntensity);
            
            cout << "\n";
            
            cout << "Select high intensity:\n";
            cout << "Range from 1-31\n";
            
            cin >> highIntensity;
                
            //setOnIntensity(highIntensity);
            
            cout << "\n";

                //here we check if intensity values are correct, low should be lower than high
                while (lowIntensity > highIntensity) { 
                    cout << "Intensity values are not corret, try again\n";
                    cout << "Select low intensity:\n";
                    cin >> lowIntensity;
                    cout << "\n";
                    cout << "Select high intensity:\n";
                    cin >> highIntensity;
                    cout << "\n";
                }
            break;
        
        case '4':
            system("CLS");
            cout << "Speed:  " << speed << endl << "Message:  " << message << endl << "Low Intensity:  " 
                << lowIntensity << endl << "High Intensity:  " << highIntensity << endl << endl;
            /*
                        cout << "Speed:  " << getSpeed << endl << "Message:  " << getMessage << endl << "Low Intensity:  " 
                << getLowIntensity << endl << "High Intensity:  " << getHighIntensity << endl << endl;
            */
            cout << "Returning in 5 seconds..." << endl;
            Sleep(5000);
            break;

        case '5':
            system("CLS");

            allAttributes = to_string(speed) + message + to_string(lowIntensity) + to_string(highIntensity);

            cout << "Connecting to Arduino...\n" << endl;

            cout << "Arduino will receive:\n" << allAttributes << endl;

            toArd(allAttributes);

            //toArd("OFF"); //TIL AT TESTE toArd FUNKTION MED CUSTOM BESKED!

            //allAttrPtr = getAllAttrPtr();
            //toArd(allAttrPtr);
            // ELLER:
            //toArd(*getallattr());

            break;

        case '6':
            cout << "Goodbye.\n";
            Sleep(2000);
            exit(1);
            break;

        default: cout << selection << " is not a valid menu item.\n";

            cout << endl;
        }

    } while (selection != 6);

    return 0;
}

int toArd(string command) {

    SerialPort arduino(port);
    if (arduino.isConnected()) {
        cout << "Connection established to Arduino\n" << endl;
    }
    else {
        cout << "Error in port name";
    }
    //while (arduino.isConnected()) {
        //string command;
        //cout << "Besked til Arduino:\n";
        //cin >> command;
        char* charArray = new char[command.size() + 1];
        copy(command.begin(), command.end(), charArray);
        charArray[command.size()] = '\n';

        arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);
        arduino.readSerialPort(output, MAX_DATA_LENGTH);

        cout << "\nAttributes updated to Arduino!" << endl;

        cout << "ARDUINO OUTPUT: " << output << endl; //output fra Arduino bliver cout'et her, måske ikke nødvendigt

        delete[] charArray;

        Sleep(3000);
    //}
    return 0;
}

int attrToArd() {
    return 0;
}