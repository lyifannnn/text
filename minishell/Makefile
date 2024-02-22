OBJ=minishell
OBJS+=main.c
OBJS+=terminal.c
OBJS+=command.c
OBJS+=record.c

$(OBJ):$(OBJS)
	gcc $^ -o $@

.PHONY:
clean:
	rm $(OBJ)
install:
	sudo cp $(OBJ) /bin
uninstall:
	sudo rm /bin/$(OBJ)
