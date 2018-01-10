/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:22:09 by anhuang           #+#    #+#             */
/*   Updated: 2018/01/08 14:22:11 by anhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void    ft_clear_img(int *img)
{
  int i;

  i = 0;
  while (i < WIN_WIDTH * WIN_HEIGHT)
     img[i++] = 0;
}

void    ft_trace_line(t_point **tab, int height, int width, t_e *e)
{
  int   x;
  int   y;

  y = 0;
  ft_clear_img(e->img_str);
  while (y < height)
  {
    x = 0;
    while (x < width)
    {
      if (x + 1 < width)
      {
          ft_line(e->img_str, e->color, tab[y][x], tab[y][x + 1]);
      }
      if (y + 1 < height)
      {
          ft_line(e->img_str, e->color, tab[y][x], tab[y + 1][x]);
      }
      x++;
    }
    y++;
  }
  mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}

void    ft_trace(int **old, t_e *e, t_point size)
{
  t_point pt;
  t_point **new;

  // for (int y = 0; y < size.y; ++y)
  // {
      // for (int x = 0; x < size.x; ++x)
      // {
        // printf("%d ", old[y][x]);
//      }
      // printf("\n");
  // }
  if (!(new = (t_point**)malloc(sizeof(t_point*) * size.y)))
    exit(0);
  pt.y = 0;
  while (pt.y < size.y)
  {
    if (!(new[pt.y] = (t_point*)malloc(sizeof(t_point) * size.x)))
      exit(0);
    pt.x = 0;
    while (pt.x < size.x)
    {
      new[pt.y][pt.x].x =  2 * (pt.x - pt.y) * (WIN_WIDTH / (3 * size.x)) + e->offset.x;
      new[pt.y][pt.x].y = (pt.x + pt.y) * (WIN_WIDTH / (3 * size.x)) + e->offset.y;
      new[pt.y][pt.x].y += old[size.y - pt.y - 1][pt.x] * 2;
      ++pt.x;
    }
    ++pt.y;
  }
  // for (int y = 0; y < size.y; ++y)
  // {
    // for (int x = 0; x < size.x; ++x)
    // {
      // printf("(%d, %d) ", new[y][x].x, new[y][x].y);
    // }
    // printf("\n");
  // }
  printf("COULEUR : %d\n", e->color);
  ft_trace_line(new, size.y, size.x, e);
  free(new);
}
