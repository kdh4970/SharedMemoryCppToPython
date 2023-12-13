// do - 2023.12.13
// The test code for data sharing between C++ process and Python process by using shared memory


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string> 
#include <unistd.h>
#include <string.h>
#include "SharedMemoryManager.hpp"


#define VERTEX_KEY 777
#define TRIANGLE_KEY 

using namespace std;

void GenSharedMemory(key_t key, size_t size)
{
  int m_shmid = shmget(key, size, IPC_CREAT | 0666);
  if (m_shmid < 0)
  {
    printf("Error : getting shared memory id");
    exit(1);
  }
  void* shmaddr = shmat(m_shmid, NULL, 0);
  if (shmaddr == (void *)-1)
  {
    printf("Error : attaching shared memory id");
    exit(1);
  }
  strcpy(static_cast<char*>(shmaddr), "Hello !");

}


int main(int argc,const char** argv)
{
  size_t size = 256;
  SharedMemoryWriter<float> man(777, size);
  float data[size];
  for (int i = 0; i < size; i++)
  {
    data[i] = i*0.01;
  }
  man.CopyToSharedMemory(data,size);
  return 0;
}