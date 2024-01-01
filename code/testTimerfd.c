#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/timerfd.h>
#include <sys/epoll.h>

int main() {

    uint64_t expirations;
    // Create a timer file descriptor
    int timer_fd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (timer_fd == -1) {
        perror("timerfd_create");
        exit(EXIT_FAILURE);
    }

    // Set the timer to expire after 5 seconds
    struct itimerspec timer_spec;
    timer_spec.it_value.tv_sec = 5;
    timer_spec.it_value.tv_nsec = 0;
    timer_spec.it_interval.tv_sec = 5;  // Non-repeating timer
    timer_spec.it_interval.tv_nsec = 0;

    if (timerfd_settime(timer_fd, 0, &timer_spec, NULL) == -1) {
        perror("timerfd_settime");
        close(timer_fd);
        exit(EXIT_FAILURE);
    }

    // Use epoll to wait for events on the timer file descriptor
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        close(timer_fd);
        exit(EXIT_FAILURE);
    }

    struct epoll_event event;
    event.events = EPOLLIN ;  // EPOLLIN for read events (timer expiration)
    event.data.fd = timer_fd;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, timer_fd, &event) == -1) {
        perror("epoll_ctl");
        close(timer_fd);
        close(epoll_fd);
        exit(EXIT_FAILURE);
    }

    // Main event loop
    while (1) {
        struct epoll_event events[1];
        int nfds = epoll_wait(epoll_fd, events, 1, -1);

        if (nfds == -1) {
            perror("epoll_wait");
            break;
        }

        for (int i = 0; i < nfds; ++i) {
            if (events[i].events & EPOLLIN) {
                // Timer event occurred, handle accordingly
                if (read(timer_fd, &expirations, sizeof(expirations)) == -1) {
                    perror("read");
                    close(timer_fd);
                    close(epoll_fd);
                    exit(EXIT_FAILURE);
                }
                printf("Timer expired, %lu.\n", expirations);

            }
        }
    }

    // Cleanup
    close(timer_fd);
    close(epoll_fd);

    return 0;
}

