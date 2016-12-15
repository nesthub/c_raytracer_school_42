#include "raystruct.h"

double cut_object(t_obj *obj, double dist, t_ray *r, char c)
{
	t_ray	tmp;
	t_cut	*cut;
	t_obj	new_plan;
	double	t;
	t_inter	i;

	new_plan = *obj;
	new_plan.type = 0;
	i.inter1 = 0;
	i.inter2 = 0;
	new_plan.type ^= PLAN;
	cut = obj->cut;
	new_plan.cut = NULL;
	while (cut)
	{
		tmp = *r;
		ft_memcpy(new_plan.pos, cut->pos, sizeof(double) * 6);
		new_plan.pos[0] += obj->pos[0];
		new_plan.pos[1] += obj->pos[1];
		new_plan.pos[2] += obj->pos[2];
		t = intersectray_plane(&tmp, &new_plan, &i);
		if (!c && t > EPS && t < dist)
			return (0);
		if (c && t > EPS && t > dist)
			return (0);
		cut = cut->next;
	}
	return (dist);
}