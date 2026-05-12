# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/02 23:20:38 by kesaitou          #+#    #+#              #
#    Updated: 2026/05/13 07:12:01 by natakaha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = cc
CFLAGS = -Wall -Werror -Wextra -I $(INCS)

INCS = includes
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

LDFLAGS = -L $(LIBFTDIR)
LDLIBS = -lft -lm

MAND_SRCS = \
	srcs/main.c \
	srcs/math/vec3_ops.c \
	srcs/math/vec3_dot_cross.c \
	srcs/math/color_ops.c \
	srcs/math/rodrigues.c \
	srcs/intersect/find_closest.c \
	srcs/intersect/ray_sphere.c \
	srcs/intersect/ray_cylinder.c \
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

HEADERS = $(wildcard $(INCS)/*.h)


all : $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(NAME):$(MAND_OBJS) $(LIBFT)
	$(CC) $(MAND_OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

bonus: all

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(MAND_OBJS)
	find srcs -name '*.d' -delete
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME) $(LIBFT)

re: fclean all


.PHONY: all clean fclean re
