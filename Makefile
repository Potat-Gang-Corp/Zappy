##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

all:
	@make zappy_server
	@make zappy_ai
	@make zappy_gui

zappy_server:
	@make -C Server/
	mv Server/zappy_server .

zappy_ai:
	@make -C IA/
	mv Server/zappy_ai .

zappy_gui:
	@make -C Graphic/
	mv Server/zappy_server .

clean:
	@make clean -C Server/
	@make clean -C IA/
	@make clean -C Graphic/

fclean:
	@make fclean -C Server/
	@make fclean -C IA/
	@make fclean -C Graphic/

re: fclean all
