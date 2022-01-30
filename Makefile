NAME = mycontainer
NAME2 = defaultcontainer
CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98
SRC = main.cpp
HDIR = headers
ODIR = objects
SDIR = sources
INCLUDES = -I../$(HDIR)
BINARIES = $(NAME) $(NAME2)

project: $(BINARIES)
$(NAME): $(ODIR)/main.o
	$(CC) -o $@ $^
$(ODIR)/main.o: $(SDIR)/main.cpp $(HDIR)/*.hpp
	cd $(ODIR) && $(CC) $(INCLUDES) $(CFLAGS) -c ../$< -o main.o

$(NAME2): $(ODIR)/main2.o
	$(CC) -o $@ $^
$(ODIR)/main2.o: $(SDIR)/main.cpp $(HDIR)/*.hpp
	cd $(ODIR) && $(CC) -D STDSTL $(INCLUDES) $(CFLAGS) -c ../$< -o main2.o

.PHONY: clean fclean re
clean:
	rm -f $(ODIR)/*.o
fclean: clean
	rm -f $(BINARIES)
re:
	make fclean
	make project
