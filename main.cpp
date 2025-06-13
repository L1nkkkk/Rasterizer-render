#include "render.h"
#include "model.h"

const int width  = 2048;
const int height = 2048;

int main(int argc, char** argv) {
	Camera camera(Vector3f(-1,1,-3),Vector3f(0,0,0),45,width/height,0.035,50);
	Scene scene(camera);
	if (2==argc) {
        scene.addModel(new Model(argv[1]));
    } else {
        scene.addModel(new Model("model/african_head"));
    }
	scene.addLight(Light(Vector3f(2,2,2),Vector3f(15,15,15)));
	scene.addLight(Light(Vector3f(-2,2,-2),Vector3f(15,15,15)));
	TGAImage image(width, height, TGAImage::RGB);
	Render render(image,shader_type::Phong_Shading);
	scene.models[0]->position=Vector3f(0,0,0);
	render.renderScene(scene);
	//render.drawModel(scene.models[0]);
	//image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

