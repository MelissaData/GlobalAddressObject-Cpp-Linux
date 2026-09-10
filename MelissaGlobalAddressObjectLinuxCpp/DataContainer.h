#include<iostream>

using namespace std;

#ifndef DATACONTAINER_H
#define DATACONTAINER_H

/**
 * Holds one record's input address fields, plus a small pre-processing filter
 * (FilterRequest) the wrapper calls before sending the data to the object.
 */
class DataContainer
{
public:
    // Input: the address fields collected from the user / CLI.
    string AddressLine1;
    string AddressLine2;
    string AddressLine3;
    string Locality;
    string AdministrativeArea;
    string PostalCode;
    string Country;

    // Output: comma-separated result codes (this sample reads them via GetOutputParameter).
    string ResultCodes;

    DataContainer() {};

    /**
     * Drops an address line that merely repeats the locality / administrative area /
     * postal code (an "area stack"), so those values are not sent to the object twice.
     */
    void FilterRequest()
    {
    if (CheckAreaStack(AddressLine3))
    {
        AddressLine3 = "";
    }
    else if (CheckAreaStack(AddressLine2))
    {
        AddressLine2 = "";
        AddressLine3 = "";
    }
    };

    /**
     * Returns true when the given address line contains the locality, administrative
     * area, and postal code all at once - i.e. it is a redundant "area stack" line.
     */
    bool CheckAreaStack(string addressLine)
    {
    bool localityCheck = false;
    bool adminAreaCheck = false;
    bool postalCheck = false;

    if (!Locality.empty() && addressLine.find(Locality) != string::npos)
    {
        localityCheck = true;
    }
    if (!AdministrativeArea.empty() && addressLine.find(AdministrativeArea) != string::npos)
    {
        adminAreaCheck = true;
    }
    if (!PostalCode.empty() && addressLine.find(PostalCode) != string::npos)
    {
        postalCheck = true;
    }

    return localityCheck && adminAreaCheck && postalCheck;
    };
};

#endif