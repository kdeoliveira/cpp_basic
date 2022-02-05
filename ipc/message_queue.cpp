#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <cstring>
#include <mqueue.h>
#include <cstdlib>


#define BUFFER_SIZE 20

// Programs using the POSIX message queue API must be compiled with
// cc -lrt to link against the real-time library, librt.

struct message_buffer{
    long msg_type;
    char data[BUFFER_SIZE];
};

//Thread to be executed through notification
static void thread_func(union sigval sv){

    printf("thread_func executing ...\n");


    // struct mq_attr attr;
    // ssize_t rcv;

    // struct message_buffer* buffer_rcv;
    // mqd_t mqueue = *((mqd_t *) sv.sival_ptr);

    // if(mq_getattr(mqueue, &attr) < 0){
    //     perror("mq_getattr");
    //     return;
    // }


    // rcv = mq_receive(mqueue, (char *) buffer_rcv, attr.mq_msgsize, nullptr);

    // if(rcv < 0){
    //     perror("malloc");
    //     return;
    // }

    // printf("Read %zd bytes from mqueue\n", rcv);
    // printf("Message from mqueue: %s\n", buffer_rcv->data);
    
    // exit(EXIT_SUCCESS);
}


int main(){

    printf("Opening mqueue\n");    

    //attributes of the message queue
    //note that only those parameters can be modified
    struct mq_attr mqueue_attr;
    mqueue_attr.mq_maxmsg = 10;
    mqueue_attr.mq_msgsize = 1024;

    struct message_buffer msg;


    mqd_t mqueue;
    // /dev/mqueue/mqueue_name
    mqueue = mq_open("/message_queue_test", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR, &mqueue_attr);

    if(mqueue < 0){
        perror("mq_open");
        return 1;
    }

    pid_t pid = fork();

    if(pid < 0){
        perror("fork");
        return 1;
    }

    //Child process

    if(pid == 0){

        // //Notification mechanism for invoking threads
        // //Note thatOnly one process can be registered to receive notification from a message queue
        // printf("Setting up notify\n");
        // struct sigevent sev;
        // sev.sigev_notify = SIGEV_THREAD;
        // //function send to new thread
        // sev.sigev_notify_function = thread_func;
        // sev.sigev_notify_attributes = nullptr;
        // //args sent to thread_func
        // sev.sigev_value.sival_ptr = &mqueue;

        //  // Notify calling process (with invoke of thread) for new messages in empty queue then remove notification (only gets notified once)
        //  // Note that if the queue is not empty, no notification is send or if a mq_receive is waiting for a msg. Hence should be set before sending message to queue
        //  // In order to remove notification: mq_notify(mqueue, nullptr)
        // if(mq_notify(mqueue, &sev) < 0){
        //     perror("mq_notify");
        //     return 1;
        // }

    struct mq_attr attr;
    ssize_t rcv;

    struct message_buffer buffer_rcv;

    if(mq_getattr(mqueue, &attr) < 0){
        perror("mq_getattr");
        exit(EXIT_FAILURE);
    }

    // receives the next message in queue
    // mq_receive suspends process if queue if empty (for NONBLOCKING mq_queue fails)
    rcv = mq_receive(mqueue, (char *)&buffer_rcv, attr.mq_msgsize, nullptr);

    if(rcv < 0){
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    printf("Read %zd bytes from mqueue\n", rcv);
    printf("Message from mqueue: %s\n", buffer_rcv.data);



        _exit(EXIT_SUCCESS);

    }
    //Parent process
    else{


        printf("Writting data\n");
        // fgets(msg->data, BUFFER_SIZE, stdin);
        
        
        msg.msg_type = 1;


        printf("String to data: ");
        fflush(stdout);

        fgets(msg.data, BUFFER_SIZE, stdin);
        

        // memcpy(
        //     msg.data, "Kevin de Oliveira", sizeof(char)*18
        // );

        //sends message to mqueue descriptor at priority 5 (priority are set for messages inside the queue)
        // mq_send suspend current process if queue is full (for NONBLOCKING mq_send fails)
        if(mq_send(mqueue, ((const char*)&msg), sizeof(msg), 5) < 0){
            perror("mq_send");
            return 1;
        }

        printf("Message has been sent\n");
        _exit(EXIT_SUCCESS);
        
    }

    mq_unlink("/message_queue_test");

    return EXIT_SUCCESS;
}   


