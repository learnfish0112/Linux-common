#include "linux_common/common.h"

#define NAME_MAX 1024
#define BUF_LEN ((sizeof(struct inotify_event) + NAME_MAX + 1))
#define TEST_FILE_PATH "./2.txt"

static void /* Display information from inotify_event structure */
displayInotifyEvent(const struct inotify_event *i)
{
    printf(" wd =%2d; ", i->wd);
    printf("mask = ");
    if (i->mask & IN_ACCESS) printf("IN_ACCESS ");
    if (i->mask & IN_ATTRIB) printf("IN_ATTRIB ");
    if (i->mask & IN_CLOSE_NOWRITE) printf("IN_CLOSE_NOWRITE ");
    if (i->mask & IN_CLOSE_WRITE) printf("IN_CLOSE_WRITE ");
    if (i->mask & IN_CREATE) printf("IN_CREATE ");
    if (i->mask & IN_DELETE) printf("IN_DELETE ");
    if (i->mask & IN_DELETE_SELF) printf("IN_DELETE_SELF ");
    if (i->mask & IN_IGNORED) printf("IN_IGNORED ");
    if (i->mask & IN_ISDIR) printf("IN_ISDIR ");
    if (i->mask & IN_MODIFY) printf("IN_MODIFY ");
    if (i->mask & IN_MOVE_SELF) printf("IN_MOVE_SELF ");
    if (i->mask & IN_MOVED_FROM) printf("IN_MOVED_FROM ");
    if (i->mask & IN_MOVED_TO) printf("IN_MOVED_TO ");
    if (i->mask & IN_OPEN) printf("IN_OPEN ");
    if (i->mask & IN_Q_OVERFLOW) printf("IN_Q_OVERFLOW ");
    if (i->mask & IN_UNMOUNT) printf("IN_UNMOUNT ");
    printf("\n");

    //monitor dir, dir's file change case
    if (i->len > 0) {
        printf(" name = %s\n", i->name);
    }
}

int main()
{
    //target: can monitor one file content change
    int inotify_fd = inotify_init();
    if(inotify_fd == -1) {
        perror("Inotify init fail");
        exit(1);
    }
    int inotify_wd = inotify_add_watch(inotify_fd, TEST_FILE_PATH, IN_CREATE | IN_MODIFY);
    if(inotify_wd == -1) {
        perror("Inotify_add_watch fail");
        exit(1);
    }
    char buf[BUF_LEN];
    bzero(buf, sizeof(buf));

    printf("monitor start\n");
    int readNum = read(inotify_fd, buf, sizeof(buf));
    if(readNum == 0) {
        printf("what happened lead read 0?\n");
    } else if(readNum == -1) {
        perror("read failed");
        exit(1);
    } else {
        printf("readNum = %d\n", readNum);
        struct inotify_event *event;
        event = (inotify_event *)buf;
        displayInotifyEvent(event);

        if(event && IN_MODIFY) {
            char file_content[1024];
            bzero(file_content, sizeof(file_content));
            FILE* fp = fopen(TEST_FILE_PATH, "r");
            ERROR_CHECK(fp, NULL, "fopen failed");
            
            size_t sz = fread(file_content, 1, sizeof(file_content), fp);
            printf("sz = %ld, file_content:%s\n", sz, file_content);
            fclose(fp);
        }
    }

    return 0;
}

