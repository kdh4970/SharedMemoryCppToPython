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
class SharedMemoryWriter
{
public:
  /**
 * @brief Construct a new Shared Memory Manager:: Shared Memory Manager object
 * 
 * @param key  The key of shared memory
 * @param size  The size of shared memory
 */
  SharedMemoryWriter(key_t key, size_t size)
  {
    m_key = key;
    m_size = size;
    m_shmid = shmget(m_key, m_size, IPC_CREAT | 0666);
    if (m_shmid < 0)
    {
      printf("Error : Failed to get shared memory id");
      exit(1);
    }
    m_ptr = shmat(m_shmid, NULL, 0);
    if (m_ptr == (void *)-1)
    {
      printf("Error : Failed to attach shared memory id");
      exit(1);
    }
    // strcpy(static_cast<char*>(m_ptr), "Hello");
    printf("Successfully created shared memory.\n");
    printf("key : %d\n", m_key);
    printf("size : %ld\n", m_size);
    printf("shmid : %d\n", m_shmid);
    // printf("ptr : %p\n", m_ptr);
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
    memcpy(m_ptr, Serialized_data.data(), Serialized_data.size());
    // strcpy(static_cast<std::string*>(m_ptr), Serialized_data.c_str());
  }


private:
  key_t m_key;
  size_t m_size;
  int m_shmid;
  void* m_ptr;
};






