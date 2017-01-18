#include "raytra_gen.h"
#include "raystruct.h"

static void		input_valid_string(t_gen *d, t_mlx *m, t_get *g)
{
	notif2(m, N_NORMAL, NOTIF_INPUT_SAVE, g->data);
	ft_strdel(&(*g->target.ptr_str));
	*g->target.ptr_str = ft_strdup(g->data);
	input_set_focus(d, m, (t_get *)NULL, -1);
}

static void		input_valid_double(t_gen *d, t_mlx *m, t_get *g)
{
	notif2(m, N_NORMAL, NOTIF_INPUT_SAVE, g->data);
	*g->target.ptr_double = ft_atob(g->data);
	input_set_focus(d, m, (t_get *)NULL, -1);
}

static void		input_valid_double_but_int(t_gen *d, t_mlx *m, t_get *g)
{
	notif2(m, N_NORMAL, NOTIF_INPUT_SAVE, g->data);
	*g->target.ptr_double = ft_atob(g->data);
	input_set_focus(d, m, (t_get *)NULL, -1);
}

static void		input_valid_int(t_gen *d, t_mlx *m, t_get *g)
{
	notif2(m, N_NORMAL, NOTIF_INPUT_SAVE, g->data);
	*g->target.ptr_int = ft_atoi(g->data);
	input_set_focus(d, m, (t_get *)NULL, -1);
}

void			input_valid(t_gen *d, t_mlx *m, t_get *g)
{
	if (g->mode == MODE_STRING_FILE)
		input_valid_string(d, m, g);
	else if (g->mode == MODE_STRING)
		input_valid_string(d, m, g);
	else if (g->mode == MODE_DOUBLE)
		input_valid_double(d, m, g);
	else if (g->mode == MODE_DOUBLE_BUT_INT)
		input_valid_double_but_int(d, m, g);
	else if (g->mode == MODE_INT)
		input_valid_int(d, m, g);
	if (g->send)
		g->send(d, m, g);
	(void)m;
}
