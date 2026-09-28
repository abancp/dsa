#include <stdio.h>
#include <string.h>

#define PPM 30
#define MAXJ 50
#define TARGET "PCCSL307 Lab cycle.pdf"

typedef struct {
    char teacher[50];
    char doc[100];
    int pages;
    double arrival, start, finish, wait;
} Job;

void sortJobs(Job j[], int n) {
    for (int i = 1; i < n; i++) {
        Job key = j[i];
        int k = i - 1;
        while (k >= 0 && j[k].arrival > key.arrival) {
            j[k + 1] = j[k];
            k--;
        }
        j[k + 1] = key;
    }
}

void schedule(Job j[], int n) {
    double clock = 0;
    for (int i = 0; i < n; i++) {
        j[i].start = j[i].arrival > clock ? j[i].arrival : clock;
        j[i].finish = j[i].start + (double)j[i].pages / PPM;
        j[i].wait = j[i].start - j[i].arrival;
        clock = j[i].finish;
    }
}

int currentJob(Job j[], int n, double t) {
    for (int i = 0; i < n; i++)
        if (j[i].start <= t && t < j[i].finish) return i;
    return -1;
}

int findDoc(Job j[], int n, const char *name) {
    for (int i = 0; i < n; i++)
        if (strcmp(j[i].doc, name) == 0) return i;
    return -1;
}

int maxWait(Job j[], int n) {
    int m = 0;
    for (int i = 1; i < n; i++)
        if (j[i].wait > j[m].wait) m = i;
    return m;
}

int main(void) {
    Job jobs[MAXJ];
    int n, choice, i;
    double t;

    printf("Number of documents: ");
    scanf("%d", &n);
    printf("Enter: teacher,document,pages,arrival_minutes\n");
    for (i = 0; i < n; i++)
        scanf(" %49[^,],%99[^,],%d,%lf", jobs[i].teacher, jobs[i].doc,
              &jobs[i].pages, &jobs[i].arrival);

    sortJobs(jobs, n);
    schedule(jobs, n);

    do {
        printf("\n1. Current printing teacher\n");
        printf("2. Waiting time for %s\n", TARGET);
        printf("3. Teacher with maximum waiting time\n");
        printf("4. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Time (minutes): ");
            scanf("%lf", &t);
            i = currentJob(jobs, n, t);
            if (i < 0) printf("Printer idle\n");
            else printf("Printing: %s (%s)\n", jobs[i].teacher, jobs[i].doc);
        } else if (choice == 2) {
            i = findDoc(jobs, n, TARGET);
            if (i < 0) printf("Document not found\n");
            else printf("Waiting time: %.2f min (%.0f sec)\n", jobs[i].wait, jobs[i].wait * 60);
        } else if (choice == 3) {
            i = maxWait(jobs, n);
            printf("%s waits the most: %.2f min\n", jobs[i].teacher, jobs[i].wait);
        }
    } while (choice != 4);

    return 0;
}
