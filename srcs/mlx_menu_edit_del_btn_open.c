#include "raystruct.h"

void			menu_edit_del_btn_open(void *gen, void *mlx)
{
	t_mlx	*m;
	t_gen	*d;

	m = mlx;
	d = gen;
	if (m->menu.id >= LOAD_SCENE && m->menu.id < LOAD_OBJECT)
		m->menu.next = LOAD_SCENE_DEL;
	else if (m->menu.id >= LOAD_OBJECT && m->menu.id < LOAD_SPOT)
		m->menu.next = LOAD_OBJECT_DEL;
}
