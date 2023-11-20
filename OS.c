    1)  ,14)       
Write a program to implement an address book with options given below: a) Create address book. b) View address book. c) Insert a record. d) Delete a record. e) Modify a record. f) Exit

opt=1
while [ "$opt" -lt 6 ]
do
	echo -e "Choose one of the Following\n1. Create a New Address Book\n2. View Records\n3. Insert new Record\n4. Delete a Record\n5. Modify a Record\n6. Exit"
	# echo -e, enables special features of echo to use \n \t \b etc.
	read opt
	case $opt in
	1)
		echo "Enter filename"
		read fileName
		if [ -e $fileName ] ; then	# -e to check if file exists, if exits remove the file
			rm $fileName
		fi
		cont=1
		echo  "NAME\tNUMBER\t\tADDRESS\n===============================\n" | cat >> $fileName
		while [ "$cont" -gt 0 ]
		do
			echo "\nEnter Name"
			read name
			echo "\nEnter Phone Number of $name"
			read number
			echo "\nEnter Address of $name"
			read address
			echo "$name\t$number\t$address" | cat >> $fileName
			echo "Enter 0 to Stop, 1 to Enter next"
			read cont
		done
		;;
	2)
		cat $fileName
		;;
	3)
		echo "\nEnter Name"
		read name
		echo "\nEnter Phone Number of $name"
		read number
		echo "\nEnter Address of $name"
		read address
		echo "$name\t$number\t$address" | cat >> $fileName
		;;
	4)
		echo "Delete record\nEnter Name/Phone Number"
		read pattern
		temp="temp"
		grep -v $pattern $fileName | cat >> $temp 
		rm $fileName
		cat $temp | cat >> $fileName
		rm $temp
		;;
	5)
		echo "Modify record\nEnter Name/Phone Number"
		read pattern
		temp="temp"
		grep -v $pattern $fileName | cat >> $temp
		rm $fileName
		cat $temp | cat >> $fileName
		rm $temp
		echo "Enter Name"
		read name
		echo "Enter Phone Number of $name"
		read number
		echo "Enter Address of $name"
		read address
		echo -e "$name\t$number\t$address" | cat >> $fileName
		;;
	esac
done




2) ,15) 
Process control system calls: The demonstration of FORK, EXECVE and WAIT system calls along with zombie and orphan states
Implement the C program in which main program accepts the integers to be sorted. Main program uses the FORK system call to create a new process called a child process. Parent process sorts the integers using sorting algorithm and waits for child process using WAIT system call to sort the integers using any sorting algorithm. Also demonstrate zombie and orphan states.



#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void bubblesort()5
{
int i,j,a[50],n,temp;
printf("\nBubble sort\n");
printf("Enter size of array\t");
scanf("%d",&n);
for(i=0;i<n;i++)
{
scanf("%d",&a[i]);
}
for(i=0;i<n;i++)
{
for(j=i+1;j<n;j++)
{
if(a[i]>a[j])
{
int temp;
temp=a[i];
a[i]=a[j];
a[j]=temp;
}
}
}
printf("\nSorted array is\t");
for(i=0;i<n;i++)
{
printf("%d\t",a[i]);
}  
}
void selectionsort()
{
int i,j,a[50],n,min;
printf("Selection sort\n");
printf("\nEnter size of array\t");
scanf("%d",&n);
for(i=0;i<n;i++)
{
scanf("%d",&a[i]);
}
 for (i = 0; i < n-1; i++)
 { 
 min= i;
 for (j = i+1; j < n; j++)
 if (a[j] < a[min])
 min= j;
if(i<min)
{
int temp;
temp=a[min];
a[min]=a[i];
a[i]=temp;
}
}
printf("\nSorted array is\t");
for(i=0;i<n;i++)
{
printf("%d\t",a[i]);
}
}

int main()
{
pid_t pid;
pid=fork();

if(fork()==0)
{
bubblesort();
}
else
{
wait(NULL);
selectionsort();
}
return 0;
}


Orphan Program Code:
#include <stdio.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{ 
 int pid;
 pid=getpid(); 
 printf("Current Process ID is : %d\n",pid); 
 printf("\n[Forking Child Process ... ] \n"); 
 pid=fork(); /* This will Create Child Process and Returns   Child's PID */
 if(pid < 0) 
 {    
  printf("\nProcess can not be created ");
 } 
 else
 {
  if(pid==0)
  { /* Child Process */
   printf("\nChild Process is Sleeping ..."); 
   sleep(5); /*Orphan Child's Parent ID is 1 */
   printf("\nOrphan Child's Parent ID : %d",getppid()); 
  }
  else
  { /* Parent Process */
   printf("\nParent Process Completed ..."); 
  } 
 }
 return 0; 
}



Zombie Program Code:
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
int pid;
printf("Current Process ID is: %d\n", pid);
printf("[Forking Child Process ... ]\n");
pid=fork();

if(pid < 0)
	{
		printf("Process can not br cretaed");
 	}
if(pid > 0)
	{
		printf("Parent Process is Sleeping ...");
		sleep(5);
		printf("\nID : %d", getppid());
 	}
else
	{
		exit(0);
	}
return 0;
}


3) ,16)
Process control system calls: The demonstration of FORK, EXECVE and WAIT system calls along with zombie and orphan states
Implement the C program in which main program accepts an array. Main program uses the FORK system call to create a new process called a child process. Parent process sorts an array and passes the sorted array to child process through the command line arguments of EXECVE system call. The child process uses EXECVE system call to load new program which display array in reverse order

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void bass(int arr[], int n)
{
    int i, j, temp;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("\nAscending Sorting\n");
    for (i = 0; i < n; i++)
        printf("\t%d", arr[i]);
}


void bdsc(int arr[], int n)
{
    int i, j, temp;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - 1; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("\nDescending Sorting\n");
    for (i = 0; i < n; i++)
        printf("\t%d", arr[i]);
    printf("\n\n");
}

void forkeg()
{
    int arr[25], arr1[25], n, i, status;
    printf("\nEnter Size: -\n");
    scanf("%d", &n);
    printf("\nEnter Array: -\n");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    int pid = fork();
    if (pid == 0)
    {
        printf("\nChild Id = %d\n", getpid());
        bdsc(arr, n);
        printf("\nBubble Sorting\n");
        printf("\n");
        for (i = 0; i < n; i++)
            printf("\t%d", arr[i]);
        printf("\n");
    }
    else
    {
        sleep(10);
        printf("Parent Id = %d\n", getppid());
        bass(arr, n);
        printf("\nBubble Sort:\n");
        printf("\n");
        for (i = 0; i < n; i++)
            printf("%d", arr[i]);
        printf("\n");
        system("ps -x");
    }
}

int main()
{
    forkeg();
    return 0;
}



Orphan Program Code:
#include <stdio.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{ 
 int pid;
 pid=getpid(); 
 printf("Current Process ID is : %d\n",pid); 
 printf("\n[Forking Child Process ... ] \n"); 
 pid=fork(); /* This will Create Child Process and Returns   Child's PID */
 if(pid < 0) 
 {    
  printf("\nProcess can not be created ");
 } 
 else
 {
  if(pid==0)
  { /* Child Process */
   printf("\nChild Process is Sleeping ..."); 
   sleep(5); /*Orphan Child's Parent ID is 1 */
   printf("\nOrphan Child's Parent ID : %d",getppid()); 
  }
  else
  { /* Parent Process */
   printf("\nParent Process Completed ..."); 
  } 
 }
 return 0; 
}



4) ,17)

Implement the C program for CPU Scheduling Algorithms: Shortest Job First (Pre-emptive) and Round Robin with different arrival time.


SJF:
#include <stdio.h>
  int main() 
{
      int arrival_time[10], burst_time[10], temp[10];
      int i, smallest, count = 0, time, limit;
      double wait_time = 0, turnaround_time = 0, end;
      float average_waiting_time, average_turnaround_time;
      printf("Enter the Total Number of Processes:");
      scanf("%d", &limit); 
      printf("nEnter Details of %d Processesn", limit);
      for(i = 0; i < limit; i++)
      {
            printf("nEnter Arrival Time:t");
            scanf("%d", &arrival_time[i]);
            printf("Enter Burst Time:t");
            scanf("%d", &burst_time[i]); 
            temp[i] = burst_time[i];
      }
      burst_time[9] = 9999;  
      for(time = 0; count != limit; time++)
      {
            smallest = 9;
            for(i = 0; i < limit; i++)
            {
                  if(arrival_time[i] <= time && burst_time[i] < burst_time[smallest] && burst_time[i] > 0)
                  {
                        smallest = i;
                  }
            }
            burst_time[smallest]--;
            if(burst_time[smallest] == 0)
            {
                  count++;
                  end = time + 1;
                  wait_time = wait_time + end - arrival_time[smallest] - temp[smallest];
                  turnaround_time = turnaround_time + end - arrival_time[smallest];
            }
      }
      average_waiting_time = wait_time / limit; 
      average_turnaround_time = turnaround_time / limit;
      printf("nnAverage Waiting Time:t%lfn", average_waiting_time);
      printf("Average Turnaround Time:t%lfn", average_turnaround_time);
      return 0;
}

Round Robin :
#include<stdio.h>
 
int main()
{
 
  int cnt,j,n,t,remain,flag=0,tq;
  int wt=0,tat=0,at[10],bt[10],rt[10];
  printf("Enter Total Process:\t ");
  scanf("%d",&n);
  remain=n;
  for(cnt=0;cnt<n;cnt++)
  {
    printf("Enter Arrival Time and Burst Time for Process Process Number %d :",cnt+1);
    scanf("%d",&at[cnt]);
    scanf("%d",&bt[cnt]);
    rt[cnt]=bt[cnt];
  }
  printf("Enter Time Quantum:\t");
  scanf("%d",&tq);
  printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n");
  for(t=0,cnt=0;remain!=0;)
  {
    if(rt[cnt]<=tq && rt[cnt]>0)
    {
      t+=rt[cnt];
      rt[cnt]=0;
      flag=1;
    }
    else if(rt[cnt]>0)
    {
      rt[cnt]-=tq;
      t+=tq;
    }
    if(rt[cnt]==0 && flag==1)
    {
      remain--;
      printf("P%d]\t|\t%d\t|\t%d\n",cnt+1,t-at[cnt],t-at[cnt]-bt[cnt]);
      wt+=t-at[cnt]-bt[cnt];
      tat+=t-at[cnt];
      flag=0;
    }
    if(cnt==n-1)
      cnt=0;
    else if(at[cnt+1]<=t)
      cnt++;
    else
      cnt=0;
  }
  printf("\nAverage Waiting Time= %f\n",wt*1.0/n);
  printf("Avg Turnaround Time = %f",tat*1.0/n);
  
  return 0;
}


5)
Thread synchronization using counting semaphores. Application to demonstrate: producerconsumer problem with counting semaphores and mutex.

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
 
 #define MaxItems 5 
#define BufferSize 5
 
sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex;
 
void *producer(void *pno)
{   
    int item;
    for(int i = 0; i < MaxItems; i++) {
        item = rand(); // Produce an random item
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno),buffer[in],in);
        in = (in+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *cno)
{   
    for(int i = 0; i < MaxItems; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n",*((int *)cno),item, out);
        out = (out+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}
 
int main()
{   
 
    pthread_t pro[5],con[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,BufferSize);
    sem_init(&full,0,0);
 
    int a[5] = {1,2,3,4,5}; //Just used for numbering the producer and consumer
 
    for(int i = 0; i < 5; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }
    for(int i = 0; i < 5; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }
 
    for(int i = 0; i < 5; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(con[i], NULL);
    }
 
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
 
    return 0;
    
}

6)
Thread synchronization and mutual exclusion using mutex. Application to demonstrate: Reader-Writer problem with reader priority
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
 
sem_t wrt;
pthread_mutex_t mutex;
int cnt = 1;
 
int numreader = 0;
 
void *writer(void *wno)
{   
    sem_wait(&wrt);
    cnt = cnt*2;
    printf("Writer %d modified cnt to %d\n",(*((int *)wno)),cnt);
    sem_post(&wrt);
 
}
void *reader(void *rno)
{   
    // Reader acquire the lock before modifying numreader
    pthread_mutex_lock(&mutex);
    numreader++;
    if(numreader == 1) {
        sem_wait(&wrt); // If this id the first reader, then it will block the writer
    }
    pthread_mutex_unlock(&mutex);
    // Reading Section
    printf("Reader %d: read cnt as %d\n",*((int *)rno),cnt);
 
    // Reader acquire the lock before modifying numreader
    pthread_mutex_lock(&mutex);
    numreader--;
    if(numreader == 0) {
        sem_post(&wrt); // If this is the last reader, it will wake up the writer.
    }
    pthread_mutex_unlock(&mutex);
}
 
int main()
{   
 
    pthread_t read[10],write[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt,0,1);
 
    int a[10] = {1,2,3,4,5,6,7,8,9,10}; //Just used for numbering the producer and consumer
 
    for(int i = 0; i < 10; i++) {
        pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]);
    }
    for(int i = 0; i < 10; i++) {
        pthread_create(&write[i], NULL, (void *)writer, (void *)&a[i]);
    }
 
    for(int i = 0; i < 10; i++) {
        pthread_join(read[i], NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(write[i], NULL);
    }
 
    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);
 
    return 0;
    
}

7)
Implement the C program for Deadlock Avoidance Algorithm: Bankers Algorithm.

#include<stdio.h>
 int main() {
 

  int p, c, count = 0, i, j, alc[5][3], max[5][3], need[5][3], safe[5], available[3], done[5], terminate = 0;
  printf("Enter the number of process and resources");
  scanf("%d %d", & p, & c);
 
  printf("enter allocation of resource of all process %dx%d matrix", p, c);
  for (i = 0; i < p; i++) {
    for (j = 0; j < c; j++) {
      scanf("%d", & alc[i][j]);
    }
  }
  printf("enter the max resource process required %dx%d matrix", p, c);
  for (i = 0; i < p; i++) {
    for (j = 0; j < c; j++) {
      scanf("%d", & max[i][j]);
    }
  }
  printf("enter the  available resource");
  for (i = 0; i < c; i++)
   scanf("%d", & available[i]);
  printf("\n need resources matrix are\n");
   for (i = 0; i < p; i++) 
{
    for (j = 0; j < c; j++) 
  {
     need[i][j] = max[i][j] - alc[i][j];
      printf("%d\t", need[i][j]);
    }
    printf("\n");
  }
  
  for (i = 0; i < p; i++) {
    done[i] = 0;
  }
  while (count < p) {
    for (i = 0; i < p; i++) {
      if (done[i] == 0) {
        for (j = 0; j < c; j++) {
          if (need[i][j] > available[j])
            break;
         }

        if (j == c) {
          safe[count] = i;
          done[i] = 1;
          
          for (j = 0; j < c; j++) {
            available[j] += alc[i][j];
          }
          count++;
          terminate = 0;
        } else {
          terminate++;
        }
      }
    }
    if (terminate == (p - 1)) {
      printf("safe sequence does not exist");
      break;
    }
  }
  if (terminate != (p - 1)) {
    printf("\n available resource after completion\n");
    for (i = 0; i < c; i++) {
      printf("%d\t", available[i]);
    }
    printf("\n safe sequence are\n");
    for (i = 0; i < p; i++) {
      printf("p%d\t", safe[i]);
    }
  }
  return 0;
 }
8)

Implement the C program for Page Replacement Algorithms: FCFS, LRU

FCFS:
#include<stdio.h>
int main()
{
int i,j,n,a[50],frame[10],no,k,avail,count=0;
            printf("\n ENTER THE NUMBER OF PAGES:\n");
scanf("%d",&n);
            printf("\n ENTER THE PAGE NUMBER :\n");
            for(i=1;i<=n;i++)
            scanf("%d",&a[i]);
            printf("\n ENTER THE NUMBER OF FRAMES :");
            scanf("%d",&no);
for(i=0;i<no;i++)
            frame[i]= -1;
                        j=0;
                        printf("\tref string\t page frames\n");
for(i=1;i<=n;i++)
                        {
                                    printf("%d\t\t",a[i]);
                                    avail=0;
                                    for(k=0;k<no;k++)
if(frame[k]==a[i])
                                                avail=1;
                                    if (avail==0)
                                    {
                                                frame[j]=a[i];
                                                j=(j+1)%no;
                                                count++;
                                                for(k=0;k<no;k++)
                                                printf("%d\t",frame[k]);
}
                                    printf("\n");
}
                        printf("Page Fault Is %d",count);
                        return 0;
}

LRU :

#include<stdio.h>
 int findLRU(int time[], int n){
int i, minimum = time[0], pos = 0;
for(i = 1; i < n; ++i){
if(time[i] < minimum){
minimum = time[i];
pos = i;
}
}
return pos;
}
 int main()
{
    int no_of_frames, no_of_pages, frames[10], pages[30], counter = 0, time[10], flag1, flag2, i, j, pos, faults = 0;
printf("Enter number of frames: ");
scanf("%d", &no_of_frames);
printf("Enter number of pages: ");
scanf("%d", &no_of_pages);
printf("Enter reference string: ");
    for(i = 0; i < no_of_pages; ++i){
     scanf("%d", &pages[i]);
    }
    for(i = 0; i < no_of_frames; ++i){
     frames[i] = -1;
    }
      for(i = 0; i < no_of_pages; ++i){
     flag1 = flag2 = 0;
    
     for(j = 0; j < no_of_frames; ++j){
     if(frames[j] == pages[i]){
     counter++;
     time[j] = counter;
   flag1 = flag2 = 1;
   break;
   }
     }
    
     if(flag1 == 0){
for(j = 0; j < no_of_frames; ++j){
     if(frames[j] == -1){
     counter++;
     faults++;
     frames[j] = pages[i];
     time[j] = counter;
     flag2 = 1;
     break;
     }
     }
     }
    
     if(flag2 == 0){
     pos = findLRU(time, no_of_frames);
     counter++;
     faults++;
     frames[pos] = pages[i];
     time[pos] = counter;
     }
    
     printf("\n");
    
     for(j = 0; j < no_of_frames; ++j){
     printf("%d\t", frames[j]);
     }
}
printf("\n\nTotal Page Faults = %d", faults);
       return 0;
}


9)
Inter process communication in Linux using following.
FIFOS: Full duplex communication between two independent processes. First process accepts sentences and writes on one pipe to be read by second process and second process counts number of characters, number of words and number of lines in accepted sentences, writes this output in a text file and writes the contents of the file on second pipe to be read by first process and displays on standard output.


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>


#define MAX_BUF 1024

int main()
{
    int fd,c=0;
    char * myfifo1="myfifo1";
    int fd1;
    char * myfifo2="myfifo2";
    
    char buf1[MAX_BUF];
    //printf("\nlets start"); //for checking
    // create fifo
    
    mkfifo(myfifo1,0777);//(for creating fifo,prmision to user 0777)
     printf("\nEnter the Sentence : \n");
    fd=open(myfifo1,O_WRONLY);
    
    char str;
   
    while((str=getchar())!='#')
   
        buf1[c++]=str;
	buf1[c]='\0';
	
	write(fd,buf1,sizeof(buf1)); //write input to buffer
	close(fd);
	
	fd1=open(myfifo2,O_RDONLY);
	read(fd1,&buf1,sizeof(buf1));
       
        printf("\nThe contents of the file are as follows : %s\n ",buf1);
	
	  close(fd1);
	   
	       unlink(myfifo2);
	       return (0);

    
}
11)
Implement the C program for Disk Scheduling Algorithms: SSTF considering the initial head position moving away from the spindle


#include<stdio.h>
#include<stdlib.h>
int main()
{
    int RQ[100],i,n,TotalHeadMoment=0,initial,count=0;
    printf("Enter the number of Requests\n");
    scanf("%d",&n);
    printf("Enter the Requests sequence\n");
    for(i=0;i<n;i++)
     scanf("%d",&RQ[i]);
    printf("Enter initial head position\n");
    scanf("%d",&initial);
    
    // logic for sstf disk scheduling
    
        /* loop will execute until all process is completed*/
    while(count!=n)
    {
        int min=1000,d,index;
        for(i=0;i<n;i++)
        {
           d=abs(RQ[i]-initial);
           if(min>d)
           {
               min=d;
               index=i;
           }
           
        }
        TotalHeadMoment=TotalHeadMoment+min;
        initial=RQ[index];
        // 1000 is for max
        // you can use any number
        RQ[index]=1000;
        count++;
    }
    
    printf("Total head movement is %d",TotalHeadMoment);
    return 0;
}


        12)
Implement the C program for Disk Scheduling Algorithms: SCAN considering the initial head position moving away from the spindle



#include<stdio.h> 
int main() 
{ 
 int i,j,sum=0,n; 
 int d[20]; 
 int disk;  //loc of head 
 int temp,max;   
 int dloc;  //loc of disk in array 
 
 printf("enter number of location\t"); 
 scanf("%d",&n); 
 printf("enter position of head\t"); 
 scanf("%d",&disk); 
 printf("enter elements of disk queue\n"); 
 for(i=0;i<n;i++) 
 { 
 scanf("%d",&d[i]); 
 } 
 d[n]=disk; 
 n=n+1; 
 for(i=0;i<n;i++)  // sorting disk locations 
 { 
 for(j=i;j<n;j++) 
 { 
 if(d[i]>d[j]) 
 { 
 temp=d[i]; 
 d[i]=d[j]; 
 d[j]=temp; 
 } 
 } 
 } 
 max=d[n]; 
 for(i=0;i<n;i++)  // to find loc of disc in array 
 { 
 if(disk==d[i]) { dloc=i; break;  } 
 } 
 for(i=dloc;i>=0;i--) 
 { 
 printf("%d -->",d[i]); 
 } 
 printf("0 -->"); 
 for(i=dloc+1;i<n;i++) 
 { 
 printf("%d-->",d[i]); 
 } 
 sum=disk+max; 
 printf("\nmovement of total cylinders %d",sum); 
  
 return 0; 
}




     13)
Implement the C program for Disk Scheduling Algorithms: SSTF, SCAN, C-Look considering the initial head position moving away from the spindle

C-look:
#include<stdio.h>
int request[50];
int SIZE;
int pre;
int head;
int uptrack;
int downtrack;
struct max{
int up;
int down;
}kate[50];
int dist(int a,int b)
{
if(a>b)
return a-b;
return b-a;
}
void sort(int n)
{
int i,j;
for (i = 0; i < n-1; i++)      
{     
for (j = 0; j < n-i-1; j++) 
{
if (request[j] > request[j+1])
{
int temp=request[j];
request[j]=request[j+1];
request[j+1]=temp;
}
}
}
j=0;
i=0;
while(request[i]!=head)
{
kate[j].down=request[i];
j++;
i++;
}
downtrack=j;
i++;
j=0;
while(i<n)
{
kate[j].up=request[i];
j++;
i++;
}
uptrack=j;
}
void look(int n)
{
int i;
int seekcount=0;
sort(n);
printf("SEEK SEQUENCE = ");
if(pre<head){
for(i=0;i<uptrack;i++)
{
printf(" %d",head);
seekcount=seekcount+dist(head,kate[i].up);
head=kate[i].up;
}
for(i=downtrack-1;i>=0;i--)
{
printf(" %d",head);
seekcount=seekcount+dist(head,kate[i].down);
head=kate[i].down;
}
}
else
{
for(i=downtrack-1;i>=0;i--)
{
printf(" %d",head);
seekcount=seekcount+dist(head,kate[i].down);
head=kate[i].down;
}
for(i=0;i<uptrack;i++)
{
printf(" %d",head);
seekcount=seekcount+dist(head,kate[i].up);
head=kate[i].up;
}   
}
printf(" %d\nTOTAL DISTANCE :%d",head,seekcount);   
}
int main()
{
int n,i;
printf("ENTER THE DISK SIZE :\n");
scanf("%d",&SIZE);
printf("ENTER THE NO OF REQUEST SEQUENCE :\n");
scanf("%d",&n);
printf("ENTER THE REQUEST SEQUENCE :\n");
for(i=0;i<n;i++)
scanf("%d",&request[i]);
printf("ENTER THE CURRENT HEAD :\n");
scanf("%d",&head);
request[n]=head;
printf("ENTER THE PRE REQUEST :\n");
scanf("%d",&pre);
look(n+1);  
}






