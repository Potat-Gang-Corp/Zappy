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
	mv IA/zappy_ai .

zappy_gui:
	@make -C Graphic/
	mv Graphic/zappy_gui .

clean:
	@make clean -C Server/
	@make clean -C IA/
	@make clean -C Graphic/
	rm -rf zappy_server
	rm -rf zappy_ai
	rm -rf zappy_gui

fclean: clean
	@make fclean -C Server/
	@make fclean -C IA/
	@make fclean -C Graphic/

re: fclean all
