##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## .
##

NAME = wolf3d


SRC = src/wolf3d.c
SRC += src/utils.c
SRC += src/init/create_window.c
SRC += src/init/init_time.c
SRC += src/game/launch_game.c
SRC += src/game/choose_window_mode.c
SRC += src/init/init_game_handler.c
SRC += src/init/free_game.c
SRC += src/free/free_game_handler.c
SRC += src/free/free_screen.c
SRC += src/init/init_game.c
SRC += src/init/init_weapons.c
SRC += src/init/init_player_ennemies.c
SRC += src/map.c
SRC += src/init/init_menu.c
SRC += src/init/init_sound.c
SRC += src/init/init_textures.c
SRC += src/get_controler/get_left_button.c
SRC += src/get_controler/check_button_right.c
SRC += src/get_controler/get_right_button.c
SRC += src/menu/buttons_func.c
SRC += src/menu/display_menu.c
SRC += src/menu/settings_func.c
SRC += src/menu/sound_settings.c
SRC += src/save/handle_save.c
SRC += src/save/load_file.c
SRC += src/save/save_value.c
SRC += src/game/handle_game_event.c
SRC += src/game/ray_casting/cancel_fisheye.c
SRC += src/game/ray_casting/init_ray_casting.c
SRC += src/game/ray_casting/dda_managment.c
SRC += src/game/ray_casting/execute_ray.c
SRC += src/game/ray_casting/wall_text_managment.c
SRC += src/game/ray_casting/draw_wall.c
SRC += src/game/hud/hud.c
SRC += src/game/weapons/launch_shoot.c
SRC += src/game/weapons/weapons.c
SRC += src/game/handle_ent_event.c
SRC += src/game/run_game.c
SRC += src/game/weapons/animate_weapons.c
SRC += src/init/init_ray_buffer.c
SRC += src/game/draw_screen.c
SRC += src/game/draw_sprite/draw_sprite.c
SRC += src/game/weapons/handle_player_shooting.c
SRC += src/game/entities_effects/rotate_entities.c
SRC += src/game/entities_effects/player_interaction.c
SRC += src/game/launch_ray.c
SRC += src/game/weapons/manege_ennemi_touch.c
SRC += src/game/entities_effects/move_ent.c
SRC += src/game/weapons/anim_ent_shoot.c
SRC += src/game/ennemies/move_ennemies.c
SRC += src/game/ray_casting/draw_floor.c
SRC += src/game/draw_lore.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Iinclude -Llib/ -lmy

LDFLAG = -g -lcsfml-graphics \
 		-lcsfml-system -lcsfml-audio \
		-lcsfml-window -lm -lncurses -g \

all: $(NAME)

$(NAME): $(OBJ)
		make -C ./lib/
		gcc -g $(OBJ) $(CFLAGS) -o $(NAME)  $(LDFLAG) -g

clean:
		make clean -C ./lib/
		rm -rf $(OBJ)

fclean: clean
		make fclean -C ./lib/
		rm -rf $(NAME)

re: fclean all

debug: CFLAGS += -g
debug: fclean all
