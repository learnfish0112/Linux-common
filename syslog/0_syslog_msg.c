#include "linux_common/common.h"

int main()
{
    int count = 100;
    while(count--) {
        syslog(LOG_CRIT, "<%s>, hi, syslog", __FILE__);
    }
    sleep(1000);
    return 0;
}

