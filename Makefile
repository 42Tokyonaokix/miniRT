# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/02 23:20:38 by kesaitou          #+#    #+#              #
#    Updated: 2026/05/14 17:36:22 by kesaitou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = cc
CFLAGS = -Wall -Werror -Wextra -I $(INCS) -I $(LIBFTDIR)/includes -I $(MLXDIR)

INCS = includes
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a
UNAME_S := $(shell uname)
ifeq ($(UNAME_S),Darwin)
MLXDIR = minilibx
MLX_LIBS = -framework OpenGL -framework AppKit -lm
else
MLXDIR = minilibx-linux
MLX_LIBS = -lXext -lX11 -lm -lz
endif
MLX = $(MLXDIR)/libmlx.a

LDFLAGS = -L $(LIBFTDIR) -L $(MLXDIR)
LDLIBS = -lft -lmlx $(MLX_LIBS)

MAND_SRCS = srcs/main.c \
	srcs/math/color.c \
	srcs/math/color_ops.c \
	srcs/math/quadratic.c \
	srcs/math/rodrigues.c \
	srcs/math/vec3_dot_cross.c \
	srcs/math/vec3_hor_ver.c \
	srcs/math/vec3_ops.c \
	srcs/math/vec3_len.c \
	srcs/intersect/find_closest.c \
	srcs/intersect/ray_sphere.c \
	srcs/intersect/ray_cylinder.c \
	srcs/intersect/ray_cylinder_t.c \
	srcs/intersect/ray_plane.c \
	srcs/render/camera.c \
	srcs/render/shade.c \
	srcs/render/normal.c \
	srcs/parser/parse_plane.c \
	srcs/parser/parse_cylinder.c \
	srcs/parser/parse_light.c \
	srcs/parser/parse_utils.c \
	srcs/parser/parse_scene.c \
	srcs/parser/parse_ambient.c \
	srcs/parser/parse_sphere.c \
	srcs/parser/parse_camera.c \
	srcs/interact/key_bindings.c \
	srcs/interact/intents.c \
	srcs/interact/mouse_bindings.c \
	srcs/interact/hud.c \
	srcs/interact/selection.c \
	srcs/interact/transform_apply.c \
	srcs/mlx/hooks.c \
	srcs/mlx/render_loop.c \
	srcs/mlx/put_pixel.c \
	srcs/mlx/app_init.c \
	srcs/memory/scene_lists.c \
	srcs/memory/app_free.c \
	srcs/memory/scene_free.c \
	srcs/error/exit_error.c

MAND_OBJS = $(MAND_SRCS:.c=.o)

HEADERS = includes/app.h \
          includes/color.h \
          includes/error.h \
          includes/interact.h \
          includes/intersect.h \
          includes/math_utils.h \
          includes/memory.h \
          includes/mlx.h \
          includes/parser.h \
          includes/render.h \
          includes/scene.h \
          includes/vector.h

all: $(NAME)

bonus: all

$(NAME): $(MAND_OBJS) $(LIBFT) $(MLX)
	$(CC) $(MAND_OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(MLX):
	$(MAKE) -C $(MLXDIR)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(MAND_OBJS)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
