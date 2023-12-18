// do - 2023.12.13
// The test code for data sharing between C++ process and Python process by using shared memory
#include <cstring>
#include <string>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <vector>
#include <unistd.h>


struct float3
{
  float x;
  float y;
  float z;
};

struct int3
{
  int x;
  int y;
  int z;
};

template <typename T>
class SharedMemoryManager
{
public:
  /**
 * @brief Construct a new Shared Memory Manager:: Shared Memory Manager object
 * 
 * @param key  The key of shared memory
 * @param size  The size of shared memory
 */
  SharedMemoryManager(key_t key, size_t size)
  {
    _key = key;
    _size = size;
    // Create Shared Memory
    _shmid = shmget(_key, _size, IPC_CREAT | 0666);
    if (_shmid < 0)
    {
      perror("Failed to get shared memory id");
      exit(1);
    }
    
    // Create Semaphore
    _semid = semget(_key, 1, IPC_CREAT | 0666);
    semctl(_semid, 0, SETVAL, 1);
    

    // Attach Shared Memory
    _shmptr = shmat(_shmid, NULL, 0);
    if (_shmptr == (void *)-1) {
      perror("Failed to attach shared memory id");
      exit(1);
    }
    printf("Shared memory and Semaphore created.\n");
  }

  ~SharedMemoryManager()
  {
    // Detach Shared Memory
    shmdt(_shmptr);
    // Delete Shared Memory
    shmctl(_shmid, IPC_RMID, NULL);
    // Delete Semaphore
    semctl(_semid, 0, IPC_RMID);
  }
  
  /**
   * @brief Copy the data to shared memory
   * 
   * @param data  The data to be copied to shared memory
   */
  void CopyToSharedMemory(T* data, size_t size)
  {
    //write something....
    
  }

  void WriteStrToSharedMemory(std::string &Serialized_data)
  {
    // Lock Semaphore
    _sb = {0, -1, 0};
    if (semop(_semid, &_sb, 1) == -1)
    {
      perror("Failed to lock semaphore");
      exit(1);
    }


    printf("Transfer data to shared memory.\n");
    // Data Copy
    memcpy(_shmptr, Serialized_data.data(), Serialized_data.size());

    // Unlock Semaphore
    _sb.sem_op = 1;
    if(semop(_semid, &_sb, 1))
    {
      perror("Failed to unlock semaphore");
      exit(1);
    }
    
  }


private:
  struct sembuf _sb;
  key_t _key;
  size_t _size;
  int _shmid, _semid;
  void* _shmptr;
};






