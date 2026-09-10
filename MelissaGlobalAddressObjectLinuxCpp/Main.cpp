/**
 * @file Main.cpp
 * @brief Global Address Object corrects, verifies, and enhances Global addresses from over 250+
 * countries and territories. International address data quality is a challenge for
 * organizations of all sizes. Its differing address structures, terms, and alphabets can
 * have a substantial negative impact on your data-driven initiatives if handled poorly.
 * By using Global Address Object, you'll reduce undeliverables, increase communication
 * efforts, and save money on all your marketing campaigns.
 *
 * This object uses a name/value parameter API: inputs go in by name through
 * SetInputParameter("input...", ...) and every result is read back by name through
 * GetOutputParameter("..."). There are no per-field getters and no GetResults() call;
 * even the result codes are just another named output ("resultCodes").
 *
 * High-level flow of this sample:
 *   1. SETUP     - create an mdGlobalAddr instance, hand it the license string and the
 *                  path to the data files, then InitializeDataFiles() (one time).
 *   2. INPUT     - set the address fields via SetInputParameter("input...", ...).
 *   3. PROCESS   - VerifyAddress() validates and standardizes the address.
 *   4. READ      - pull the corrected fields back out with GetOutputParameter("...")
 *                  (formattedAddress, latitude, iso2Code, MAK, ...).
 *   5. INTERPRET - GetOutputParameter("resultCodes") returns comma-separated result
 *                  codes describing what the object did/found.
 *
 * The pieces of this sample map onto that flow:
 *   - main / ParseArguments / RunAsConsole : console harness (argument parsing + the interactive loop).
 *   - GlobalAddressObject : thin wrapper around mdGlobalAddr that owns setup + the call sequence.
 *   - DataContainer       : holds one record's input fields, plus a small request filter.
 *
 * Where mdGlobalAddr comes from:
 *   There is no generated wrapper source for C++. mdGlobalAddr.h and
 *   mdEnums.h declare the API, and libmdGlobalAddr.so carries the implementation. libmdAddr.so, libmdGeo.so,
 *   and libmdRightFielder.so are downloaded alongside it. The
 *   accompanying MelissaGlobalAddressObjectLinuxCpp.sh script downloads all six on every run.
 *
 * Reference:
 *   Quickstart    : https://docs.melissa.com/on-premise-api/global-address-object/global-address-object-quickstart.html
 *   Release notes : https://releasenotes.melissa.com/on-premise-api/global-address-object/
 *   Result codes  : https://docs.melissa.com/on-premise-api/global-address-object/result-codes.html
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <list>

#include "mdGlobalAddr.h"
#include "GlobalAddressObject.h"
#include "DataContainer.h"

using namespace std;

// function declarations
void ParseArguments(string& license, string& testAddressLine1, string& testAddressLine2, string& testAddressLine3, string& testLocality, string& testAdminArea, string& testPostalCode, string& testCountry, string& dataPath, int argc, char* argv[]);
void RunAsConsole(string license, string testAddressLine1, string testAddressLine2, string testAddressLine3, string testLocality, string testAdminArea, string testPostalCode, string testCountry, string dataPath);
list<string> SplitResultCodes(string s, string delimiter);

/**
 * Entry point. Reads the optional command-line arguments, then hands control to
 * RunAsConsole, which performs the actual Global Address Object setup and processing.
 *
 * @param argc The count of command-line arguments.
 * @param argv The raw command-line arguments.
 */
int main(int argc, char* argv[])
{
    // variables
    string testAddressLine1 = "";
    string testAddressLine2 = "";
    string testAddressLine3 = "";
    string testLocality = "";
    string testAdminArea = "";
    string testCountry = "";
    string testPostalCode = "";
    string license = "";
    string dataPath = "";

    ParseArguments(license, testAddressLine1, testAddressLine2, testAddressLine3, testLocality, testAdminArea, testPostalCode, testCountry, dataPath, argc, argv);
    RunAsConsole(license, testAddressLine1, testAddressLine2, testAddressLine3, testLocality, testAdminArea, testPostalCode, testCountry, dataPath);

    return 0;
}

/**
 * Reads the supported command-line options into the reference parameters.
 *
 * Recognized flags (each followed by its value):
 *   --license / -l            : the Melissa license string
 *   --addressLine1            : street address line 1
 *   --addressLine2            : street address line 2
 *   --addressLine3            : street address line 3
 *   --locality                : locality (city)
 *   --administrativeArea      : administrative area (state/province)
 *   --postalCode              : postal code
 *   --country                 : country
 *   --dataPath / -d           : path to the Global Address Object data files
 *
 * @param license          Receives the Melissa license string.
 * @param testAddressLine1 Receives street address line 1 to test in one-shot mode.
 * @param testAddressLine2 Receives street address line 2 to test in one-shot mode.
 * @param testAddressLine3 Receives street address line 3 to test in one-shot mode.
 * @param testLocality     Receives the locality to test in one-shot mode.
 * @param testAdminArea    Receives the administrative area to test in one-shot mode.
 * @param testPostalCode   Receives the postal code to test in one-shot mode.
 * @param testCountry      Receives the country to test in one-shot mode.
 * @param dataPath         Receives the path to the Global Address Object data files.
 * @param argc             The count of command-line arguments to parse.
 * @param argv             The raw command-line arguments to parse.
 */
void ParseArguments(string& license, string& testAddressLine1, string& testAddressLine2, string& testAddressLine3, string& testLocality, string& testAdminArea, string& testPostalCode, string& testCountry, string& dataPath, int argc, char* argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "--addressLine1")
        {
            if (argv[i + 1] != NULL)
            {
                testAddressLine1 = argv[i + 1];
            }
        }
        if (string(argv[i]) == "--addressLine2")
        {
            if (argv[i + 1] != NULL)
            {
                testAddressLine2 = argv[i + 1];
            }
        }
        if (string(argv[i]) == "--addressLine3")
        {
            if (argv[i + 1] != NULL)
            {
                testAddressLine3 = argv[i + 1];
            }
        }
        if (string(argv[i]) == "--locality")
        {
            if (argv[i + 1] != NULL)
            {
                testLocality = argv[i + 1];
            }
        }
        if (string(argv[i]) == "--administrativeArea")
        {
            if (argv[i + 1] != NULL)
            {
                testAdminArea = argv[i + 1];
            }
        }
        if (string(argv[i]) == "--postalCode")
        {
            if (argv[i + 1] != NULL)
            {
                testPostalCode = argv[i + 1];
            }
        }
        if (string(argv[i]) == "--country")
        {
            if (argv[i + 1] != NULL)
            {
                testCountry = argv[i + 1];
            }
        }
        if (string(argv[i]) == "--license" || string(argv[i]) == "-l")
        {
            if (argv[i + 1] != NULL)
            {
                license = argv[i + 1];
            }
        }
        if (string(argv[i]) == "--dataPath" || string(argv[i]) == "-d")
        {
            if (argv[i + 1] != NULL)
            {
                dataPath = argv[i + 1];
            }
        }
    }
}

/**
 * Sets up the Global Address Object once, then drives the input -> process -> output cycle.
 *
 * In interactive mode (no address args) it loops, prompting for each field until the
 * user answers "N". In one-shot mode (address args supplied) it runs a single pass and exits.
 *
 * @param license          The Melissa license string used to initialize the object.
 * @param testAddressLine1 Street address line 1 to process in one-shot mode; if empty, the program prompts interactively.
 * @param testAddressLine2 Street address line 2 to process in one-shot mode.
 * @param testAddressLine3 Street address line 3 to process in one-shot mode.
 * @param testLocality     Locality to process in one-shot mode.
 * @param testAdminArea    Administrative area to process in one-shot mode.
 * @param testPostalCode   Postal code to process in one-shot mode.
 * @param testCountry      Country to process in one-shot mode.
 * @param dataPath         Path to the Global Address Object data files.
 */
void RunAsConsole(string license, string testAddressLine1, string testAddressLine2, string testAddressLine3, string testLocality, string testAdminArea, string testPostalCode, string testCountry, string dataPath)
{
    cout << "\n\n=========== WELCOME TO MELISSA GLOBAL ADDRESS OBJECT LINUX C++ ============\n" << endl;

    // Construct the wrapper. This is where the object is licensed, pointed at the
    // data files, and initialized (see the GlobalAddressObject constructor below).
    GlobalAddressObject* globalAddressObject = new GlobalAddressObject(license, dataPath);

    bool shouldContinueRunning = true;

    while (shouldContinueRunning)
    {
        // Holder for this pass's input and result codes.
        DataContainer dataContainer = DataContainer();

        if (testAddressLine1.empty() && testAddressLine2.empty() && testAddressLine3.empty() && testLocality.empty() && testAdminArea.empty() && testPostalCode.empty() && testCountry.empty())
        {
            // Interactive mode: prompt the user for each address field.
            cout << "\nFill in each value to see the Global Address Object results" << endl;

            cout << "Address Line 1: ";
            getline(cin, dataContainer.AddressLine1);

            cout << "Address Line 2: ";
            getline(cin, dataContainer.AddressLine2);

            cout << "Address Line 3: ";
            getline(cin, dataContainer.AddressLine3);

            cout << "Locality: ";
            getline(cin, dataContainer.Locality);

            cout << "Administrative Area: ";
            getline(cin, dataContainer.AdministrativeArea);

            cout << "Postal Code: ";
            getline(cin, dataContainer.PostalCode);

            cout << "Country: ";
            getline(cin, dataContainer.Country);
        }
        else
        {
            // One-shot mode: use the address fields passed on the command line.
            dataContainer.AddressLine1 = testAddressLine1;
            dataContainer.AddressLine2 = testAddressLine2;
            dataContainer.AddressLine3 = testAddressLine3;
            dataContainer.Locality = testLocality;
            dataContainer.AdministrativeArea = testAdminArea;
            dataContainer.PostalCode = testPostalCode;
            dataContainer.Country = testCountry;
        }

        // Print user input
        cout << "\n================================= INPUTS ==================================\n" << endl;
        cout << "                  Address Line 1: " + string(dataContainer.AddressLine1) << endl;
        cout << "                  Address Line 2: " + string(dataContainer.AddressLine2) << endl;
        cout << "                  Address Line 3: " + string(dataContainer.AddressLine3) << endl;
        cout << "                        Locality: " + string(dataContainer.Locality) << endl;
        cout << "             Administrative Area: " + string(dataContainer.AdministrativeArea) << endl;
        cout << "                     Postal Code: " + string(dataContainer.PostalCode) << endl;
        cout << "                         Country: " + string(dataContainer.Country) << endl;

        // Execute Global Address Object
        // Runs the verify sequence; results are then read via GetOutputParameter below.
        globalAddressObject->ExecuteObjectAndResultCodes(dataContainer);

        // Print output
        // Each GetOutputParameter("...") below returns one field the object produced for
        // the most recently processed address. These read directly from the mdGlobalAddr
        // instance, which still holds the results from the Execute call above.
        cout << "\n================================= OUTPUT ==================================\n" << endl;
        cout << "\n\tAddress Object Information:" << endl;
        cout << "\t                MAK: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("MAK")) << endl;
        cout << "\t            Company: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("Organization")) << endl;
        cout << "\t     Address Line 1: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("addressline1")) << endl;
        cout << "\t     Address Line 2: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("addressline2")) << endl;
        cout << "\t     Address Line 3: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("addressline3")) << endl;
        cout << "\t     Address Line 4: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("addressline4")) << endl;
        cout << "\t     Address Line 5: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("addressline5")) << endl;
        cout << "\t           Locality: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("locality")) << endl;
        cout << "\tAdministrative Area: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("administrativeArea")) << endl;
        cout << "\t        Postal Code: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("postalCode")) << endl;
        cout << "\t            Postbox: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("postBox")) << endl;
        cout << "\t            Country: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("countryName")) << endl;
        cout << "\t      Country ISO 2: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("iso2Code")) << endl;
        cout << "\t      Country ISO 3: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("iso3Code")) << endl;
        cout << "\t           Latitude: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("latitude")) << endl;
        cout << "\t          Longitude: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("longitude")) << endl;
        cout << "\t  Formatted Address: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("formattedAddress")) << endl;
        cout << "\t       Result Codes: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("resultCodes")) << endl;

        // Unlike the other objects, Global Address returns its result codes through
        // GetOutputParameter("resultCodes") (printed above) rather than GetResults(), so
        // there is no per-code description loop to run here.

        bool isValid = false;

        // In one-shot mode there is nothing more to do after a single pass: mark the
        // input handled and stop the outer loop.
        if (!(testAddressLine1 + testAddressLine2 + testAddressLine3 + testLocality + testAdminArea + testPostalCode + testCountry).empty())
        {
            isValid = true;
            shouldContinueRunning = false;
        }

        // Interactive mode: ask whether to process another address. Keep prompting until
        // we get a valid Y/N. "N" ends the program; "Y" falls through to another pass.
        while (!isValid)
        {
            string testAnotherResponse;

            cout << "\nTest another address? (Y/N)" << endl;
            getline(cin, testAnotherResponse);

            if (!testAnotherResponse.empty())
            {
                if (testAnotherResponse == "y" || testAnotherResponse == "Y")
                {
                    isValid = true;
                }
                else if (testAnotherResponse == "n" || testAnotherResponse == "N")
                {
                    isValid = true;
                    shouldContinueRunning = false;
                }
                else
                {
                    cout << "Invalid Response, please respond 'Y' or 'N'" << endl;
                }
            }
        }
    }
    cout << "\n================= THANK YOU FOR USING MELISSA C++ OBJECT ==================\n" << endl;
}

/**
 * Splits the comma-separated result-code string into individual codes.
 *
 * @param s         The result-code string (e.g. "AC01,AV25").
 * @param delimiter The delimiter string to split on.
 * @return A list holding each individual result code.
 */
list<string> SplitResultCodes(string s, string delimiter) {
    list<string> resultCodes;

    size_t pos = 0;
    string token;

    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        resultCodes.push_back(token);
        s.erase(0, pos + delimiter.length());
    }

    // push back the last resultCode
    resultCodes.push_back(s);

    return resultCodes;
}