#include "CuTest_internal.h"

unsigned long int progressstart = 0;
unsigned long int progressend = 0;
unsigned long int progressrange = 0;

const char *progressFormatStr = "%3d%%";

int CuTestSetProgressStartEnd (unsigned long int st, unsigned long int en) {
    progressstart = st;
    progressend = en;
    progressrange = abs (en - st);

    return EXIT_SUCCESS;
}

unsigned long int CuTestGetProgressStart (void) {
    return progressstart;
};

unsigned long int CuTestGetProgressEnd (void) {
    return progressend;
};

unsigned long int CuTestGetProgressRange (void) {
    return progressrange;
};

void CuTestReservePrintPositions (void) {
    fputs ("    ", stdout);
}

/*int CuTestGetProgressState(unsigned long int current, unsigned long int interleave){
    return EXIT_SUCCESS;
}*/

int CuTestPrintProgressState (unsigned long int current, unsigned long int interleave) {
    int percent;
    static unsigned long int call = 0;


    if (0 != progressrange) {
        if (0 == call) {
            if (progressstart < progressend) {
                percent = 100 * (current - progressstart) / progressrange;
            }
            else {
                percent = 100 * (progressstart - current) / progressrange;
            }

            fputs ("\b\b\b\b", stdout);
            printf (progressFormatStr, percent);
            ++call;
            return EXIT_SUCCESS;
        }
        else {
            ++call;

            if (interleave == call) {
                call = 0;
            }
        }
    }

    return EXIT_FAILURE;
}
