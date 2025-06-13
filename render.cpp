#include "render.h"

void Render::drawLine(Vector2i& p0,Vector2i& p1,TGAImage& image,TGAColor color)
{
    int x0,y0,x1,y1;
    x0=p0[0];x1=p1[0];y0=p0[1];y1=p1[1];
    bool steep = false; 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0>x1) { 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    int dx = x1-x0; 
    int dy = y1-y0; 
    int derror2 = std::abs(dy)*2; 
    int error2 = 0; 
    int y = y0; 
    for (int x=x0; x<=x1; x++) { 
        if (steep) { 
            image.set(y, x, color); 
        } else { 
            image.set(x, y, color); 
        } 
        error2 += derror2; 
        if (error2 > dx) { 
            y += (y1>y0?1:-1); 
            error2 -= dx*2; 
        } 
    } 
}
void Render::drawLine(Vector2f& p0,Vector2f& p1,TGAImage& image,TGAColor color)
{
    int x0,y0,x1,y1;
    x0=p0[0];x1=p1[0];y0=p0[1];y1=p1[1];
    bool steep = false; 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0>x1) { 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    int dx = x1-x0; 
    int dy = y1-y0; 
    int derror2 = std::abs(dy)*2; 
    int error2 = 0; 
    int y = y0; 
    for (int x=x0; x<=x1; x++) { 
        if (steep) { 
            image.set(y, x, color); 
        } else { 
            image.set(x, y, color); 
        } 
        error2 += derror2; 
        if (error2 > dx) { 
            y += (y1>y0?1:-1); 
            error2 -= dx*2; 
        } 
    } 
}
void Render::drawLine(const Vector2i& p0,const Vector2i& p1,TGAImage& image,TGAColor color)
{
    int x0,y0,x1,y1;
    x0=p0[0];x1=p1[0];y0=p0[1];y1=p1[1];
    bool steep = false; 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0>x1) { 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    int dx = x1-x0; 
    int dy = y1-y0; 
    int derror2 = std::abs(dy)*2; 
    int error2 = 0; 
    int y = y0; 
    for (int x=x0; x<=x1; x++) { 
        if (steep) { 
            image.set(y, x, color); 
        } else { 
            image.set(x, y, color); 
        } 
        error2 += derror2; 
        if (error2 > dx) { 
            y += (y1>y0?1:-1); 
            error2 -= dx*2; 
        } 
    } 
}
void Render::drawTriangle(Triangle& triangle,Scene& scene,std::vector<Vector4f>& worldpos)
{
    int maxidx = zBuffer.size();
    int minx=std::min(triangle.v_homogeneous[0].x,std::min(triangle.v_homogeneous[1].x,triangle.v_homogeneous[2].x));
    int maxx=std::max(triangle.v_homogeneous[0].x,std::max(triangle.v_homogeneous[1].x,triangle.v_homogeneous[2].x));
    int miny=std::min(triangle.v_homogeneous[0].y,std::min(triangle.v_homogeneous[1].y,triangle.v_homogeneous[2].y));
    int maxy=std::max(triangle.v_homogeneous[0].y,std::max(triangle.v_homogeneous[1].y,triangle.v_homogeneous[2].y));
    //std::cout<<minx<<" "<<triangle[0].z<<" "<<triangle[1].z<<" "<<triangle[2].z<<std::endl;
    for(int i=minx;i<=maxx;++i)
    {
        for(int j=miny;j<=maxy;++j)
        {
            if(triangle.isInside(Vector2i(i,j)))
            {
                auto [alpha,beta,gamma] = triangle.getBarycentricCoord(i+0.5,j+0.5);
                float Z = 1.0 / (alpha / triangle.v_homogeneous[0].w + beta / triangle.v_homogeneous[1].w + gamma / triangle.v_homogeneous[2].w);
                float zp = alpha * triangle.v_homogeneous[0].z / triangle.v_homogeneous[0].w+
                           beta * triangle.v_homogeneous[1].z / triangle.v_homogeneous[1].w+ 
                           gamma * triangle.v_homogeneous[2].z / triangle.v_homogeneous[2].w;
                float z=zp*Z;
                int idx = getIndexBy2D(i,j);
                
                if(idx>=0&&idx<maxidx&&zBuffer[idx]<z)
                {
                    TGAColor color(255,255,255,255);
                    
                    Vector3f texcoord = (triangle.uv_coords[0]*alpha/triangle.v_homogeneous[0].w+
                                        triangle.uv_coords[1]*beta/triangle.v_homogeneous[1].w+
                                        gamma*triangle.uv_coords[2]/triangle.v_homogeneous[0].w)*Z;
                    auto shadingcoord = ((worldpos[0]*alpha/triangle.v_homogeneous[0].w) +
                                         (worldpos[1] * beta /triangle.v_homogeneous[1].w) +
                                         (worldpos[2] * gamma /triangle.v_homogeneous[0].w))*Z;
                    Vector3f frag_pos(shadingcoord[0],shadingcoord[1],shadingcoord[2]);

                    ShadingPixel pix(
                        texcoord,
                        frag_pos,
                        scene.camera.pos,
                        &triangle,
                        scene.Lights
                    );
                    zBuffer[idx]=z;
                    shader->fragment_prosess(pix,color);
                    image.set(i,j,color);
                }
            }
        }
    }
}
void Render::renderScene(Scene& scene)
{
    Matrix4f trans_matrix = getProjectionMatrix(scene.camera)*getViewMatrix(scene.camera);
    for(auto& model : scene.models)
    {
        Matrix4f model_matrix = getModelMatrix(model);
        trans_matrix = trans_matrix*model_matrix;
        for(auto& face : model->faces_)
        {
            std::vector<Vector4f> worldpos(3);
            for(int i=0;i<3;++i) worldpos[i]=model_matrix*face.v_homogeneous[i];
            shader->vert_prosess(trans_matrix,face);
            drawTriangle(face,scene,worldpos);
        }
    }
}

Matrix4f Render::getModelMatrix(Model* model)
{
    float alpha = MY_PI*model->rotation.x/360.;
    float beta = MY_PI*model->rotation.y/360.;
    float theta = MY_PI*model->rotation.z/360;
    Matrix4f rotation_alpha({
        Vector4f({1,0,0,0}),
        Vector4f({0,std::cos(alpha),-std::sin(alpha),0}),
        Vector4f({0,std::sin(alpha),std::cos(alpha),0}),
        Vector4f({0,0,0,1})
    });
    Matrix4f rotation_beta({
        Vector4f({std::cos(beta),0,std::sin(beta),0}),
        Vector4f({0,1,0,0}),
        Vector4f({-std::sin(beta),0,std::cos(beta),0}),
        Vector4f({0,0,0,1})
    });
    Matrix4f rotation_theta({
        Vector4f({std::cos(theta),-std::sin(theta),0,0}),
        Vector4f({std::sin(theta),std::cos(theta),0,0}),
        Vector4f({0,0,1,0}),
        Vector4f({0,0,0,1})
    });
    Matrix4f rotation = rotation_alpha * rotation_beta * rotation_theta;
    Matrix4f scale({
        Vector4f({model->scale.x,0,0,0}),
        Vector4f({0,model->scale.y,0,0}),
        Vector4f({0,0,model->scale.z,0}),
        Vector4f({0,0,0,1})
    });
    Matrix4f position({
        Vector4f({1,0,0,model->position.x}),
        Vector4f({0,1,0,model->position.y}),
        Vector4f({0,0,1,model->position.z}),
        Vector4f({0,0,0,1})
    });
    return position*rotation*scale;
}

Matrix4f Render::getViewMatrix(Camera camera)
{
    Matrix4f Tview({
        Vector4f({1,0,0,-camera.pos.x}),
        Vector4f({0,1,0,-camera.pos.y}),
        Vector4f({0,0,1,-camera.pos.z}),
        Vector4f({0,0,0,1})
    });
    Vector3f g=(camera.look_at);
    Vector3f t=(camera.up);
    Vector3f gxt = (g.cross(t)).normalize();
    Matrix4f Rview({
        Vector4f({gxt[0],gxt[1],gxt[2],0}),
        Vector4f({t[0],t[1],t[2],0}),
        Vector4f({-g[0],-g[1],-g[2],0}),
        Vector4f({0,0,0,1})
    });
    return Rview*Tview;
}

Matrix4f Render::getProjectionMatrix(Camera camera)
{
    float h = std::tan(camera.fov/360*MY_PI)*camera.z_near*2;
    float w = camera.aspect_ratio*h;
    float n=-camera.z_near;
    float f=-camera.z_far;
    std::cout<<"h: "<<h<<" w: "<<w<<std::endl;
    Matrix4f mat_ortho1({
        Vector4f(1,0,0,0),
        Vector4f(0,1,0,0),
        Vector4f(0,0,1,-(n+f)/2),
        Vector4f(0,0,0,1)
    });
    Matrix4f mat_ortho2({
        Vector4f(2./w,0,0,0),
        Vector4f(0,2./h,0,0),
        Vector4f(0,0,2./(n-f),0),
        Vector4f(0,0,0,1)
    });
    Matrix4f mat_project({
        Vector4f(n,0,0,0),
        Vector4f(0,n,0,0),
        Vector4f(0,0,n+f,-n*f),
        Vector4f(0,0,1,0)
    });
    return mat_ortho2*mat_ortho1*mat_project;
}