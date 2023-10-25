/*
 * myJob.h
 *
 *  Created on: 18 oct. 2023
 *      Author: 21304302
 */

#ifndef SRC_MYJOB_H_
#define SRC_MYJOB_H_

class myJob {
public:
	myJob();
	virtual ~myJob();
	/*
	 *
	 * // le point de l'ecran par lequel passe ce rayon
			auto & screenPoint = screen[y][x];
			// le rayon a inspecter
			Rayon  ray(scene.getCameraPos(), screenPoint);

			int targetSphere = findClosestInter(scene, ray);

			if (targetSphere == -1) {
				// keep background color
				continue ;
			} else {
				const Sphere & obj = *(scene.begin() + targetSphere);
				// pixel prend la couleur de l'objet
				Color finalcolor = computeColor(obj, ray, scene.getCameraPos(), lights);
				// le point de l'image (pixel) dont on vient de calculer la couleur
				Color & pixel = pixels[y*scene.getHeight() + x];
				// mettre a jour la couleur du pixel dans l'image finale.
				pixel = finalcolor;
	 *
	 *
	 * */
};

#endif /* SRC_MYJOB_H_ */
