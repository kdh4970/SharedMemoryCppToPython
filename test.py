# do - 2023.12.13
# The test code for data sharing between C++ process and Python process by using shared memory

import sysv_ipc
import struct
import array

if __name__ == "__main__":
    
    # Create shared memory object
    # if shm exist, there is no error. But if shm is not exist, error occurs.
    shm_vertex = sysv_ipc.SharedMemory(100)
    shm_triangle = sysv_ipc.SharedMemory(101)
    
    # Read value from shared memory
    # value = shm.read()
    # print(type(value))
    # print(value)
    

    # data = struct.unpack('f' * (len(value) // 4), value)
    # print(data)

    # Delete shared memory object
    shm_vertex.detach()
    shm_vertex.remove()

    shm_triangle.detach()
    shm_triangle.remove()