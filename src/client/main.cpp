#include "cli.h"
#include "../patchwork/patchwork.h"

int main(int argc, const char *argv[]) {

    initializePatchwork();

    startCli();

    terminatePatchwork();

    return 0;
}