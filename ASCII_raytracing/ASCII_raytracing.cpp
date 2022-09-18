#include <iostream>
#include "Funcs.h"
#include "Vec2.h"
#include "Vec3.h"

using namespace std;

int main() {

	int width = 120;
	int height = 30;
	float aspect = (float)width / height;				//compress image by x
	float pixelAspect = 11.0f / 24.0f;					//single pixel dimensions are 11x24 - adjust x value
	char* screen = new char[width * height + 1];		//screen is 1D array of size 120x30 plus null termenator

	char gradient[] = " .:!/r(l1Z4H9W8$@";				//chars by density
	int gradientSize = std::size(gradient) - 2;

	screen[width * height] = '\0';


	for (int t = 0; t < 10000; t++) {
		//vec3 light = normal(vec3(sin(t * 0.005), cos(t * 0.005), -1.0));		//dynamic lighting
		vec3 light = normal(vec3(-0.5, 0.5, -1.0));
		vec3 spherePos = vec3(0, 2, 0);
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {

				vec2 uv = vec2(i, j) / vec2(width, height) * 2.0f - 1.0f;
				/*	this block is changed to uv vector
				float x = (float)i / width * 2.0f - 1.0f;
				float y = (float)j / height * 2.0f - 1.0f;*/
				uv.x *= aspect * pixelAspect;
				vec3 ro = vec3(-5, 0, 0);				//viewpoint - ray origin
				vec3 rd = normal(vec3(2, uv));			//ray direction aiming at object at uv

				/* this block is used for static sphere w/ no reflections and plane
				uv.x += sin(t * 0.005);
				char pixel = ' ';
				int color = 0;
				vec2 intersection = sphere(ro, rd, 1);
				//if (intersection.x > 0) color = 10;
				if (intersection.x > 0) {
					vec3 itPoint = ro + rd * intersection.x;
					vec3 n = normal(itPoint);
					float diff = dot(n, light);
					color = diff * 20;
				}
				*/

				/* this block is changed to 3D model
				float dist = sqrt(uv.x * uv.x + uv.y * uv.y);
				int color = (int)(1.0f / dist);
				*/
				ro = rotateY(ro, 0.25);
				rd = rotateY(rd, 0.25);
				ro = rotateZ(ro, t * 0.01);
				rd = rotateZ(rd, t * 0.01);
				float diff = 1;
				for (int k = 0; k < 5; k++) {
					float minIt = 99999;
					vec2 intersection = sphere(ro - spherePos, rd, 1);
					vec3 n = 0;
					float dRef = 1;			//reflection quotient
					if (intersection.x > 0) {		//sphere image
						vec3 itPoint = ro - spherePos + rd * intersection.x;
						minIt = intersection.x;
						n = normal(itPoint);
					}

					intersection = plane(ro, rd, vec3(0, 0, -1), 1);
					if (intersection.x > 0 && intersection.x < minIt) {		//plane image
						minIt = intersection.x;
						n = vec3(0, 0, -1);
						dRef = 0.5;
					}
					if (minIt < 99999) {
						diff *= (dotProduct(n, light) * 0.5 + 0.5) * dRef;
						ro = ro + rd * (minIt - 0.01);
						rd = reflect(rd, n);
					}
					else break;
				}
				int color = (int)(diff * 20);
				color = restrict(color, 0, gradientSize);
				char pixel = gradient[color];
				screen[i + j * width] = pixel;

			}
		}
		printf(screen);
	}



	return 0;
}

