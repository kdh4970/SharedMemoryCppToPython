# do - 2023.12.13
# The test code for data sharing between C++ process and Python process by using shared memory

import sysv_ipc
import struct
import array
import mesh_pb2


def test():
    mesh = mesh_pb2.Mesh()
    mesh.class_info = "test"
    mesh.vertices.add().position.extend([1.0, 1.0, 1.0])
    mesh.vertices.add().position.extend([2.0, 2.0, 2.0])
    mesh.vertices.add().position.extend([3.0, 3.0, 3.0])
    mesh.triangles.add().vertex_indices.extend([1, 2, 3])
    mesh.triangles.add().vertex_indices.extend([4, 5, 6])
    mesh.triangles.add().vertex_indices.extend([7, 8, 9])
    print("mesh : ", mesh)
    print("Number of vertices : ", len(mesh.vertices))
    print("Number of triangles : ", len(mesh.triangles))

    
    #serialize
    serialized = mesh.SerializeToString()
    print("serialized : ", serialized)
    print("type : ", type(serialized))
    print("size : ", len(serialized))
    
    #deserialize
    mesh2 = mesh_pb2.Mesh()
    mesh2.ParseFromString(serialized)
    print("mesh2 : ", mesh2)
    print("Number of vertices : ", len(mesh2.vertices))
    print("Number of triangles : ", len(mesh2.triangles))


if __name__ == "__main__":
    # test()
    # Create shared memory object
    # if shm exist, there is no error. But if shm is not exist, error occurs.
    shm = sysv_ipc.SharedMemory(777)
    # shm_triangle = sysv_ipc.SharedMemory(101)
    
    # Read value from shared memory
    value = shm.read()
    print("dtype : ", type(value))
    print("size : ", len(value))
    # print("value : ", value)
    
    Mesh = mesh_pb2.Mesh()
    Mesh.ParseFromString(value)
    # print("Mesh : ", Mesh)
    print("Number of vertices : ", len(Mesh.vertices))
    print("Number of triangles : ", len(Mesh.triangles))




    # data = struct.unpack('f' * (len(value) // 4), value)
    # print(data)

    # Delete shared memory object
    shm.detach()
    shm.remove()

    # shm_triangle.detach()
    # shm_triangle.remove()