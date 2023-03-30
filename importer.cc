#include <iostream>
#include <fstream>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex {
    float x, y, z;
};

struct Face {
    unsigned int a, b, c;
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./stl_to_binary <input_stl_file> <output_binary_file>" << std::endl;
        return 1;
    }

    const char* input_stl_file = argv[1];
    const char* output_binary_file = argv[2];

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(input_stl_file, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

    if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
        std::cerr << "Error: " << importer.GetErrorString() << std::endl;
        return 1;
    }

    std::vector<Vertex> vertices;
    std::vector<Face> faces;

    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        const aiMesh* mesh = scene->mMeshes[i];

        for (unsigned int j = 0; j < mesh->mNumVertices; ++j) {
            Vertex vertex;
            vertex.x = mesh->mVertices[j].x;
            vertex.y = mesh->mVertices[j].y;
            vertex.z = mesh->mVertices[j].z;
            vertices.push_back(vertex);
        }

        for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {
            const aiFace& face = mesh->mFaces[j];
            if (face.mNumIndices == 3) {
                Face f;
                f.a = face.mIndices[0];
                f.b = face.mIndices[1];
                f.c = face.mIndices[2];
                faces.push_back(f);
            }
        }
    }

    std::ofstream out(output_binary_file, std::ios::binary);
    if (!out) {
        std::cerr << "Error: Could not open output file." << std::endl;
        return 1;
    }

    size_t vertices_size = vertices.size();
    size_t faces_size = faces.size();
    out.write(reinterpret_cast<const char*>(&vertices_size), sizeof(vertices_size));
    out.write(reinterpret_cast<const char*>(&faces_size), sizeof(faces_size));
    out.write(reinterpret_cast<const char*>(vertices.data()), vertices_size * sizeof(Vertex));
    out.write(reinterpret_cast<const char*>(faces.data()), faces_size * sizeof(Face));
    out.close();

    std::cout << "Successfully converted STL file to binary format." << std::endl;
    return 0;
}