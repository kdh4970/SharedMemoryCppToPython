// do - 2023.12.13
// The test code for data sharing between C++ process and Python process by using shared memory

#include "include/SharedMemoryManager.hpp"
#include "include/mesh.pb.h"

#define VERTEX_KEY 100
#define TRIANGLE_KEY 101

using namespace std;

vector<float3> vertices;
vector<int3> triangles;

string sample_file_path = "/home/do/Desktop/do_code/SharedMemoryCppToPython/mesh_data_all.txt";

bool test_wait = true;

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

void testFunc()
{
  size_t size = 256;
  SharedMemoryWriter<float> man(777, size);
  float data[size];
  for (int i = 0; i < size; i++)
  {
    data[i] = i*0.01;
  }
  man.CopyToSharedMemory(data,size);
  exit(0);
}

void ReadSample(){
  FILE* fp = fopen(sample_file_path.c_str(), "r");
  if (fp == NULL)
  {
    printf("Error : Failed to open file\n");
    exit(1);
  }
  // read line by line and chk v and f and store them
  char line[256];
  while (fgets(line, sizeof(line), fp))
  {
    if (line[0] == 'v')
    {
      float3 vertex;
      sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
      vertices.push_back(vertex);
    }
    else if (line[0] == 'f')
    {
      int3 triangle;
      sscanf(line, "f %d %d %d", &triangle.x, &triangle.y, &triangle.z);
      triangles.push_back(triangle);
    }
  }
}



int main(int argc,const char** argv)
{
  // Add the Data reading code here (temporarily, it will not used because this will be used as module)
  printf("Reading Sample Data...");
  ReadSample();
  printf("Done\n");
  printf("The Number of Vertices : %ld\nThe Number of Triangles : %ld\n", vertices.size(), triangles.size());

  
  Mesh mesh;
  mesh.set_class_info("all");
  for (int i = 0; i < vertices.size(); i++)
  {
    Vertex vertex;
    vertex.add_position(vertices[i].x);
    vertex.add_position(vertices[i].y);
    vertex.add_position(vertices[i].z);
    mesh.add_vertices()->CopyFrom(vertex);
  }
  for (int i = 0; i < triangles.size(); i++)
  {
    Triangle triangle;
    triangle.add_vertex_indices(triangles[i].x);
    triangle.add_vertex_indices(triangles[i].y);
    triangle.add_vertex_indices(triangles[i].z);
    mesh.add_triangles()->CopyFrom(triangle);
  }

  string serialized_mesh;
  mesh.SerializeToString(&serialized_mesh);

  SharedMemoryWriter<char> shm_mesh(777, serialized_mesh.size());

  shm_mesh.WriteStrToSharedMemory(serialized_mesh);
  // Add the Data allocation code here
  printf("serialized data size : %ld\n", serialized_mesh.size());
  
  if(test_wait){
    scanf("Press Enter to exit...");
    exit(0);
  }

  return 0;
}