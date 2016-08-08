/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 03:46:50 by vbauguen          #+#    #+#             */
/*   Updated: 2016/08/08 11:11:40 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_raystruct.h"

double	equa_sec(double a, double b, double discriminant, double *x1, double *y1, double nbr)
{
	if (discriminant == 0)
	{
		*y1 = -1;
		*x1 = ((-b + sqrtf(discriminant)) / (2 * a))+ nbr;
		return (*x1); 
	}
	else
	{
		*x1 = ((-b + sqrtf(discriminant)) / (2 * a))+ nbr;
		*y1 = ((-b - sqrtf(discriminant)) / (2 * a)) + nbr;
		if (*y1 >= 0 && (*y1 < *x1 || *x1 < 0))
		{
			discriminant = *y1;
			*y1 = *x1;
			*x1 = discriminant;
		}
		if (*x1 >= 0)
			return (*x1);
		return (0);
	}
}

double	ferrari(double a, double b, double c, double d, double e)
{
	double p;
	double q;
	double r;
	double x[4];
	int i;
	//double discriminant;
	if (a != 0)
	{
		q = (8 * a * a * d + b * b * b - 4 * a * b * c) / (8 * a * a * a);
		p = (8 * a * c - 3 * b * b) / (8 * a * a);
		r = (16 * a * b * b * c - 64 * a * a * b * d - 3 * b * b * b * b + 256 * a * a * a * e) / 256 * a * a * a * a;
		if (q != 0)
		{
			x[0] = sqrtf((-p - sqrtf(p * p - 4 * r)) / 2) - b / (4 * a);
			x[1] = -sqrtf((-p - sqrtf(p * p - 4 * r)) / 2) - b / (4 * a);
			x[2] = sqrtf((-p + sqrtf(p * p - 4 * r)) / 2) - b / (4 * a);
			x[3] = -sqrtf((-p + sqrtf(p * p - 4 * r)) / 2) - b / (4 * a);
			i = 0;
			q = 0;
			while (i != 4)
			{
				if (x[i] >= 0 && (x[i] < q || q == 0))
					q = x[i];
				i++;
			}
			return (q);
		}
		else
		{
			return (0);
		}
	}
	return (0);
}

double intersectRayCone(t_ray *r, t_obj *s, double *x1, double *y1)
{
	(void)x1;
	(void)y1;
	(void)r;
	(void)s;

	double discriminant;
	double a;
	double b;
	double c;
	double k;
	double dist;
	t_vector cone_pos;
	t_vector cone_dir;
	t_vector x;
	double test1;
	double test2;

	cone_pos = newVector(s->pos[0], s->pos[1],s->pos[2]);
	cone_dir = vectorNormalize(newVector(s->pos[3], s->pos[4],s->pos[5]));
	x = vectorSub(r->start, cone_pos);
	k = tan(((s->size[1] > 150) ? 150 : s->size[1]) * (M_PI / 180) / 2);
	a = vectorDot(r->dir, r->dir) - (1 + k * k) * vectorDot(r->dir, cone_dir) * vectorDot(r->dir, cone_dir);
	b = 2 * (vectorDot(r->dir, x) - (1 + k * k) * vectorDot(r->dir, cone_dir) * vectorDot(x, cone_dir));
	c = vectorDot(x, x) - (1 + k * k) *  vectorDot(x, cone_dir) *  vectorDot(x, cone_dir);

	discriminant = b * b - 4.0 * (a * c);

	if (discriminant < 0)
		return (0);
	if (discriminant >= 0)
	{
		test1 = *x1;
		test2 = *y1;
		dist = equa_sec(a, b, discriminant, x1, y1, 0);
		if (dist < 0)
		{
			*x1 = test1;
			*y1 = test2;
			return (0);
		}
		if (vectorDist(getHitpoint(r->start, r->dir, dist), cone_pos) > s->size[0] || vectorDist(getHitpoint(r->start, r->dir, dist), getHitpoint(cone_pos, cone_dir, s->size[0])) < s->size[0])
		{
			if ((-b + sqrtf(discriminant)) / (2 * a) > dist)
				dist = (-b + sqrtf(discriminant)) / (2 * a);
			if ((-b - sqrtf(discriminant)) / (2 * a) > dist)
				dist = (-b - sqrtf(discriminant)) / (2 * a);
			if (vectorDist(getHitpoint(r->start, r->dir, dist), cone_pos) > s->size[0] || vectorDist(getHitpoint(r->start, r->dir, dist), getHitpoint(cone_pos, cone_dir, s->size[0])) < s->size[0])
			{
				*x1 = test1;
				*y1 = test2;
				return (0);
			}
		}
		
	t_vector intersection_pos;

	intersection_pos = getHitpoint(r->start, r->dir, dist);
	x = vectorSub(intersection_pos, cone_pos);// P - C
	k = vectorDot(x, cone_dir);
	r->norm = vectorSub(x, vectorMultByScalar(cone_dir, k));// (P - C) - V * k? 
	if (*x1 < 0)
	{
		r->norm.x = -r->norm.x;
		r->norm.y = -r->norm.y;
		r->norm.z = -r->norm.z;
	}
	vectorNormalize(r->norm);
		return dist;
	}
	return (0);
}

double intersectRayBoloid(t_ray *r, t_obj *s, double *x1, double *y1)
{
	(void)r;
	(void)s;
	(void)x1;
	(void)y1;
	return (0);
}
double intersectRayTorus(t_ray *r, t_obj *s, double *x1, double *y1)
{
	double a;
	double b;
	double c;
	double d;
	double e;
	double dist;
	t_vector torus_pos;
	t_vector torus_dir;
	t_vector intersection_pos;
	t_vector x;
	(void)x1;
	(void)y1;
	torus_pos = newVector(s->pos[0], s->pos[1],s->pos[2]);
	torus_dir = vectorNormalize(newVector(s->pos[3], s->pos[4],s->pos[5]));
	x = vectorSub(r->start, torus_pos);
	
	a = pow(vectorDot(r->dir, r->dir), 2);
	b = 4 * vectorDot(r->dir, r->dir) * vectorDot(x, r->dir);
	c = 4 * pow(vectorDot(x, r->dir), 2) + 2 * vectorDot(r->dir, r->dir) * (vectorDot(x, x) - pow(s->size[1], 2) - pow(s->size[0], 2))
			+ 4 * pow(s->size[0], 2) * pow(vectorDot(r->dir, torus_dir), 2);
	d = 4 * vectorDot(x, r->dir) * (vectorDot(x, x)
			- pow(s->size[1], 2) - pow(s->size[0], 2)) + 8
			* pow(s->size[0], 2) *  vectorDot(x, torus_dir) * vectorDot(r->dir, torus_dir);
	e = pow((vectorDot(x, x) - pow(s->size[1], 2)
			- pow(s->size[0], 2)), 2) + 4 * pow(s->size[0], 2) * pow( vectorDot(x, torus_dir), 2)
			- 4 * pow(s->size[0], 2) * pow(s->size[1], 2);

	dist = ferrari(a, b, c, d, e);
	t_vector circ_pos;
	intersection_pos = getHitpoint(r->start, r->dir, dist);
	circ_pos = getHitpoint(torus_pos, torus_dir, s->size[0] - s->size[1]);
	r->norm = vectorNormalize(vectorSub(intersection_pos, circ_pos));
	return (dist);
}

double intersectRayCylindre(t_ray *r, t_obj *s, double *x1, double *y1)
{
		(void)x1;
	(void)y1;
	(void)r;
	(void)s;

	double discriminant;
	double dot;
	double dot2;
	double a;
	double b;
	double c;
	double dist;
	t_vector cyl_pos;
	t_vector cyl_dir;
	t_vector tmp;
	// t_vector p_top;
	// t_vector p_bot;

	cyl_pos = newVector(s->pos[0], s->pos[1],s->pos[2]);
	cyl_dir = vectorNormalize(newVector(s->pos[3], s->pos[4],s->pos[5]));

	dot = vectorDot(r->dir, cyl_dir);
	tmp = vectorSub(r->start, cyl_pos);//delta p cyl_pos == pa
	dot2 = vectorDot(tmp, cyl_dir);
	// dot2 = vectorDot(r->dir, cyl_dir);

	a = vectorDot(vectorSub(r->dir, vectorMultByScalar(cyl_dir, dot)), vectorSub(r->dir, vectorMultByScalar(cyl_dir, dot)));
	b = 2 * vectorDot(vectorSub(r->dir, vectorMultByScalar(cyl_dir, dot)), vectorSub(tmp, vectorMultByScalar(cyl_dir, dot2)));
	c = vectorDot(vectorSub(tmp, vectorMultByScalar(cyl_dir, dot2)), vectorSub(tmp, vectorMultByScalar(cyl_dir, dot2))) - s->size[0] * s->size[0];


	discriminant = b * b - 4 * (a * c);
	// p_top = newVector(s->pos[0] - s->size[1], s->pos[1] - s->size[1], s->pos[2] - s->size[1]);
	// p_bot = newVector(s->pos[0] + s->size[1], s->pos[1] + s->size[1], s->pos[2] + s->size[1]);

	if (discriminant >= 0)
	{
		dist = ((-b + sqrtf(discriminant)) / (2 * a));
		if ( ((-b - sqrtf(discriminant)) / (2 * a)) < (dist))
		{
			dist = ((-b - sqrtf(discriminant)) / (2 * a));
			if (dist < 0)
				return (0);
			*x1 = dist;
			*y1 = ((-b + sqrtf(discriminant)) / (2 * a));
		}
		else
		{
			if (dist < 0)
				return (0);
			*x1 = ((-b + sqrtf(discriminant)) / (2 * a));
			*y1 = ((-b - sqrtf(discriminant)) / (2 * a));
		}
		t_vector temp;
		t_vector tp;
		t_vector ab;
		t_vector proj;
		t_vector cyl_pos_dir = newVector(s->pos[0] + s->pos[3], s->pos[1] + s->pos[4], s->pos[2] + s->pos[5]);

		temp = vectorMultByScalar(r->dir, dist);
		temp = vectorAdd(temp, r->start);
		proj = vectorSub(cyl_pos_dir, temp);
		ab = vectorSub(cyl_pos, cyl_pos_dir);
		tp = vectorMultByScalar(ab, vectorDot(ab, proj) / vectorDot(ab, ab));
		tp = vectorAdd(tp, cyl_pos_dir);

		proj.x = tp.x;
		proj.y = tp.y;
		proj.z = tp.z;
		proj = vectorSub(cyl_pos, proj);
		r->norm = temp;
		proj = vectorAdd(proj, cyl_pos);
		r->norm = vectorNormalize(vectorSub(proj, r->norm));
		if (vectorDist(getHitpoint(r->start, r->dir, dist), cyl_pos) > s->size[1])
		{
			if (((-b + sqrtf(discriminant)) / (2 * a)) > dist)
				dist = ((-b + sqrtf(discriminant)) / (2 * a));
			if (((-b - sqrtf(discriminant)) / (2 * a)) > dist)
				dist = ((-b - sqrtf(discriminant)) / (2 * a));
			if (vectorDist(getHitpoint(r->start, r->dir, dist), cyl_pos) > s->size[1])
				return (0);
		}
		r->norm.x = -r->norm.x;
		r->norm.y = -r->norm.y;
		r->norm.z = -r->norm.z;
		r->norm = vectorNormalize(r->norm);
		return dist;
	}
 		return 0;
	
}

t_vector ComputeNormal(t_vector inter, t_vector aabbCenter)
{
    t_vector normals[] = { // A cube has 3 possible orientations
       (t_vector){1,0,0},
       (t_vector){0,1,0},
       (t_vector){0,0,1}
    };
    const t_vector interRelative = vectorNormalize(vectorSub(inter, aabbCenter));
    const float xyCoef = interRelative.y / interRelative.x;
    const float zyCoef = interRelative.y / interRelative.z;

    const int coef = (xyCoef < 1 && -1 < xyCoef) ? 1 :
                      (zyCoef > 1 || -1 > zyCoef ? 0 : 2);
    normals[coef].x = (interRelative.x < 0) ? normals[coef].x : -normals[coef].x;
    normals[coef].y = (interRelative.y < 0) ? normals[coef].y : -normals[coef].y;
    normals[coef].z = (interRelative.z < 0) ? normals[coef].z : -normals[coef].z;
    return normals[coef]; // The sign he is used to know direction of the normal
}

double intersectRayCarre(t_ray *r, t_obj *s, double *x1, double *y1)
{
	(void)x1;
	(void)y1;
	double t_min = (-s->size[0] - (r->start.x - s->pos[0])) / r->dir.x; 
    double tmax = (s->size[0] - (r->start.x - s->pos[0])) / r->dir.x; 
 	double t;
    if (t_min > tmax)
    { 
    	t = t_min;
    	t_min = tmax;
    	tmax = t;
 	}
    double tymin = (-s->size[1] - (r->start.y - s->pos[1])) / r->dir.y; 
    double tymax = (s->size[1] - (r->start.y - s->pos[1])) / r->dir.y; 
 
    if (tymin > tymax)
    {
    	t = tymin;
    	tymin = tymax;
    	tymax = t;
    } 

    if ((t_min > tymax) || (tymin > tmax)) 
        return 0; 
 
    if (tymin > t_min) 
        t_min = tymin; 
 
    if (tymax < tmax) 
        tmax = tymax; 
 
    double tzmin = (-s->size[2] - (r->start.z - s->pos[2])) / r->dir.z; 
    double tzmax = (s->size[2] - (r->start.z - s->pos[2])) / r->dir.z; 
 
    if (tzmin > tzmax)
	{
		t = tzmin;
		tzmin = tzmax;
		tzmax = t;
	}
 
    if ((t_min > tzmax) || (tzmin > tmax)) 
        return 0; 
 
    if (tzmin > t_min) 
        t_min = tzmin; 
 
    if (tzmax < tmax) 
        tmax = tzmax; 
	

    r->norm = ComputeNormal(getHitpoint(r->start, r->dir, (t_min < tmax) ? t_min : tmax), newVector(s->pos[0], s->pos[1], s->pos[2]));
    return (t_min < tmax) ? t_min : tmax; 
}

double intersectRaySphere(t_ray *r, t_obj *s, double *x1, double *y1)
{

	(void)x1;
	(void)y1;

	double a, b, c, discriminant;
	double dist;

	t_vector newpos;
	newpos = newVector(r->start.x - s->pos[0], r->start.y - s->pos[1],r->start.z - s->pos[2]);

	a = vectorDot(r->dir, r->dir);
	b = 2 * vectorDot(r->dir, newpos);
	c = vectorDot(newpos, newpos) - s->size[0] * s->size[0];


	discriminant = b * b - 4 * (a * c);

	dist = 0;
	if (discriminant >= 0)
	{
		dist = ((-b + sqrtf(discriminant)) / (2 * a));

		if (((-b + sqrtf(discriminant)) / (2 * a)) <= 0 || ((-b - sqrtf(discriminant)) / (2 * a)) <= 0)
			return (0);
		// dist = ((-b + sqrtf(discriminant)) / (2 * a));
		
		if ( ((-b - sqrtf(discriminant)) / (2 * a)) < (dist))
		{
			dist = ((-b - sqrtf(discriminant)) / (2 * a));
			*x1 = dist;
			*y1 = ((-b + sqrtf(discriminant)) / (2 * a));
		}
		else
		{
			*x1 = ((-b + sqrtf(discriminant)) / (2 * a));
			*y1 = ((-b - sqrtf(discriminant)) / (2 * a));
		}

		if ( ((-b - sqrtf(discriminant)) / (2 * a)) < (dist))
			dist = ((-b - sqrtf(discriminant)) / (2 * a));
		t_vector hitpoint;
		hitpoint = getHitpoint(r->start, r->dir, dist);

		r->norm = newVector((hitpoint.x - s->pos[0]) / s->size[0], 
			(hitpoint.y - s->pos[1]) / s->size[0],
			(hitpoint.z - s->pos[2]) / s->size[0]);
		r->norm = vectorNormalize(r->norm);
		if (s->cut[3] || s->cut[4] || s->cut[5])
		{
			t_vector hitpoint;
			t_vector plan;
			double t;
			t_vector l;
			t_vector p0_l0;
			t_vector n;

			hitpoint = getHitpoint(r->start, r->dir, dist);
			plan = newVector(s->pos[0] + s->cut[0], s->pos[1] + s->cut[1], s->pos[2] + s->cut[2]);
			n = newVector(s->cut[3], s->cut[4], s->cut[5]);
			l = vectorDir(plan, hitpoint);
			n = vectorNormalize(n);
			p0_l0 = vectorSub(plan, hitpoint);
		 	double denom = vectorDot(l, n); 
   			t = vectorDot(p0_l0, n) / denom ;
	
					
			if (t > 0.000001 && t < s->size[0])
			{
				dist = fabs((-b + sqrtf(discriminant)) / (2 * a));

				if ( fabs((-b - sqrtf(discriminant)) / (2 * a)) > fabs(dist))
				{
					dist = fabs((-b - sqrtf(discriminant)) / (2 * a));
				// r->norm = newVector(-(hitpoint.x - s->pos[0]) / s->size[0], 
			// -(hitpoint.y - s->pos[1]) / s->size[0],
			// -(hitpoint.z - s->pos[2]) / s->size[0]);
		// r->norm = vectorNormalize(r->norm);
				}
				hitpoint = getHitpoint(r->start, r->dir, dist);
				plan = newVector(s->pos[0] + s->cut[0], s->pos[1] + s->cut[1], s->pos[2] + s->cut[2]);
				// n = newVector(s->cut[3], s->cut[4], s->cut[5]);
				l = vectorDir(plan, hitpoint);
				// n = vectorNormalize(n);
				p0_l0 = vectorSub(plan, hitpoint);
			 	double denom = vectorDot(l, n); 
					t = vectorDot(p0_l0, n) / denom ;
				if (t > 0.001 && t < s->size[0])
				{
					return (0);
				}
				else
				{
			if (dist >= fabs((-b - sqrtf(discriminant)) / (2 * a)) && dist >= fabs((-b + sqrtf(discriminant)) / (2 * a)))
			{
				r->norm = newVector(-(hitpoint.x - s->pos[0]) / s->size[0], 
			-(hitpoint.y - s->pos[1]) / s->size[0],
			-(hitpoint.z - s->pos[2]) / s->size[0]);
		r->norm = vectorNormalize(r->norm);
			}
					hitpoint = getHitpoint(hitpoint, l, t); // getHitpoint(p0_l0, l, t) pour surface pleine
			

					return (vectorDist(r->start, hitpoint));
					
				}
			}
			if (dist >= fabs((-b - sqrtf(discriminant)) / (2 * a)) && dist >= fabs((-b + sqrtf(discriminant)) / (2 * a)))
			{
				r->norm = newVector(-(hitpoint.x - s->pos[0]) / s->size[0], 
			-(hitpoint.y - s->pos[1]) / s->size[0],
			-(hitpoint.z - s->pos[2]) / s->size[0]);
		r->norm = vectorNormalize(r->norm);
			}
		}
 		return dist;
	}
 	else
 		return 0;
}

double intersectRayComplex(t_ray *r, t_obj *p, double *x1, double *y1, int *col)
{
	double		t;
	t_obj		*tmp;
	t_obj		*temp;
	double		nearest[2];
	double		tmp_near[2];
	t_vector	norm;
	double		new_nearest;

	(void)x1;
	(void)y1;
	tmp = p->comp;
	nearest[0] = -1;
	nearest[1] = INT_MAX;
	while (tmp)
	{
		if (!tmp->eff[3])
		{
			tmp = tmp->next;
			continue ;
		}
		tmp_near[0] = -1;
		tmp_near[1] = INT_MAX;
		if (tmp->type == SPHERE)
			t = intersectRaySphere(r, tmp, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (tmp->type == PLAN)
			t = intersectRayPlane(r, tmp, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (tmp->type == CYLINDRE)
			t = intersectRayCylindre(r, tmp, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (tmp->type == RECTANGLE)
			t = intersectRayCarre(r, tmp, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (tmp->type == CONE)
			t = intersectRayCylindre(r, tmp, &tmp_near[0], &tmp_near[1]);
		else if (tmp->type == BOLOID)
			t = intersectRayBoloid(r, tmp, &tmp_near[0], &tmp_near[1]);
		else if (tmp->type == TORUS)
			t = intersectRayCone(r, tmp, &tmp_near[0], &tmp_near[1]);
		if (t > 0.01 && tmp_near[0] != -1)
		{
			if (nearest[0] == -1 || (tmp_near[0] < nearest[0]) || tmp_near[1] > nearest[1])
			{
				if (nearest[0] == -1 || tmp_near[0] < nearest[0])
					nearest[0] = tmp_near[0];
				if (nearest[1] == INT_MAX || tmp_near[1] > nearest[1])
					nearest[1] = tmp_near[1];
				norm = r->norm;
			}
			t = 0;
		}
		tmp = tmp->next;
	}
	tmp = p->comp;
	temp = NULL;
	new_nearest = -1;
	while (tmp) //pour toute la liste d'objets
	{
		if (tmp->eff[3])
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp->type == SPHERE)
			t = intersectRaySphere(r, tmp, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (tmp->type == PLAN)
			t = intersectRayPlane(r, tmp, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (tmp->type == CYLINDRE)
			t = intersectRayCylindre(r, tmp, &tmp_near[0], &tmp_near[1]); // a chaque forme sa formule mathematique 
		else if (tmp->type == RECTANGLE)
			t = intersectRayCarre(r, tmp, &tmp_near[0], &tmp_near[1]);
		else if (tmp->type == CONE)
			t = intersectRayCylindre(r, tmp, &tmp_near[0], &tmp_near[1]);
		else if (tmp->type == TORUS)
			t = intersectRayCone(r, tmp, &tmp_near[0], &tmp_near[1]);
		else if (tmp->type == BOLOID)
			t = intersectRayBoloid(r, tmp, &tmp_near[0], &tmp_near[1]);
		if ((t < new_nearest && t > 0.00001)|| (new_nearest < 0 && t > 0.00001))
		{
			// si la distance actuelle calculee est plus petite que la precedente, on garde en memoire 
			//: la nouvelle plus courte intersection, l'objet concerne, et la normale du point touche
			if (t > nearest[0] && t < nearest[1] && nearest[0] > 0 /*&& nearest[1] < INT_MAX*/)
			{
				if (tmp_near[1] <= nearest[1] && tmp_near[0] >= nearest[0])
				{
					tmp = tmp->next;
					continue;
				}
				new_nearest = nearest[1];
				temp = tmp;
				r->obj = tmp;
				norm.x = -r->norm.x;
				norm.y = -r->norm.y;
				norm.z = -r->norm.z;
			}
			else
			{
				new_nearest = t;
				temp = tmp;
				r->obj = tmp;
				norm = r->norm;
			}
		}
		tmp = tmp->next; //objet suivant
	}
	if (new_nearest > 0.00001)
	{
		*col = temp->c_o;
		r->norm = norm;
	}
	return ((new_nearest != -1) ? new_nearest : 0); 
}

double intersectRayTriangle(t_ray *r, t_obj *p, double *x1, double *y1)
{
	(void)y1;	
	double t;
	double d;
	double near;
	t_obj		*tmp;
	t_vector new;
	t_vector test;
	t_vector c0;
	t_vector c1;
	t_vector c2;
	t_vector c3;
	
	tmp = p->comp;
	near = INT_MAX;
	while (tmp)
	{
		c0 = vectorSub(tmp->tri[1], tmp->tri[0]);
		c1 = vectorSub(tmp->tri[2], tmp->tri[0]);
		test = vectorCross(r->dir, c1);
		d = vectorDot(c0, test);
		if (d > -0.00001 && d < 0.00001)
		{
			tmp = tmp->next;
			continue ;
		}
		t = 1.0 / d;
		c2 = vectorSub(r->start, tmp->tri[0]);
		double u = t * vectorDot(c2, test);
		if (u < 0.0 || u > 1.0)
		{
			tmp = tmp->next;
			continue ;	
		}
		c3 = vectorCross(c2, c0);
		double v = t * vectorDot(r->dir, c3);
		if (v < 0.0 || u + v > 1.0)
		{
			tmp = tmp->next;
			continue ;	
		}
		t = t * vectorDot(c1, c3);
		if (t > 0.0001 && t < near)
		{
			new = tmp->nor;
			near = t;
		}
		tmp = tmp->next;
	}
	if (near > 0 && near < INT_MAX)
	{
		r->norm.x = new.x;
		r->norm.y = new.y;
		r->norm.z = new.z;
		*x1 = near;
		r->norm = vectorNormalize(r->norm);
		return (near);
	}
	return (0);
}

double intersectRayPlane(t_ray *r, t_obj *p, double *x1, double *y1)
{
	(void)x1;
	(void)y1;	
	double t;
	t_vector n;
	t_vector p0;

	p0 = newVector(p->pos[0], p->pos[1], p->pos[2]);
	n = vectorNormalize(newVector(p->pos[3], p->pos[4], p->pos[5]));
	t = (vectorDot(vectorSub(p0, r->start),n) / vectorDot(r->dir, n));
	if (t > 0.00001)
	{
		r->norm.x = n.x;
		r->norm.y = n.y;
		r->norm.z = n.z;
		// *x1 = t;
		// *y1 = *x1; 
		r->norm = vectorNormalize(r->norm);
		return (t);
	}
	return (0);
}
