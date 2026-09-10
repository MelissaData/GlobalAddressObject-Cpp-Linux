#include<iostream>
#include <string>

#include "mdGlobalAddr.h"
#include "DataContainer.h"

using namespace std;

#ifndef GLOBALADDRESSOBJECT_H
#define GLOBALADDRESSOBJECT_H

/**
 * Wrapper that owns a single Melissa Global Address Object instance and encapsulates the
 * two things every Melissa object needs: one-time setup (license + data files) and the
 * per-record processing sequence. Reuse one instance across many addresses; do NOT
 * re-initialize per address.
 */
class GlobalAddressObject
{
public:
    // Path to the Global Address Object data files.
    string dataFilePath;

    // The underlying Melissa Global Address Object instance.
    mdGlobalAddr* mdGlobalAddressObj = new mdGlobalAddr;

    /**
     * Performs the mandatory one-time setup, in this required order:
     *   1. SetLicenseString         - authorize the object.
     *   2. SetPathToGlobalAddrFiles - tell it where the data files live.
     *   3. InitializeDataFiles      - load the data into memory.
     *
     * @param license  The Melissa license string used to authorize the object.
     * @param dataPath Path to the folder containing the Global Address Object data files.
     */
    GlobalAddressObject(string license, string dataPath);

    /**
     * Runs the full Global Address Object processing sequence for one address. This is the
     * canonical per-record call pattern to copy into your own application:
     *   ClearProperties -> FilterRequest -> SetInputParameter (per field) -> VerifyAddress
     * Results are read afterwards via GetOutputParameter (see RunAsConsole).
     *
     * @param data The record to process; its address fields are read as input.
     */
    void ExecuteObjectAndResultCodes(DataContainer& data);
};

#endif
