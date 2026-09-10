#include "GlobalAddressObject.h"

GlobalAddressObject::GlobalAddressObject(string license, string dataPath)
{
    // Set license string and set path to data files
    mdGlobalAddressObj->SetLicenseString(license.c_str());
    dataFilePath = dataPath;

    // Tell the object where the data files live, then load them below.
    // If you see a different date than expected, check your license string and either download the new data files or use the Melissa Updater program to update your data files.  
    mdGlobalAddressObj->SetPathToGlobalAddrFiles(dataFilePath.c_str());

    // Load the data files. The returned ProgramStatus reports whether initialization succeeded.
    mdGlobalAddr::ProgramStatus pStatus = mdGlobalAddressObj->InitializeDataFiles();

    // If an issue occurred, please investigate the common causes.
    // Common causes: an invalid/expired license, or missing/wrong-path data files.
    if (pStatus != mdGlobalAddr::ProgramStatus::ErrorNone)
    {
    cout << "Failed to Initialize Object." << endl;
    cout << pStatus << endl;
    return;
    }

    // Diagnostic information, handy for confirming the object loaded the data you expect:

    // Build date of the data files
    cout << "                   DataBase Date: " + string(mdGlobalAddressObj->GetOutputParameter("databaseDate")) << endl;

    // When the license stops working
    cout << "                 Expiration Date: " + string(mdGlobalAddressObj->GetOutputParameter("databaseExpirationDate")) << endl;

    /**
        * This number should match with the file properties of the Melissa Object binary file.
        * If TEST appears with the build number, there may be a license key issue.
        */
    cout << "                  Object Version: " + string(mdGlobalAddressObj->GetOutputParameter("buildNumber")) << endl;
}

// Runs the verify sequence for the input address and leaves the results on the object for the caller to read via GetOutputParameter
void GlobalAddressObject::ExecuteObjectAndResultCodes(DataContainer& data)
{
    // Reset any state left over from a previous address so fields don't bleed across records.
    mdGlobalAddressObj->ClearProperties();

    // Drop any address line that just repeats locality/area/postal (see DataContainer).
    data.FilterRequest();  

    // Hand each input field to the object by its parameter name.
    mdGlobalAddressObj->SetInputParameter("inputAddressLine1", data.AddressLine1.c_str());
    mdGlobalAddressObj->SetInputParameter("inputAddressLine2", data.AddressLine2.c_str());
    mdGlobalAddressObj->SetInputParameter("inputAddressLine3", data.AddressLine3.c_str());
    mdGlobalAddressObj->SetInputParameter("inputLocality", data.Locality.c_str());
    mdGlobalAddressObj->SetInputParameter("inputAdministrativeArea", data.AdministrativeArea.c_str());
    mdGlobalAddressObj->SetInputParameter("inputPostalCode", data.PostalCode.c_str());
    mdGlobalAddressObj->SetInputParameter("inputCountry", data.Country.c_str());

    // Validate and standardize the address
    mdGlobalAddressObj->VerifyAddress();

    // ResultsCodes explain any issues Global Address Object has with the object.
    // List of result codes for Global Address Object
    // https://docs.melissa.com/on-premise-api/global-address-object/result-codes.html
}
