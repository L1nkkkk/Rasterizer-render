#include "model.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

Model::Model(const char* filename)
{
    rotation=position = Vector3f(0);
    scale=Vector3f(1);
    std::string fn(filename);
    std::string normalMapFileName = fn+"_nm.tga";
    std::string diffuseMapFileName = fn+"_diffuse.tga";
    std::string specMapFileName = fn+"_spec.tga";
    std::string modelFileName = fn+".obj";
    normalMap.read_tga_file(normalMapFileName.c_str());
    normalMap.flip_vertically();
    diffuseMap.read_tga_file(diffuseMapFileName.c_str());
    diffuseMap.flip_vertically();
    specMap.read_tga_file(specMapFileName.c_str());
    specMap.flip_vertically();
    std::ifstream in;
    in.open(modelFileName.c_str(),std::ifstream::in);//Read Only Load
    if (in.fail()) return;
    std::string line;
    while(!in.eof())
    {
        std::getline(in,line);
        std::istringstream iss(line.c_str());
        char trash;
        if(!line.compare(0,2,"v "))
        {
            //std::cout<<line<<std::endl;
            iss>>trash;
            Vector3f v;
            for(int i=0;i<3;++i) iss >> v[i];
            verts_.push_back(v);
        } 
        else if (!line.compare(0,2,"f "))
        {
            std::vector<Vector3f> verts_face(3);
            std::vector<Vector3f> texcoords_face(3);
            int itrash,idx;
            iss >> trash;
            std::vector<Vector3i> f;
            Vector3i tmp;
            while (iss >> tmp[0] >> trash >> tmp[1] >> trash >> tmp[2]) {
                for (int i=0; i<3; ++i) tmp[i]--; // in wavefront obj all indices start at 1, not zero
                f.push_back(tmp);
            }

            for(int i=0;i<3;++i)
            {
                verts_face[i]=vert(f[i][0]);
                verts_face[i].print();
                texcoords_face[i]=texcoord(f[i][1]);
            }
            Triangle tri(verts_face);
            tri.setUVcoords(texcoords_face);
            tri.diffuse_map = &diffuseMap;
            tri.normal_map = &normalMap;
            faces_.push_back(tri);    
        }
        else if(!line.compare(0,3,"vt "))
        {
            Vector3f texcoord;
            iss>>trash;
            iss>>trash;
            for(int i=0;i<3;++i) iss >> texcoord[i];
            texcoords_.push_back(texcoord);
        }
    }
    std::cerr << "# v# " << verts_.size() << " f# "  << faces_.size() << std::endl;
}

Model::~Model() {
}

int Model::num_verts() {
    return (int)verts_.size();
}

int Model::num_faces() {
    return (int)faces_.size();
}

Triangle Model::face(int idx) {
    return faces_[idx];
}

Vector3f Model::vert(int i) {
    return verts_[i];
}

Vector3f Model::texcoord(int i) {
    return texcoords_[i];
}